#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_SORT_H__)
#define C4DMISC_SORT_H__

#include "../general.h"

/// @file

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

/// Flags for the behavior of BaseSort when moving objects.
/// If you pass the default value BASESORTFLAGS_0 an auto-detection checks for POD and sets BASESORTFLAGS_MOVEANDCOPYOBJECTS if applicable.
/// For non-POD datatypes BASESORTFLAGS_MOVEANDCOPYOBJECTS can be manually set to increase performance (if your datatype allows memory operations).
enum BASESORTFLAGS
{
	BASESORTFLAGS_0									 = 0,	///< always use constructor/destructor or move operator, never memcpy, memmove or realloc
	BASESORTFLAGS_MOVEANDCOPYOBJECTS = 1	///< elements are PODs and can be moved and copied using memcpy and moved using memmove
} ENUM_LIST(BASESORTFLAGS);

// helper class to make the compiler choose Type BASESORTFLAGS_0 or Type BASESORTFLAGS_MOVEANDCOPYOBJECTS (as a joint source won't compile)
template <typename SORTCLASS, typename ITERATOR, typename CONTENT, BASESORTFLAGS FLAGS> class HelperClass
{
public:
	void IntroSortLoop(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last, Int depthLimit) const;
	void FinalInsertionSort(const SORTCLASS* sortClass, ITERATOR data, ITERATOR end, Int count) const;
};

