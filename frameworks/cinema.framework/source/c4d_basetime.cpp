#ifdef __API_INTERN__
	#include "basevar.h"
	#include "ge_tools.h"
#else
	#include "c4d_tools.h"
	#include "c4d_general.h"
#endif

#include "c4d_basetime.h"



BaseTime::BaseTime(Float r)
{
	if (r > (Float) 1.0e15)
		r = (Float) 1.0e15;
	if (r < (Float) - 1.0e15)
		r = (Float) - 1.0e15;
	numerator = Floor(r * (Float) 1000.0 + (Float) 0.5);
	denominator = (Float) 1000.0;
	Reduce();
}

BaseTime::BaseTime(Float z, Float n)
{
	Bool sgn = (z >= 0.0) == (n >= 0.0);

	numerator = Floor(Abs(z) + (Float) 0.5);
	denominator = Floor(Abs(n) + (Float) 0.5);
	if (denominator < (Float) 1.0)
	{
		CriticalStop();
		denominator = 1.0;
	}

	if (!sgn)
		numerator = -numerator;
	Reduce();
}

void BaseTime::SetDenominator(Float r)
{
	denominator = r;
	if (denominator < (Float) 1.0)
	{
		CriticalStop();
		denominator = 1.0;
	}
}

void BaseTime::Quantize(Float fps)
{
	if (fps < (Float) 1.0)
	{
		CriticalStop();
		fps = 1.0;
	}
	numerator = Floor(Floor(numerator * fps) / Floor(denominator));
	denominator = Floor(fps);
	Reduce();
}

void BaseTime::Reduce(void)
{
	Float z, n, m;

	z = Abs(numerator);
	n = Abs(denominator);

	if (z < 0.001 || n < 0.001)
	{
		numerator = 0.0;
		denominator = 1.0;
	}
	else if (z < MAXVALUE_INT32_FLOAT32 && n < MAXVALUE_INT32_FLOAT32)
	{
		Int32 iz = (Int32)z, in = (Int32)n, im;

		if (in == 0)	// failsafe
		{
			numerator = 0.0;
			denominator = 1.0;
		}
		else
		{
			do
			{
				im = iz % in;
				iz = in; in = im;
			} while (im);

			numerator /= Float(iz);
			denominator /= Float(iz);
		}
	}
	else
	{
		Float64 div = 1.0e18 / FMax(Float64(z), Float64(n));
		if (div < 1.0)
		{
			z *= div;
			n *= div;
			numerator *= div;
			denominator *= div;
		}
		if (n < 1.0)
		{
			n = 1.0; denominator = 1.0;
		}

		do
		{
			m = FMod(z, n);
			z = n; n = m;
		} while (m >= 0.5);

		numerator /= z;
		denominator /= z;
	}
}
