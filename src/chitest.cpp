#include "chitest.hpp"

#include <map>
#include <algorithm>
#include <cmath>

namespace chitest {

std::vector<result> test(prng_func_ptr function, std::size_t range, std::size_t elements, std::size_t repeat,
                         double chi_level_accepted) {

    std::vector<result> results;
    for (std::size_t j = 0; j < repeat; j++) {
        result res;
        std::map<uint32_t, uint32_t> map;
        uint32_t state = j + 1;
        res.deviation = 0;
        res.mean = 0;
        res.variation = 0;
        double predicted_mean = static_cast<double>(range - 1) / 2;
        for (std::size_t i = 0; i < elements; i++) {
            auto value = function(state, range);
            res.max = std::max(value, res.max);
            res.min = std::min(value, res.min);
            res.deviation += (predicted_mean - value) * (predicted_mean - value);
            res.mean += value;
            if (map.find(value) == map.end())
                map[value] = 0;
            map[value] += 1;
        }
        res.mean = static_cast<double>(res.mean) / elements;
        res.deviation /= elements;
        res.deviation = std::sqrt(res.deviation);
        res.variation = res.deviation / res.mean;
        res.accepted_chi_level = chi_level_accepted;

        res.chi_level = 0;
        for (std::size_t i = 0; i < range; i++) {
            double got = 0;
            if (map.find(i) != map.end())
                got = map[i];
            double expected = static_cast<double>(elements) / range;
            res.chi_level += (got - expected) * (got - expected) / expected;
        }
        res.passed = false;
        if (res.accepted_chi_level >= res.chi_level)
            res.passed = true;

        results.push_back(res);
    }
    return results;
}



} // chitest
