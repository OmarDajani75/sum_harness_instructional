#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

void setup(int64_t N, uint64_t A[])
{
   printf(" inside sum_indirect problem_setup, N=%lld \n", N);
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int64_t> dist(0, N - 1);
   for (int64_t i = 0; i <= N; i++)
   {
      A[i] = dist(gen) % N;
   }
}

int64_t
sum(int64_t N, uint64_t A[])
{
   printf(" inside sum_indirect perform_sum, N=%lld \n", N);
   uint64_t sumTotal = 0;
   uint64_t index = A[0];

   for (int64_t i = 0; i <= N; i++)
   {
      sumTotal += A[index];
      index = A[index];
   }

   return sumTotal;
}