#include "benchmark.h"

#include "error.h"

Benchmark::Benchmark(const String &name) {
  _name = name;
  _start = std::chrono::high_resolution_clock::now();
}

Benchmark::~Benchmark() { this->StopBenchmark(); }

void Benchmark::StopBenchmark() {
  if (_stopped)
    return;
  _stopped = true;
  std::chrono::duration<double> duration =
      std::chrono::high_resolution_clock::now() - _start;
  double formattedDuration = duration.count();
  String postFix = " s"_s;

  if (formattedDuration < 1.0) {
    formattedDuration *= 1000;
    postFix = " ms"_s;
  }

  if (formattedDuration < 1.0) {
    formattedDuration *= 1000;
    postFix = " ns"_s;
  }

  String msg = "Benchmark '" + _name + "' completed in ";
  msg += maxon::String::FloatToString(Float(formattedDuration), -1, 3);
  msg += postFix;
  Log(msg);
}
