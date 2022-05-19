#include "benchmark.h"

#include "error.h"

namespace st
{
	Benchmark::Benchmark(const String& name, Bool printOnDestruct, Bool startImmediately)
	{
		_name = name;
		_printOnDestruct = printOnDestruct;
		_stopped = true;
		_elapsedTime = 0.0;
		if (startImmediately) StartBenchmark();
	}

	Benchmark::~Benchmark()
	{
		if (_printOnDestruct) {
			String msg = "Benchmark '" + _name + "' completed in " + GetElapsedTimeFormatted();
			Log(msg);
		}
	}

	void Benchmark::StopBenchmark()
	{
		if (_stopped) return;
		_stopped = true;
		std::chrono::duration<double> tp = std::chrono::steady_clock::now() - _start;
		_elapsedTime += Float64(tp.count());
	}

	void Benchmark::StartBenchmark()
	{
		if (!_stopped) return;
		_stopped = false;
		_start = std::chrono::steady_clock::now();
	}

	Float64 Benchmark::GetElapsedSeconds() const
	{
		if (!_stopped) {
			std::chrono::duration<double> tp = std::chrono::steady_clock::now() - _start;
			return _elapsedTime + Float64(tp.count());
		} else {
			return _elapsedTime;
		}
	}

	String Benchmark::GetElapsedTimeFormatted() const
	{
		Float64 eTime = GetElapsedSeconds();
		String postFix = " s"_s;

		if (eTime < 1.0)
		{
			eTime *= 1000.0;
			postFix = " ms"_s;
		}

		if (eTime < 1.0)
		{
			eTime *= 1000.0;
			postFix = " us"_s;
		}

		String rval = maxon::String::FloatToString(Float(eTime), -1, 3);
		rval += postFix;
		return rval;
	}

	Bool Benchmark::IsRunning() const
	{
		return !_stopped;
	}
}