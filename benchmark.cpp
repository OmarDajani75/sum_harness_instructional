//
// (C) 2022-2023, E. Wes Bethel
// benchmark-* harness for running different versions of the sum study
//    over different problem sizes
//
// usage: no command line arguments
// set problem sizes, block sizes in the code below

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

extern void setup(int64_t N, uint64_t A[]);
extern int64_t sum(int64_t N, uint64_t A[]);

/* The benchmarking program */
int main(int argc, char **argv)
{
   std::cout << std::fixed << std::setprecision(2);

#define MAX_PROBLEM_SIZE 1 << 28 //  256M
   std::vector<int64_t> problem_sizes{MAX_PROBLEM_SIZE >> 5, MAX_PROBLEM_SIZE >> 4, MAX_PROBLEM_SIZE >> 3, MAX_PROBLEM_SIZE >> 2, MAX_PROBLEM_SIZE >> 1, MAX_PROBLEM_SIZE};

   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);

   int64_t t;
   int n_problems = problem_sizes.size();

   /* For each test size */
   for (int64_t n : problem_sizes)
   {
      printf("Working on problem size N=%lld \n", n);

      // invoke user code to set up the problem
      setup(n, &A[0]);

      // insert your timer code here
      auto start = std::chrono::high_resolution_clock::now();
      // invoke method to perform the sum
      t = sum(n, &A[0]);
      // insert your end timer code here, and print out elapsed time for this problem size
      auto end = std::chrono::high_resolution_clock::now();

      double duration = std::chrono::duration<double>(end - start).count();

      double capacity = 204.8e9;

      double mflops = (n / 1e6) / duration;

      double bytes = n * sizeof(uint64_t);

      double memoryBandwidthUtilized = ((((bytes / 1e9) / duration) / capacity) * 100) * 1e9; // % of memory bandwidth utilized

      double accesses = n;

      double avgMemoryLatency = (duration / accesses) * 1e9;

      std::cout << mflops << " " << memoryBandwidthUtilized << " " << avgMemoryLatency;

      // This is from you Professor. Too lazy to make it cout
      printf(" Sum result = %lld \n", t);

   } // end loop over problem sizes
}

// EOF