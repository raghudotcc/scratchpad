// author@raghu
// Fast alternative to std::find
// gcc, msvc use linear scan in std::find
// although std::boyre-moore is present in std::search
// in C++ 17 but most of us still are stuck in 
// C++ 11
/********************************
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <type_traits>
#include <ostream>
#include <algorithm>
**********************************/

namespace fast {

  template <typename T, typename U> 
  struct is_same;

  template <typename T>
  struct is_string;

  template <typename T, typename U> 
  struct is_same {
    static const bool value = false;
  };

  template <typename T>
  struct is_same<T, T> {
    static const bool value = true;
  };

  template <typename T>
  struct is_string {
    std::string testString;
    static const bool value = is_same<T, 
      decltype(testString)>::value;
  };

  const uint8_t kNumberOfBadCharacters = 255;

  template <typename T>
  typename std::enable_if<is_string<T>::value, 
    std::vector<size_t>>::type 
  find(T& haystack, T& needle) 
  {
    size_t haystackSize = haystack.size();
    size_t needleSize = needle.size();
    // change from UPPERCASE to LOWERCASE for better checking
    std::transform(haystack.begin(), 
                   haystack.end(), 
                   haystack.begin(), 
                   ::tolower);
    std::transform(needle.begin(), 
                   needle.end(), 
                   needle.begin(), 
                   ::tolower);

    std::vector<size_t> matchPos;

    // initialize number of bad characters with -1 to indicate 
    // there are none infact at the begining
    std::vector<int> badCharacter(
        kNumberOfBadCharacters, 
        -1); 

    for (auto i = 0; i < needleSize; i++) {
      auto idx = static_cast<int>(needle[i]);
      badCharacter[idx] = i;
    }

    int shiftWidth = 0;

    while (shiftWidth <= (haystackSize - needleSize)) {
      int j = needleSize - 1;

      while (j >= 0 && needle[j] == 
          haystack[shiftWidth + j]) {
        j--;
      }

      if (j < 0) {
        matchPos.push_back(shiftWidth);
        shiftWidth += (shiftWidth + needleSize < haystackSize) ? 
          needleSize - badCharacter[haystack[shiftWidth + needleSize]] : 
          1;
      } else {
        shiftWidth += std::max(1, 
            j - badCharacter[haystack[shiftWidth + j]]);
      }
    }

    return matchPos;
  }

}

/* Driver stub to test the funtion */
template <typename T>
std::ostream & operator<< (std::ostream& out, 
    const std::vector<T> &out_vector)
{
  auto vector_iterator = out_vector.begin();
  for (;vector_iterator != out_vector.end(); 
      ++vector_iterator) {
    out << (*vector_iterator) << std::endl;
  }
}

int main()
{
  std::string haystack = "What is this ? Is this the new technology \
    you were talking about ? Is it really that good ?";
  std::string needle = "is";

  std::cout << fast::find<decltype(haystack)>(haystack, needle) 
            << std::endl;  
  return 0;
}
