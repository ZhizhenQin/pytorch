#include <fstream>
#include <iterator>
#include <string>
#include <iostream>

#include <thread>
#include <chrono>

// #include "caffe2/core/init.h"
// #include "binaries/benchmark_args.h"

using namespace std;
using namespace std::chrono;

// C10_DEFINE_int(
//     interval_in_ms,
//     100,
//     "The interval of logging in frequency in ms");
// C10_DEFINE_int(
//     timeout_in_seconds,
//     300,
//     "The interval of logging in frequency in ms");


void readFrequency(high_resolution_clock::time_point start,
                   ofstream &outFile,
                   int interval_in_ms,
                   int timeout_in_seconds);
