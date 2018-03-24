#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_POINTERARRAY_H__)
#define C4DMISC_POINTERARRAY_H__

#include "basearray.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

//----------------------------------------------------------------------------------------
///	Array of pointers to objects.
/// The array consists of pointers to objects of type T (instead of storing the objects directly
/// like a BaseArray does). Internally each time you append or insert an element a new object
/// of type T is allocated, constructed and the corresponding index of the array will point to
/// it. Nonetheless this array has the same interface as a BaseArray except for AppendPtr(),
/// InsertPtr() and PopPtr() which allow you to directly add or remove already existing objects.
/// Like with all other arrays the destructor of the PointerArray will release memory for all
/// objects that are still part of the array. If you want to use the objects yourself after
/// they have been created by the PointerArray you have to take ownership of them by
/// calling PopPtr() or use a BaseArray<T*> instead of a PointerArray<T>.
///
/// @note Note that the array element class has special requirements regarding @link movecopy copy and move constructors @endlink.
//----------------------------------------------------------------------------------------
template<typename T, Int MINCHUNKSIZE = BASEARRAY_DEFAULT_CHUNK_SIZE, typename ALLOCATOR = DefaultAllocator> class PointerArray
{
	MAXON_DISALLOW_COPY_AND_ASSIGN(PointerArray);

	BaseArray<T*, MINCHUNKSIZE, BASEARRAYFLAGS_MOVEANDCOPYOBJECTS, ALLOCATOR> _ptr;

public:
	typedef T ValueType;
	typedef ALLOCATOR AllocatorType;

	template <Bool CONSTITERATOR> class IteratorTemplate;
	typedef IteratorTemplate<false> Iterator;
	typedef IteratorTemplate<true> ConstIterator;

	PointerArray()
	{
	}

	/// this constructor has to be used if an array should use a custom allocator with member variables
	explicit PointerArray(const ALLOCATOR& a) : _ptr(a)
	{
	}

	~PointerArray()
	{
		Reset();
	}

	/// move constructor
	PointerArray(PointerArray&& src) : _ptr(std::move(src._ptr))
	{
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(PointerArray)

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (calls destructors and frees memory)
	//----------------------------------------------------------------------------------------
	void  Reset()
	{
		for (Int i = GetCount() - 1; i >= 0; i--)
		{
			T*& element = _ptr[i];
			element->~T();
			Free(element);
		}

		_ptr.Reset();
	}

	//----------------------------------------------------------------------------------------
	/// Deletes all elements, but doesn't free memory (calls destructors though).
	//----------------------------------------------------------------------------------------
	void Flush()
	{
		for (Int i = GetCount() - 1; i >= 0; i--)
		{
			T*& element = _ptr[i];
			element->~T();
			Free(element);
		}

		_ptr.Flush();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of array elements.
	/// @return												Number of array elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		return _ptr.GetCount();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of elements for which memory has been allocated (for a PointerArray this is equal to GetCount())
	/// @return												Number of array elements for which memory has been allocated.
	//----------------------------------------------------------------------------------------
	Int GetCapacityCount() const
	{
		return GetCount();
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	const T& operator [](Int idx) const
	{
		return *_ptr[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for non-const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	// this is duplicate code but casting constness away for this case is plain ugly
	T& operator [](Int idx)
	{
		return *_ptr[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append()
	{
		T* element = MAXON_SAFE_PLACEMENT_NEW(Alloc(SIZEOF(T))) T();
		if (element)
		{
			if (_ptr.Append(element) == nullptr)									// appending the pointer failed?
			{
				element->~T();
				Free(element);
			}
		}

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and initializes it with a copy of x.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(const T& x)
	{
		T* buf = (T*) Alloc(SIZEOF(T));
		if (buf == nullptr)
			return nullptr;

		T* element = ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::Copy(*buf, x);
		if (element == nullptr || _ptr.Append(element) == nullptr)	// allocation, copy or append failed?
		{
			if (element)																					// appending the pointer failed?
				element->~T();
			Free(buf);																						// if the copy failed buf holds the pointer to the allocated memory
		}

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and moves the content of x to it.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(T&& x)
	{
		T* element = MAXON_SAFE_PLACEMENT_NEW(Alloc(SIZEOF(T))) T(std::move(x));
		if (element)
		{
			if (_ptr.Append(element) == nullptr)									// appending the pointer failed?
			{
				x = std::move(*element);														// move back
				element->~T();
				Free(element);
			}
		}

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// PointerArray specific: Adds a pointer to the new element at the end of the array.
	/// @param[in] x									Pointer to new element (PointerArray will take ownership of it)
	/// @return												Element pointer or nullptr (in this case x is still valid)
	//----------------------------------------------------------------------------------------
	T* AppendPtr(T* x)
	{
		return _ptr.Append(x) ? x : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position)
	{
		T*	element = MAXON_SAFE_PLACEMENT_NEW (Alloc(SIZEOF(T))) T();
		if (element)
		{
			if (_ptr.Insert(position, element) == nullptr)				// inserting the pointer failed?
			{
				element->~T();
				Free(element);
			}
		}

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at iterator position.
	/// @param[in] position						Insert position.
	/// @return												Iterator for the new element (IsInvalid() if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position)
	{
		Int	idx = position - Begin();
		T*	element = Insert(idx);
		return element ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and initializes it with a copy of x.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T& x)
	{
		T* buf = (T*) Alloc(SIZEOF(T));
		if (buf == nullptr)
			return buf;

		T* element = ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::Copy(*buf, x);
		if (element == nullptr || _ptr.Insert(position, element) == nullptr)	// allocation, copy or insert failed?
		{
			if (element)																					// inserting the pointer failed?
				element->~T();
			Free(buf);																						// if the copy failed buf holds the pointer to the allocated memory
		}

		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and initializes it with a copy of x.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be copied.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T& x)
	{
		Int	idx = position - Begin();
		T*	element = Insert(idx, x);
		return element ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and moves the content of x to it.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, T&& x)
	{
		T*	element = MAXON_SAFE_PLACEMENT_NEW (Alloc(SIZEOF(T))) T(std::move(x));
		if (element)
		{
			if (_ptr.Insert(position, element) == nullptr)				// inserting the pointer failed?
			{
				x = std::move(*element);														// move back
				element->~T();
				Free(element);
			}
		}

		return element;
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
	/// PointerArray specific: Inserts a pointer to a new element at index position.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Pointer to new element (PointerArray will take ownership of it)
	/// @return												Element pointer or nullptr (in this case x is still valid)
	//----------------------------------------------------------------------------------------
	T* InsertPtr(Int position, T* x)
	{
		return _ptr.Insert(position, x) ? x : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new elements at index position (the pointers to all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T* x, Int insertCnt)
	{
		T*	element = nullptr;
		T**	ptrs = (T**) Alloc(insertCnt * SIZEOF(T*));
		if (ptrs)
		{
			Int	idx;

			for (idx = 0; idx < insertCnt; idx++)
			{
				T* o = (T*) Alloc(SIZEOF(T));
				if (o == nullptr)
					break;

				ptrs[idx] = x ? new (o) T(*x++) : new (o) T();

				if (idx == insertCnt - 1)													// created copies of all objects?
				{
					if (_ptr.Insert(position, ptrs, insertCnt) == nullptr)	// inserting the pointers failed?
						break;

					element = ptrs[0];
				}
			}

			if (idx < insertCnt)																	// insert failed?
			{
				for (; idx >= 0; idx--)
				{
					ptrs[idx]->~T();
					Free(ptrs[idx]);
				}
			}
			Free(ptrs);
		}
		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at iterator position (the pointers to all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert position.
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T* x, Int insertCnt)
	{
		Int	idx = position - Begin();
		T*	element = Insert(idx, x, insertCnt);
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
		Int	cnt = GetCount();

		if (UInt(position) >= UInt(cnt))
		{
			DebugAssert(eraseCnt == 0);
			return nullptr;
		}

		if (UInt(position + eraseCnt) > UInt(cnt))
		{
			DebugStop();
			eraseCnt = cnt - position;
		}

		for (Int idx = position + eraseCnt - 1; idx >= position; idx--)
		{
			T*& element = _ptr[idx];
			element->~T();
			Free(element);
		}

		T** p = _ptr.Erase(position, eraseCnt);									// erase pointers
		return p ? *p : nullptr;
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
		T*	element = Erase(idx, eraseCnt);
		return (element || idx == GetCount()) ? Iterator(*this, idx) : Iterator();
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetFirst() const
	{
		return (GetCount() > 0) ? _ptr[0] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetFirst()
	{
		return (GetCount() > 0) ? _ptr[0] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetLast() const
	{
		Int last = GetCount() - 1;
		return (last >= 0) ? _ptr[last] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetLast()
	{
		Int last = GetCount() - 1;
		return (last >= 0) ? _ptr[last] : nullptr;
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
		Int	i;
		Int	cnt = GetCount();
		Int	increment = newCnt - cnt;

		if (increment <= 0)																			// decrease array size?
		{
			if (newCnt >= 0)
			{
				for (i = newCnt; i < cnt; i++)
				{
					T*& element = _ptr[i];
					element->~T();
					Free(element);
				}

				_ptr.Resize(newCnt);
			}
			else
			{
				DebugStop();
				return false;
			}
		}
		else																										// increase array size
		{
			if (_ptr.Resize(newCnt) == false)
				return false;

			for (i = cnt; i < newCnt;  i++)
			{
				_ptr[i] = MAXON_SAFE_PLACEMENT_NEW (Alloc(SIZEOF(T))) T();
				if (_ptr[i] == nullptr)
					break;
			}

			if (i < newCnt)																				// object allocation failed?
			{
				for (; i >= cnt; i--)
				{
					T*& element = _ptr[i];
					element->~T();
					Free(element);
				}

				_ptr.Resize(cnt);
				return false;
			}
		}

		return true;
	}

	//----------------------------------------------------------------------------------------
	/// Deletes the last element.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool  Pop(T* dst = nullptr)
	{
		Int	i = GetCount() - 1;
		if (i >= 0)
		{
			T* element = _ptr[i];
			if (dst)
				*dst = std::move(*element);													// call move operator if available

			element->~T();
			Free(element);
			_ptr.Pop();
			return true;
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// PointerArray specific:  Removes the last element and returns the pointer.
	/// @param[out] dst								Used to return pointer to the last element (must not be null), the caller will take ownership of the element.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool  PopPtr(T** dst)
	{
		Int	i = GetCount() - 1;
		if (i >= 0)
		{
			*dst = _ptr[i];
			_ptr.Pop();
			return true;
		}
		*dst = nullptr;
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the index of the element. The element must be part of the array, otherwise (e.g. if x is
	/// a copy of an array element) InvalidArrayIndex will be returned.
	/// This is quite slow because GetIndex() has to iterate over the array.
	/// @return												Index of element or InvalidArrayIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T& x) const
	{
		for (Int i = 0; i < GetCount(); i++)
		{
			if (_ptr[i] == &x)
				return i;
		}

		return InvalidArrayIndex;
	}

	//----------------------------------------------------------------------------------------
	/// Copies an array.
	/// @param[in] src								Source array.
	/// @param[in] fitToSize					If true the array will be copied to a new memory block that is as small as possible to hold the data.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	template <typename SourceArray> Bool CopyFrom(const SourceArray& src, Bool fitToSize = false)
	{
		Int	cnt = src.GetCount();
		Reset();

		if (_ptr.Resize(cnt, fitToSize ? BASEARRAYRESIZEFLAGS_FIT_TO_SIZE : BASEARRAYRESIZEFLAGS_DEFAULT))
		{
			typename SourceArray::ConstIterator it(src);
			Int	i;

			for (i = 0; i < cnt;  i++, it++)
			{
				_ptr[i] = MAXON_SAFE_PLACEMENT_NEW (Alloc(SIZEOF(T))) T(*it);
				if (_ptr[i] == nullptr)
					break;
			}

			if (i == cnt)																					// object allocation succesful?
				return true;

			for (; i < cnt;  i++)
				_ptr[i] = nullptr;

			Reset();
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Swaps elements a and b (just the pointers are swapped, this is more efficient than global Swap(array[a], array[b])
	/// @param[in] a									Position of element to be swapped.
	/// @param[in] b									Position of element to be swapped.
	//----------------------------------------------------------------------------------------
	void Swap(Iterator a, Iterator b)
	{
		maxon::Swap(a.GetPtr(), b.GetPtr());
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	ConstIterator Begin() const
	{
		return ConstIterator(*this);
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
		return Iterator(*this);
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
		return ConstIterator(*this, GetCount());
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
		return Iterator(*this, GetCount());
	}

	Iterator end()
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	///	The PointerArray iterator can be used to iterate over an array or parts of it. For more
	/// ease of use you may want to invoke this via AutoIterator.
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
	public:
		// For a const iterator, both the PointerArray and its values have to be const within the iterator, otherwise they are non-const.
		// These typedefs have to be used throughout the iterator code instead of just PointerArray or T.
		typedef typename ConstIf<CONSTITERATOR, PointerArray>::Type CollectionType;
		typedef typename ConstIf<CONSTITERATOR, T>::Type ValueType;
		static const Bool isLinearIterator = false;

		explicit IteratorTemplate(CollectionType& a, Int start = 0) : _data(a.GetCount() ? static_cast<ValueType* const*>(&a._ptr[0]) + start : nullptr)
		{
		}
		explicit IteratorTemplate(ValueType* const* pos = nullptr) : _data(pos)
		{
		}

		IteratorTemplate(const IteratorTemplate& src) : _data(src._data)
		{
		}
		IteratorTemplate& operator =(const IteratorTemplate& src)
		{
			_data = src._data;																		// self assignment is no problem here, therefore no check if (this != &src)
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
			return _data != nullptr;
		}

		ValueType* GetPtr() const
		{
			return *_data;
		}
		ValueType& operator *() const
		{
			return **_data;
		}
		ValueType* operator ->() const
		{
			return *_data;
		}

		Bool operator ==(const IteratorTemplate& b) const
		{
			return _data == b._data;
		}
		Bool operator !=(const IteratorTemplate& b) const
		{
			return _data != b._data;
		}
		Bool operator >=(const IteratorTemplate& b) const
		{
			return _data >= b._data;
		}
		Bool operator <=(const IteratorTemplate& b) const
		{
			return _data <= b._data;
		}
		Bool operator <(const IteratorTemplate& b) const
		{
			return _data < b._data;
		}
		Bool operator >(const IteratorTemplate& b) const
		{
			return _data > b._data;
		}

		IteratorTemplate& operator ++()																	// prefix operator ++ (increment and fetch)
		{
			_data++;
			return *this;
		}
		const IteratorTemplate operator ++(int)													// postfix operator ++ (fetch and increment)
		{
			ValueType* const* tmp = _data;
			_data++;
			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate& operator +=(Int i)														// operator +=
		{
			_data += i;
			return *this;
		}
		IteratorTemplate& operator --()																	// prefix operator -- (decrement and fetch)
		{
			_data--;
			return *this;
		}
		const IteratorTemplate operator --(int)													// postfix operator -- (fetch and decrement)
		{
			ValueType* const* tmp = _data;
			_data--;
			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate& operator -=(Int i)														// operator -=
		{
			_data -= i;
			return *this;
		}
		IteratorTemplate operator +(Int i) const												// operator +
		{
			return IteratorTemplate(_data + i);														// use RVO
		}
		IteratorTemplate operator -(Int i) const												// operator -
		{
			return IteratorTemplate(_data - i);														// use RVO
		}
		Int operator -(const IteratorTemplate& b) const
		{
			return _data - b._data;
		}

	private:
		ValueType* const* _data;
	};

	//----------------------------------------------------------------------------------------
	/// Returns the allocator as reference. Typically this is used by the arrays and other
	/// base classes when multiple of them are "stiched" together as one big object all
	/// shall use one main allocator.
	/// @return												Allocator reference.
	//----------------------------------------------------------------------------------------
	ALLOCATOR& GetAllocator()
	{
		return _ptr.GetAllocator();
	}

private:
	void*	Alloc(Int s)
	{
		return _ptr.GetAllocator().Alloc(s, MAXON_SOURCE_LOCATION);
	}
	template <typename X> void	Free(X*& p)
	{
		_ptr.GetAllocator().Free(p);
	}
};

/// @}

} // namespace maxon

#endif	// POINTERARRAY_H__
