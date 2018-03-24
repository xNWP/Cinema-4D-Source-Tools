#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_SORTEDARRAY_H__)
#define C4DMISC_SORTEDARRAY_H__

#include "sort.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

//----------------------------------------------------------------------------------------
///	Sorted array.
/// The class can be combined with any standard array type. Sorting is done on first read access,
/// e.g. if you access the array by using the index operator.
/// Note that sorted arrays will be extremely slow if read and write access is constantly alternating,
/// as for every write access a sort needs to be done, which needs O(log n) time. In those cases
/// other datastructures will be better suited.
/// Please also take into consideration that sorted arrays are not thread-safe, even for read-access
/// unless you call Sort() once before multiple threads start reading the data (if the array was in a
/// non-sorted state the first read-access will sort it otherwise, which will obviously cause problems)
///
/// @tparam MYSELF								The class itself.
/// @tparam ARRAY									The used array, e.g. BaseArray, BlockArray or PointerArray.
/// @tparam FLAGS									See BASESORTFLAGS, normally can be left at default.
///
/// @note Note that the array element class has special requirements regarding @link movecopy copy and move constructors @endlink.
//----------------------------------------------------------------------------------------
template <typename MYSELF, typename ARRAY, BASESORTFLAGS FLAGS = BASESORTFLAGS_0> class SortedArray
{
	MAXON_DISALLOW_COPY_AND_ASSIGN(SortedArray);

public:
	typedef typename ARRAY::ValueType	ValueType;
	typedef typename ARRAY::ValueType	T;

	/// The SortedArray iterator is just a typedef for the underlying array's iterator.
	/// This means that using the iterator to access array elements will not sort the
	/// array or mark it as being modified.
	typedef typename ARRAY::Iterator Iterator;
	typedef typename ARRAY::ConstIterator	ConstIterator;

	SortedArray()
	{
		_sorted = false;
	}

	/// this constructor has to be used if an array should use a custom allocator with member variables
	explicit SortedArray(const typename ARRAY::AllocatorType& a) : _array(a)
	{
	}

	~SortedArray()
	{
	}

	/// move constructor
	SortedArray(SortedArray&& src) : _array(std::move(src._array)), _sorted(std::move(src._sorted))
	{
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(SortedArray)

	//----------------------------------------------------------------------------------------
	/// Delete all elements (call destructors and free memory)
	//----------------------------------------------------------------------------------------
	void Reset()
	{
		SortChanged();
		_array.Reset();
	}

	//----------------------------------------------------------------------------------------
	/// Delete all elements, but don't free memory (call destructors though)
	//----------------------------------------------------------------------------------------
	void Flush()
	{
		SortChanged();
		_array.Flush();
	}

	//----------------------------------------------------------------------------------------
	/// Get number of array elements.
	/// @return												Number of array elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		return _array.GetCount();
	}

	//----------------------------------------------------------------------------------------
	/// Get number of elements for which memory has been allocated (this is usually bigger than GetCount())
	/// @return												Number of array elements for which memory has been allocated.
	//----------------------------------------------------------------------------------------
	Int GetCapacityCount() const
	{
		return _array.GetCapacityCount();
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	T& operator [](Int idx) const
	{
		CheckSort();
		return _array[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for non-const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	// this is duplicate code but casting constness away for this case is plain ugly
	T& operator [](Int idx)
	{
		CheckSort();
		return _array[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Add a new element at the end of the array.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append()
	{
		SortChanged();
		return _array.Append();
	}

	//----------------------------------------------------------------------------------------
	/// Add a new element at the end of the array and initialize it with a copy of x.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(const T& x)
	{
		SortChanged();
		return _array.Append(x);
	}

	//----------------------------------------------------------------------------------------
	/// Add a new element at the end of the array and move the content of x to it.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(T&& x)
	{
		SortChanged();
		return _array.Append(std::move(x));
	}

	/// PointerArray specific
	T* AppendPtr(T* x)
	{
		SortChanged();
		return _array.AppendPtr(x);
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new default element at index position.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position)
	{
		SortChanged();
		return _array.Insert(position);
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new default element at iterator position.
	/// @param[in] position						Insert position.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position)
	{
		SortChanged();
		return _array.Insert(position);
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new element at index position and initialize it with a copy of x.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T& x)
	{
		SortChanged();
		return _array.Insert(position, x);
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new element at iterator position and initialize it with a copy of x.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be copied.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T& x)
	{
		SortChanged();
		return _array.Insert(position, x);
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new element at index position and move the content of x to it.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, T&& x)
	{
		SortChanged();
		return _array.Insert(position, std::move(x));
	}

	//----------------------------------------------------------------------------------------
	/// Insert a new element at iterator position and move the content of x to it.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be moved.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, T&& x)
	{
		SortChanged();
		return _array.Insert(position, std::move(x));
	}

	//----------------------------------------------------------------------------------------
	/// Insert new elements at index position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T* x, Int insertCnt)
	{
		SortChanged();
		return _array.Insert(position, x, insertCnt);
	}

	//----------------------------------------------------------------------------------------
	/// Insert new elements at iterator position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert position.
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T* x, Int insertCnt)
	{
		SortChanged();
		return _array.Insert(position, x, insertCnt);
	}

	//----------------------------------------------------------------------------------------
	/// Erase (remove and delete) elements.
	/// @param[in] position						Index (Erase() will fail if out of bounds and return nullptr)
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Pointer to the element that is now at position or nullptr (no more element at position, either because position is out of bounds or the last element was erased)
	//----------------------------------------------------------------------------------------
	T* Erase(Int position, Int eraseCnt = 1)
	{
		return _array.Erase(position, eraseCnt);
	}

	//----------------------------------------------------------------------------------------
	/// Erase (remove and delete) elements.
	/// @param[in] position						Erase position.
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Iterator for the element at position (IsValid() == false if something failed)
	//----------------------------------------------------------------------------------------
	Iterator Erase(Iterator position, Int eraseCnt = 1)
	{
		return _array.Erase(position, eraseCnt);
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetFirst() const
	{
		CheckSort();
		return _array.GetFirst();
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetFirst()
	{
		CheckSort();
		return _array.GetFirst();
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetLast() const
	{
		CheckSort();
		return _array.GetLast();
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetLast()
	{
		CheckSort();
		return _array.GetLast();
	}

	//----------------------------------------------------------------------------------------
	/// Resize the array to contain newCnt elements
	/// If newCnt is smaller than GetCount() all extra elements are being deleted. If it is
	/// greater the array is expanded and the default constructor is called for new elements.
	/// @param[in] newCnt							New array size.
	/// @param[in] fitToSize					If true the array will be copied to a new memory block that is as small as possible to hold the data.
	/// @return												False if allocation failed.
	//----------------------------------------------------------------------------------------
	Bool Resize(Int newCnt, Bool fitToSize = false)
	{
		SortChanged();
		return _array.Resize(newCnt, fitToSize);
	}

	//----------------------------------------------------------------------------------------
	/// Delete last element.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool Pop(T* dst = nullptr)
	{
		return _array.Pop(dst);
	}

	//----------------------------------------------------------------------------------------
	/// Get index of element. The element must be part of the array, otherwise (e.g. if x is
	/// a copy of an array element) InvalidArrayIndex will be returned.
	/// @return												Index of element or InvalidArrayIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T& x) const
	{
		CheckSort();
		return _array.GetIndex(x);
	}

	//----------------------------------------------------------------------------------------
	/// Copy array.
	/// @param[in] src								Source array.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const SortedArray& src)
	{
		_sorted = src._sorted;
		return _array.CopyFrom(src._array);
	}

	//----------------------------------------------------------------------------------------
	/// Swap elements a and b.
	/// @param[in] a									Position of element to be swapped.
	/// @param[in] b									Position of element to be swapped.
	//----------------------------------------------------------------------------------------
	void Swap(Iterator a, Iterator b)
	{
		SortChanged();
		_array.Swap(a, b);
	}

	//----------------------------------------------------------------------------------------
	/// Get iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	ConstIterator Begin() const
	{
		CheckSort();
		return _array.Begin();
	}

	ConstIterator begin() const
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Get iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	Iterator Begin()
	{
		CheckSort();
		return _array.Begin();
	}

	Iterator begin()
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Get iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	ConstIterator End() const
	{
		CheckSort();
		return _array.End();
	}

	ConstIterator end() const
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	/// Get iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	Iterator End()
	{
		CheckSort();
		return _array.End();
	}

	Iterator end()
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	/// Mark array as non-sorted
	/// Sorting will happen upon the next read access
	//----------------------------------------------------------------------------------------
	void SortChanged()
	{
		_sorted = false;
	}

	//----------------------------------------------------------------------------------------
	/// Manually sort the array
	//----------------------------------------------------------------------------------------
	void Sort()
	{
		CheckSort();
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array.
	/// The time for searching will be O(log(n))
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] ptr								Only defined so that the compiler can resolve the template, default argument set to nullptr.
	/// @return												If an element is found a pointer to it will be returned, otherwise the result is nullptr. If multiple elements have the same key value the first of those elements will be returned.
	//----------------------------------------------------------------------------------------
	template <typename SEARCH> T* FindValue(const SEARCH& key, const T* ptr = nullptr) const
	{
		CheckSort();
		BaseSort<MYSELF> sort;
		return sort.Find(key, _array);
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array or insert it if it was not found.
	/// The time for this operation will be O(log(n)) for searching plus O(n) for inserting.
	/// Keep in mind that the resulting pointer will only be valid right after the operation as any additional array operation might shuffle array indices.
	/// To use this routine the SortedArray class must define the following member: @code static void	InitInsertData(T& initme, const SEARCH& key); @endcode
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] ptr								Only defined so that the compiler can resolve the template, default argument set to nullptr.
	/// @return												If an element was found a pointer to it will be returned, otherwise the result is the inserted element. If not enough memory was available nullptr will be returned.
	//----------------------------------------------------------------------------------------
	template <typename SEARCH> T* FindOrInsert(const SEARCH& key, const T* ptr = nullptr)
	{
		CheckSort();
		BaseSort<MYSELF> sort;
		Int insertIdx = NOTOK;
		T*	e = sort.FindInsertionIndex(key, _array, insertIdx);
		if (!e)
		{
			e = _array.Insert(insertIdx);
			if (e)
				MYSELF::InitInsertData(*e, key);
		}
		return e;
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array or insert it if it was not found.
	/// The time for this operation will be O(log(n)) for searching plus O(n) for inserting.
	/// Keep in mind that the resulting pointer will only be valid right after the operation as any additional array operation might shuffle array indices.
	/// To use this routine the SortedArray class must define the following member: @code static void	InitInsertData(T& initme, const SEARCH& key); @endcode
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[out] newElement				Specifies if the element was newly inserted (true) or if it was found in the array (false)
	/// @param[in] ptr								Only defined so that the compiler can resolve the template, default argument set to nullptr.
	/// @return												If an element was found a pointer to it will be returned, otherwise the result is the inserted element. If not enough memory was available nullptr will be returned.
	//----------------------------------------------------------------------------------------
	template <typename SEARCH> T* FindOrInsert(const SEARCH& key, Bool& newElement, const T* ptr = nullptr)
	{
		CheckSort();
		BaseSort<MYSELF> sort;
		Int insertIdx = NOTOK;
		T*	e = sort.FindInsertionIndex(key, _array, insertIdx);
		if (!e)
		{
			e = _array.Insert(insertIdx);
			newElement = true;
		}
		else
		{
			newElement = false;
		}
		return e;
	}

private:
	mutable ARRAY	_array;
	mutable Bool	_sorted;

	C4D_MISC_NO_INLINE void DoSort() const;

	void CheckSort() const
	{
		if (!_sorted)
		{
			DoSort();
		}
	}
};

// doxygen generates an error here, nobody knows why. so we exclude that for doxy.
/// @cond IGNORE

template <typename MYSELF, typename ARRAY, BASESORTFLAGS FLAGS> C4D_MISC_NO_INLINE void SortedArray<MYSELF, ARRAY, FLAGS>::DoSort() const
{
	BaseSort<MYSELF, FLAGS> sort;
	sort.Sort(_array);
	_sorted = true;
}

/// @endcond

/// @}

} // namespace maxon

#endif	// SORTEDARRAY_H__