//----------------------------------------------------------------------------------------
///	Template for sorting arrays and searching in sorted arrays
///
/// To use this template derive a class from it and define the member 'LessThan' that implements an element comparison.
/// If you do searching the member 'IsEqual' needs to be implemented that does an element comparison with the search key as the first argument.
/// If the search key is different from the element type a second LessThan routine is needed (comparing SEARCHKEY to an element).
///
/// @tparam SORTCLASS							The class itself.
/// @tparam FLAGS									See BASESORTFLAGS.
///
/// @note Note that the classes that will be sorted have special requirements regarding @link movecopy copy and move constructors @endlink.
///
/// Example for traditional C-style arrays:
///
/// @code
/// class Sort1 : public BaseSort<Sort1>
/// {
/// public:
///   static inline Bool LessThan(Int a, Int b)
///   {
///     return a < b;
///   }
/// };
///
/// ...
///
/// Int array1[100];
///
/// ...
///
/// Sort1 sort1;
/// sort1.Sort(&array1[0], &array1[100]); // note that the 'end' iterator is the last element + 1 and not the last element!
/// sort1.Sort(array1, 100); // even easier
/// @endcode
///
/// @note LessThan can be a member of the sort class itself (not static), but needs to be const in that case.
///
/// Example for maxon arrays:
///
/// @code
/// class Sort2 : public BaseSort<Sort2>
/// {
/// public:
///   static inline Bool LessThan(Int a, Int b)
///   {
///     return a < b;
///   }
/// };
///
/// ...
///
/// BlockArray<Int> array2;
///
/// ...
///
/// Sort2  sort2;
/// sort2.Sort(array2.Begin(), array2.End()); // do not write Sort(&array2[0], &array2[array2.GetCount()]) as this will create a debug assert (the second array access is illegal)
/// sort2.Sort(array2); // any arrays derived from BaseArray can be passed directly
/// @endcode
///
/// Example for arbitrary structures with multiple sort criteria:
///
/// @code
/// class MyStruct
/// {
/// public:
///   String _str;
///   Int    _index;
///   Float  _weight;
/// };
///
/// class Sort3 : public BaseSort<Sort3>
/// {
/// public:
///   static inline Bool LessThan(const MyStruct& a, const MyStruct& b)
///   {
///     if (a._weight < b._weight) return true;
///     if (a._weight > b._weight) return false;
///     return a._index < b._index; // if weights are identical sort by index
///   }
/// };
///
/// ...
///
/// BlockArray<MyStruct> array3;
///
/// ...
///
/// Sort3  sort3;
/// sort3.Sort(array3);
/// @endcode
///
///
/// Searching Example:
///
/// @code
/// class MyStruct
/// {
/// public:
///   String _str;
///   Int    _index;
///   Float  _weight;
/// };
///
/// class MySearch : public BaseSort <MySearch, BlockArray<MyStruct>::Iterator>
/// {
/// public:
///   // for sorting: compare array element to array element
///   static inline Bool LessThan(const MyStruct& a, const MyStruct& b)
///   {
///     if (a._weight < b._weight) return true;
///     if (a._weight > b._weight) return false;
///     return a._index < b._index; // if weights are identical sort by index
///   }
///
///   // for searching: compare search key to array element
///   static inline Bool LessThan(Float weight, const MyStruct& b)
///   {
///     return weight < b._weight;
///   }
///
///   // for searching: compare search key to array element
///   static inline Bool IsEqual(Float weight, const MyStruct& b)
///   {
///     return weight == b._weight;
///   }
/// };
///
/// ...
///
/// BlockArray<MyStruct> array4;
///
/// ...
///
/// MySearch search;
/// search.Sort(array4);
///
/// ...
///
/// // array is now sorted, we can search it
/// MyStruct* result = search.Find(5.0, array4);
/// @endcode
///
//----------------------------------------------------------------------------------------
template <typename SORTCLASS, BASESORTFLAGS FLAGS = BASESORTFLAGS_0> class BaseSort
{
public:
	//----------------------------------------------------------------------------------------
	/// Sort elements of an array, so that the smallest element comes first.
	/// Note that the sorting is not guaranteed to be stable (elements with the same sort value may change their order).
	/// The time for sorting is O(n * log(n))
	/// @param[in] start							The start iterator of an array.
	/// @param[in] end								The end iterator of an array. Note that this is not the last element! It needs to be the boundary (which is last element + 1). See in the BaseSort class description for examples.
	//----------------------------------------------------------------------------------------
	template <typename ITERATOR> void Sort(ITERATOR start, ITERATOR end) const
	{
		Int count = end - start;
		if (count > 1)
			ISort(start, count, *start);
	}

	//----------------------------------------------------------------------------------------
	/// Sort elements of an array, so that the smallest element comes first.
	/// Note that the sorting is not guaranteed to be stable (elements with the same sort value may change their order).
	/// The time for sorting is O(n * log(n))
	/// @param[in] start							The start iterator of an array.
	/// @param[in] count							The number of elements to be sorted.
	//----------------------------------------------------------------------------------------
	template <typename ITERATOR> inline void Sort(ITERATOR start, Int count) const
	{
		if (count > 1)
			ISort(start, count, *start);
	}

	//----------------------------------------------------------------------------------------
	/// Sort elements of an array, so that the smallest element comes first.
	/// Note that the sorting is not guaranteed to be stable (elements with the same sort value may change their order).
	/// The time for sorting is O(n * log(n))
	/// @param[in] arr								The array to be sorted.
	//----------------------------------------------------------------------------------------
	template <typename ARRAY> void Sort(ARRAY& arr) const
	{
		Int count = arr.GetCount();
		if (count > 1)
			ISort(arr.Begin(), count, *arr.Begin());
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array.
	/// The array must be in a sorted state.
	/// The time for searching will be O(log(n))
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] arr								The array to be searched.
	/// @param[in] count							The number of elements of the array.
	/// @return												If an element is found a pointer to it will be returned, otherwise the result is nullptr. If multiple elements have the same key value the first of those elements will be returned.
	//----------------------------------------------------------------------------------------
	template <typename SEARCHTYPE, typename ITERATOR> ITERATOR Find(const SEARCHTYPE& key, ITERATOR arr, Int count) const
	{
		Int l, r, mp, tmp;

		if (count < 1)
			return ITERATOR();

		ITERATOR dat;
		if (((const SORTCLASS*)this)->LessThan(key, *arr))	// value is smaller than anything in the array
			return ITERATOR();
		else if (((const SORTCLASS*)this)->IsEqual(key, *arr))
			return arr;

		l = 1;
		r = count - 1;

		while (l <= r)
		{
			mp	= (l + r) >> 1;
			dat = arr + mp;

			if (((const SORTCLASS*)this)->LessThan(key, *dat))
			{
				r = mp - 1;
			}
			else if (!((const SORTCLASS*)this)->IsEqual(key, *dat))
			{
				l = mp + 1;
			}
			else
			{
				while (mp > 0)
				{
					tmp = mp--;
					if (!((const SORTCLASS*)this)->IsEqual(key, *(arr + mp)))
						return arr + tmp;
				}
				return arr + mp;
			}
		}
		return ITERATOR();
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array derived from BaseArray.
	/// The array must be in a sorted state.
	/// The time for searching will be O(log(n))
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] arr								The array to be searched.
	/// @return												If an element is found a pointer to it will be returned, otherwise the result is nullptr. If multiple elements have the same key value the first of those elements will be returned.
	//----------------------------------------------------------------------------------------
	template <typename ARRAY, typename SEARCHTYPE> typename ARRAY::ValueType* Find(const SEARCHTYPE& key, const ARRAY& arr) const
	{
		ARRAY* nonConstArray = const_cast<ARRAY*>(&arr);
		return Find(key, nonConstArray->Begin(), arr.GetCount()).GetPtr();
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array and return the insertion index if the element was not found.
	/// The array must be in a sorted state.
	/// The time for searching will be O(log(n))
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] arr								The array to be searched.
	/// @param[in] count							The number of elements of the array.
	/// @param[out] insertionIndex		The index an element needs to be inserted at if it does not exist in the array. Inserting at the designated place ensures that the array stays sorted.
	/// @return												If an element was found a pointer to it will be returned, otherwise the result is nullptr. If multiple elements have the same key value the first of those elements will be returned.
	//----------------------------------------------------------------------------------------
	template <typename SEARCHTYPE, typename ITERATOR> ITERATOR FindInsertionIndex(const SEARCHTYPE& key, ITERATOR arr, Int count, Int& insertionIndex) const
	{
		Int l, r, mp, tmp;

		insertionIndex = 0;

		if (count < 1)
			return ITERATOR();

		ITERATOR dat;
		if (((const SORTCLASS*)this)->LessThan(key, *arr))	// value is smaller than anything in the array
			return ITERATOR();
		else if (((const SORTCLASS*)this)->IsEqual(key, *arr))
			return arr;

		l = 1;
		r = count - 1;

		insertionIndex = 1;	// necessary if c > 0 and r < l

		while (l <= r)
		{
			mp	= (l + r) >> 1;
			dat = arr + mp;

			if (((const SORTCLASS*)this)->LessThan(key, *dat))
			{
				insertionIndex = mp;
				r = mp - 1;
			}
			else if (!((const SORTCLASS*)this)->IsEqual(key, *dat))
			{
				l = mp + 1;
				insertionIndex = l;
			}
			else
			{
				while (mp > 0)
				{
					tmp = mp--;
					if (!((const SORTCLASS*)this)->IsEqual(key, *(arr + mp)))
					{
						insertionIndex = tmp;
						return arr + tmp;
					}
				}
				insertionIndex = mp;
				return arr + mp;
			}
		}

		return ITERATOR();
	}

	//----------------------------------------------------------------------------------------
	/// Find an element in an array derived from BaseArray and return the insertion index if the element was not found.
	/// The array must be in a sorted state.
	/// The time for searching will be O(log(n))
	///
	/// @param[in] key								The key that the array is searched for.
	/// @param[in] arr								The array to be searched.
	/// @param[out] insertionIndex		The index an element needs to be inserted at if it does not exist in the array. Inserting at the designated place ensures that the array stays sorted.
	/// @return												If an element was found a pointer to it will be returned, otherwise the result is nullptr. If multiple elements have the same key value the first of those elements will be returned.
	//----------------------------------------------------------------------------------------
	template <typename ARRAY, typename SEARCHTYPE> typename ARRAY::ValueType* FindInsertionIndex(const SEARCHTYPE& key, const ARRAY& arr, Int& insertionIndex) const
	{
		ARRAY* nonConstArray = const_cast<ARRAY*>(&arr);
		return FindInsertionIndex(key, nonConstArray->Begin(), arr.GetCount(), insertionIndex).GetPtr();
	}

private:
	inline Int Log2(Int n) const
	{
		Int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		return k;
	}

	template <typename ITERATOR, typename CONTENT> inline void ISort(ITERATOR start, Int count, const CONTENT& valType) const
	{
#ifdef MAXON_TARGET_DEBUG
		// test if LessThan implementation is correct - if a value is compared to itself LessThan must never return true
		if (((const SORTCLASS*)this)->LessThan(valType, valType))
		{
			CriticalStop();
			return;
		}
#endif
		// automatically correct the flags if a POD type is detected
		HelperClass<SORTCLASS, ITERATOR, CONTENT, (BASESORTFLAGS) ((Int)FLAGS | (std::is_pod<CONTENT>::value ? (Int)BASESORTFLAGS_MOVEANDCOPYOBJECTS : 0))> help;

		ITERATOR end = start + count;
		help.IntroSortLoop((const SORTCLASS*)this, start, end, Log2(count) * 2);
		help.FinalInsertionSort((const SORTCLASS*)this, start, end, count);
	}
};

