#include "lcm.hpp"


namespace lcm {

    uint32_t generate(uint32_t &state, uint32_t range) {
        // constants suggested by glibc
        constexpr std::size_t mod = 2147483648;
        constexpr std::size_t koef = 1103515245;
        constexpr std::size_t addition = 12345;

        state = (state * koef + addition) % mod;

        return state % range;
    }

} // lcm
