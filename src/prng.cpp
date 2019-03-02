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
    constexpr std::size_t range = 5000, elements = 30000, tries = 10, chi_accept = 82, dof = 100;
    std::cout << "RANGE:" << range << "\n";
    std::cout << "ELEMENTS:" << elements << "\n";
    std::cout << "TRIES:" << tries << "\n";
    std::cout << "DOF:" << tries << "\n";
    std::cout << "CHI_ACCEPT:" << chi_accept << "\n";

    struct {
        std::string name;
        chitest::prng_func_ptr func;
    } tests[] = {{"stdcrand", stdcrand},
                {"xorshift", xorshift::generate},
                {"lcm", lcm::generate}};
    
    for (auto& test : tests) {
        std::cout << "NAME:" << test.name << "\n";
        auto results = chitest::test(test.func, range, elements, tries, chi_accept, dof);
        double chi_mean = 0;
        for (const auto& result : results) {
            std::cout << "min|max: " << result.min << "|" << result.max << "\n";
            std::cout << "mean|deviation|variation: ";
            std::cout << result.mean << "|" << result.deviation << "|" << result.variation << "\n";
            std::cout << "chi|level|passed:";
            std::cout << result.chi_level << "|" << result.accepted_chi_level;
            std::cout << (result.passed ? "|PASSED\n" : "|FAILED\n");
            chi_mean += result.chi_level;
        }
        chi_mean /= results.size();
        std::cout << "CHI MEAN:" << chi_mean << "\n";
        std::cout << "\n-----------\n";
    }
}

