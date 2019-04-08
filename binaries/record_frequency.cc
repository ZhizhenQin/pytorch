#include <fstream>
#include <iterator>
#include <string>
#include <iostream>

#include <thread>
#include <chrono>
#include <sstream>

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
                   int timeout_in_seconds) {
  int num_cpu = 8;
  ifstream inFile[num_cpu];
  for(int i = 0; i < num_cpu; ++i) {
    std::ostringstream filename;
    filename << "/sys/devices/system/cpu/cpu" << i << "/cpufreq/scaling_cur_freq";
    inFile[i].open(filename.str());
  }

  while(true) {
    high_resolution_clock::time_point curr = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(curr - start);
    double elapsed_time = time_span.count();

    outFile << elapsed_time;
    for(int i = 0; i < num_cpu; ++i) {
      int frequency;
      inFile[i].seekg(0, inFile[i].beg);
      inFile[i] >> frequency;
      // cout << frequency << endl;
      outFile << "," << frequency;
    }
    outFile << endl;

    if(elapsed_time >= timeout_in_seconds) {
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(interval_in_ms));
  }
  for(int i = 0; i < num_cpu; ++i) {
    inFile[i].close();
  }
}


// int main(int argc, char** argv) {
//   caffe2::GlobalInit(&argc, &argv);
//   ofstream outFile("/data/local/tmp/frequency.csv");
//   outFile << "Time(s),cpu0,cpu1,cpu2,cpu3,cpu4,cpu5,cpu6,cpu7" << endl;
//   // readFrequency(outFile, 10);
//   high_resolution_clock::time_point start = high_resolution_clock::now();
//   readFrequency(
//     start,
//     std::ref(outFile),
//     FLAGS_interval_in_ms,
//     FLAGS_timeout_in_seconds
//   );
//   // thread freqLogger = thread(readFrequency, start, std::ref(outFile), FLAGS_interval_in_ms);
//   // std::this_thread::sleep_for(std::chrono::milliseconds(15000));
//   outFile.close();
// }
