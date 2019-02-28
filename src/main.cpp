#include <cstdint>
#include <iostream>
#include <map>


uint32_t lcm(uint32_t& state, std::size_t range) {
    // constants suggested by glibc
    constexpr std::size_t mod = 2147483648;
    constexpr std::size_t koef = 1103515245;
    constexpr std::size_t addition = 12345;
    
    state = ( state * koef + addition) % mod;

    return state % range;
}


int main() {
    std::map<uint32_t, uint32_t> map;
    uint32_t state = 17;
    for (std::size_t i = 0; i < 10000000; i++) {
        auto value = lcm(state, 30);
        if (map.find(value) == map.end())
            map[value] = 0;
        map[value] += 1;
    }
    for (const auto& pair : map)
        std::cout << pair.first << ":" << pair.second << "\n";
}
