/*
 * Purpose: Test calling sum directly vs with a function pointer
 * Observation: The intention here is to check if by any means, the call to sum was any faster when called directly as 
 *              opposed to calling it with a function pointer.Although with chrono I couldn't find any considerable 
 *              differenc on my 8th I7 2.5 GHz, Laptop running a Ubuntu 18. But the cool thing I observed when 
 *              tried to use "perf stat" on this, there was always visible difference in cycle count and runtime
 *              but in opposite way i.e.,the call via fp was running faster than the direct call. I still cannot 
 *              figure out the issue here. but probably I should try a different way to benchmark it.
 *              Reasons why perf or chrono(high res clock) didn't work imo:
 *                1. my pc does not support high res counting.
 *                2. probably the idea that calling via fp might take extra 10-20 extra cycles was not true after all.
 *              Although it needs further investigation but I rest my case saying this was a failed experiment.
 */

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <chrono>
int sum (int a, int b)
{
  return  a + b;
}

int main(int argc, char** argv) 
{
  assert(argc == 2);
  int (*sumfp)(int, int) = &sum;
  if (std::atoi(argv[1]) == 0) {
    auto  _start(std::chrono::high_resolution_clock::now());
    (*sumfp)(23, 98);
    auto _end(std::chrono::high_resolution_clock::now());
    auto runtime = std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start);
    std::cout << runtime.count() << "\n";
  }
  else {
    auto  _start(std::chrono::high_resolution_clock::now());
    sum(23, 98);
    auto _end(std::chrono::high_resolution_clock::now());
    auto runtime = std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start);
    std::cout << runtime.count() << "\n";
  }


  return 0;
}
