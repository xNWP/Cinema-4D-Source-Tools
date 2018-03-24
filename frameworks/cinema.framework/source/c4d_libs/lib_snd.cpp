#include "lib_snd.h"

#ifndef __API_INTERN__
#define LIBID			LIB_SND
#define LIB				GeSndLib

static LIB *library_cache = nullptr;

#include "c4d_basesound.h"
GeSndInfo::GeSndInfo(BaseSound *bs)
{
	data = nullptr;
	if (bs)
	{
		bs->GetSoundInfo(this);
	}
}

static inline LIB *CheckLibSnd(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library_cache);
}


GePlaySnd* GePlaySnd::Alloc()
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Alloc)); if (!lib || !lib->Alloc) return nullptr;
	return lib->Alloc();
}

void GePlaySnd::Free(GePlaySnd *&data)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Free)); if (!lib || !lib->Free) return;
	lib->Free(data);
}

GePlaySnd::GePlaySnd()
{
}

Bool GePlaySnd::Open(const BaseSound *snd)
{
	const Float	start_offset = 0;
	GeSndInfo	info;

	snd->GetSoundInfo(&info);

	return Open(1, &snd, &start_offset, info.GetLength().Get());
}

Bool GePlaySnd::Open(Int32 stream_cnt, const BaseSound **streams, const Float *start_offsets, Float max_length)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Open)); if (!lib || !lib->Open) return false;
	return (this->*lib->Open)(stream_cnt, streams, start_offsets, max_length);
}

void GePlaySnd::Close()
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Close)); if (!lib || !lib->Close) return;
	(this->*lib->Close)();
}

void GePlaySnd::StartAt(Float64 start)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, StartAt)); if (!lib || !lib->StartAt) return;
	(this->*lib->StartAt)(start);
}

void GePlaySnd::Scrub(Float64 start, Float64 duration)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Scrub)); if (!lib || !lib->Scrub) return;
	(this->*lib->Scrub)(start, duration);
}

void GePlaySnd::Stop()
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, Stop)); if (!lib || !lib->Stop) return;
	(this->*lib->Stop)();
}

Bool GePlaySnd::IsPlaying()
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, IsPlaying)); if (!lib || !lib->IsPlaying) return false;
	return (this->*lib->IsPlaying)();
}

Float64 GePlaySnd::GetPositionEstimate()
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, GetPositionEstimate)); if (!lib || !lib->GetPositionEstimate) return 0.0;
	return (this->*lib->GetPositionEstimate)();
}


void	GePlaySnd::SetScale(Float64 scale)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, SetScale)); if (!lib || !lib->SetScale) return;
	(this->*lib->SetScale)(scale);
}

Float64	GePlaySnd::GetScale(void)
{
	LIB *lib = CheckLibSnd(LIBOFFSET(LIB, GetScale)); if (!lib || !lib->GetScale) return 0;
	return (this->*lib->GetScale)();
}

#endif
