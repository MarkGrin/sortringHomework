#include "lcm.hpp"
#include "xorshift.hpp"
#include "chitest.hpp"

#include <iostream>

#include <cstdlib>

uint32_t stdcrand(uint32_t& state, uint32_t range) {
    return rand() % range;
}

int main () {
    srand(time(0));
    constexpr std::size_t range = 1000, elements = 30000, tries = 10, chi_accept = 969;
    std::cout << "RANGE:" << range << "\n";
    std::cout << "ELEMENTS:" << elements << "\n";
    std::cout << "TRIES:" << tries << "\n";
    std::cout << "chi_accept:" << chi_accept << "\n";

    auto results = chitest::test(xorshift::generate, range, elements, tries, chi_accept);
    for (const auto& result : results) {
        std::cout << "min|max: " << result.min << "|" << result.max << "\n";
        std::cout << "mean|deviation|variation: ";
        std::cout << result.mean << "|" << result.deviation << "|" << result.variation << "\n";
        std::cout << "chi|level|passed:";
        std::cout << result.chi_level << "|" << result.accepted_chi_level;
        std::cout << (result.passed ? "|PASSED\n" : "|FAILED\n");
    }
}

