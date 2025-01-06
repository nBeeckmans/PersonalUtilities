#include <chrono>
#include <string>
#include <iostream>

#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
#define MEASURE_FUNCTION()
#endif


class ScopedTimer {
using ClockType = std::chrono::steady_clock;
const std::string m_functionName;
const ClockType::time_point m_startTime;

public:
    ScopedTimer(const std::string& functionName) : m_functionName(functionName) {}
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer& operator=(ScopedTimer&&) = delete;

    ~ScopedTimer() {
      using namespace std::chrono;
      auto stop = ClockType::now();
      auto duration = (stop - m_startTime);
      auto ms = duration_cast<microseconds>(duration).count();
      std::cout << m_functionName << ": " << ms << " us" << '\n';
    }
private:

};
