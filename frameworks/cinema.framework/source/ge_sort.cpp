#include "ge_sort.h"
#ifdef __API_INTERN__
	#include "ge_tools.h"
#else
	#include "c4d_general.h"
#endif

inline void GeSortAndSearchEx::Bswap(Char* a, Char* b, Int32 i)
{
	Char tmp;

	for (a--, b--, i++; --i; )
	{
		tmp = *++b;
		*b	= *++a;
		*a	= tmp;
	}
}

inline void GeSortAndSearchEx::Wswap(Int16* a, Int16* b, Int32 i)
{
	Int16 tmp;

	for (a--, b--, i++; --i; )
	{
		tmp = *++b;
		*b	= *++a;
		*a	= tmp;
	}
}

inline void GeSortAndSearchEx::Lswap(Int32* a, Int32* b, Int32 i)
{
	Int32 tmp;

	for (a--, b--, i++; --i; )
	{
		tmp = *++b;
		*b	= *++a;
		*a	= tmp;
	}
}

#define CalcSortPtr(i) (((Char*)start) + (msize * ((i) - 1)))

void GeSortAndSearchEx::Bsort(void* start, Int32 count, Int32 msize)
{
	Int32 l, r, j;
	Char* lp, *rp, *ip, *jp, *kp;

	if (count < 2)
		return;

	r = count;
	l = (r >> 1) + 1;

	lp = CalcSortPtr(l);
	rp = CalcSortPtr(r);

	for (; ; )
	{
		if (l > 1)
		{
			l--;
			lp -= msize;
		}
		else
		{
			Bswap(lp, rp, msize);
			if (--r == 1)
				return;
			rp -= msize;
		}

		j	 = l;
		jp = CalcSortPtr(j);

		while ((j << 1) <= r)
		{
			j <<= 1;
			ip	= jp;
			jp	= CalcSortPtr(j);

			if (j < r)
			{
				kp = jp + msize;
				if (Compare(jp, kp) < 0)
				{
					j++;
					jp = kp;
				}
			}

			if (Compare(ip, jp) < 0)
				Bswap(ip, jp, msize);
			else
				break;
		}
	}
}

void GeSortAndSearchEx::Wsort(void* start, Int32 count, Int32 msize)
{
	Int32 l, r, j, s = msize >> 1;
	Char* lp, *rp, *ip, *jp, *kp;

	if (count < 2)
		return;

	r = count;
	l = (r >> 1) + 1;

	lp = CalcSortPtr(l);
	rp = CalcSortPtr(r);

	for (; ; )
	{
		if (l > 1)
		{
			l--;
			lp -= msize;
		}
		else
		{
			Wswap((Int16*)lp, (Int16*)rp, s);
			if (--r == 1)
				return;
			rp -= msize;
		}

		j	 = l;
		jp = CalcSortPtr(j);

		while ((j << 1) <= r)
		{
			j <<= 1;
			ip	= jp;
			jp	= CalcSortPtr(j);

			if (j < r)
			{
				kp = jp + msize;
				if (Compare(jp, kp) < 0)
				{
					j++;
					jp = kp;
				}
			}

			if (Compare(ip, jp) < 0)
				Wswap((Int16*)ip, (Int16*)jp, s);
			else
				break;
		}
	}
}

void GeSortAndSearchEx::Lsort(void* start, Int32 count, Int32 msize)
{
	Int32 l, r, j, s = msize >> 2;
	Char* lp, *rp, *ip, *jp, *kp;

	if (count < 2)
		return;

	r = count;
	l = (r >> 1) + 1;

	lp = CalcSortPtr(l);
	rp = CalcSortPtr(r);

	for (; ; )
	{
		if (l > 1)
		{
			l--;
			lp -= msize;
		}
		else
		{
			Lswap((Int32*)lp, (Int32*)rp, s);
			if (--r == 1)
				return;
			rp -= msize;
		}

		j	 = l;
		jp = CalcSortPtr(j);

		while ((j << 1) <= r)
		{
			j <<= 1;
			ip	= jp;
			jp	= CalcSortPtr(j);

			if (j < r)
			{
				kp = jp + msize;
				if (Compare(jp, kp) < 0)
				{
					j++;
					jp = kp;
				}
			}

			if (Compare(ip, jp) < 0)
				Lswap((Int32*)ip, (Int32*)jp, s);
			else
				break;
		}
	}
}

void GeSortAndSearchEx::Sort(void* start, Int32 count, Int32 msize)
{
	if (!(msize & 3))
		Lsort(start, count, msize);
	else if (!(msize & 1))
		Wsort(start, count, msize);
	else
		Bsort(start, count, msize);
}


#define CalcSearchPtr(i) (((Char*)Start) + (msize*(i)))

void* GeSortAndSearchEx::Search(void* Key, void* Start, Int32 count, Int32 msize)
{
	Int32 l, r, m, c;
	Char* mp, *mt;

	if (!Key || !Start || !count || !msize)
		return nullptr;

	mp = CalcSearchPtr(0);
	c	 = Compare(Key, mp);

	if (c == 0)
		return mp;
	else if (c < 0)
		return nullptr;

	l = 1;
	r = count - 1;

	while (l <= r)
	{
		m	 = (l + r) >> 1;
		mp = CalcSearchPtr(m);
		c	 = Compare(Key, mp);
		if (c == 0)
		{
			while (m > 0)
			{
				m--;
				mt = CalcSearchPtr(m);
				if (Compare(Key, mt))
					break;
				else
					mp = mt;
			}
			return mp;
		}
		else if (c < 0)
		{
			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}

	return nullptr;
}

void* GeSortAndSearchEx::SearchOrInsert(void* Key, void* Start, Int32 count, Int32 msize, Int32& insertidx)
{
	Int32 l, r, m, c;
	Char* mp, *mt;

	if (!Key || !Start || !count || !msize)
	{
		insertidx = NOTOK;
		return nullptr;
	}

	mp = CalcSearchPtr(0);
	c	 = Compare(Key, mp);

	if (c == 0)
	{
		return mp;
	}
	else if (c < 0)
	{
		insertidx = 0;
		return nullptr;
	}

	l = 1;
	r = count - 1;
	m = 0;	// if (c>0) but r<l

	while (l <= r)
	{
		m	 = (l + r) >> 1;
		mp = CalcSearchPtr(m);
		c	 = Compare(Key, mp);
		if (c == 0)
		{
			while (m > 0)
			{
				m--;
				mt = CalcSearchPtr(m);
				if (Compare(Key, mt))
					break;
				else
					mp = mt;
			}
			return mp;
		}
		else if (c < 0)
		{
			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}

	if (c > 0)
	{
		insertidx = m + 1;
	}
	else
	{
		insertidx = m;
	}
#ifdef MAXON_TARGET_DEBUG
	if (insertidx < count)
	{
		mp = CalcSearchPtr(insertidx);
		if (Compare(Key, mp) >= 0)
			CriticalStop();
	}
	if (insertidx > 0)
	{
		mp = CalcSearchPtr(insertidx - 1);
		if (Compare(Key, mp) <= 0)
			CriticalStop();
	}
#endif
	return nullptr;
}
