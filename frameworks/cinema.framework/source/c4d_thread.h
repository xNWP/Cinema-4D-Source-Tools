/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_THREAD_H__
#define C4D_THREAD_H__

#ifdef __API_INTERN__
	#include "ge_sys_thread.h"
#else

#include "operatingsystem.h"

#define ThreadCall(fnc) (this->*C4DOS.Bt->fnc)

//----------------------------------------------------------------------------------------
/// A very fast lock.
//----------------------------------------------------------------------------------------
struct GeSpinlock
{
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	GeSpinlock() : state(0) { }

	volatile Int32 state;			///< Lock state.

	//----------------------------------------------------------------------------------------
	/// Locks.
	//----------------------------------------------------------------------------------------
	inline void Lock() { ThreadCall(Lock) (); }


	//----------------------------------------------------------------------------------------
	/// Unlocks.
	//----------------------------------------------------------------------------------------
	inline void Unlock() { ThreadCall(Unlock) (); }

	//----------------------------------------------------------------------------------------
	/// Attempts and locks if possible.
	/// @return												@trueIfOtherwiseFalse{locking succeeded and the lock needs to be unlocked later}
	//----------------------------------------------------------------------------------------
	inline Bool AttemptLock() { return ThreadCall(AttemptLock) (); }
};

//----------------------------------------------------------------------------------------
/// A read-write lock has the following constraints:
/// - Multiple readers can hold the lock at any time.
/// - Only one writer can hold the lock at any given time.
/// - A writer must block until all readers have released the lock before obtaining the lock for writing.
/// - Readers arriving while a writer is waiting to acquire the lock will block until after the writer has obtained and released the lock.
//----------------------------------------------------------------------------------------
struct GeRWSpinlock
{
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	GeRWSpinlock() : state(0) { }

	volatile Int32 state;			///< Read-write lock state.

	//----------------------------------------------------------------------------------------
	/// Locks and waits for reading.
	//----------------------------------------------------------------------------------------
	inline void ReadLock() { ThreadCall(ReadLock) (); }

	//----------------------------------------------------------------------------------------
	/// Unlocks for waiting.
	//----------------------------------------------------------------------------------------
	inline void ReadUnlock() { ThreadCall(ReadUnlock) (); }

	//----------------------------------------------------------------------------------------
	/// Locks and waits for writing.
	//----------------------------------------------------------------------------------------
	inline void WriteLock() { ThreadCall(WriteLock) (); }

	//----------------------------------------------------------------------------------------
	/// Unlocks for writing.
	//----------------------------------------------------------------------------------------
	inline void WriteUnlock() { ThreadCall(WriteUnlock) (); }

	//----------------------------------------------------------------------------------------
	/// Attempts and locks if possible.
	/// @return												@trueIfOtherwiseFalse{locking succeeded and the lock needs to be unlocked later}
	//----------------------------------------------------------------------------------------
	inline Bool AttemptWriteLock() { return ThreadCall(AttemptWriteLock) (); }
};

//----------------------------------------------------------------------------------------
/// Main thread base class used internally by @C4D.
/// @note Cannot be instantiated.
//----------------------------------------------------------------------------------------
class BaseThread
{
private:
	BaseThread();
	~BaseThread();

public:
	//----------------------------------------------------------------------------------------
	/// Checks if the thread received a break command to stop processing.\n
	/// Normally this is only true when @C4D is closing, or when End() has been called.
	/// @return												@trueOtherwiseFalse{processing should be terminated}
	//----------------------------------------------------------------------------------------
	Bool TestBreak(void) { return C4DOS.Bt->TestBreak(this); }

	//----------------------------------------------------------------------------------------
	/// Ends the thread. This function will not return until the thread has completely stopped.
	/// @warning If the thread does not check for TestBreak() then this function will not return until the thread has finished and this might get into a deadlock situation.
	/// @param[in] wait								Determines if thread termination is synchronous or asynchronous:
	///																- If @formatConstant{true} the function will not return until the thread is finished.
	///																- If @formatConstant{false} the function returns immediately although the thread will still run until it is finished.
	//----------------------------------------------------------------------------------------
	void End(Bool wait = true) { C4DOS.Bt->End(this, wait); }

