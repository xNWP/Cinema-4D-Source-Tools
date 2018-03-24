#ifdef __API_INTERN__
	#error "Not in the kernel"
#endif

#include "operatingsystem.h"
#include "c4d_memory.h"
#include "c4d_thread.h"

void XThreadMain(void* data)
{
	((C4DThread*)data)->Main();
}

Bool XThreadTest(void* data)
{
	return ((C4DThread*)data)->TestDBreak();
}

static const Char* XThreadName(void* data)
{
	return ((C4DThread*)data)->GetThreadName();
}

C4DThread::C4DThread(void)
{
	weak = false;
	bt = C4DOS.Bt->Alloc(XThreadMain, XThreadTest, this, XThreadName);
}

C4DThread::~C4DThread(void)
{
	if (!weak)
		C4DOS.Bt->Free(bt);
}

Bool C4DThread::Start(THREADMODE mode, THREADPRIORITY priority)
{
	if (!bt)
		return false;
	return C4DOS.Bt->Start(bt, mode, priority, nullptr);
}

void C4DThread::End(Bool wait)
{
	if (bt)
		C4DOS.Bt->End(bt, wait);
}

void C4DThread::Wait(Bool checkevents)
{
	if (bt)
		C4DOS.Bt->Wait(bt, checkevents);
}

GeSignal* GeSignal::Alloc(void)
{
	return C4DOS.Bt->SIGAlloc();
}

void GeSignal::Free(GeSignal*& sm)
{
	C4DOS.Bt->SIGFree(sm);
}

Semaphore* Semaphore::Alloc(void)
{
	return C4DOS.Bt->SMAlloc();
}

void Semaphore::Free(Semaphore*& sm)
{
	C4DOS.Bt->SMFree(sm);
}

MPThreadPool::MPThreadPool(void)
{
	mp = nullptr;
	mpcount = 0;
}

MPThreadPool::~MPThreadPool(void)
{
	if (!mp)
		return;
	C4DOS.Bt->MPEnd(mp);
	C4DOS.Bt->MPFree(mp);
	mp = nullptr;
}

Bool MPThreadPool::Init(const C4DThread& parent, Int32 count, C4DThread** thread)
{
	return Init(parent.Get(), count, thread);
}

Bool MPThreadPool::Init(BaseThread* parent, Int32 count, C4DThread** thread)
{
	if (mp)
	{
		C4DOS.Bt->MPFree(mp); mp = nullptr; mpcount = 0;
	}

	mpcount = count;
	mp = C4DOS.Bt->MPAlloc(parent, count, XThreadMain, XThreadTest, (void**)thread, XThreadName);

	Int32 i;
	for (i = 0; i < count; i++)
	{
		if (!thread[i]->weak)
		{
			thread[i]->weak = true;
			C4DOS.Bt->Free(thread[i]->bt);
		}
		thread[i]->bt = C4DOS.Bt->MPGetThread(mp, i);
	}

	return mp != nullptr;
}

Bool MPThreadPool::Start(THREADPRIORITY worker_priority)
{
	BaseThread* bt = nullptr;
	Int32				i;

	for (i = 0; i < mpcount; i++)
	{
		bt = C4DOS.Bt->MPGetThread(mp, i);
		if (!bt || !C4DOS.Bt->Start(bt, THREADMODE_ASYNC, worker_priority, nullptr))
		{
			C4DOS.Bt->MPEnd(mp);
			return false;
		}
	}

	return true;
}

C4DThread* MPThreadPool::WaitForNextFree(void)
{
	return (C4DThread*)C4DOS.Bt->MPWaitForNextFree(mp);
}

void MPThreadPool::Wait(void)
{
	C4DOS.Bt->MPWait(mp);
}

void MPThreadPool::End(void)
{
	C4DOS.Bt->MPEnd(mp);
}
