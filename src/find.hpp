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
     * @return iterator to the found element or end iterator if it wasn't found.
     */
    template<typename RandomIterator, typename T>
    RandomIterator straightSearch (RandomIterator begin, RandomIterator end, const T& value) {
        while (begin != end) {
            if (*begin == value)
                return begin;
            begin++;
        }
        return end;
    }

    /*
     * Searches for element in array. Using binary search.
     *
     * @param begin - iterator to the first element
     * @param end   - iterator to the element after last
     * @param value - value to search for
     *
     * @return iterator to the found element or end iterator if it wasn't found.
     */
    template<typename RandomIterator, typename T>
    RandomIterator binarySearch (RandomIterator begin, RandomIterator end, const T& value) {
        RandomIterator notFound = end;
        std::size_t distance = end - begin;
        while (distance) {
            RandomIterator current = begin + (distance - 1) / 2;
            if (*current == value)
                return current;
            if (value < *current)
                end = current;
            else
                begin = current + 1;

            distance = end - begin;
        }
        return notFound;
    }


} // HWFind

#endif // H_4D0454F6FFF642A0971342B2FF36CFE7