	//----------------------------------------------------------------------------------------
	/// Checks if the thread is running.
	/// @return												@trueIfOtherwiseFalse{the thread is running}
	//----------------------------------------------------------------------------------------
	Bool IsRunning(void) { return C4DOS.Bt->IsRunning(this); }
};

//----------------------------------------------------------------------------------------
/// %User thread object.
//----------------------------------------------------------------------------------------
class C4DThread
{
	friend class MPThreadPool;
	friend void XThreadMain(void* data);
	friend Bool XThreadTest(void* data);

private:
	Bool weak;
	BaseThread* bt;

public:

	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	C4DThread();

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	virtual ~C4DThread(void);

	//----------------------------------------------------------------------------------------
	/// Retrieves the BaseThread for the thread.
	/// @return												The BaseThread of the thread. @theOwnsPointed{thread,base thread}
	//----------------------------------------------------------------------------------------
	BaseThread* Get(void) const { return bt; }

	//----------------------------------------------------------------------------------------
	/// Starts the thread running.
	/// @param[in] mode								The thread mode: @enumerateEnum{THREADMODE}
	/// @param[in] priority						The thread priority: @enumerateEnum{THREADPRIORITY}
	/// @return												@trueIfOtherwiseFalse{the thread was started}
	//----------------------------------------------------------------------------------------
	Bool Start(THREADMODE mode = THREADMODE_ASYNC, THREADPRIORITY priority = THREADPRIORITY_NORMAL);

	//----------------------------------------------------------------------------------------
	/// Ends the thread. This function will not return until the thread has completely stopped.
	/// @warning If the thread does not check for TestBreak() then this function will not return until the thread has finished and this might get into a deadlock situation.
	/// @param[in] wait								Determines if thread termination is synchronous or asynchronous:
	///																- If @formatConstant{true} the function will not return until the thread is finished.
	///																- If @formatConstant{false} the function returns immediately although the thread will still run until it is finished.
	//----------------------------------------------------------------------------------------
	void End(Bool wait = true);

	//----------------------------------------------------------------------------------------
	/// Checks if the thread is running.
	/// @return												@trueIfOtherwiseFalse{the thread is running}
	//----------------------------------------------------------------------------------------
	Bool IsRunning(void) { return C4DOS.Bt->IsRunning(bt); }
	//----------------------------------------------------------------------------------------
	/// Checks if the thread received a break command to stop processing.\n
	/// Normally this is only true when @C4D is closing, or when End() has been called.\n
	/// This function is used by the Semaphore class during the Semaphore::Lock() to check if the thread has been stopped.
	/// @note Add more break conditions, such as if @em ESC has been pressed, in TestDBreak().
	/// @return												@trueOtherwiseFalse{processing should be terminated}
	//----------------------------------------------------------------------------------------
	Bool TestBreak(void) { return C4DOS.Bt->TestBreak(bt); }

	//----------------------------------------------------------------------------------------
	/// Waits until the thread has finished.
	/// @param[in] checkevents				If @formatConstant{false} then wait until the thread has finished. If @formatConstant{true} then additionally return if a @C4D event occurred.
	//----------------------------------------------------------------------------------------
	void Wait(Bool checkevents = false);

	//----------------------------------------------------------------------------------------
	/// Override to add user breaks such as pressing the @em ESC key. This function is called by TestBreak().
	/// @return												@trueIfOtherwiseFalse{processing should be terminated}
	//----------------------------------------------------------------------------------------
	virtual Bool TestDBreak(void) { return false; }

	//----------------------------------------------------------------------------------------
	/// Override with the thread main code.
	//----------------------------------------------------------------------------------------
	virtual void Main(void) = 0;

	//----------------------------------------------------------------------------------------
	/// Override to return the name of the thread.
	/// @return												The thread name. @theOwnsPointed{thread,character buffer}
	//----------------------------------------------------------------------------------------
	virtual const Char* GetThreadName(void) = 0;
};

