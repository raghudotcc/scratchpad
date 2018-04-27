#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <type_traits>
#include <ostream>

template <typename T, typename U> 
struct is_same;

template <typename T>
struct is_string;

template <typename T>
std::ostream & operator<< (std::ostream& out, const std::vector<T> &out_vector)
{
	auto vector_iterator = out_vector.begin();
	for (;vector_iterator != out_vector.end(); ++vector_iterator) {
		out << (*vector_iterator) << std::endl;
	}
}

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
	static const bool value = is_same<T, decltype(testString)>::value;
};

const uint8_t kNumberOfBadCharacters = 255;

namespace nonstd {

	template <typename T>
	typename std::enable_if<is_string<T>::value, std::vector<size_t>>::type 
	find(T& haystack, T& needle) 
	{
			size_t haystackSize = haystack.size();
			size_t needleSize = needle.size();
			std::vector<size_t> matchPos;

			// initialize number of bad characters with -1 to indicate 
			// there are none infact at the begining
			std::vector<int> badCharacter(kNumberOfBadCharacters, -1); 

			for (auto i = 0; i < needleSize; i++) {
				auto idx = static_cast<int>(needle[i]);
				badCharacter[idx] = i;
			}

			int shiftWidth = 0;

			while (shiftWidth <= (haystackSize - needleSize)) {
				int j = needleSize - 1;

				while (j >= 0 && needle[j] == haystack[shiftWidth + j]) {
					j--;
				}

				if (j < 0) {
					matchPos.push_back(shiftWidth);
					shiftWidth += (shiftWidth + needleSize < haystackSize) ? needleSize - badCharacter[haystack[shiftWidth + needleSize]] : 1;
				} else {
					shiftWidth += std::max(1, j - badCharacter[haystack[shiftWidth + j]]);
				}
			}

			return matchPos;
	}

}

/* Driver program to test above funtion */
int main()
{
	std::string haystack = "Are you really listening ? I mean really, are you ?";
  std::string needle = "are";

  std::cout << nonstd::find<decltype(haystack)>(haystack, needle) << std::endl;  
  return 0;
}
