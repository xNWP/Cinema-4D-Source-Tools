#pragma once

#include "c4d_string.h"
#include <chrono>

#ifdef ST_PROFILING
#define IF_PROFILING(CODE) CODE
#else
#define IF_PROFILING(CODE)
#endif

namespace st
{
	class Benchmark
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> _start;
		std::chrono::duration<double> _elapsedTime;
		String _name;
		Bool _stopped;
		Bool _printOnDestruct;

		Benchmark() = default;

	public:
		Benchmark(const String& name, Bool printOnDestruct = true, Bool startImmediately = true);
		~Benchmark();

		void StopBenchmark();
		void StartBenchmark();
		Float64 GetElapsedSeconds() const;
		String GetElapsedTimeFormatted() const;
		Bool IsRunning() const;
	};
}