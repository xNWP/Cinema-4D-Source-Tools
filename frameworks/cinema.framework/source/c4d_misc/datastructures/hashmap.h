#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(HASHMAP_H__)
#define HASHMAP_H__

#include "../memory/defaultallocator.h"
#include "collection.h"

namespace maxon
{

class EmptyClass
{
};

/// @addtogroup group_maxondatastructures
/// @{

/// Marker class to be used as template argument for HashMap for the usual case when the values don't contain the keys (so the HashMap has to store key-value-pairs).
class HashMapKeyValuePair
{
};

/// Base class for HashMap::Entry.
template <typename K, typename V, typename GET_KEY> class HashMapEntryBase
{
public:
	//----------------------------------------------------------------------------------------
	/// Returns this entry's key.
	/// @return												Key of this entry.
	//----------------------------------------------------------------------------------------
	const K& GetKey() const
	{
		return GET_KEY::GetKey(_value);
	}

	//----------------------------------------------------------------------------------------
	/// Returns this entry's value.
	/// @return												Value of this entry.
	//----------------------------------------------------------------------------------------
	V& GetValue()
	{
		return _value;
	}

	//----------------------------------------------------------------------------------------
	/// Returns this entry's value.
	/// @return												Value of this entry.
	//----------------------------------------------------------------------------------------
	const V& GetValue() const
	{
		return _value;
	}

	//----------------------------------------------------------------------------------------
	/// Sets the value of this entry by copy assignment.
	/// @param[in] value							New value.
	//----------------------------------------------------------------------------------------
	void SetValue(const V& value)
	{
		_value = value;
	}

	//----------------------------------------------------------------------------------------
	/// Sets the value of this entry by move assignment.
	/// @param[in] value							New value.
	//----------------------------------------------------------------------------------------
	void SetValue(V&& value)
	{
		_value = std::move(value);
	}

protected:
	HashMapEntryBase(const K& key)
	{
	}

	template <typename A> HashMapEntryBase(const K& key, const A& value): _value(value)
	{
	}

private:
	MAXON_DISALLOW_COPY_AND_ASSIGN(HashMapEntryBase);
	V _value;
};

template <typename K, typename V> class HashMapEntryBase<K, V, HashMapKeyValuePair>
{
public:
	const K& GetKey() const
	{
		return _key;
	}

	V& GetValue()
	{
		return _value;
	}

	const V& GetValue() const
	{
		return _value;
	}

	void SetValue(const V& value)
	{
		_value = value;
	}

	void SetValue(V&& value)
	{
		_value = std::move(value);
	}

protected:
	HashMapEntryBase(const K& key): _key(key)
	{
	}

	template <typename A> HashMapEntryBase(const K& key, const A& value): _key(key), _value(value)
	{
	}

private:
	MAXON_DISALLOW_COPY_AND_ASSIGN(HashMapEntryBase);
	const K _key;
	V _value;
};

template <typename K> class HashMapEntryBase<K, EmptyClass, HashMapKeyValuePair>
{
public:
	const K& GetKey() const
	{
		return _key;
	}

	EmptyClass& GetValue()
	{
		return *(EmptyClass*) this;
	}

	const EmptyClass& GetValue() const
	{
		return *(const EmptyClass*) this;
	}

	void SetValue(const EmptyClass&)
	{
	}

protected:
	HashMapEntryBase(const K& key): _key(key)
	{
	}

	template <typename A> HashMapEntryBase(const K& key, const A& value): _key(key)
	{
	}

private:
	MAXON_DISALLOW_COPY_AND_ASSIGN(HashMapEntryBase);
	const K _key;
};


//----------------------------------------------------------------------------------------
/// A HashMap maps keys to values with the help of hash codes for the keys.
/// It expects a function static UInt HASH::GetHashCode(const K&) in the class HASH (given as template argument) to compute a hash code for a key,
/// and then it uses the lower bits of the hash code as an index into a table of buckets.
/// Each bucket contains a singly linked list of entries (key-value-pairs) having the same lower bits,
/// and the function static maxon::Bool HASH::IsEqual(const K&, const K&) is used to find the entry with matching key, if any.
/// By default, DefaultHash is used for HASH, this handles keys of integral type, pointers and objects which have a GetHashCode member function
/// themselves as well as the == operator. For other keys, you have to define your own class for HASH, see CStringHash as an example.
///
/// This example uses a HashMap to store String values addressed by Int keys:
/// @code
/// typedef HashMap<Int, String> IntStringMap;
/// IntStringMap map;
/// ...
/// // now store "Hello World" at key 42
/// maxon::Bool created = false;
/// IntStringMap::Entry* e = map.FindOrCreateEntry(42, created);
/// if (!e) ... allocation failed ...;
/// if (created) // if created is false, there already exists an entry for 42 in the map
/// {
///   // initialize the new value
///   e->SetValue(CONSTSTRING("Hello World"));
/// }
/// ...
/// // now check if there is an entry at key 42
/// IntStringMap::Entry* e = map.FindEntry(42);
/// if (e)
/// {
///   DiagnosticOutput(CONSTSTRING("Found value ") + e->GetValue());
/// }
/// @endcode
///
/// Instead of FindOrCreateEntry(), you can also use Put() if you don't need to differentiate between the cases whether the entry existed
/// before or not:
/// @code
/// IntStringMap::Entry* e = map.Put(42, CONSTSTRING("Hello World"));
/// if (!e) ... allocation failed ...;
/// @endcode
///
/// The larger the table of buckets, the less is the chance of several entries within a single bucket.
/// The HashMap uses a load factor to automatically double the size of the table if the number of entries exceeds
/// the table size multiplied by the load factor (re-hashing). So with a load factor of 0.5 there are at most half as many entries
/// as there are buckets, and then with evenly distributed hash codes there is only a negligible number
/// of buckets with more than one entry. The default load factor is 0.65. If you use a load factor <= 0, the
/// automatic increase of table size is switched off, thus the HashMap will keep the initial size of the table.
///
/// A HashMap performs the map operations in constant time if the hash function computes evenly distributed
/// hash codes for the keys.
///
/// There are applications of the HashMap where the values already contain the keys (e.g., think of a map
/// from names to objects, and the objects know their names). Then it might be wasteful to store the keys
/// again in the HashMap entries. In such a case, you have to specify a class as argument for the template
/// parameter GET_KEY which contains the function static const K& GET_KEY::GetKey(const V&). This function
/// will be used to extract keys from values. You also have to make sure that each HashMap entry has a valid
/// value. I.e., when you have added a new entry with FindOrCreateEntry(), then you have to initialize it with
/// a value whose key is the same key as the one used for FindOrCreateEntry().
///
/// If you want to iterate over the entries of a HashMap, you can either use #Iterator or #ConstIterator,
/// or you can use GetNonEmptyBucketCount() and GetNonEmptyBucket() to loop over the non-empty buckets,
/// and then HashMap::Entry::GetNextInBucket() to run through the entries of a bucket.
/// @code
/// for (IntStringMap::ConstIterator i = map.Begin(); i != map.End(); ++i)
/// {
///   DiagnosticOutput(String::IntToString(i->GetKey()) + CONSTSTRING(" => ") + i->GetValue());
/// }
/// @endcode
///
/// @tparam K											Type of keys.
/// @tparam V											Type of values.
/// @tparam HASH									Class to be used to compute the hash code of keys, and to compare keys for equality (DefaultHash by default)
/// @tparam GET_KEY								Use this class if the keys shall be extracted from values, rather than being stored separately.
/// 															With the default argument HashMapKeyValuePair, keys and values are stored separately in the entries as key-value-pairs.
/// @tparam ALLOCATOR							Class for memory allocation.
//----------------------------------------------------------------------------------------
template <typename K, typename V, typename HASH = maxon::DefaultHash, typename GET_KEY = maxon::HashMapKeyValuePair, typename ALLOCATOR = maxon::DefaultAllocator> class HashMap
{
public:
	class Entry;

	typedef V ValueType;

	//----------------------------------------------------------------------------------------
	/// Constructs a new HashMap with an optional load factor.
	/// This will not allocate any memory. Memory allocation can be done explicitly by Init(), or it will be done implicitly when needed.
	/// @param[in] loadFactor					The load factor of the HashMap.
	//----------------------------------------------------------------------------------------
	HashMap(Float loadFactor = Float(0.65)): _table(nullptr), _nonemptyBuckets(nullptr), _nonemptyBucketCount(0), _size(0), _loadFactor(loadFactor)
	{
	}

	//----------------------------------------------------------------------------------------
	/// Initializes the underlying allocator and constructs a new HashMap with an optional load factor.
	/// This will not allocate any memory. Memory allocation can be done explicitly by Init(), or it will be done implicitly when needed.
	/// @param[in] alloc							Used to initialize the underlying allocator by its copy constructor.
	/// @param[in] loadFactor					The load factor of the HashMap.
	//----------------------------------------------------------------------------------------
	HashMap(const ALLOCATOR& alloc, Float loadFactor = Float(0.65)): _allocator(alloc), _table(nullptr), _nonemptyBuckets(nullptr), _nonemptyBucketCount(0),
		_size(0), _loadFactor(loadFactor)
	{
	}

	/// Destructs all entries and frees any allocated memory
	~HashMap()
	{
		Reset();
	}

	//----------------------------------------------------------------------------------------
	/// Resets the HashMap and initializes the table of buckets.
	/// This will destruct and free all existing entries at first, and then it will allocate a table of buckets
	/// which is large enough to hold at least capacity entries, taking into account the load factor
	/// (see explanation of the class HashMap itself).
	/// If you don't invoke Init() explicitly, it will be invoked implicitly with a default capacity of 20 when the first entry has to be added.
	/// @param[in] capacity						The required capacity of entries which can be stored without the need for re-hashing.
	/// @return												True iff memory allocations succeeded.
	//----------------------------------------------------------------------------------------
	Bool Init(Int capacity = 20)
	{
		Reset();
		if (_loadFactor > 0)
		{
			capacity = (Int) ((capacity + 1) / _loadFactor) + 2;
		}
		Int c = 1;
		while (c < capacity)
		{
			c <<= 1;
		}
		_resizeThreshold = (_loadFactor > 0) ? (Int) (c * _loadFactor) : LIMIT<Int>::MAX;
		_tableLengthM1 = c - 1;
//			table = allocator.template AllocArray<Bucket>(c);
		_table = (Bucket*) _allocator.Alloc((Int) c * SIZEOF(Bucket), MAXON_SOURCE_LOCATION);
		if (!_table)
		{
			return false;
		}
		ClearMemType(_table, (Int) c);
//			nonEmptyBuckets = allocator.template AllocArray<Int>(c);
		_nonemptyBuckets = (Bucket**) _allocator.Alloc((Int) c * SIZEOF(Bucket*), MAXON_SOURCE_LOCATION);
		if (!_nonemptyBuckets)
		{
			_allocator.Free(_table);
			_table = nullptr;
			return false;
		}
		return true;
	}

	/// Resets the map. This destructs all entries and frees any memory held by the map, so the map
	/// will be in a state as if it had been newly constructed.
	/// @sa Flush()
	void Reset()
	{
		Flush();
		_allocator.Free(_table);
		_table = nullptr;
		_allocator.Free(_nonemptyBuckets);
		_nonemptyBuckets = nullptr;
	}

	/// Flushes the map. This destructs and frees all entries, but does not free the bucket table.
	/// @sa Reset()
	void Flush()
	{
		if (!_table)
		{
			return;
		}
		for (Int b = 0; b < _nonemptyBucketCount; b++)
		{
			Entry* e, * next;
			for (e = _nonemptyBuckets[b]->list; e; e = next)
			{
				next = e->_next;
				DeleteEntry(e);
			}
		}
		ClearMemType(_table, (Int) _tableLengthM1 + 1);
		_size = 0;
		_nonemptyBucketCount = 0;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the number of entries in this map.
	/// @return												Number of entries.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		return _size;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the number of non-empty buckets in this map.
	/// This can be used together with GetNonEmptyBucket() to iterate over non-empty buckets.
	/// @return												Number of non-empty buckets.
	//----------------------------------------------------------------------------------------
	Int GetNonEmptyBucketCount() const
	{
		return _nonemptyBucketCount;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the i-th non-empty bucket of this map.
	/// @param[in] i									Index into the list of non-empty buckets (from 0 to GetNonEmptyBucketCount() - 1)
	/// @return												I-th non-empty bucket.
	//----------------------------------------------------------------------------------------
	Entry* GetNonEmptyBucket(Int i)
	{
		DebugAssert((UInt) i < (UInt) _nonemptyBucketCount);
		return _nonemptyBuckets[i]->list;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the i-th non-empty bucket of this map.
	/// @param[in] i									Index into the list of non-empty buckets (from 0 to GetNonEmptyBucketCount() - 1)
	/// @return												I-th non-empty bucket.
	//----------------------------------------------------------------------------------------
	const Entry* GetNonEmptyBucket(Int i) const
	{
		DebugAssert((UInt) i < (UInt) _nonemptyBucketCount);
		return _nonemptyBuckets[i]->list;
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key in this map.
	/// @param[in] key								Key to search for.
	/// @return												Entry having the given key, or nullptr if no such entry exists in this map.
	//----------------------------------------------------------------------------------------
	Entry* FindEntry(const K& key)
	{
		if (!_table)
		{
			return nullptr;
		}
		for (Entry* e = _table[HASH::GetHashCode(key) & (UInt) _tableLengthM1].list; e; e = e->_next)
		{
			if (HASH::IsEqual(key, e->GetKey()))
			{
				return e;
			}
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key in this map.
	/// @param[in] key								Key to search for.
	/// @return												Entry having the given key, or nullptr if no such entry exists in this map.
	//----------------------------------------------------------------------------------------
	const Entry* FindEntry(const K& key) const
	{
		return const_cast<HashMap*>(this)->FindEntry(key);
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key in this map. Unlike FindEntry(const K&), this function allows you to
	/// use a key of a type different from the map's key type K. You have to specify an additional
	/// class KEYHASH to compute the hash code of the specified key (function KEYHASH::GetHashCode(const KEY&)),
	/// and to compare a key of type KEY with a key of type K for equality (function KEYHASH::IsEqual(const KEY&, const K&)).
	/// @tparam KEY										Type of key.
	/// @tparam KEYHASH								Hash class to compute the hash code of key, and to compare key with the map's keys.
	/// @param[in] key								Key to search for.
	/// @return												Entry having the given key, or nullptr if no such entry exists in this map.
	//----------------------------------------------------------------------------------------
	template <typename KEY, typename KEYHASH> Entry* FindEntry(const KEY& key)
	{
		if (!_table)
		{
			return nullptr;
		}
		for (Entry* e = _table[KEYHASH::GetHashCode(key) & (UInt) _tableLengthM1].list; e; e = e->_next)
		{
			if (KEYHASH::IsEqual(key, e->GetKey()))
			{
				return e;
			}
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key in this map. Unlike FindEntry(const K&), this function allows you to
	/// use a key of a type different from the map's key type K. You have to specify an additional
	/// class KEYHASH to compute the hash code of the specified key (function KEYHASH::GetHashCode(const KEY&)),
	/// and to compare a key of type KEY with a key of type K for equality (function KEYHASH::IsEqual(const KEY&, const K&)).
	/// @tparam KEY										Type of key.
	/// @tparam KEYHASH								Hash class to compute the hash code of key, and to compare key with the map's keys.
	/// @param[in] key								Key to search for.
	/// @return												Entry having the given key, or nullptr if no such entry exists in this map.
	//----------------------------------------------------------------------------------------
	template <typename KEY, typename KEYHASH> const Entry* FindEntry(const KEY& key) const
	{
		return const_cast<HashMap*>(this)->FindEntry<KEY, KEYHASH>(key);
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key, or creates such an entry if it doesn't exist yet.
	/// If a new entry has to be created, it is constructed with the help of the object passed to the constructor
	/// parameter: Its class C has to provide a function C::ConstructHashMapEntry(void* ptr, const K& key) which uses
	/// the memory in ptr to construct a new entry for the key.
	/// If the constructor does not initialize the value of the new entry, this has to be done afterwards.
	/// @tparam C											Type of the constructor argument.
	/// @param[in] key								Key of the entry to find or create.
	/// @param[in] constructor				Constructor.ConstructHashMapEntry(ptr, key) will be used to construct a new entry from the memory in ptr.
	/// @param[out] created						This will be set to true if a new entry has been created successfully, otherwise it will be set to false.
	/// @return												Entry for the given key, or nullptr if the entry didn't exist and allocation of a new entry failed.
	//----------------------------------------------------------------------------------------
	template <typename C> Entry* FindOrCreateEntry(const K& key, C& constructor, maxon::Bool& created)
	{
		if ((_table == nullptr) && !Init())
		{
			created = false;
			return nullptr;
		}
		UInt h = HASH::GetHashCode(key) & (UInt) _tableLengthM1;
		for (Entry* e = _table[h].list; e; e = e->_next)
		{
			if (HASH::IsEqual(key, e->GetKey()))
			{
				created = false;
				return e;
			}
		}
//			e = allocator.template AllocType<Entry>();
		Entry* e = (Entry*) _allocator.Alloc(SIZEOF(Entry), MAXON_SOURCE_LOCATION);
		if (!e)
		{
			created = false;
			return nullptr;
		}
		e = constructor.ConstructHashMapEntry(e, key);
		e->_next = _table[h].list;
		if (e->_next == nullptr)
		{
			_table[h].nonemptyBucketsIndex = _nonemptyBucketCount;
			_nonemptyBuckets[_nonemptyBucketCount++] = _table + h;
		}
		_table[h].list = e;
		if (++_size > _resizeThreshold)
		{
			Int tlM1 = ((_tableLengthM1 + 1) << 1) - 1;
			//				Bucket* t = allocator.template AllocArray<Bucket>(tlM1 + 1);
			// TODO: (Ole) use code like this once the allocators support it (also below)
			Bucket* t = (Bucket*) _allocator.Alloc(SIZEOF(Bucket) * Int(tlM1 + 1), MAXON_SOURCE_LOCATION);
			if (t)
			{
				ClearMemType(t, Int(tlM1 + 1));
				//				Int* neb = allocator.template AllocArray<Int>(tlM1 + 1);
				Bucket** neb = (Bucket**) _allocator.Alloc(SIZEOF(Bucket*) * Int(tlM1 + 1), MAXON_SOURCE_LOCATION);
				if (!neb)
				{
					_allocator.Free(t);
				}
				else
				{
					_allocator.Free(_nonemptyBuckets);
					_nonemptyBuckets = neb;
					_nonemptyBucketCount = 0;
					for (Int j = 0; j <= _tableLengthM1; j++)
					{
						Entry* entry = _table[j].list;
						while (entry)
						{
							Entry* n = entry->_next;
							h = HASH::GetHashCode(entry->GetKey()) & (UInt) tlM1;
							entry->_next = t[h].list;
							if (entry->_next == nullptr)
							{
								t[h].nonemptyBucketsIndex = _nonemptyBucketCount;
								neb[_nonemptyBucketCount++] = t + h;
							}
							t[h].list = entry;
							entry = n;
						}
					}

					_allocator.Free(_table);
					_table = t;
					_tableLengthM1 = tlM1;
					_resizeThreshold = (Int) ((tlM1 + 1) * _loadFactor);
				}
			}
		}
		created = true;
		return e;
	}

private:
	struct DefaultEntryConstructor {static Entry* ConstructHashMapEntry(void* ptr, const K& key) {return new (ptr) Entry(key); }};

public:
	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key, or creates such an entry if it doesn't exist yet.
	/// The value of a new entry has to be initialized afterwards.
	/// @param[in] key								Key of the entry to find or create.
	/// @param[out] created						This will be set to true if a new entry has been created successfully, otherwise it will be set to false.
	/// @return												Entry for the given key, or nullptr if the entry didn't exist and allocation of a new entry failed.
	//----------------------------------------------------------------------------------------
	Entry* FindOrCreateEntry(const K& key, maxon::Bool& created)
	{
		return FindOrCreateEntry(key, *(DefaultEntryConstructor*) nullptr, created);
	}

	//----------------------------------------------------------------------------------------
	/// Finds the entry with the given key, or creates such an entry if it doesn't exist yet.
	/// If a new entry has to be created, it is constructed with the help of the object passed to the constructor
	/// parameter: Its class C has to provide a function C::ConstructHashMapEntry(void* ptr, const K& key) which uses
	/// the memory in ptr to construct a new entry for the key.
	/// If the constructor does not initialize the value of the new entry, this has to be done afterwards.
	/// @tparam C											Type of the constructor argument.
	/// @param[in] key								Key of the entry to find or create.
	/// @param[in] constructor				Constructor.ConstructHashMapEntry(ptr, key) will be used to construct a new entry from the memory in ptr.
	/// @return												Entry for the given key, or nullptr if the entry didn't exist and allocation of a new entry failed.
	//----------------------------------------------------------------------------------------
	template <typename C> Entry* FindOrCreateEntry(const K& key, C& constructor)
	{
		Bool created;
		return FindOrCreateEntry(key, constructor, created);
	}

	//----------------------------------------------------------------------------------------
	/// Associates the given value with the given key. This convenience function uses FindOrCreateEntry(const K&, Bool&) to
	/// obtain an entry for key, and then sets its value to the given value, whether the entry existed before or not.
	/// @param[in] key								Key which shall map to the value.
	/// @param[in] value							Value to which the key shall map.
	/// @return												Entry for the key-value-association, or nullptr if such an entry didn't exist before and allocation of a new entry failed.
	//----------------------------------------------------------------------------------------
	Entry* Put(const K& key, const V& value)
	{
		Bool created = false;
		Entry* e = FindOrCreateEntry(key, created);
		if (e)
		{
			e->SetValue(value);
		}
		return e;
	}

	//----------------------------------------------------------------------------------------
	/// Removes the given entry from this HashMap.
	/// @param[in] entry							The entry to remove.
	/// @return												True if the entry has been removed, or false if entry is nullptr or couldn't be found in the map.
	//----------------------------------------------------------------------------------------
	Bool Remove(const Entry* entry)
	{
		if (!entry || !_table)
		{
			return false;
		}
		UInt h = HASH::GetHashCode(entry->GetKey()) & (UInt) _tableLengthM1;
		Entry* prev = nullptr;
		for (Entry* e = _table[h].list; e; e = e->_next)
		{
			if (e == entry)
			{
				_size--;
				if (prev)
				{
					prev->_next = e->_next;
				}
				else
				{
					_table[h].list = e->_next;
					if (e->_next == nullptr)
					{
						Int i = _table[h].nonemptyBucketsIndex;
						if (i < --_nonemptyBucketCount)
						{
							(_nonemptyBuckets[i] = _nonemptyBuckets[_nonemptyBucketCount])->nonemptyBucketsIndex = i;
						}
					}
				}
				DeleteEntry(e);
				return true;
			}
			prev = e;
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Removes an entry with the given key from this HashMap (if possible).
	/// @param[in] key								An entry having this key shall be removed.
	/// @return												True iff an entry could be found for the key (in which case the entry has been removed)
	//----------------------------------------------------------------------------------------
	Bool Remove(const K& key)
	{
		if (!_table)
		{
			return false;
		}
		UInt h = HASH::GetHashCode(key) & (UInt) _tableLengthM1;
		Entry* prev = nullptr;
		for (Entry* e = _table[h].list; e; e = e->_next)
		{
			if (HASH::IsEqual(key, e->GetKey()))
			{
				_size--;
				if (prev)
				{
					prev->_next = e->_next;
				}
				else
				{
					_table[h].list = e->_next;
					if (e->_next == nullptr)
					{
						Int i = _table[h].nonemptyBucketsIndex;
						if (i < --_nonemptyBucketCount)
						{
							(_nonemptyBuckets[i] = _nonemptyBuckets[_nonemptyBucketCount])->nonemptyBucketsIndex = i;
						}
					}
				}
				DeleteEntry(e);
				return true;
			}
			prev = e;
		}
		return false;
	}


private:
	template <typename T> struct CopyFromConstructor
	{
		CopyFromConstructor(const T& v): value(v) {}
		const T& value;
		Entry* ConstructHashMapEntry(void* ptr, const K& key) {return new (ptr) Entry(key, value); }
	};

public:
	//----------------------------------------------------------------------------------------
	/// Adds all entries from src to this map. Existing entries will be kept, or they will be overwritten if src
	/// has an entry with equal key and the parameter overwrite is true.
	/// src has to be a data structure supported by AutoIterator (such as a HashMap or one of the array classes),
	/// and its values have to have GetKey() and GetValue() functions.
	/// If adding doesn't succeed for all entries, the map will be left in a valid, but intermediate state with only some entries from src added.
	/// @param[in] src								Source from which the entries are taken.
	/// @param[in] overwrite					Overwrite an existing entry if src has an entry with equal key?
	/// @return												True iff adding succeeded.
	//----------------------------------------------------------------------------------------
	template <typename S> Bool AddAll(const S& src, Bool overwrite = true)
	{
		for (AutoIterator<const S> it(src); it; it++)
		{
			CopyFromConstructor<typename S::ValueType> ctor((*it).GetValue());
			Bool created = false;
			Entry* e = FindOrCreateEntry((*it).GetKey(), ctor, created);
			if (!e)
			{
				return false;
			}
			if (!created && overwrite)
			{
				e->~Entry();
				new (e) Entry((*it).GetKey(), (*it).GetValue());
			}
		}
		return true;
	}

	//----------------------------------------------------------------------------------------
	/// Makes this map a copy of src. At first, this map is flushed, and then all entries of src are added to this map.
	/// src has to be a data structure supported by AutoIterator (such as a HashMap or one of the array classes),
	/// and its values have to have GetKey() and GetValue() functions.
	/// If copying doesn't succeed for all entries, the map will be left in a valid, but intermediate state with only some entries from src added.
	/// @param[in] src								Source from which the entries are taken.
	/// @return												True iff copying succeeded.
	//----------------------------------------------------------------------------------------
	template <typename S> Bool CopyFrom(const S& src)
	{
		Flush();
		return AddAll(src, false);
	}

	/// Class used for entries of the HashMap.
	/// The entries of a bucket are stored as a singly linked list, you can loop over this list via GetNextInBucket().
	class Entry: public HashMapEntryBase<K, V, GET_KEY>
	{
	private:
		typedef HashMapEntryBase<K, V, GET_KEY> Super;

	public:
		Entry(const K& key) : Super(key), _next(nullptr)
		{
		}

		template <typename A> Entry(const K& key, const A& valueInit) : Super(key, valueInit), _next(nullptr)
		{
		}

#if 0 // not needed at the moment (it is needed for a multi-map which allows more than one entry per key)
		Entry* GetNextWithSameKey()
		{
			for (Entry* e = _next; e; e = e->_next)
			{
				if (HASH::IsEqual(e->Super::GetKey(), Super::GetKey()))
				{
					return e;
				}
			}
			return nullptr;
		}
#endif

		//----------------------------------------------------------------------------------------
		/// Returns the next entry in the same bucket.
		/// @return												Next entry in bucket, or nullptr if this is the last entry.
		//----------------------------------------------------------------------------------------
		const Entry* GetNextInBucket() const
		{
			return _next;
		}

		//----------------------------------------------------------------------------------------
		/// Returns the next entry in the same bucket.
		/// @return												Next entry in bucket, or nullptr if this is the last entry.
		//----------------------------------------------------------------------------------------
		Entry* GetNextInBucket()
		{
			return _next;
		}

	private:
		MAXON_DISALLOW_COPY_AND_ASSIGN(Entry);
		friend class HashMap;

		Entry* _next;
	};


	template <Bool CONSTITERATOR> class IteratorTemplate;

	/// Iterator class for HashMap.
	typedef IteratorTemplate<false> Iterator;

	/// Iterator class for const HashMap.
	typedef IteratorTemplate<true> ConstIterator;

	/// Iterator template class, used for #Iterator and #ConstIterator.
	template <Bool CONSTITERATOR> class IteratorTemplate
	{
	public:
		// For a const iterator, both the HashMap and its entries have to be const within the iterator, otherwise they are non-const.
		// These typedefs have to be used throughout the iterator code instead of just HashMap or Entry.
		typedef typename ConstIf<CONSTITERATOR, HashMap>::Type CollectionType;
		typedef typename ConstIf<CONSTITERATOR, Entry>::Type ValueType;

		explicit IteratorTemplate(CollectionType& m) : _map(m), _bucket(0)
		{
			_entry = m.GetNonEmptyBucketCount() ? m.GetNonEmptyBucket(0) : nullptr;
		}

		explicit IteratorTemplate(CollectionType& m, Int b, ValueType* e) : _map(m), _bucket(b), _entry(e)
		{
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

		Bool operator ==(const IteratorTemplate& b) const
		{
			return _entry == b._entry;
		}
		Bool operator !=(const IteratorTemplate& b) const
		{
			return _entry != b._entry;
		}
		ValueType& operator *() const
		{
			return *_entry;
		}
		ValueType* operator ->() const
		{
			return _entry;
		}
		ValueType& GetEntry() const
		{
			return *_entry;
		}

		const K& GetKey() const
		{
			return GetEntry().GetKey();
		}

		typename ConstIf<CONSTITERATOR, V>::Type& GetValue() const
		{
			return GetEntry().GetValue();
		}

		IteratorTemplate& operator ++()																	// prefix operator++ (increment and fetch)
		{
			_entry = _entry->GetNextInBucket();
			if (!_entry)
			{
				++_bucket;
				if (_bucket < _map.GetNonEmptyBucketCount())
				{
					_entry = _map.GetNonEmptyBucket(_bucket);
				}
			}
			return *this;
		}

		const IteratorTemplate operator ++(int)													// postfix operator++ (fetch and increment)
		{
			const IteratorTemplate tmp(*this);
			++(*this);
			return tmp;
		}

	private:
		CollectionType& _map;
		Int _bucket;
		ValueType* _entry;

		void operator =(const IteratorTemplate& i);
	};


	Iterator Begin()
	{
		return Iterator(*this);
	}

	Iterator begin()
	{
		return Begin();
	}

	Iterator End()
	{
		return Iterator(*this, 0, nullptr);
	}

	Iterator end()
	{
		return End();
	}

	ConstIterator Begin() const
	{
		return ConstIterator(*this);
	}

	ConstIterator begin() const
	{
		return Begin();
	}

	ConstIterator End() const
	{
		return ConstIterator(*this, 0, nullptr);
	}

	ConstIterator end() const
	{
		return End();
	}

private:
	struct Bucket
	{
		Entry* list;
		Int nonemptyBucketsIndex;
	};

	void DeleteEntry(Entry* e)
	{
		e->~Entry();
		_allocator.Free(e);
	}

	void operator =(const HashMap& h);

	ALLOCATOR _allocator;
	Bucket* _table;
	Int _tableLengthM1;
	Bucket** _nonemptyBuckets;
	Int _nonemptyBucketCount;
	Int _size;
	Int _resizeThreshold;
	const Float _loadFactor;
};


template <typename V, typename HASH = DefaultHash, typename ALLOCATOR = DefaultAllocator> class HashSet: private HashMap<V, EmptyClass, HASH, HashMapKeyValuePair, ALLOCATOR>
{
private:
	typedef HashMap<V, EmptyClass, HASH, HashMapKeyValuePair, ALLOCATOR> Super;

public:
	typedef V ValueType;
	typedef SetOpsWithHash<HASH> Ops;

	HashSet(const ALLOCATOR& alloc, Float loadFactor = Float(0.65)): Super(alloc, loadFactor)
	{
	}

	HashSet(Float loadFactor = Float(0.65)): Super(loadFactor)
	{
	}

	using Super::Init;
	using Super::Reset;
	using Super::Flush;
	using Super::GetCount;

	template <typename H, typename A> Bool AddAll(const HashSet<V, H, A>& src)
	{
		return Super::AddAll(*static_cast<const HashMap<V, EmptyClass, H, HashMapKeyValuePair, A>*>(&src), false);
	}

	template <typename H, typename A> Bool CopyFrom(const HashSet<V, H, A>& src)
	{
		return Super::CopyFrom(*static_cast<const HashMap<V, EmptyClass, H, HashMapKeyValuePair, A>*>(&src));
	}

	Bool Contains(const V& value) const
	{
		return Super::FindEntry(value) != nullptr;
	}

	template <typename KEY, typename KEYHASH> Bool Contains(const KEY& key) const
	{
		return Super::template FindEntry<KEY, KEYHASH>(key) != nullptr;
	}

	const V* Add(const V& value, maxon::Bool& added)
	{
		typename Super::Entry* e = Super::FindOrCreateEntry(value, added);
		return e ? &e->GetKey() : nullptr;
	}

	const V* Add(const V& value)
	{
		Bool added;
		typename Super::Entry* e = Super::FindOrCreateEntry(value, added);
		return e ? &e->GetKey() : nullptr;
	}

	void Remove(const V& value)
	{
		Super::Remove(value);
	}


	class Iterator: private Super::ConstIterator
	{
	public:
		typedef const V ValueType;

		explicit Iterator(const HashSet& s) : Super::ConstIterator(s)
		{
		}

		explicit Iterator(const HashSet& s, Int b, typename Super::Entry* e) : Super::ConstIterator(s, b, e)
		{
		}

		Bool operator ==(const Iterator& b) const
		{
			return Super::ConstIterator::operator ==(b);
		}

		Bool operator !=(const Iterator& b) const
		{
			return !operator ==(b);
		}

		ValueType& operator *() const
		{
			return Super::ConstIterator::GetKey();
		}

		ValueType* operator ->() const
		{
			return &Super::ConstIterator::GetKey();
		}

		Iterator& operator ++()																	// prefix operator++ (increment and fetch)
		{
			Super::ConstIterator::operator++();
			return *this;
		}

		const Iterator operator ++(int)													// postfix operator++ (fetch and increment)
		{
			const Iterator tmp(*this);
			Super::ConstIterator::operator++();
			return tmp;
		}

	private:
		void operator =(const Iterator& i);
	};

	typedef Iterator ConstIterator;

	Iterator Begin() const
	{
		return Iterator(*this);
	}

	Iterator End() const
	{
		return Iterator(*(HashSet*) this, 0, nullptr);
	}
};

/// @}

} // maxon

#endif
