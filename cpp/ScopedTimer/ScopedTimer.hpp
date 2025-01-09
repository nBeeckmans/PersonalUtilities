#pragma once
#include <chrono>
#include <string>
#include <iostream>

#ifdef USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
#define MEASURE_FUNCTION()
#endif


class ScopedTimer {
using ClockType = std::chrono::steady_clock;
const std::string m_functionName;
const ClockType::time_point m_startTime;

public:
    ScopedTimer(const std::string& functionName) : m_functionName(functionName), m_startTime(ClockType::now()) {
    }
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer& operator=(ScopedTimer&&) = delete;

    ~ScopedTimer() {
      using namespace std::chrono;
      const auto stop = ClockType::now();
      const auto duration = (stop - m_startTime);
      const auto ms = duration_cast<microseconds>(duration).count();
      std::cout << m_functionName << ": " << ms << " microseconds" << '\n';
    }
};