//----------------------------------------------------------------------------------------
/// Multiple processor thread array. Starts each thread in the array on a separate CPU:
/// @code
/// class MPTest : public C4DThread
/// {
/// 	public:
/// 		virtual void Main(void);
/// };
///
/// class ControlThread : public C4DThread
/// {
/// public:
/// 	virtual void Main(void)
/// 	{
/// 		MPThreadPool mp;
/// 		Int32 i, cnt=GeGetCurrentThreadCount();
/// 		MPAlloc<MPTest> thread;
/// 		AutoGeFree<C4DThread*> list = NewMemClear(C4DThread*, cnt);
/// 		if (!list || !thread.Init(cnt))
/// 			return;
///
/// 		for (i=0; i<cnt; i++)
/// 		{
/// 			list[i]=&thread[i];
/// 		}
///
/// 		if (!mp.Init(*this,cnt,list)) =
/// 			return;
/// 		if (!mp.Start(THREADPRIORITY_BELOW))
/// 			return;
///
/// 		mp.Wait();
/// 	}
/// };
///
/// ControlThread ct;
/// ct.Start(THREADMODE_SYNCHRONOUS);
/// @endcode
/// @warning MP threads must not use any OS functions. This is strictly forbidden. The only system calls allowed are memory allocations/freeings.
//----------------------------------------------------------------------------------------
class MPThreadPool
{
private:
	MPBaseThread* mp;
	Int32 mpcount;

public:
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	MPThreadPool();

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~MPThreadPool();

	//----------------------------------------------------------------------------------------
	/// Initializes the multi-processor threads.
	/// @param[in] parent							The control thread that will manage the multiple threads. A control thread is necessary so this parameter cannot be set to @formatConstant{nullptr}.
	/// @param[in] count							The number of threads to create: 1 <= @formatParam{count} <= GeGetCurrentThreadCount()\n
	///																It does not need to match the actual GeGetCurrentThreadCount() on the machine. However for best speed GeGetCurrentThreadCount() should be used.
	/// @param[in] thread							Pointer to an array of pointers to C4DThread structures that hold the threads to create. @callerOwnsPointed{threads array}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Init(BaseThread* parent, Int32 count, C4DThread** thread);

	//----------------------------------------------------------------------------------------
	/// Initializes the multi-processor threads.
	/// @param[in] parent							The control thread that will manage the multiple threads.
	/// @param[in] count							The number of threads to create: 1 <= @formatParam{count} <= GeGetCurrentThreadCount()\n
	///																It does not need to match the actual GeGetCurrentThreadCount() on the machine. However for best speed GeGetCurrentThreadCount() should be used.
	/// @param[in] thread							Pointer to an array of pointers to C4DThread structures that hold the threads to create. @callerOwnsPointed{threads array}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Init(const C4DThread& parent, Int32 count, C4DThread** thread);

	//----------------------------------------------------------------------------------------
	/// Starts execution of all the multi-processor threads.
	/// @param[in] worker_priority		The thread priority: @enumerateEnum{THREADPRIORITY}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Start(THREADPRIORITY worker_priority);

	//----------------------------------------------------------------------------------------
	/// Waits for the next thread, that is after one has completed its execution.
	/// @return												The next available thread in the array passed to Init().
	//----------------------------------------------------------------------------------------
	C4DThread* WaitForNextFree(void);

	//----------------------------------------------------------------------------------------
	/// Waits for all of the threads to complete.
	//----------------------------------------------------------------------------------------
	void Wait(void);

	//----------------------------------------------------------------------------------------
	/// End the threads running.\n
	/// This function will not return until all MP threads have completely stopped working, so if the MP threads do not check for BaseThread::TestBreak() this will result in a deadlock.
	//----------------------------------------------------------------------------------------
	void End(void);
};

//----------------------------------------------------------------------------------------
/// A synchronization object that allows only a single thread to lock it at the same time. It functions as a reentrant mutex.
/// @addAllocFreeAutoAllocNote
//----------------------------------------------------------------------------------------
class Semaphore
{
private:
	Semaphore();
	~Semaphore();

public:
	//----------------------------------------------------------------------------------------
	/// @allocatesA{semaphore}
	/// @return												@allocReturn{semaphore}
	//----------------------------------------------------------------------------------------
	static Semaphore* Alloc(void);

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{semaphores}
	/// @param[in] sm									@theToDestruct{semaphore}
	//----------------------------------------------------------------------------------------
	static void Free(Semaphore*& sm);