//----------------------------------------------------------------------------------------
///	Specialized BaseSort template for simple datatypes.
///
/// @tparam BASICTYPE							Datatype that offers the operators == and <
///
///
/// Example:
///
/// @code
/// BaseArray<Int> array;
/// SimpleSort<Int> test;
/// test.Sort(array);
/// @endcode
///
/// or
///
/// @code
/// BaseArray<Int> array2;
/// SimpleSort<Int> test2;
/// test2.Sort(&array2[0], array2.GetCount());
/// @endcode
//----------------------------------------------------------------------------------------
template <typename BASICTYPE> class SimpleSort : public BaseSort<SimpleSort<BASICTYPE> >
{
public:
	static Bool LessThan(const BASICTYPE& a, const BASICTYPE& b)
	{
		return a < b;
	}

	static Bool IsEqual(const BASICTYPE& a, const BASICTYPE& b)
	{
		return a == b;
	}
};

// regular implementation
template <typename SORTCLASS, typename ITERATOR, typename CONTENT> class HelperClass<SORTCLASS, ITERATOR, CONTENT, BASESORTFLAGS_0>
{
	static const Int SORT_THRESHOLD = 32;

	inline ITERATOR Median(const SORTCLASS* sortClass, ITERATOR a, ITERATOR b, ITERATOR c) const
	{
		if (sortClass->LessThan(*a, *b))
		{
			if (sortClass->LessThan(*b, *c))
				return b;
			else if (sortClass->LessThan(*a, *c))
				return c;
			return a;
		}
		else if (sortClass->LessThan(*a, *c))
		{
			return a;
		}
		else if (sortClass->LessThan(*b, *c))
		{
			return c;
		}
		return b;
	}

	void FinalSort(const SORTCLASS* sortClass, ITERATOR start, Int count) const
	{
		if (count < 2)
			return;

		Int r = count;
		Int l = (r / 2) + 1;

		while (true)
		{
			if (l > 1)
			{
				l--;
			}
			else
			{
				r--;
				maxon::Swap(*(start + (l - 1)), *(start + r));
				if (r <= 1)
					return;
			}

			Int j = l;
			ITERATOR jp = start + (j - 1);

			while (j * 2 <= r)
			{
				ITERATOR ip = jp;
				j *= 2;
				jp = start + (j - 1);

				if (j < r)
				{
					if (sortClass->LessThan(*jp, *(jp + 1)))
					{
						j++;
						jp++;
					}
				}

				if (sortClass->LessThan(*ip, *jp))
					maxon::Swap(*ip, *jp);
				else
					break;
			}
		}
	}

	inline void InsertionSort(const SORTCLASS* sortClass, ITERATOR data, ITERATOR end) const
	{
		if (end - data > SORT_THRESHOLD)
		{
			FinalSort(sortClass, data, end - data);
		}
		else
		{
			ITERATOR i = data + 1;
			do
			{
				for (ITERATOR j = i, j1 = j - 1; j != data && (sortClass->LessThan(*j, *j1)); j--, j1--)
					maxon::Swap(*j1, *j);
				i++;
			} while (i != end);
		}
	}

	ITERATOR UnguardedPartition(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last, ITERATOR pivot) const
	{
		first--;
		while (true)
		{
			while (sortClass->LessThan(*++first, *pivot))
			{
			}

			while (sortClass->LessThan(*pivot, *--last))
			{
			}

			if (first >= last)
				return first;

			maxon::Swap(*first, *last);

			if (first == pivot)
				pivot = last;
			else if (last == pivot)
				pivot = first;
		}
	}

	void UnguardedLinearInsert(const SORTCLASS* sortClass, ITERATOR data) const
	{
		if (sortClass->LessThan(*data, *(data - 1)))
		{
			CONTENT tmp(std::move(*data));

			do
			{
				*data = std::move(*(data - 1));
				data--;
			} while (sortClass->LessThan(tmp, *(data - 1)));

			*data = std::move(tmp);
		}
	}

	inline void UnguardedInsertionSort(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last) const
	{
		for (; first != last; ++first)
			UnguardedLinearInsert(sortClass, first);
	}

public:
	void IntroSortLoop(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last, Int depthLimit) const
	{
		while (last - first > SORT_THRESHOLD)
		{
			if (depthLimit == 0)
			{
				InsertionSort(sortClass, first, last);	// insertion sort is faster than old merge sort algorithm
				return;
			}
			depthLimit--;

			ITERATOR mid = Median(sortClass, first, (first + (last - first) / 2), (last - 1));
			ITERATOR cut = UnguardedPartition(sortClass, first, last, mid);

			IntroSortLoop(sortClass, cut, last, depthLimit);

			last = cut;
		}
	}

	void FinalInsertionSort(const SORTCLASS* sortClass, ITERATOR data, ITERATOR end, Int count) const
	{
		if (count > SORT_THRESHOLD)
		{
			ITERATOR mid = data + SORT_THRESHOLD;
			InsertionSort(sortClass, data, mid);					// sort the first SORT_THRESHOLD elements
			UnguardedInsertionSort(sortClass, mid, end);	// sort the rest of the array; data is moved beyond lower limit (mid) inside
		}
		else if (data != end)
		{
			InsertionSort(sortClass, data, end);
		}
	}
};

