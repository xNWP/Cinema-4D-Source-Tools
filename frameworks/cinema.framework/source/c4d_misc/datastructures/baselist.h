#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_BASELIST_H__)
#define C4DMISC_BASELIST_H__

#include "../memory/defaultallocator.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

struct BaseListLinkPOD
{
	void*	_next;
	UInt	_prevFlag;																					// bit0: listheadflag bit>0 ptr
};

//----------------------------------------------------------------------------------------
///	Link field for the pointers of a list node
//----------------------------------------------------------------------------------------
template <typename NODE> class BaseListLink : public BaseListLinkPOD
{
public:
	BaseListLink(NODE* prev = nullptr, NODE* next = nullptr, Bool is_head = false)
	{
		_next = next;
		_prevFlag = ComputePrevFlag(prev, is_head);
	}

#ifdef MAXON_TARGET_DEBUG
	/// <B> NOTE: the destructor is not virtual </B>
	~BaseListLink()
	{
		if (_GetNextChecked() || _GetPrevChecked())
			DebugStop();
	}
#endif

	/// move constructor
	BaseListLink(BaseListLink&& src)
	{
		_next = src._next;
		_prevFlag = src._prevFlag;
		src._next = nullptr;
		src._prevFlag = 0;
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(BaseListLink)

	//----------------------------------------------------------------------------------------
	/// Gets the next element.
	/// @return												Next element (can never be null, but points to list head if this is the last element)
	//----------------------------------------------------------------------------------------
	NODE* _GetNext() const
	{
		return (NODE*) _next;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the previous element.
	/// @return												Previous element (can never be null, but points to list head if this is the first element)
	//----------------------------------------------------------------------------------------
	NODE* _GetPrev() const
	{
		return (NODE*) (_prevFlag & ADDRESS_MASK);
	}

	//----------------------------------------------------------------------------------------
	/// Removes the element (just removes it from the list, does not delete it).
	//----------------------------------------------------------------------------------------
	static void Remove(NODE* remove)
	{
		NODE*	p = remove->_GetPrev();
		NODE*	n = remove->_GetNext();
		if (p) p->SetNext(n);
		if (n) n->SetPrev(p);
		remove->SetNext(nullptr);
		remove->SetPrev(nullptr);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts this before next.
	/// @param[in] insert							Node to insert.
	/// @param[in] next								The next object's link.
	//----------------------------------------------------------------------------------------
	static void InsertBefore(NODE* insert, NODE* next)
	{
		NODE* prev = next->_GetPrev();

		insert->SetNext(next);
		insert->SetPrev(prev);
		prev->SetNext(insert);
		next->SetPrev(insert);
	}

	//----------------------------------------------------------------------------------------
	/// Returns true if this is a list head (_GetNext() would return pointer to the first element of the list, _GetPrev() to the last)
	/// @return												True if this is a list head.
	//----------------------------------------------------------------------------------------
	Bool IsListHead() const
	{
		return (_prevFlag & HEAD_MASK) != 0;
	}

	NODE* _GetNextChecked() const
	{
		NODE* n = _GetNext();
		return n && !n->IsListHead() ? n : nullptr;
	}

	NODE* _GetPrevChecked() const
	{
		NODE* p = _GetPrev();
		return p && !p->IsListHead() ? p : nullptr;
	}

	void SetNext(NODE* val) { _next = (void*) val; }
	void SetPrev(NODE* val) { _prevFlag &= HEAD_MASK; _prevFlag |= UInt(val) & ADDRESS_MASK; }

private:

	void SetListHead(Bool val) { _prevFlag &= ADDRESS_MASK; _prevFlag |= (UInt)val; }

	UInt ComputePrevFlag(NODE* prev, Bool head) const { return (UInt(prev) & ADDRESS_MASK) | (UInt)head; }

private:
	static const UInt HEAD_MASK = 1;
	static const UInt ADDRESS_MASK = ~HEAD_MASK;
};

template <typename T, Bool hasCopyFrom = TestForCopyFromMember<T>::isSupported> class BaseListNode {};

//----------------------------------------------------------------------------------------
///	Template for list node containing element data of type T (T has a copy constructor that cannot fail).
///
/// If you have to define a custom list node (which should rarely be the case) you can
/// simply use the IMPLEMENT_CUSTOM_BASELISTNODE(YourClass, PointerToBaseListPOD) macro that
/// will implement the required methods.
///
/// @tparam T											Content of the list node.
//----------------------------------------------------------------------------------------
template <typename T> class BaseListNode<T, false> : public BaseListLink<BaseListNode<T> >
{
public:
	BaseListNode() : _data()
	{
	}

	BaseListNode(const T& src) : _data(src)
	{
	}

	BaseListNode(T&& src) : _data(std::move(src))
	{
	}

	~BaseListNode()
	{
		Remove();
	}

	//----------------------------------------------------------------------------------------
	/// Removes element (just removes it from the list, does not delete it).
	//----------------------------------------------------------------------------------------
	void Remove()
	{
		BaseListLink<BaseListNode<T> >::Remove(this);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts this before next.
	/// @param[in] next								The next object's link.
	//----------------------------------------------------------------------------------------
	void InsertBefore(BaseListNode* next)
	{
		BaseListLink<BaseListNode<T> >::InsertBefore(this, next);
	}

	/// returns element data of the list node
	T* _GetData() const
	{
		return &_data;
	}

	BaseListLinkPOD* _GetLink() const
	{
		return (BaseListLink<BaseListNode<T> >*) this;
	}

protected:
	mutable T	_data;
};

//----------------------------------------------------------------------------------------
///	Template for list node containing element data of type T (to copy T you must use CopyFrom)
///
/// If you have to define a custom list node (which should rarely be the case) you can
/// simply use the IMPLEMENT_CUSTOM_BASELISTNODE(YourClass, PointerToBaseListPOD) macro that
/// will implement the required methods.
///
/// @tparam T											Content of the list node.
//----------------------------------------------------------------------------------------
template <typename T> class BaseListNode<T, true> : public BaseListLink<BaseListNode<T> >
{
public:
	BaseListNode() : _data()
	{
	}

	BaseListNode(const T& src)
	{
		DebugStop();																						// this is a dummy, instead _data.CopyFrom() has to be used
	}

	BaseListNode(T&& src) : _data(std::move(src))
	{
	}

	~BaseListNode()
	{
		Remove();
	}

	//----------------------------------------------------------------------------------------
	/// Removes element (just removes it from the list, does not delete it).
	//----------------------------------------------------------------------------------------
	void Remove()
	{
		BaseListLink<BaseListNode<T> >::Remove(this);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts this before next.
	/// @param[in] next								The next object's link.
	//----------------------------------------------------------------------------------------
	void InsertBefore(BaseListNode* next)
	{
		BaseListLink<BaseListNode<T> >::InsertBefore(this, next);
	}

	/// returns element data of the list node
	T* _GetData() const
	{
		return &_data;
	}

	BaseListLinkPOD* _GetLink() const
	{
		return (BaseListLink<BaseListNode<T> >*) this;
	}

protected:
	mutable T	_data;
};

//----------------------------------------------------------------------------------------
///	Template for list head pointing to elements of T.
/// @tparam T											Content of the list node.
/// @tparam NODE									List node containing T.
//----------------------------------------------------------------------------------------
template <typename T, typename NODE> class BaseListHead : public BaseListLink<NODE>
{
public:
	BaseListHead() : BaseListLink<NODE>(End(), End(), true)
	{
	}
	~BaseListHead()
	{
		CriticalAssert(GetFirst() == nullptr);									// all elements must be flushed by the derived template (they know the allocator and can implement a virtual destructor if necessary)
	}

	/// move constructor
	BaseListHead(BaseListHead&& src) : BaseListLink<NODE>(std::move(src))
	{
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(BaseListHead)

	//----------------------------------------------------------------------------------------
	/// Gets the first element.
	/// @return												First element or nullptr.
	//----------------------------------------------------------------------------------------
	T* GetFirst() const
	{
		NODE* n = (NODE*) this->_GetNext();
		return n == End() ? nullptr : n->_GetData();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the last element.
	/// @return												Last element or nullptr.
	//----------------------------------------------------------------------------------------
	T* GetLast() const
	{
		NODE* p = (NODE*) this->_GetPrev();
		return p == End() ? nullptr : p->_GetData();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of elements.
	/// @return												Number of elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		Int cnt = 0;

		for (NODE* e = Begin(); e != End(); e = e->_GetNext())
			cnt++;

		return cnt;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the element by index.
	/// @return												Element or nullptr (not element of this)
	//----------------------------------------------------------------------------------------
	T* GetElement(Int idx) const
	{
		NODE* node = GetNode(idx);
		return node ? node->_GetData() : nullptr;
	}

	NODE* GetNode(Int idx) const
	{
		for (NODE* e = Begin(); e != End(); e = e->_GetNext(), idx--)
		{
			if (idx == 0)
				return e;
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the index of the element. The element must be part of the array, otherwise (e.g.
	/// if x is a copy of an array element) InvalidArrayIndex will be returned.
	/// @return												Index of element or InvalidArrayIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T* x) const
	{
		Int idx = 0;
		for (NODE* e = Begin(); e != End(); e = e->_GetNext(), idx++)
		{
			if (x == e->_GetData())
				return idx;
		}
		return InvalidArrayIndex;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the pointer to the first node.
	/// @return												Pointer to the first element (equal to End() if the list is empty)
	//----------------------------------------------------------------------------------------
	NODE* Begin() const
	{
		return this->_GetNext();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the pointer to the virtual end node (the node after the last node). This is the address
	/// of a virtual (non-existing) node that contains this list head.
	/// @return												Pointer to the end node (the node after the last node)
	//----------------------------------------------------------------------------------------
	NODE* End() const
	{
		// The BaseListLinkPOD might be somewhere in the NODE. Since offsetof() is a nogo and
		// NODE might contain virtual stuff we have to get this offset the hard way. Since
		// some compilers try to be mighty clever the dummy pointer must not be 0.
		static const NODE* dummy = (NODE*) sizeof(void*);
		static const Int offset = Int(dummy->_GetLink()) - Int(dummy);
		return (NODE*) (Int(this) - offset);
	}
};

//----------------------------------------------------------------------------------------
///	Basic list template (double linked).
///
/// The BaseList implements the same methods as the arrays. Nonetheless it is highly
/// recommended to <B> use the iterator based methods </B> instead of those taking an index
/// or count as paramter because the latter perform poorly due to the nature of a list.
///
/// If you want to control the list nodes themselves or their memory layout you can specify
/// the list node type with NODE instead of using the default template BaseListNode<T>
/// (the same goes for the list head HEAD).
///
/// @tparam T											Type of the list element content.
/// @tparam NODE									A node that encapsulates the element content T and holds the pointers to the next and previous element (see BaseListNode for details).
/// @tparam HEAD									A list head for nodes of type NODE.
/// @tparam ALLOCATOR							Class for memory allocation.
//----------------------------------------------------------------------------------------
template<typename T, typename NODE = BaseListNode<T>, typename HEAD = BaseListHead<T, NODE>, typename ALLOCATOR = DefaultAllocator> class BaseList : protected ALLOCATOR
{
	MAXON_DISALLOW_COPY_AND_ASSIGN(BaseList);

public:
	typedef T ValueType;
	typedef ALLOCATOR AllocatorType;

	template <Bool CONSTITERATOR> class IteratorTemplate;
	typedef IteratorTemplate<false> Iterator;
	typedef IteratorTemplate<true> ConstIterator;

	BaseList()
	{
	}

	/// this constructor has to be used if a list should use a custom allocator with member variables
	explicit BaseList(const ALLOCATOR& a) : ALLOCATOR(a)
	{
	}

	~BaseList()
	{
		Reset();
	}

	/// move constructor
	BaseList(BaseList&& src) : ALLOCATOR(std::move(src)), _head(std::move(src._head))
	{
	}

	/// move assignment operator
	MAXON_OPERATOR_MOVE_ASSIGNMENT(BaseList)

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (calls destructors and frees memory)
	//----------------------------------------------------------------------------------------
	void  Reset()
	{
		for (Iterator e = End(); e != Begin(); e = End())
			Erase(--e);
	}

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (same as Reset() for the BaseList).
	//----------------------------------------------------------------------------------------
	void Flush()
	{
		Reset();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of list elements.
	/// <B> This has to iterate over all list elements. You may better want to use iterators directly! </B>
	/// @return												Number of list elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		return _head.GetCount();
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for const objects.
	/// <B> This is very ineffective on a list - better use iterators! </B>
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												List element.
	//----------------------------------------------------------------------------------------
	const T& operator [](Int idx) const
	{
		return *_head.GetElement(idx);
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for non-const objects.
	/// <B> This is very ineffective on a list - better use iterators! </B>
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												List element.
	//----------------------------------------------------------------------------------------
	// this is duplicate code but casting constness away for this case is plain ugly
	T& operator [](Int idx)
	{
		return *_head.GetElement(idx);
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the list.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append()
	{
		NODE* node = MAXON_SAFE_PLACEMENT_NEW(AllocNode()) NODE();
		return node ? InsertNode(End(), node) : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the list and initializes it with a copy of x.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(const T& x)
	{
		NODE* node = (NODE*) AllocNode();

		if (TestForCopyFromMember<T>::isSupported)
		{
			MAXON_SAFE_PLACEMENT_NEW(node) NODE();
			if (AssignCopy(*node->_GetData(), x) == false)				// copy failed?
			{
				DeleteNode(node);
				node = nullptr;
			}
		}
		else																										// use trivial copy constructor
		{
			MAXON_SAFE_PLACEMENT_NEW(node) NODE(x);
		}

		return node ? InsertNode(End(), node) : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the list and moves the content of x to it.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(T&& x)
	{
		NODE* node = MAXON_SAFE_PLACEMENT_NEW(AllocNode()) NODE(std::move(x));
		return node ? InsertNode(End(), node) : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// BaseList specific: Adds a new list node at the end of the list.
	/// @param[in] node								Pointer to new list node (BaseList will take ownership of it)
	/// @return												Element pointer or nullptr (in this case x is still valid)
	//----------------------------------------------------------------------------------------
	T* AppendNode(NODE* node)
	{
		return InsertNode(End(), node);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at index position. <B> Use the iterator based Insert() below! </B>
	/// This is compatible to the arrays but slow because Insert() has to iterate over the list
	/// to find the element corresponding to the index position.
	/// @param[in] position						Insert index.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position)
	{
		Iterator it(_head.GetNode(position));
		return it.IsValid() ? Insert(it).GetPtr() : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at iterator position.
	/// @param[in] position						Insert position.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position)
	{
		NODE* node = MAXON_SAFE_PLACEMENT_NEW(AllocNode()) NODE();
		if (node)
			InsertNode(position, node);
		return Iterator(node);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and initializes it with a copy of x. <B> Use the iterator based Insert() below! </B>
	/// This is compatible to the arrays but slow because Insert() has to iterate over the list.
	/// @param[in] position						Insert index.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T& x)
	{
		Iterator it(_head.GetNode(position));
		return it.IsValid() ? Insert(it, x).GetPtr() : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and initializes it with a copy of x.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be copied.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T& x)
	{
		NODE* node = (NODE*) AllocNode();

		if (TestForCopyFromMember<T>::isSupported)
		{
			MAXON_SAFE_PLACEMENT_NEW(node) NODE();
			if (AssignCopy(*node->_GetData(), x) == false)				// copy failed?
			{
				DeleteNode(node);
				node = nullptr;
			}
		}
		else																										// use trivial copy constructor
		{
			MAXON_SAFE_PLACEMENT_NEW(node) NODE(x);
		}

		if (node)
			InsertNode(position, node);
		return Iterator(node);
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and moves the content of x to it. <B> Use the iterator based Insert() below! </B>
	/// This is compatible to the arrays but slow because Insert() has to iterate over the list.
	/// @param[in] position						Insert index.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, T&& x)
	{
		Iterator it(_head.GetNode(position));
		return it.IsValid() ? Insert(it, std::move(x)).GetPtr() : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and moves the content of x to it.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be moved.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, T&& x)
	{
		NODE* node = MAXON_SAFE_PLACEMENT_NEW(AllocNode()) NODE(std::move(x));
		if (node)
			InsertNode(position, node);
		return Iterator(node);
	}

	//----------------------------------------------------------------------------------------
	/// BaseList specific: Inserts a new list node at iterator position.
	/// @param[in] position						Insert position.
	/// @param[in] node								Pointer to new list node (BaseList will take ownership of it)
	/// @return												Iterator for the new element (IsValid() == false if something failed, in this case x is still valid)
	//----------------------------------------------------------------------------------------
	T* InsertNode(Iterator position, NODE* node)
	{
		node->InsertBefore(position.GetNode());
		return node->_GetData();
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at index position. <B> Use the iterator based Insert() below! </B>
	/// This is compatible to the arrays but slow because Insert() has to iterate over the list.
	/// @param[in] position						Insert index.
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T* x, Int insertCnt)
	{
		NODE* node = _head.GetNode(position);
		return node ? Insert(Iterator(node), x, insertCnt).GetPtr() : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at iterator position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert position.
	/// @param[in] x									List with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T* x, Int insertCnt)
	{
		for (Int i = insertCnt - 1; i >= 0; i--)
		{
			Iterator next = position;

			if (x)
				position = Insert(next, x[i]);
			else
				position = Insert(next);

			if (position.IsValid() == false)											// insertion failed (not enough memory)?
			{
				for (i = insertCnt - 1 - i; i > 0; i--)
					next = Erase(next);																// remove the already inserted elements

				DebugStop();
				break;
			}
		}

		return position;
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements. <B> Use the iterator based Erase() below! </B>
	/// This is compatible to the arrays but slow because Erase() has to iterate over the list.
	/// @param[in] position						Index (Erase() will fail if out of bounds and return nullptr)
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Pointer to the element that is now at position or nullptr (no more element at position, either because position is out of bounds or the last element was erased)
	//----------------------------------------------------------------------------------------
	T* Erase(Int position, Int eraseCnt = 1)
	{
		NODE* node = _head.GetNode(position);
		T* element = node ? Erase(Iterator(node), eraseCnt).GetPtr() : nullptr;
		return (element != End().GetPtr()) ? element : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements.
	/// @param[in] position						Erase position.
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Iterator for the element that is now at position (IsValid() == false if something failed)
	//----------------------------------------------------------------------------------------
	Iterator Erase(Iterator position, Int eraseCnt)
	{
		for (Int i = 0; i < eraseCnt; i++)
		{
			if (position == End())
			{
				position = Iterator();															// set invalid iterator to signal an error
				DebugStop();
				break;
			}
			position = Erase(position);
		}

		return position;
	}

	Iterator Erase(Iterator position)
	{
		NODE* node = position.GetNode();
		position++;
		DeleteNode(node);

		return position;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the list.
	/// @return												Pointer to the first element (null if the list is empty)
	//----------------------------------------------------------------------------------------
	const T* GetFirst() const
	{
		return _head.GetFirst();
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the list.
	/// @return												Pointer to the first element (null if the list is empty)
	//----------------------------------------------------------------------------------------
	T* GetFirst()
	{
		return _head.GetFirst();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the last element.
	/// @return												Last element or nullptr.
	//----------------------------------------------------------------------------------------
	const T* GetLast() const
	{
		return _head.GetLast();
	}

	//----------------------------------------------------------------------------------------
	/// Gets the last element.
	/// @return												Last element or nullptr.
	//----------------------------------------------------------------------------------------
	T* GetLast()
	{
		return _head.GetLast();
	}

	//----------------------------------------------------------------------------------------
	/// Resizes the list to contain newCnt elements
	/// If newCnt is smaller than GetCount() all extra elements are being deleted. If it is
	/// greater the list is expanded and the default constructor is called for new elements.
	/// @param[in] newCnt							New list size.
	/// @return												False if allocation failed.
	//----------------------------------------------------------------------------------------
	Bool Resize(Int newCnt)
	{
		Int	cnt = GetCount();
		Int	increment = newCnt - cnt;
		Bool	success = false;

		if (increment <= 0)																			// decrease list size?
		{
			if (newCnt >= 0)
			{
				for (Iterator it = --End(); increment != 0; increment++)
					Erase(it--);

				success = true;
			}
			else
				DebugStop();
		}
		else																										// increase list size
		{
			for (; increment > 0; increment--)
			{
				if (Append() == nullptr)
					break;
			}
			success = increment == 0;
		}

		return success;
	}

	//----------------------------------------------------------------------------------------
	/// Deletes the last element.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool  Pop(T* dst = nullptr)
	{
		Iterator it = End();
		if (it != Begin())
		{
			--it;
			if (dst)
				*dst = std::move(*it);															// call move constructor if available

			Erase(it);
			return true;
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// BaseList specific:  Removes the last node and returns the pointer to it.
	/// @param[out] dst								Used to return pointer to the last node (must not be null), the caller will take ownership of the node.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool  PopNode(NODE** dst)
	{
		Iterator it = End();
		if (it != Begin())
		{
			--it;
			it.GetNode()->Remove();
			*dst = it.GetNode();
			return true;
		}
		*dst = nullptr;
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the index of element. The element must be part of the list, otherwise (e.g. if x is
	/// a copy of a list element) InvalidArrayIndex will be returned.
	/// This is compatible to the arrays but slow because GetIndex() has to iterate over the list.
	/// @return												Index of element or InvalidArrayIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T& x) const
	{
		return _head.GetIndex(&x);
	}

	//----------------------------------------------------------------------------------------
	/// BaseList specific:			Removes the node and returns a pointer to it.
	/// @param[in] position						Position of the element to be removed.
	/// @return												Node pointer or null, the caller will take ownership of it.
	//----------------------------------------------------------------------------------------
	static NODE* RemoveNode(Iterator position)
	{
		NODE* node = nullptr;
		if (position.IsValid())
		{
			node = position.GetNode();
			node->Remove();
		}
		return node;
	}

	//----------------------------------------------------------------------------------------
	/// BaseList specific:			Removes the node and returns a pointer to it.
	/// @param[in] x									The element to be removed.
	/// @return												Node pointer or null, the caller will take ownership of it.
	//----------------------------------------------------------------------------------------
	static NODE* RemoveNode(T* x)
	{
		return RemoveNode(Iterator(x));
	}

	//----------------------------------------------------------------------------------------
	/// Swaps elements a and b (just changes the pointers, more efficient than global Swap(list[a], list[b])
	/// @param[in] a									Position of element to be swapped.
	/// @param[in] b									Position of element to be swapped.
	//----------------------------------------------------------------------------------------
	void Swap(Iterator a, Iterator b)
	{
		NODE*	aNode = a.GetNode();
		NODE*	bNode = b.GetNode();
		NODE* aNext = aNode->_GetNext();
		NODE* bNext = bNode->_GetNext();

		if (aNext == bNode)																			// b is directly behind a?
		{
			bNode->Remove();
			bNode->InsertBefore(aNode);
		}
		else if (bNext == aNode)																// a is directly behind b?
		{
			aNode->Remove();
			aNode->InsertBefore(bNode);
		}
		else																										// a and b are not directly linked
		{
			aNode->Remove();
			bNode->Remove();

			bNode->InsertBefore(aNext);
			aNode->InsertBefore(bNext);
		}
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the list Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the list is empty)
	//----------------------------------------------------------------------------------------
	ConstIterator Begin() const
	{
		return ConstIterator(_head.Begin());
	}

	ConstIterator begin() const
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the list Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the list is empty)
	//----------------------------------------------------------------------------------------
	Iterator Begin()
	{
		return Iterator(_head.Begin());
	}

	Iterator begin()
	{
		return Begin();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the list is not empty)
	/// For the BaseList End() is in fact a constant value, it won't change even if you insert
	/// or remove elements. That's different from all arrays (where End() will change when you
	/// modify the array).
	/// @return												Iterator for the list end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	ConstIterator End() const
	{
		return ConstIterator(_head.End());
	}

	ConstIterator end() const
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the list is not empty)
	/// For the BaseList End() is in fact a constant value, it won't change even if you insert
	/// or remove elements. That's different from all arrays (where End() will change when you
	/// modify the array).
	/// @return												Iterator for the list end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	Iterator End()
	{
		return Iterator(_head.End());
	}

	Iterator end()
	{
		return End();
	}

	//----------------------------------------------------------------------------------------
	///	The BaseList iterator internally is a pointer to the NODE containing the data of
	/// type T and using it to iterate over a list or parts of it is as efficient as using a
	/// real pointer to the list nodes (for more ease of use you may want to invoke this via AutoIterator).
	///
	/// As already said you can use an Iterator almost like a pointer, e.g.
	/// @code
	/// it++;								// go to the next element
	/// it--;								// go to the previous element
	/// it += 5;						// advance by 5 elements
	/// it -= 3;						// go back 3 elements
	/// cnt = itB - itA;		// number of elements from itA to itB
	/// it = list.Begin();	// iterator to the first element of the list
	/// *it = value;				// assign value to the elements referenced by the iterator
	/// value = *it;				// get value of the element referenced by the iterator
	/// @endcode
	///
	/// Please note that using a postfix operator access (*it++ or *it--) can be slower than
	/// using the prefix form or a separate assignment. E.g.
	/// @code	value = *it++; @endcode is most likely slower than
	/// @code	value = it; ++it; @endcode or @code	value = it; it++; @endcode
	///	because *it++ requires a temporary copy of the iterator that the compiler may not
	/// be able to remove during optimization. As long as you only use the iterator's postfix
	/// operator without assignment it should be fine because the compiler will remove the
	/// temporary copy.
	//----------------------------------------------------------------------------------------
	template <Bool CONSTITERATOR> class IteratorTemplate
	{
	public:
		// For a const iterator, the BaseList, its values and its nodes have to be const within the iterator, otherwise they are non-const.
		// These typedefs have to be used throughout the iterator code instead of just BaseList, NODE or T.
		typedef typename ConstIf<CONSTITERATOR, BaseList>::Type CollectionType;
		typedef typename ConstIf<CONSTITERATOR, T>::Type ValueType;
		typedef typename ConstIf<CONSTITERATOR, NODE>::Type NodeType;
		static const Bool isLinearIterator = false;

		explicit IteratorTemplate(CollectionType& l) : _node(l._head.Begin())
		{
		}
		// NODE can be the same as T, therefore just one constructor for the iterator
		explicit IteratorTemplate(NodeType* pos = nullptr) : _node(pos)
		{
		}
		IteratorTemplate(const IteratorTemplate& src) : _node(src._node)
		{
		}
		IteratorTemplate& operator =(const IteratorTemplate& src)
		{
			_node = src._node;																		// self assignment is no problem here, therefore no check if (this != &src)
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

		ValueType* GetPtr() const
		{
			return _node->_GetData();
		}

		//----------------------------------------------------------------------------------------
		/// @return												true if the iterator points to an element (Iterator().IsValid() will return false)
		//----------------------------------------------------------------------------------------
		Bool IsValid() const
		{
			return _node != nullptr;
		}

		ValueType& operator *() const
		{
			return *_node->_GetData();
		}
		ValueType* operator ->() const
		{
			return _node->_GetData();
		}

		Bool operator ==(const IteratorTemplate& b) const
		{
			return _node == b._node;
		}
		Bool operator !=(const IteratorTemplate& b) const
		{
			return _node != b._node;
		}

		IteratorTemplate& operator ++()																	// prefix operator ++ (increment and fetch)
		{
			_node = _node->_GetNext();
			return *this;
		}
		const IteratorTemplate operator ++(int)													// postfix operator ++ (fetch and increment)
		{
			NodeType* tmp = _node;
			_node = _node->_GetNext();
			return IteratorTemplate(tmp);																	// use RVO
		}

		IteratorTemplate& operator --()																	// prefix operator -- (decrement and fetch)
		{
			_node = _node->_GetPrev();
			return *this;
		}
		const IteratorTemplate operator --(int)													// postfix operator -- (fetch and decrement)
		{
			NodeType* tmp = _node;
			_node = _node->_GetPrev();
			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate operator +(Int i) const												// operator +
		{
			NodeType* tmp = _node;

			for (; i > 0; i--)
				tmp = tmp->_GetNext();

			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate operator -(Int i) const
		{
			NodeType* tmp = _node;

			for (; i > 0; i--)
				tmp = tmp->_GetPrev();

			return IteratorTemplate(tmp);																	// use RVO
		}
		NodeType* GetNode() const
		{
			return _node;
		}
	private:
		NodeType* _node;
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
	void*	AllocNode()
	{
		return this->Alloc(SIZEOF(NODE), MAXON_SOURCE_LOCATION);
	}
	void	DeleteNode(NODE* node)
	{
		node->~NODE();																						// will implicitely call Remove()
		this->Free(node);
	}

	HEAD	_head;
};


/// This supports c4d style list code that iterates through a list with GetNext()/GetPrev() and stops when null is returned
template <typename T> class BaseListLegacyNode
{
	typedef BaseListNode<T> NODE;
public:
	/// Returns the pointer to the next element or null (this is the last element of the list)
	T*	GetNext() const
	{
		// The data of type T might be somewhere in the NODE. Since offsetof() is a nogo and
		// NODE might contain virtual stuff we have to get this offset the hard way. Since
		// some compilers try to be mighty clever the dummy pointer must not be 0.
		static const NODE* dummy = (NODE*) sizeof(void*);
		static const Int offset = Int(dummy->_GetData()) - Int(dummy);
		NODE* node = (NODE*) (Int(this) - offset);
		NODE*	next = node->_GetNext();
		return next->IsListHead() ? nullptr : (T*) (Int(next) + offset);
	}

	/// Returns the pointer to the previous element or null (this is the first element of the list)
	T*	GetPrev() const
	{
		// The data of type T might be somewhere in the NODE. Since offsetof() is a nogo and
		// NODE might contain virtual stuff we have to get this offset the hard way. Since
		// some compilers try to be mighty clever the dummy pointer must not be 0.
		static const NODE* dummy = (NODE*) sizeof(void*);
		static const Int offset = Int(dummy->_GetData()) - Int(dummy);
		NODE* node = (NODE*) (Int(this) - offset);
		NODE*	prev = node->_GetPrev();
		return prev->IsListHead() ? nullptr : (T*) (Int(prev) + offset);
	}
};

/// Use this macro to implement custom BaseListNodes where T and NODE are equal.
/// NODE is the name of the class and linkPtr is the address of the BaseListLinkPOD.
/// <B> Don't forget that your custom node must have a destructor which has to call this->Remove(). </B>
#define IMPLEMENT_CUSTOM_BASELISTNODE(NODE, linkPtr) \
friend class BaseList<NODE, NODE>; \
typedef BaseListLink<NODE> Link;	\
void	Remove()										{ Link::Remove(this); }	\
void	InsertBefore(NODE* next)		{ Link::InsertBefore(this, next); }		\
NODE*	_GetNext() const						{ return ((Link*)linkPtr)->_GetNext(); }	\
NODE*	_GetPrev() const						{ return ((Link*)linkPtr)->_GetPrev(); }	\
void	SetNext(NODE* val)					{ ((Link*)linkPtr)->SetNext(val); }	\
void	SetPrev(NODE* val)					{ ((Link*)linkPtr)->SetPrev(val); }	\
Bool	IsListHead() const					{ return ((Link*)linkPtr)->IsListHead(); }	\
NODE*	_GetData() const						{ return (NODE*) this; }	\
BaseListLinkPOD* _GetLink() const	{ return (Link*) linkPtr; }




/// @}

} // namespace maxon

#endif	// BASELIST_H__
