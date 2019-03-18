#include "chitest.hpp"

#include <map>
#include <algorithm>
#include <cmath>

namespace {
double findPercentile(double score) {
     std::vector<std::pair<double, double>> scores = {{5 , 18.7},
                                                      {10, 20.43},
                                                      {15, 22.7},
                                                      {20, 27.85},
                                                      {25, 29.05},
                                                      {30, 30.17},
                                                      {35, 31.21},
                                                      {40, 32.28},
                                                      {45, 33.05},
                                                      {50, 34.5},
                                                      {55, 35.38},
                                                      {60, 36.47},
                                                      {65, 37.63},
                                                      {70, 38.85},
                                                      {75, 40.22},
                                                      {80, 41.77},
                                                      {85, 43.15},
                                                      {90, 46.22},
                                                      {95, 49.8}};
     double level = 0;
     for (const auto& pair : scores) {
         level = pair.first;
         if (score < pair.second)
             break;
     }
     return level;
}

} // namespace

namespace chitest {

std::vector<result> test(prng_func_ptr function) {
    constexpr std::size_t range = 5000, elements = 30000, repeat = 10, dof = 35;
    std::vector<result> results;
    double dof_koef = static_cast<double>(dof) / range;
    for (std::size_t j = 0; j < repeat; j++) {
        result res;
        std::map<uint32_t, uint32_t> map;
        uint32_t state = j + 100;
        res.deviation = 0;
        res.mean = 0;
        res.variation = 0;
        double predicted_mean = static_cast<double>(range - 1) / 2;
        res.max = res.min = function(state, range);;
        for (std::size_t i = 0; i < elements; i++) {
            auto value = function(state, range);
            res.max = std::max(value, res.max);
            res.min = std::min(value, res.min);
            res.deviation += (predicted_mean - value) * (predicted_mean - value);
            res.mean += value;
            value = value*dof_koef;
            if (map.find(value) == map.end())
                map[value] = 0;
            map[value] += 1;
        }
        res.mean = static_cast<double>(res.mean) / elements;
        res.deviation /= elements;
        res.deviation = std::sqrt(res.deviation);
        res.variation = res.deviation / res.mean;

        res.chi_level = 0;
        for (std::size_t i = 0; i < dof; i++) {
            double got = 0;
            if (map.find(i) != map.end())
                got = map[i];
            double expected = static_cast<double>(elements) / dof;
            res.chi_level += (got - expected) * (got - expected) / expected;
        }
        res.percentile = findPercentile(res.chi_level);

        results.push_back(res);
    }
    return results;
}


} // chitest