	//----------------------------------------------------------------------------------------
	/// Locks the semaphore to prevent access. Return instantly and do not wait until access is given.
	/// @return												@formatConstant{false} if semaphore already was locked.
	//----------------------------------------------------------------------------------------
	Bool AttemptLock(void) { return C4DOS.Bt->SMLock(this); }

	//----------------------------------------------------------------------------------------
	/// Tries and locks. If the semaphore is already locked, this will also wait for access.\n
	/// If a thread is pass it will also check the BaseThread::TestBreak() for the thread and exit with false if a user break is detected.
	/// @param[in] bt									The base thread that the semaphore belongs to or @formatConstant{nullptr}. @callerOwnsPointed{base thread}
	/// @return												@formatConstant{false} if semaphore already was locked, otherwise @formatConstant{true}.
	//----------------------------------------------------------------------------------------
	Bool Lock(BaseThread* bt) { return C4DOS.Bt->SMLockAndWait(this, bt); }

	//----------------------------------------------------------------------------------------
	/// Tries and locks. If the semaphore is already locked, this will also wait for access.\n
	/// If a thread is pass it will also check the C4DThread::TestBreak() for the thread and exit with false if a user break is detected.
	/// @param[in] bt									The thread that the semaphore belongs to or @formatConstant{nullptr}. @callerOwnsPointed{thread}
	/// @return												@formatConstant{false} if semaphore already was locked, otherwise @formatConstant{true}.
	//----------------------------------------------------------------------------------------
	Bool Lock(C4DThread* bt) { return C4DOS.Bt->SMLockAndWait(this, bt ? bt->Get() : nullptr); }

#ifdef MAXON_TARGET_DEBUG
		#define AttemptLockDebug _AttemptLock(__LINE__, __FILE__)
		#define LockDebug(_x_) _LockDebug(_x_, __LINE__, __FILE__)
	Bool _AttemptLockDebug(Int32 line, const char* file) { return C4DOS.Bt->SMLockDebug(this, line, file); }
	Bool _LockDebug(BaseThread* bt, Int32 line, const char* file) { return C4DOS.Bt->SMLockAndWaitDebug(this, bt, line, file); }
	Bool _LockDebug(C4DThread* bt, Int32 line, const char* file) { return C4DOS.Bt->SMLockAndWaitDebug(this, bt ? bt->Get() : nullptr, line, file); }
#else
		#define AttemptLockDebug AttemptLock
		#define LockDebug(_x_) Lock(_x_)
#endif

	//----------------------------------------------------------------------------------------
	/// Unlocks the semaphore and allows access by other threads.
	//----------------------------------------------------------------------------------------
	void Unlock(void) { C4DOS.Bt->SMUnlock(this); }
};

//----------------------------------------------------------------------------------------
/// Signals are mechanisms for efficient thread synchronization.\n
/// One thread is sent to sleep (Wait()), so it will not take up any CPU time until another thread signals it (Set()) so it wakes up.
/// @note Of course you could write your own @c while() loop with GeSleep() and a check for a boolean variable that is written by a different thread, but this is much less efficient.
//----------------------------------------------------------------------------------------
class GeSignal
{
private:
	GeSignal();
	~GeSignal();

public:
	//----------------------------------------------------------------------------------------
	/// @allocatesA{signal}
	/// @return												@allocReturn{signal}
	//----------------------------------------------------------------------------------------
	static GeSignal* Alloc(void);

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{signal}
	/// @param[in] sm									@theToDestruct{signal}
	//----------------------------------------------------------------------------------------
	static void Free(GeSignal*& sm);

	//----------------------------------------------------------------------------------------
	/// Initializes the signal.
	/// @param[in] mode								The signal mode: @enumerateEnum{SIGNALMODE}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Init(SIGNALMODE mode = SIGNALMODE_DEFAULT)
	{
		return ThreadCall(SIGInit) (mode);
	}

	//----------------------------------------------------------------------------------------
	/// Wakes up the thread waiting for this condition.
	/// THREADSAFE
	//----------------------------------------------------------------------------------------
	void Set()
	{
		ThreadCall(SIGSet) ();
	}