// implementation for objects with private constructors or no copy/assigment operators
template <typename SORTCLASS, typename ITERATOR, typename CONTENT> class HelperClass<SORTCLASS, ITERATOR, CONTENT, BASESORTFLAGS_MOVEANDCOPYOBJECTS>
{
	static const Int SORT_THRESHOLD = 32;

	inline ITERATOR Median(const SORTCLASS* sortClass, ITERATOR a, ITERATOR b, ITERATOR c) const
	{
		if (sortClass->LessThan(*a, *b))
		{
			if (sortClass->LessThan(*b, *c))
				return b;
			else if (sortClass->LessThan(*a, *c))
				return c;
			return a;
		}
		else if (sortClass->LessThan(*a, *c))
		{
			return a;
		}
		else if (sortClass->LessThan(*b, *c))
		{
			return c;
		}
		return b;
	}

	void FinalSort(const SORTCLASS* sortClass, ITERATOR start, Int count) const
	{
		if (count < 2)
			return;

		UChar swap[sizeof(CONTENT)];

		Int r = count;
		Int l = (r / 2) + 1;

		while (true)
		{
			if (l > 1)
			{
				l--;
			}
			else
			{
				r--;

				void* s1 = &(*(start + (l - 1)));
				void* s2 = &(*(start + r));

				memcpy(swap, s1, sizeof(CONTENT));
				memcpy(s1, s2, sizeof(CONTENT));
				memcpy(s2, swap, sizeof(CONTENT));

				if (r <= 1)
					return;
			}

			Int j = l;
			ITERATOR jp = start + (j - 1);

			while (j * 2 <= r)
			{
				ITERATOR ip = jp;
				j *= 2;
				jp = start + (j - 1);

				if (j < r)
				{
					if (sortClass->LessThan(*jp, *(jp + 1)))
					{
						j++;
						jp++;
					}
				}

				if (sortClass->LessThan(*ip, *jp))
				{
					memcpy(swap, &(*ip), sizeof(CONTENT));
					memcpy(&(*ip), &(*jp), sizeof(CONTENT));
					memcpy(&(*jp), swap, sizeof(CONTENT));
				}
				else
				{
					break;
				}
			}
		}
	}

	inline void InsertionSort(const SORTCLASS* sortClass, ITERATOR data, ITERATOR end) const
	{
		if (end - data > SORT_THRESHOLD)
		{
			FinalSort(sortClass, data, end - data);
		}
		else
		{
			ITERATOR i = data + 1;
			do
			{
				for (ITERATOR j = i, j1 = j - 1; j != data && (sortClass->LessThan(*j, *j1)); j--, j1--)
				{
					UChar swap[sizeof(CONTENT)];
					memcpy(swap, &(*j), sizeof(CONTENT));
					memcpy(&(*j), &(*j1), sizeof(CONTENT));
					memcpy(&(*j1), swap, sizeof(CONTENT));
				}
				i++;
			} while (i != end);
		}
	}

	ITERATOR UnguardedPartition(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last, ITERATOR pivot) const
	{
		first--;
		while (true)
		{
			while (sortClass->LessThan(*++first, *pivot))
			{
			}

			while (sortClass->LessThan(*pivot, *--last))
			{
			}

			if (first >= last)
				return first;

			UChar swap[sizeof(CONTENT)];	// copy/move memory manually
			memcpy(swap, &(*first), sizeof(CONTENT));
			memcpy(&(*first), &(*last), sizeof(CONTENT));
			memcpy(&(*last), swap, sizeof(CONTENT));

			if (first == pivot)
				pivot = last;
			else if (last == pivot)
				pivot = first;
		}
	}

	void UnguardedLinearInsert(const SORTCLASS* sortClass, ITERATOR data) const
	{
		if (sortClass->LessThan(*data, *(data - 1)))
		{
			UChar valMemory[sizeof(CONTENT)];	// copy/move memory manually
			memcpy(valMemory, &(*data), sizeof(CONTENT));
			const CONTENT& val = *((CONTENT*)valMemory);

			do
			{
				memcpy(&(*data), &(*(data - 1)), sizeof(CONTENT));
				data--;
			} while (sortClass->LessThan(val, *(data - 1)));

			memcpy(&(*data), &val, sizeof(CONTENT));
		}
	}

	inline void UnguardedInsertionSort(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last) const
	{
		for (; first != last; ++first)
			UnguardedLinearInsert(sortClass, first);
	}

public:
	void IntroSortLoop(const SORTCLASS* sortClass, ITERATOR first, ITERATOR last, Int depthLimit) const
	{
		while (last - first > SORT_THRESHOLD)
		{
			if (depthLimit == 0)
			{
				InsertionSort(sortClass, first, last);	// insertion sort is faster than old merge sort algorithm
				return;
			}
			depthLimit--;

			ITERATOR mid = Median(sortClass, first, (first + (last - first) / 2), (last - 1));
			ITERATOR cut = UnguardedPartition(sortClass, first, last, mid);

			IntroSortLoop(sortClass, cut, last, depthLimit);

			last = cut;
		}
	}

	void FinalInsertionSort(const SORTCLASS* sortClass, ITERATOR data, ITERATOR end, Int count) const
	{
		if (count > SORT_THRESHOLD)
		{
			ITERATOR mid = data + SORT_THRESHOLD;
			InsertionSort(sortClass, data, mid);					// sort the first SORT_THRESHOLD elements
			UnguardedInsertionSort(sortClass, mid, end);	// sort the rest of the array; data is moved beyond lower limit (mid) inside
		}
		else if (data != end)
		{
			InsertionSort(sortClass, data, end);
		}
	}
};

/// @}

} // namespace maxon

#endif	// SORT_H__
