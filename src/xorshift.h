#include <cstdint>

namespace xorshift {

uint32_t generate(uint32_t& state, uint32_t range)
{
    uint32_t result = state;

    // XOR shift
    result ^= result << 13;
    result ^= result >> 17;
    result ^= result << 5;

    state = result;

    return result % range;
}

} // xorshift
