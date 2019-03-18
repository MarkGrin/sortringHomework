#ifndef H_4D0454F6FFF642A0971342B2FF36CFE7

#define H_4D0454F6FFF642A0971342B2FF36CFE7

#include <cstddef> // std::size_t
#include <iostream>

namespace HWFind {

    /*
     * Searches for element in array. Using straight search.
     *
     * @param begin - iterator to the first element
     * @param end   - iterator to the element after last
     * @param value - value to search for
     *
     * @return vector of found elements
     */
    template<typename RandomIterator, typename T>
    std::vector<T> straightSearch (RandomIterator begin, RandomIterator end, const T& value) {
        std::vector<T> results;
        while (begin != end) {
            if (*begin == value)
                results.push_back(value);
            begin++;
        }
        return results;
    }

    /*
     * Searches for element in array. Using binary search.
     *
     * @param begin - iterator to the first element
     * @param end   - iterator to the element after last
     * @param value - value to search for
     *
     * @return vector of found elements
     */
    template<typename RandomIterator, typename T>
    std::vector<T> binarySearch (RandomIterator begin, RandomIterator end, const T& value) {
        RandomIterator notFound = end;
        RandomIterator start = begin;
        std::size_t distance = end - begin;
        std::vector<T> results;
        while (distance) {
            RandomIterator current = begin + (distance - 1) / 2;
            if (*current == value) {
                auto left = current;
                while (left >= start && *left == value) {
                    results.push_back(*left);
                    left -= 1;
                }
                auto right = current;
                right += 1;
                while (right < notFound && *right == value) {
                    results.push_back(*right);
                    right += 1;
                }
                return results;
            }
            if (value < *current)
                end = current;
            else
                begin = current + 1;

            distance = end - begin;
        }
        return results;
    }


} // HWFind

#endif // H_4D0454F6FFF642A0971342B2FF36CFE7
