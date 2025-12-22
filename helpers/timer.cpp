#include "timer.hpp"
#include <iostream>

void Timer::start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stopAndPrint(const std::string& label)
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << label << " took " << duration << " µs\n" << std::endl;
}

ScopedTimer::ScopedTimer(const std::string& lbl) : label(lbl)
{
    t.start();
}

ScopedTimer::~ScopedTimer()
{
    t.stopAndPrint(label);
}
