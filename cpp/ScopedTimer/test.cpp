#define USE_TIMER
#include <map>

#include "ScopedTimer.hpp"
#undef USE_TIMER

constexpr long fib_number = 50;

std::map<int, long> fibMap;

long fib(const int target) {
  if (fibMap.contains(target)) {
    return fibMap[target];
  }
  if (target < 2) {
    return target;
  }
  long result = fib(target - 1) + fib(target - 2);
  fibMap[target] = result;
  return result;
}

void fibonacciMethod() {
  MEASURE_FUNCTION();
  std::cout
    << std::format("Calculating the {}th fibonacci number, resulting in : {}", fib_number, fib(fib_number))
    << std::endl;
}

void emptyMethod() {
  MEASURE_FUNCTION();
}

int main() {
  emptyMethod();
  fibonacciMethod();
  return 0;
}