	//----------------------------------------------------------------------------------------
	/// Clears the condition variable.\n
	/// When Clear() is called after Wait() make sure that there are no more threads still waiting for the same condition.\n
	/// Only after the last thread has left Wait() it is allowed to call Clear(). Otherwise one of the threads may keep waiting because the condition was cleared before it was able to wake up.
	//----------------------------------------------------------------------------------------
	void Clear()
	{
		ThreadCall(SIGClear) ();
	}

	//----------------------------------------------------------------------------------------
	/// Waits until the condition has been set or a certain amount of time has passed.\n
	/// GeSignal is auto-clear by default, this means only one thread can wait for the condition and the condition is cleared after Wait().
	/// @warning You can only call this from a BaseThread. You are not allowed to wait for a condition variable from a job; doing this could result in a deadlock.
	/// @note For compatibility reasons the return value works differently than in [Core]ConditionVariable.
	/// THREADSAFE.
	/// @param[in] timeout						The maximum wait interval in milliseconds (or FOREVER).
	/// @return												@trueIfOtherwiseFalse{the wait timed-out}
	//----------------------------------------------------------------------------------------
	Bool Wait(Int32 timeout)
	{
		return ThreadCall(SIGWait) (timeout);
	}
};

//----------------------------------------------------------------------------------------
/// Retrieves the number of threads being used for the current (render) context.
/// @note This might be smaller than the actual CPU core or thread count if the user selected a custom number of render threads.
/// @return												The number of threads being used for the current context.
//----------------------------------------------------------------------------------------
inline Int32 GeGetCurrentThreadCount(void) { return C4DOS.Bt->GetCurrentThreadCount(); }

//----------------------------------------------------------------------------------------
/// A global semaphore. When this is locked, any other thread trying to acquire the lock will have to wait. Other threads will continue.
/// @warning As this blocks all threads it should only be used if and when necessary, a local semaphore is a more elegant and efficient solution to multiple thread data access.
//----------------------------------------------------------------------------------------
inline void GeThreadLock(void) { C4DOS.Bt->ThreadLock(); }

//----------------------------------------------------------------------------------------
/// Continues blocked threads after a call to GeThreadLock().
//----------------------------------------------------------------------------------------
inline void GeThreadUnlock(void) { C4DOS.Bt->ThreadUnlock(); }

//----------------------------------------------------------------------------------------
/// Identifies the type of a thread.
/// @param[in] bt									The thread to identify. @callerOwnsPointed{thread}
/// @return												The thread type: @enumerateEnum{THREADTYPE}
//----------------------------------------------------------------------------------------
inline THREADTYPE IdentifyThread(BaseThread* bt) { return C4DOS.Bt->Identify(bt); }

//----------------------------------------------------------------------------------------
/// Retrieves a unique ID for the current thread.
/// @note Usually you do not have to care about this.
/// @return												The unique ID for the current thread.
//----------------------------------------------------------------------------------------
inline UInt32 GeGetCurrentThreadId() { return C4DOS.Bt->GetCurrentThreadId(); }

//----------------------------------------------------------------------------------------
/// Retrieves the current thread.
/// @return												The current thread.
//----------------------------------------------------------------------------------------
inline BaseThread* GeGetCurrentThread() { return C4DOS.Bt->GetCurrentThread(); }

//----------------------------------------------------------------------------------------
/// Returns a dummy thread (TestBreak() will always return @formatConstant{false}).
/// @since R17.032
/// @return												A pointer to a dummy thread (guaranteed to be valid).
//----------------------------------------------------------------------------------------
inline BaseThread* GeGetDummyThread() { return C4DOS.Bt->NoThread; }

//----------------------------------------------------------------------------------------
/// Returns a dummy thread for escape key testing (TestBreak() will always return @formatConstant{true}).
/// @since R17.032
/// @return												A pointer to an escape key test thread (guaranteed to be valid).
//----------------------------------------------------------------------------------------
inline BaseThread* GeGetEscTestThread() { return C4DOS.Bt->userEscTestThread; }

#endif

