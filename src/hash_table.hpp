#ifndef HPP_HASH_TABLE

#define HPP_HASH_TABLE

#include <vector>
#include <list>
#include <functional>


template<typename T>
class hash_table {
    
    std::function<int(const T&)> hash_function;
    std::size_t buckets_num;
    std::vector<std::list<T>> buckets;
    std::size_t collision_count = 0;
    public:
    hash_table () = delete;
    hash_table (std::size_t buckets, std::function<std::size_t(const T&)> hashing=std::hash<T>());	

    void add(const T& element);
    const T& find(const T& element) const;
    const std::list<T>& find_by_hash(std::size_t hash) const;
    
    std::size_t collisions() const;
};

template<typename T>
hash_table<T> :: hash_table (std::size_t size, std::function<std::size_t(const T&)> hashing)
    :
    buckets_num   (size),
    hash_function (hashing) {
    buckets.resize(buckets_num);
}

template<typename T>
void hash_table<T> :: add (const T& element) {
    std::size_t index = hash_function(element) % buckets_num;

    if (!buckets[index].empty())
        collision_count += true;

    for (const auto& item : buckets[index]) {
        if ( item == element ) {
            collision_count -= 1;
            return ;
        }
    }
    buckets[index].push_back (element);
}

template<typename T>
const std::list<T>& hash_table<T> :: find_by_hash (std::size_t hash_) const {
    std::size_t index = hash_ % buckets_num;

    return buckets[index];
}

template<typename T>
const T& hash_table<T> :: find (const T& element) const {
    std::size_t index = hash_function(element) % buckets_num;

    for (const auto& item : buckets[index])
        if ( item == element )
            return item; // found
    return element; // not found
}

template<typename T>
std::size_t hash_table<T> :: collisions () const {
    return collision_count;
}

#endif /* HPP_HASH_TABLE */
