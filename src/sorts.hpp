#ifndef H_A68E994EDBC54A51839034B831D034F0

#define H_A68E994EDBC54A51839034B831D034F0

#include <algorithm>

namespace HWSorts {

/**
 * Sorting data using bubble sort.
 *
 * RandomIterator - Iterator that complies to RandomAccessIterator concept
 * Type dereferenced by iterator must comply to:
 *  Swappable, MoveAssignable and MoveConstructable concept
 * Comp must be must compy to Compare concept
 *
 * @param array - iterator to the first element
 * @param end - iterator to the element after last one
 * @param comp - comparison function object
 */
template<typename RandomIterator, typename Comparison>
void bubbleSort (RandomIterator array, RandomIterator end, Comparison comp) {

    using std::swap;

    std::size_t size = std::distance (array, end);
    for (std::size_t i = 0; i < size; i++) {

        RandomIterator bubble = array;

        while (std::distance(bubble, end) != 1) {

            if ( comp(*(bubble + 1), *bubble) )
                swap(*bubble, *(bubble + 1));

            bubble++;
        }
    }
}

/**
 * Sorting data using qsort with Hoare partition scheme.
 *
 * RandomIterator - Iterator that complies to RandomAccessIterator concept
 * Type dereferenced by iterator must comply to:
 *  Swappable, MoveAssignable and MoveConstructable concept
 * Comp must be must compy to Compare concept
 *
 * @param array - iterator to the first element
 * @param end - iterator to the element after last one
 * @param comp - comparison function object
 */
template<typename RandomIterator, typename Comparison>
void qsort (RandomIterator array, RandomIterator end, Comparison comp) {
    using std::swap;

    std::size_t size = std::distance(array, end);

    /* Ending recursion call for small sized array parts */
    if ( size <= 1 )
        return ;
    if ( size == 2 ) {
        if ( comp(*(end - 1),*array) )
            swap(*array, *(end - 1));
        return ;
    }

    /* Hoare partition function */
    auto partition = [array, end, &comp]() {
        auto i = array;
        auto j = end - 1;
        auto pivot = array;
        while ( true ) {
            while (comp(*i, *pivot) && i < j)
                i++;
            while (!comp(*j, *pivot) && i < j)
                j--;

            if ( i == j ) {
                if ( i == array ) /* Left partition should not be empty */
                    return j + 1;
                return j;
            }
            if ( i == pivot ) /* Since we don't store pivot value, we will have
                                 to move the pointer to it */
                pivot = j;
            using std::swap;
            swap (*i, *j);
        }
    };

    /* Qsort algorithm */
    auto pivot = partition();
    qsort (array, pivot, comp);
    qsort (pivot, end, comp);
}

/**
 * Same as bubbleSort, but Comparison is = std::less<decltype(*array)>
 * 
 * @see bubbleSort
 */
template<typename RandomIterator>
void bubbleSort (RandomIterator array, RandomIterator end) {
    bubbleSort(array, end, std::less<decltype(*array)>());
}

/**
 * Same as qsort, but Comparison is = std::less<decltype(*array)>
 * 
 * @see qsort
 */
template<typename RandomIterator>
void qsort (RandomIterator array, RandomIterator end) {
    qsort(array, end, std::less<decltype(*array)>());
}

} /* namespace HWSorts */

# endif /* H_A68E994EDBC54A51839034B831D034F0 */

