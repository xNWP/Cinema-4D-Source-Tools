#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_BLOCKARRAY_H__)
#define C4DMISC_BLOCKARRAY_H__

#include "basearray.h"

/// @file

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

/// Flags for the behaviour of BlockArray when moving objects (only relevant for Insert() and Erase())
enum BLOCKARRAYFLAGS
{
	BLOCKARRAYFLAGS_0										= 0,									///< always use constructor/destructor or move operator, never memcpy, memmove or realloc
	BLOCKARRAYFLAGS_MOVEANDCOPYOBJECTS	= (1 << 0),						///< elements are PODs and can be copied using memcpy and moved using memmove/realloc (for Resize, Insert, Erase, Append etc.)
	BLOCKARRAYFLAGS_NOINSERTERASE				= (1 << 1),						///< do not support Insert() and Erase() (will  make the subscript operator faster)
	BLOCKARRAYFLAGS_GROW_SLOWLY					= (1 << 2)						///< the first block will increase its size gradually (and memory might move) until it reaches 1 << BLOCK_SIZE_EXPONENT)
} ENUM_FLAGS(BLOCKARRAYFLAGS);

static const Int BLOCKARRAY_DEFAULT_SIZE_EXPONENT = 10;

//----------------------------------------------------------------------------------------
///	Block array template.
/// The array consists of multiple blocks containing 2^BLOCK_SIZE_EXPONENT elements. Therefore
/// the memory address of the elements will not change if the array grows and no memory is
/// copied. Nonetheless objects have to be copied/moved when you call Insert() or Erase(),
/// but the amount of memory is limited to the size of a block which makes it much faster
/// than a BaseArray for these purposes.
///
/// @tparam T											Type of the array elements.
/// @tparam BLOCK_SIZE_EXPONENT		Size of an array block: 2^BLOCK_SIZE_EXPONENT.
/// @tparam MEMFLAGS							Use BLOCKARRAYFLAGS_0 unless you know the object can be moved and/or copied.
/// @tparam ALLOCATOR							Class for memory allocation.
///
/// @note Note that the array element class has special requirements regarding @link movecopy copy and move constructors @endlink.
//----------------------------------------------------------------------------------------
template<typename T, Int BLOCK_SIZE_EXPONENT = BLOCKARRAY_DEFAULT_SIZE_EXPONENT, BLOCKARRAYFLAGS MEMFLAGS = BLOCKARRAYFLAGS_0, typename ALLOCATOR = DefaultAllocator> class BlockArray : protected ALLOCATOR
{
	MAXON_DISALLOW_COPY_AND_ASSIGN(BlockArray);

	struct ForwardAllocator;
	typedef BaseArray<T, (Int) MEMFLAGS & (Int) BLOCKARRAYFLAGS_GROW_SLOWLY ? BASEARRAY_DEFAULT_CHUNK_SIZE : (Int)1 << BLOCK_SIZE_EXPONENT, (BASEARRAYFLAGS) ((Int) MEMFLAGS & ~(Int) BLOCKARRAYFLAGS_NOINSERTERASE), ForwardAllocator> Block;

public:
	static const Int BLOCK_SIZE = (Int) 1 << BLOCK_SIZE_EXPONENT;
	typedef T ValueType;
	typedef ALLOCATOR AllocatorType;

	template <Bool CONSTITERATOR> class IteratorTemplate;
	typedef IteratorTemplate<false> Iterator;
	typedef IteratorTemplate<true> ConstIterator;

	BlockArray() : _blocks(ForwardAllocator(this)), _usedBlockCnt(InvalidArrayIndex), _submittedElementCnt(InvalidArrayIndex), _isContinuous(Int(true)), _reserved(0)
	{
		static_assert(SIZEOF(BlockArray) == 8 * SIZEOF(UInt), "Check BlockArray memory layout");
	}

	/// this constructor has to be used if an array should use a custom allocator with member variables
	explicit BlockArray(const ALLOCATOR& a) : ALLOCATOR(a), _blocks(ForwardAllocator(this)), _usedBlockCnt(InvalidArrayIndex), _submittedElementCnt(InvalidArrayIndex), _isContinuous(Int(true)), _reserved(0)
	{
	}

	~BlockArray()
	{
	}

	/// move constructor
	BlockArray(BlockArray&& src) : ALLOCATOR(std::move(src)), _blocks(std::move(src._blocks)), _usedBlockCnt(src._usedBlockCnt), _submittedElementCnt(src._submittedElementCnt), _isContinuous(src._isContinuous), _reserved(0)
	{
		src._usedBlockCnt = 0;
		src._submittedElementCnt = 0;
		src._isContinuous = Int(false);
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(BlockArray)

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (calls destructors and frees memory)
	//----------------------------------------------------------------------------------------
	void  Reset()
	{
		_blocks.Reset();
	}

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (calls destructors and frees memory), but doesn't free the memory
	/// of the array which contains the blocks. The memory used by the blocks themselves
	/// is freed nevertheless.
	//----------------------------------------------------------------------------------------
	void  Flush()
	{
		_blocks.Flush();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of array elements.
	/// @return												Number of array elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		Int blockCnt = _blocks.GetCount();
		Int cnt				= 0;

		if (blockCnt > 0)
		{
			Int i = 0;

			if (MEMFLAGS == BLOCKARRAYFLAGS_NOINSERTERASE || _isContinuous)
			{
				i = blockCnt - 1;
				cnt	 = i << BLOCK_SIZE_EXPONENT;
			}

			for (; i < blockCnt; i++)
				cnt += _blocks[i].GetCount();
		}

		return cnt;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of elements for which memory has been allocated (for a BlockArray this is equal to GetCount() plus the number of free elements in the last block)
	/// @return												Number of array elements for which memory has been allocated.
	//----------------------------------------------------------------------------------------
	Int GetCapacityCount() const
	{
		Int	capacity = GetCount();

		if (capacity > 0)
		{
			const Block& last = _blocks[_blocks.GetCount() - 1];
			capacity += last.GetCapacityCount() - last.GetCount();
		}

		return capacity;
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	const T& operator [](Int idx) const
	{
		const Block* block = GetBlockAndIndex(idx);
		return (*block)[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for non-const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	// this is duplicate code but casting constness away for this case is plain ugly
	T& operator [](Int idx)
	{
		Block* block = GetBlockAndIndex(idx);
		return (*block)[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append()
	{
		Int	 blockIdx = _blocks.GetCount() - 1;
		Block* block = _blocks.Begin().GetPtr() + blockIdx;			// this is equivalent to &_blocks[blockIdx] but it won't cause a debug break when blockIdx == -1

		if ((blockIdx < 0) || (block->GetCount() == GetBlockSize()))	// no block or current block full?
		{
			block = _blocks.Append();
			if (block == nullptr)
				return nullptr;
		}

		return block->Append();
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and initializes it with a copy of x.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(const T& x)
	{
		Int	 blockIdx = _blocks.GetCount() - 1;
		Block* block = _blocks.Begin().GetPtr() + blockIdx;			// this is equivalent to &_blocks[blockIdx] but it won't cause a debug break when blockIdx == -1

		if ((blockIdx < 0) || (block->GetCount() == GetBlockSize()))	// no block or current block full?
		{
			block = _blocks.Append();
			if (block == nullptr)
				return nullptr;
		}

		return block->Append(x);
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and moves the content of x to it.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(T&& x)
	{
		Int	 blockIdx = _blocks.GetCount() - 1;
		Block* block = _blocks.Begin().GetPtr() + blockIdx;			// this is equivalent to &_blocks[blockIdx] but it won't cause a debug break when blockIdx == -1

		if ((blockIdx < 0) || (block->GetCount() == GetBlockSize()))	// no block or current block full?
		{
			block = _blocks.Append();
			if (block == nullptr)
				return nullptr;
		}

		return block->Append(std::move(x));
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new default element at index position.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position)
	{
		return MAXON_SAFE_PLACEMENT_NEW(Insert(position, nullptr, 1)) T();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at iterator position.
	/// @param[in] position						Insert position.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position)
	{
		Int	idx = position - Begin();
		T* element = Insert(idx);
		return element ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and initializes it with a copy of x.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T& x)
	{
		return Insert(position, &x, 1);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and initializes it with a copy of x.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be copied.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T& x)
	{
		return Insert(position, &x, 1);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and moves the content of x to it.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, T&& x)
	{
		return MAXON_SAFE_PLACEMENT_NEW(Insert(position, nullptr, 1)) T(std::move(x));
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and moves the content of x to it.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be moved.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, T&& x)
	{
		Int	idx = position - Begin();
		T*	element = Insert(idx, std::move(x));
		return element ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at index position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Element pointer or nullptr (allocation failed) <B> You MUST use the Iterator if you want to access the elements after this! </B>
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T* x, Int insertCnt)
	{
		T*	first = nullptr;
		Int	saveCnt = insertCnt;

		if (_isContinuous && (position != GetCount()))
		{
			if (MEMFLAGS == BLOCKARRAYFLAGS_NOINSERTERASE)
			{
				DebugStop();																				// Insert() within the array is not supported with these flags
				return nullptr;
			}
			_isContinuous = Int(false);
		}

		while (insertCnt > 0)
		{
			Int	blockIdx	= 0;
			Int	localIdx = position;
			Block*	block = GetInsertBlockAndIndex(position, blockIdx, localIdx);

			if (block == nullptr)
			{
				DebugStop();																				// check for invalid position
				return nullptr;
			}

			Int	currentCnt = block->GetCount();

			if (currentCnt >= GetBlockSize())											// we have to insert a new block
			{
				Block*	splittableBlock;

				if (localIdx < GetBlockSize() / 2)									// insert before current block
				{
					block = _blocks.Insert(blockIdx);
					if (block == nullptr)
						goto handle_error;															// clean up, erase already inserted elements

					splittableBlock = &_blocks[blockIdx + 1];					// Insert() has moved or reallocated memory, therefore the full block has a different address than before
					if (splittableBlock->MoveAndShrink(*block, 0, localIdx) == false)	// move localIdx elements to the new block
						DebugStop();
				}
				else																								// insert behind current block
				{
					block = _blocks.Insert(blockIdx + 1);
					if (block == nullptr)
						goto handle_error;															// clean up, erase already inserted elements

					if (localIdx < currentCnt)												// insert position is not at the end of the current block?
					{
						splittableBlock = &_blocks[blockIdx];						// Insert() has moved or reallocated memory, therefore the full block has a different address than before
						if (splittableBlock->MoveAndShrink(*block, localIdx, currentCnt - localIdx) == false)	// move all elements between localIdx and currentCnt to the inserted block
							DebugStop();

						block = splittableBlock;												// insert at the end of the "old" block
					}
					else																							// insert at the start of the new block
						localIdx = 0;
				}
			}

			Int	cnt = insertCnt;
			if (localIdx + insertCnt > GetBlockSize())
			{
				cnt = GetBlockSize() - localIdx;
				DebugAssert(cnt != 0);															// if cnt was 0 someone had broken the array code
			}

			T*	element = block->Insert(localIdx, x, cnt);
			if (element == nullptr)																// insertion failed?
			{
				DebugStop();
				first = nullptr;
				break;
			}

			if (block->GetCount() > GetBlockSize())
				DebugStop();

			if (first == nullptr)
				first = element;

			position += cnt;
			if (x)
				x += cnt;
			insertCnt -= cnt;
		}

		if (first == nullptr)
		{
			// this is only an error if there were elements to be inserted
			if (insertCnt > 0)
			{
			handle_error:
				DebugStop();
				insertCnt = saveCnt - insertCnt;										// this is the number of elements that have already been inserted before failure
				Erase(position - insertCnt, insertCnt);							// remove these
				first =  nullptr;
			}
		}

		return first;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at iterator position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert position.
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T* x, Int insertCnt)
	{
		Int	idx = position - Begin();
		T* element = Insert(idx, x, insertCnt);
		return element ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements.
	/// @param[in] position						Erase index (Erase() will fail if out of bounds and return nullptr)
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Pointer to the element that is now at position or nullptr (no more element at position, either because position is out of bounds or the last element was erased)
	//----------------------------------------------------------------------------------------
	T* Erase(Int position, Int eraseCnt = 1)
	{
		T*	element = nullptr;
		Int	cnt = GetCount();

		if (UInt(position) >= UInt(cnt))
		{
			DebugAssert(eraseCnt == 0, "The position is invalid.");
			return nullptr;
		}

		if (UInt(position + eraseCnt) > UInt(cnt))
		{
			DebugStop("You are trying to erase more elements than available.");
			eraseCnt = cnt - position;
		}

		Int idx = position;
		Block* block = GetBlockAndIndex(idx);

		if (position + eraseCnt != cnt)
		{
			// Return a pointer unless it would point behind the last element.
			element = &(*block)[idx];

			if (MEMFLAGS == BLOCKARRAYFLAGS_NOINSERTERASE)
			{
				DebugStop("Erase within the array is not supported with these flags.");
				return nullptr;
			}

			// Erase within the array will make it non-continuous.
			_isContinuous = Int(false);
		}

		while (eraseCnt > 0)
		{
			Int blkCnt = block->GetCount() - idx;

			if (blkCnt > eraseCnt)
				blkCnt = eraseCnt;

			block->Erase(idx, blkCnt);

			// Update the number of elements still to erase.
			eraseCnt -= blkCnt;
			cnt -= blkCnt;

			// Remove block if it is empty and get pointer to the next block.
			blkCnt = block->GetCount();
			if (blkCnt == 0)
			{
				Int	blockIdx = _blocks.GetIndex(*block);
				block = _blocks.Erase(blockIdx);
				idx = 0;
			}
			else if (blkCnt == idx)
			{
				// Advance a block if everything from idx on was erased.
				block += 1;
				idx = 0;
			}
		}

		// Return a pointer unless it would point behind the last element.
		if (cnt != position)
			element = &(*block)[idx];

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements.
	/// @param[in] position						Erase position.
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Iterator for the element that is now at position (IsValid() == false if something failed)
	//----------------------------------------------------------------------------------------
	Iterator Erase(Iterator position, Int eraseCnt = 1)
	{
		Int	idx = position - Begin();
		T* element = Erase(idx, eraseCnt);
		return element ? Iterator(*this, idx) : idx == GetCount() ? End() : Iterator(nullptr);
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetFirst() const
	{
		return (_blocks.GetCount() > 0) ? &_blocks[0][0] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetFirst()
	{
		return (_blocks.GetCount() > 0) ? &_blocks[0][0] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetLast() const
	{
		Int	blockCnt = _blocks.GetCount();
		T*	last = nullptr;

		if (blockCnt > 0)
		{
			const Block& lastBlock = _blocks[blockCnt - 1];
			last = &lastBlock[lastBlock.GetCount() - 1];
		}
		return last;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetLast()
	{
		Int	blockCnt = _blocks.GetCount();
		T*	last = nullptr;

		if (blockCnt > 0)
		{
			Block& lastBlock = _blocks[blockCnt - 1];
			last = &lastBlock[lastBlock.GetCount() - 1];
		}
		return last;
	}

	//----------------------------------------------------------------------------------------
	/// Resizes the array to contain newCnt elements
	/// If newCnt is smaller than GetCount() all extra elements are being deleted. If it is
	/// greater the array is expanded and the default constructor is called for new elements.
	/// @param[in] newCnt							New array size.
	/// @return												False if allocation failed.
	//----------------------------------------------------------------------------------------
	Bool Resize(Int newCnt)
	{
		Int oldCnt = GetCount();

		if (newCnt > oldCnt)																		// increase array size?
		{
			Block* block	= nullptr;
			Int	 blockCnt	= _blocks.GetCount();
			Int	 addCnt	= newCnt - oldCnt;												// number of elements to be added

			if (blockCnt > 0)
			{
				block = &_blocks[blockCnt - 1];
				goto add_elements;
			}

			while (addCnt > 0)
			{
				block = _blocks.Append();
				if (block == nullptr)
					return false;

			add_elements:
				Int currentCnt = block->GetCount();
				Int increment = GetBlockSize() - currentCnt;
				if (increment > 0)																	// still room available?
				{
					if (increment > addCnt)
						increment = addCnt;

					if (block->Resize(currentCnt + increment) == false)	// no fitToSize because the block has the right size (GetBlockSize())
						break;

					addCnt -= increment;
				}
			}
			return addCnt == 0;
		}
		else if (newCnt == oldCnt)
		{
			return true;
		}
		else
		{
			// decrease array size
			if (newCnt >= 0)
			{
				Erase(newCnt, oldCnt - newCnt);
				return true;
			}
			else
				DebugStop();
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Deletes the last element.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool  Pop(T* dst = nullptr)
	{
		Int blockCnt = _blocks.GetCount();
		Bool	success = false;

		if (blockCnt > 0)
		{
			Block& block = _blocks[blockCnt - 1];

			if (block.Pop(dst))
			{
				if (block.GetCount() == 0)													// block is empty?
					_blocks.Pop();

				success = true;
			}
		}
		return success;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the index of an element. The element must be part of the array, otherwise (e.g. if x is
	/// a copy of an array element) InvalidArrayIndex will be returned.
	/// This is slower than for a BaseArray because it has to iterate over the block.
	/// @return												Index of element or InvalidIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T& x) const
	{
		Int	idx = 0;

		for (Int i = 0; i < _blocks.GetCount(); i++)
		{
			const Block& block = _blocks[i];
			const T* first = &block[0];														// first data element of this block
			Int	cnt = block.GetCount();

			if ((&x >= first) && (&x < first + cnt))
				return idx + &x - first;

			idx += cnt;
		}

		DebugStop();
		return InvalidArrayIndex;
	}

	//----------------------------------------------------------------------------------------
	/// Copies an array.
	/// @param[in] src								Source array.
	/// @param[in] fitToSize					Is ignored.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	template <typename SourceArray> Bool CopyFrom(const SourceArray& src, Bool fitToSize = false)
	{
		Int	cnt = src.GetCount();

		Reset();

		while (cnt > 0)
		{
			Int	insertCnt = cnt > GetBlockSize() ? GetBlockSize() : cnt;
			typename SourceArray::ConstIterator it(src);
			Block* block = _blocks.Append();

			if (block == nullptr)
				break;

			for (cnt -= insertCnt; insertCnt > 0; insertCnt--, it++)
			{
				if (block->Append(*it) == nullptr)
					break;
			}

			cnt += insertCnt;
			if (insertCnt > 0)
				break;
		}

		if (cnt == 0)																						// array copy successful?
			return true;

		Reset();
		return false;
	}

	// specialization for BaseArray
	template <typename X> Bool CopyFrom(const BaseArray<X>& src, Bool fitToSize = false)
	{
		Int	cnt = src.GetCount();
		Int	i = 0;

		Reset();

		while (cnt > 0)
		{
			Block* block = _blocks.Append();
			Int	insertCnt = cnt > GetBlockSize() ? GetBlockSize() : cnt;

			if (block == nullptr)
				break;

			if (block->Insert(0, &src[i], insertCnt) == nullptr)
				break;

			i += insertCnt;
			cnt -= insertCnt;
		}

		if (cnt == 0)																						// array copy successful?
			return true;

		Reset();
		return false;
	}

	Bool CopyFrom(const BlockArray& src)
	{
		return CopyFrom(src, false);
	}

	//----------------------------------------------------------------------------------------
	/// Swaps elements a and b (equivalent to global Swap(array[a], array[b])
	/// @param[in] a									Position of element to be swapped.
	/// @param[in] b									Position of element to be swapped.
	//----------------------------------------------------------------------------------------
	void Swap(Iterator a, Iterator b)
	{
		maxon::Swap(*a, *b);
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	ConstIterator Begin() const
	{
		return ConstIterator(*this, 0);
	}

	ConstIterator begin() const
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	Iterator Begin()
	{
		return Iterator(*this, 0);
	}

	Iterator begin()
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	ConstIterator End() const
	{
		Int	 blockIdx = _blocks.GetCount() - 1;
		const Block* block = _blocks.Begin().GetPtr() + blockIdx;			// this is equivalent to &_blocks[blockIdx] but it won't cause a debug break when blockIdx == -1

		return blockIdx >= 0 ? ConstIterator(this, block, block->End(), block->End()) : ConstIterator(this);
	}

	ConstIterator end() const
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	Iterator End()
	{
		Int	 blockIdx = _blocks.GetCount() - 1;
		Block* block = _blocks.Begin().GetPtr() + blockIdx;			// this is equivalent to &_blocks[blockIdx] but it won't cause a debug break when blockIdx == -1

		return blockIdx >= 0 ? Iterator(this, block, block->End(), block->End()) : Iterator(this);
	}

	Iterator end()
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	///	The BlockArray iterator uses several tricks to make iteration faster than using a
	/// for loop with operator []. Therefore you should use it (or AutoIterator) to iterate
	/// over the array or parts of it.
	///
	/// You can use an iterator almost like a pointer, e.g.
	/// @code
	/// it++;								// go to the next element
	/// it--;								// go to the previous element
	/// it += 5;						// advance by 5 elements
	/// it -= 3;						// go back 3 elements
	/// cnt = itB - itA;		// number of elements from itA to itB
	/// it = array.Begin();	// iterator to the first element of the array
	/// *it = value;				// assign value to the elements referenced by the iterator
	/// value = *value;			// get value of the element referenced by the iterator
	/// @endcode
	//----------------------------------------------------------------------------------------
	template <Bool CONSTITERATOR> class IteratorTemplate
	{
		// For a const iterator, the BlockArray, its values, the blocks and their iterators have to be const within the iterator, otherwise they are non-const.
		// These typedefs have to be used throughout the iterator code instead of just BlockArray, T, etc.
		typedef typename Select<CONSTITERATOR, typename Block::ConstIterator, typename Block::Iterator>::Type BlockIterator;
		typedef typename ConstIf<CONSTITERATOR, Block>::Type BlockType;

	public:
		typedef typename ConstIf<CONSTITERATOR, BlockArray>::Type CollectionType;
		typedef typename ConstIf<CONSTITERATOR, T>::Type ValueType;
		static const Bool isLinearIterator = false;

		explicit IteratorTemplate(CollectionType& a, Int start = 0) : _array(&a), _block(nullptr)
		{
			if (a._blocks.GetCount() > 0)
			{
				_block = a.GetBlockAndIndex(start);
				_iterator = _block->Begin() + start;
				_end = _block->End();

			}
		}
		explicit IteratorTemplate(CollectionType* a = nullptr, BlockType *block = nullptr, BlockIterator it = BlockIterator(), BlockIterator end = BlockIterator()) : _array(a), _block(block), _iterator(it), _end(end)
		{
		}

		IteratorTemplate(const IteratorTemplate& src) : _array(src._array), _block(src._block), _iterator(src._iterator), _end(src._end)
		{
		}

		IteratorTemplate& operator =(const IteratorTemplate& src)
		{
			_array = src._array;																	// self assignment is no problem here, therefore no check if (this != &src)
			_block = src._block;
			_iterator = src._iterator;
			_end = src._end;

			return *this;
		}

#ifdef __INTEL_COMPILER
	#pragma warning disable 597
#endif
		operator ConstIterator&()
		{
			return *(ConstIterator*) this;
		}
#ifdef __INTEL_COMPILER
	#pragma warning enable 597
#endif

		//----------------------------------------------------------------------------------------
		/// @return												true if the iterator points to an element (Iterator().IsValid() will return false)
		//----------------------------------------------------------------------------------------
		Bool IsValid() const
		{
			return _array != nullptr;
		}

		ValueType* GetPtr() const
		{
			return _iterator.GetPtr();
		}
		ValueType& operator *() const
		{
			return *_iterator;
		}
		ValueType* operator ->() const
		{
			return &(*_iterator);
		}

		Bool operator ==(const IteratorTemplate& b) const
		{
			return _iterator == b._iterator;
		}
		Bool operator !=(const IteratorTemplate& b) const
		{
			return _iterator != b._iterator;
		}
		Bool operator >=(const IteratorTemplate& b) const
		{
			if ((_block > b._block) || ((_block == b._block) && (_iterator >= b._iterator)))
				return true;

			return false;
		}
		Bool operator <=(const IteratorTemplate& b) const
		{
			if ((_block < b._block) || ((_block == b._block) && (_iterator <= b._iterator)))
				return true;

			return false;
		}
		Bool operator <(const IteratorTemplate& b) const
		{
			if ((_block < b._block) || ((_block == b._block) && (_iterator < b._iterator)))
				return true;

			return false;
		}
		Bool operator >(const IteratorTemplate& b) const
		{
			if ((_block > b._block) || ((_block == b._block) && (_iterator > b._iterator)))
				return true;

			return false;
		}

		IteratorTemplate& operator ++()																	// prefix operator ++ (increment and fetch)
		{
			++_iterator;
			if (_iterator == _end)																// at the end of the current block?
			{
				if (_block != &_array->_blocks[_array->_blocks.GetCount() - 1])	// not the last block?
				{
					_block++;																					// go to next block
					_iterator = _block->Begin();
					_end = _block->End();
				}
			}
			return *this;
		}
		const IteratorTemplate operator ++(int)													// postfix operator ++ (fetch and increment)
		{
			BlockType*	tmpBlock = _block;
			BlockIterator	tmpIterator = _iterator;
			BlockIterator	tmpEnd = _end;

			++(*this);

			return IteratorTemplate(_array, tmpBlock, tmpIterator, tmpEnd);	// use RVO
		}
		IteratorTemplate& operator +=(Int i)														// operator +=
		{
			if (i > 0)
			{
				BlockType* lastBlock = _array->_blocks.GetLast();
				Int	maxDiff = _end - _iterator;

				// check against lastBlock because i might equal GetCount() and in this case the iterator has to point behind the last element
				while (_block != lastBlock && i >= maxDiff)					// element not in current block?
				{
					i -= maxDiff;
					_block++;																					// go to next block
					_iterator = _block->Begin();
					_end = _block->End();
					maxDiff = _end - _iterator;
				}
				_iterator += i;
			}
			else if (i < 0)
				*this -= -i;

			return *this;
		}
		IteratorTemplate operator +(Int i) const												// operator +
		{
			IteratorTemplate tmp = *this;
			tmp += i;
			return tmp;
		}
		IteratorTemplate& operator --()																	// prefix operator -- (decrement and fetch)
		{
			if (_iterator == _block->Begin())											// at the start of the current block?
			{
				_block--;																						// goto previous block
				_iterator = _end = _block->End();
			}
			--_iterator;
			return *this;
		}
		const IteratorTemplate operator --(int)													// postfix operator -- (fetch and decrement)
		{
			BlockType*	tmpBlock = _block;
			BlockIterator	tmpIterator = _iterator;
			BlockIterator	tmpEnd = _end;

			--(*this);

			return IteratorTemplate(_array, tmpBlock, tmpIterator, tmpEnd);	// use RVO
		}
		IteratorTemplate& operator -=(Int i)														// operator -=
		{
			if (i > 0)
			{
				Int	maxDiff = _iterator - _block->Begin();

				while (i > maxDiff)																	// element not in current block?
				{
					i -= maxDiff;
					_block--;
					_iterator = _end = _block->End();
					maxDiff = _end - _block->Begin();
				}
				_iterator -= i;
			}
			else if (i < 0)
				*this += -i;

			return *this;
		}
		IteratorTemplate operator -(Int i) const												// operator -
		{
			IteratorTemplate	tmp = *this;
			tmp -= i;
			return tmp;
		}
		Int operator -(const IteratorTemplate& b) const
		{
			BlockType* block = _block;
			Int	cnt = _iterator - b._iterator;

			if (block > b._block)																	// b has a smaller index (result must be positive)?
			{
				cnt = _iterator - block->Begin();

				for (block--; block > b._block; block--)
					cnt += block->GetCount();

				cnt += block->End() - b._iterator;
			}
			else if (block < b._block)														// b has a bigger index (result must be negative)?
			{
				cnt = _iterator - _end;

				for (block++; block < b._block; block++)
					cnt -= block->GetCount();

				cnt -= b._iterator - block->Begin();
			}
			return cnt;
		}

	private:
		CollectionType*								_array;
		BlockType*										_block;
		BlockIterator							_iterator;
		BlockIterator							_end;
	};

	//----------------------------------------------------------------------------------------
	/// Returns the allocator as reference. Typically this is used by the arrays and other
	/// base classes when multiple of them are "stiched" together as one big object all
	/// shall use one main allocator.
	/// @return												Allocator reference.
	//----------------------------------------------------------------------------------------
	ALLOCATOR& GetAllocator()
	{
		return *this;
	}

private:

	//----------------------------------------------------------------------------------------
	/// Returns the block and local index within that block for a global array index.
	/// @param[in,out] idx						On input the global index, on return the local index within the block (must be < GetCount())
	/// @return												Block pointer.
	//----------------------------------------------------------------------------------------
	inline Block*	GetBlockAndIndex(Int &idx)
	{
		Int blockIdx = idx >> BLOCK_SIZE_EXPONENT;

		if (MEMFLAGS != BLOCKARRAYFLAGS_NOINSERTERASE && !_isContinuous)
		{
			Int blockCnt = _blocks.GetCount();

			for (blockIdx = 0; blockIdx < blockCnt; blockIdx++)
			{
				Int	cnt = _blocks[blockIdx].GetCount();
				if (idx < cnt)
					break;
				idx -= cnt;
			}
		}

		idx &= GetBlockSize() - 1;
		return &_blocks[blockIdx];															// this will cause a debug break if blockIdx is invalid
	}

	inline const Block* GetBlockAndIndex(Int &idx) const
	{
		return const_cast<BlockArray*>(this)->GetBlockAndIndex(idx);
	}

	//----------------------------------------------------------------------------------------
	/// For the Insert operation get the block and local index within that block for a global array index.
	/// @param[in] idx								Global index.
	/// @param[out] blockIdx					Returns index of the block.
	/// @param[out] localIdx					Returns index within the block.
	/// @return												Block pointer or null if idx was invalid (block can be empty if idx equaled the number of elements)
	//----------------------------------------------------------------------------------------
	inline Block*	GetInsertBlockAndIndex(Int idx, Int& blockIdx, Int& localIdx)
	{
		Int blockCnt = _blocks.GetCount();
		blockIdx = idx >> BLOCK_SIZE_EXPONENT;

		if (MEMFLAGS != BLOCKARRAYFLAGS_NOINSERTERASE && !_isContinuous)
		{
			for (blockIdx = 0; blockIdx < blockCnt; blockIdx++)
			{
				Int	cnt = _blocks[blockIdx].GetCount();
				if ((idx <= cnt) && (idx < GetBlockSize()))					// if idx == cnt make sure that the block is not full
					break;
				idx -= cnt;
			}
		}

		localIdx = idx & (GetBlockSize() - 1);
		if (blockIdx >= blockCnt)																// append a new block?
		{
			if ((localIdx != 0) || (blockIdx != blockCnt))				// invalid index?
				return nullptr;

			if (_blocks.Append() == nullptr)
				return nullptr;
		}
		return &_blocks[blockIdx];															// this will cause a debug break if blockIdx is invalid
	}

	inline Int  GetBlockSize() const
	{
		return BLOCK_SIZE;
	}

	struct ForwardAllocator
	{
		explicit ForwardAllocator(ALLOCATOR* a) : _a(*a)
		{
		}
		ForwardAllocator(const ForwardAllocator& src) : _a(src._a)
		{
		}
		void operator =(const ForwardAllocator&)
		{
		}

		Int ComputeArraySize(Int current_size, Int increment, Int min_chunk_size)
		{
			return _a.ComputeArraySize(current_size, increment, min_chunk_size);
		}
		void* Alloc(Int s, MAXON_SOURCE_LOCATION_DECLARATION)
		{
			return _a.Alloc(s, MAXON_SOURCE_LOCATION_FORWARD);
		}
		void* Realloc(void* p, Int n, MAXON_SOURCE_LOCATION_DECLARATION)
		{
			return _a.Realloc(p, n, MAXON_SOURCE_LOCATION_FORWARD);
		}
		template<typename X> void  Free(X*& p)
		{
			_a.Free(p);
		}

	private:
		ALLOCATOR& _a;
	};

	class ArrayOfBlocks : public BaseArray<Block, BASEARRAY_DEFAULT_CHUNK_SIZE, BASEARRAYFLAGS_0, ForwardAllocator>
	{
	public:
		ArrayOfBlocks()
		{
		}
		ArrayOfBlocks(const ForwardAllocator& a) : BaseArray<Block, BASEARRAY_DEFAULT_CHUNK_SIZE, BASEARRAYFLAGS_0, ForwardAllocator>(a)
		{
		}
		ArrayOfBlocks(ArrayOfBlocks&& src) : BaseArray<Block, BASEARRAY_DEFAULT_CHUNK_SIZE, BASEARRAYFLAGS_0, ForwardAllocator>(std::move(src))
		{
		}

		// this overides the method from BaseArray and makes sure that the new Block uses our allocator (that forwards calls to the BlockArray)
		Block* Append()
		{
			Block* block = MAXON_SAFE_PLACEMENT_NEW(this->AppendWithoutConstructor()) Block(*this);

			if (block && (!(MEMFLAGS & BLOCKARRAYFLAGS_GROW_SLOWLY) || this->GetCount() > 1))
				block->EnsureCapacity(BLOCK_SIZE);

			return block;
		}
		// this overides the method from BaseArray and makes sure that the new Block uses our allocator (that forwards calls to the BlockArray)
		Block* Insert(Int position)
		{
			Block* block = MAXON_SAFE_PLACEMENT_NEW(this->InsertWithoutConstructor(position)) Block(*this);

			if (block && (!(MEMFLAGS & BLOCKARRAYFLAGS_GROW_SLOWLY) || this->GetCount() > 1))
				block->EnsureCapacity(BLOCK_SIZE);

			return block;
		}
	};

private:
	ArrayOfBlocks _blocks;
	Int _usedBlockCnt;					// Number of used blocks.
	Int _submittedElementCnt;		// Number of elements excluding the last (not yet submitted) block.
	Int	_isContinuous;					// _isContinuous is currently being used as a flag. In the future it might be used to the store the last index until which the blocks are continuous (without gaps from Insert/Erase).
	Int _reserved;
};

/// @}

} // namespace maxon

#endif	// BLOCKARRAY_H__
