#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

int main()
{
  // 0 = 1, 1 = 2, 2 = 3, 3 = 4, 4 = 5, 5 = 6, 6 = 7, 7 = 8, 8 = 9, 9 = 10, 
  // 10 = 11, 11 = 12, 12 = 13, 13 = 14, 14 = 15, 15 = 16, 16 = 17, 17 = 18,
  // 18 = 19, 19 = 20, 20 = 30, 21 = 40, 22 = 50, 23 = 60, 24 = 70, 25 = 80,
  // 26 = 90, 27 = hundred, 28 = and, 29 = thousand
  std::vector<int> count_lookup {3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8, 6, 6, 5, 5, 5, 7, 6, 6, 7, 3, 8};

  int sum = std::accumulate(count_lookup.begin() + 9, count_lookup.begin() + 19, 0); // 10 to 19
  for (int i = 19; i < 27; i++) {
    sum += (count_lookup[i] * 10); // the 20s, 30s, 40s ... 90s
  }
  sum += (9 * std::accumulate(count_lookup.begin(), count_lookup.begin() + 9, 0)); // sum from 1 to 9, through 20s to 90s
  int sum_upto_ninetynine = sum; // store 1 to 99 sum
  for (int i = 0; i < 9; i++) {
    sum += count_lookup[i] + count_lookup[27]; // the one hundred, two hundred, three hundred ...
    sum += (count_lookup[i] + count_lookup[27] + count_lookup[28]) * 99; // The one hundred and, two hundred and..
    sum += sum_upto_ninetynine; // The sum from one to ninetynine
  }

  sum += count_lookup[0] + count_lookup[29]; // one thousand
  std::cout << sum << std::endl;
  return 0;
}
