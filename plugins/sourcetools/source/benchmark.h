#pragma once

#include "c4d_string.h"
#include <chrono>

#ifdef ST_PROFILING
#define IF_PROFILING(CODE) CODE
#else
#define IF_PROFILING(CODE)
#endif

class Benchmark
{
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	String _name;
	bool _stopped = false;

	Benchmark() = default;

public:
	Benchmark(const String& name);
	~Benchmark();

	void StopBenchmark();
};