//----------------------------------------------------------------------------------------
/// Scope based auto-spinlock.
//----------------------------------------------------------------------------------------
class AutoSpinLock
{
private:
	GeSpinlock* l;
	AutoSpinLock& operator = (const AutoSpinLock& d);
	AutoSpinLock(AutoSpinLock& data);

public:
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	explicit AutoSpinLock(GeSpinlock* lock = nullptr)
	{
		l = nullptr;
		if (!lock)
			return;
		DoLock(lock);
	}

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~AutoSpinLock()
	{
		Unlock();
	}

	//----------------------------------------------------------------------------------------
	/// Locks the passed spin lock.
	/// @param[in] lock								The spinlock to lock.
	//----------------------------------------------------------------------------------------
	void DoLock(GeSpinlock* lock)
	{
		if (l || !lock)
			return;
		lock->Lock();
		l = lock;
	}

	//----------------------------------------------------------------------------------------
	/// Unlocks the spinlock.
	//----------------------------------------------------------------------------------------
	void Unlock(void)
	{
		if (!l)
			return;
		l->Unlock();
		l = nullptr;
	}
};

class AutoLocker;

//----------------------------------------------------------------------------------------
/// Has to be embedded in a structure to be protected by AutoLocker.
/// @note Needs the keyword @c mutable.
/// @see AutoLocker for an example.
//----------------------------------------------------------------------------------------
class AutoLock
{
private:
	friend class AutoLocker;
	GeSpinlock lock;
	volatile UInt32 threadid;
	AutoLock(const AutoLock& al);
	AutoLock(const AutoLocker& al);

public:
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	AutoLock()
	{
		threadid = UInt32(NOTOK);
	}
};

