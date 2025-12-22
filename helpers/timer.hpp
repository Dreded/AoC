#pragma once
#include <chrono>
#include <string>

struct Timer
{
    std::chrono::high_resolution_clock::time_point start_time;

    // Start the timer
    void start();

    // Stop the timer and print the duration with a label
    void stopAndPrint(const std::string& label);
};
struct ScopedTimer
{
  std::string label;
  Timer t;

  ScopedTimer(const std::string& lbl);
  ~ScopedTimer();
};
