#ifndef HPP_3B038D5D2C914DFBB455C9E2586D6295
#define HPP_3B038D5D2C914DFBB455C9E2586D6295

#include <utility>
#include <vector>
#include <cstdint>

namespace chitest {

using prng_func_ptr = uint32_t (*) (uint32_t&, uint32_t);

struct result {
    double mean;
    uint32_t max;
    uint32_t min;
    double deviation;
    double variation;
    double chi_level;
    double percentile;
};

std::vector<result> test(prng_func_ptr function);

}

#endif // HPP_3B038D5D2C914DFBB455C9E2586D6295