//----------------------------------------------------------------------------------------
/// A class for thread-safe code access within its current scope.\n
/// @b Example:<br>
/// Embed AutoLock in a class that needs to be protected.
/// @code
/// class DriverHelper
/// {
/// 	public:
/// 		...
/// 		mutable AutoLock lock; // Note the keyword mutable
/// };
/// @endcode
/// In a member function:
/// @code
/// void DriverHelper::FunctionXYZ()
/// {
/// 	AutoLocker al(lock);
///
/// 	// Do something
/// }
/// @endcode
/// AutoLocker guarantees that all code within the member function can be accessed thread-safe as no other thread can have access at the same time.\n
/// This does not solve the general problem of deadlocks that can occur if the calls are done cross-wise, meaning calls between threads.\n
/// AutoLocker has the advantage over Spinlock that calls of subroutines with the same protection will not get a deadlock.\n
/// Also, AutoLocker will automatically unlock everything, so there are no missing Unlock() calls (can be tricky if the code returns at multiple places otherwise).
///
/// Another example of recursive or deep calls with the same AutoLock:
/// @code
/// class ClassA
/// {
/// 	public:
/// 	AutoLock lock;
///
/// 	void FunctionA()
/// 	{
/// 		AutoLocker al(lock);
///
/// 		...
/// 		FunctionB(doc->GetFirstObject());
/// 		...
/// 	}
///
/// 	void FunctionB(BaseObject *op)
/// 	{
/// 		AutoLocker al(lock);
///
/// 		...
/// 		FunctionB(op->GetDown());
/// 		...
/// 	}
/// };
/// @endcode
/// Both @c FunctionB() calls are fine and will not cause deadlocks. It is important that the lock is performed on the same AutoLock otherwise you will run into deadlocks.
///
/// @note	Should be used for fast methods, for instance to serialize short data access.\n
///				As an example within normal objects or GUI managers where routines are called by maybe 1 or 2 threads. In an object for instance one for the viewport and one for generation/execution and maybe a message from another thread.\n
///				Should be avoided for rendering though where locking to access one thread will seriously impair speed.
//----------------------------------------------------------------------------------------
class AutoLocker
{
private:
	GeSpinlock*				l;
	volatile UInt32*	ct;
	AutoLocker&				operator = (const AutoLocker& d);
	AutoLocker(AutoLocker& data);

public:
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	AutoLocker()
	{
		l		= nullptr;
		ct	= nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Copy constructor.
	/// @since R17.032
	/// @param[in] src								The source AutoLocker.
	//----------------------------------------------------------------------------------------
	AutoLocker(AutoLocker&& src) : l(src.l), ct(src.ct)
	{
		src.l = nullptr;
		src.ct = nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Locks the passed AutoLock.
	/// @param[in] data								The AutoLock to lock.
	//----------------------------------------------------------------------------------------
	explicit AutoLocker(AutoLock& data)
	{
		l		= nullptr;
		ct	= nullptr;
		DoLock(data);
	}

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~AutoLocker()
	{
		Unlock();
	}

	//----------------------------------------------------------------------------------------
	/// Locks the passed AutoLock.
	/// @param[in] data								The AutoLock to lock.
	//----------------------------------------------------------------------------------------
	void DoLock(AutoLock& data)
	{
		if (l)
			return;

		UInt32 id = GeGetCurrentThreadId();
		if (data.threadid == id)
			return;

		data.lock.Lock();
		l		= &data.lock;
		ct	= &data.threadid;
		if (ct)
			*ct = id;
	}

	//----------------------------------------------------------------------------------------
	/// Unlocks the locked AutoLock.
	//----------------------------------------------------------------------------------------
	void Unlock(void)
	{
		if (!l)
			return;
		*ct = UInt32(NOTOK);
		l->Unlock();
		l		= nullptr;
		ct	= nullptr;
	}
};

//----------------------------------------------------------------------------------------
/// Has to be embedded in a structure to be protected by AutoRWLocker.
/// @note Needs the keyword mutable.
/// @see AutoRWLocker.
//----------------------------------------------------------------------------------------
class AutoRWLock
{
	friend class AutoRWLocker;
	GeRWSpinlock lock;
	volatile UInt32 threadid;

public:
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	AutoRWLock()
	{
		threadid = UInt32(NOTOK);
	}
};

//----------------------------------------------------------------------------------------
/// Much the same as AutoLocker but allows differentiation of read/write access.
/// @see AutoLocker for examples.
//----------------------------------------------------------------------------------------
class AutoRWLocker
{
private:
	GeRWSpinlock* l;
	volatile UInt32* ct;
	volatile Bool is_write;
	AutoRWLocker& operator = (const AutoRWLocker& d);
	AutoRWLocker(AutoRWLocker& lock);

public:
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	AutoRWLocker()
	{
		l		= nullptr;
		ct	= nullptr;
		is_write = false;
	}

	//----------------------------------------------------------------------------------------
	/// Locks the passed AutoRWLock.
	/// @param[in] lock								The AutoRWLock to lock.
	/// @param[in] write_lock					@formatConstant{true} for write access, @formatConstant{false} for read access only.
	//----------------------------------------------------------------------------------------
	explicit AutoRWLocker(AutoRWLock& lock, Bool write_lock = true)
	{
		l		= nullptr;
		ct	= nullptr;
		is_write = write_lock;
		DoLock(lock, write_lock);
	}

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~AutoRWLocker()
	{
		Unlock();
	}

	//----------------------------------------------------------------------------------------
	/// Locks the passed AutoRWLock.
	/// @param[in] lock								The AutoRWLock to lock.
	/// @param[in] write_lock					@formatConstant{true} for write access, @formatConstant{false} for read access only.
	//----------------------------------------------------------------------------------------
	void DoLock(AutoRWLock& lock, Bool write_lock = true)
	{
		if (l)
			return;
		UInt32 id = 0;

		id = GeGetCurrentThreadId();
		if (lock.threadid == id)
			return;

		if (write_lock)
			lock.lock.WriteLock();
		else
			lock.lock.ReadLock();

		is_write = write_lock;
		l		= &lock.lock;
		ct	= &lock.threadid;
		if (ct)
			*ct = id;
	}

	//----------------------------------------------------------------------------------------
	/// Unlocks the locked AutoRWLock.
	//----------------------------------------------------------------------------------------
	void Unlock(void)
	{
		if (!l)
			return;
		*ct = UInt32(NOTOK);
		if (is_write)
			l->WriteUnlock();
		else
			l->ReadUnlock();
		l		= nullptr;
		ct	= nullptr;
	}
};

#endif // C4D_THREAD_H__
