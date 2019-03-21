#include "logger.hpp"

#include <string>
#include <algorithm>
#include <iostream>

std::string generate() {
    std::string numbers = "0123456789";
    std::random_shuffle(numbers.begin(), numbers.end());
    numbers.erase(numbers.begin() + 4, numbers.end());

    log::Logger::instance().log("Generated " + numbers, log::IMPORTANCE::NORMAL);

    return numbers;
}

bool is_not_digit (char c) {
    return !std::isdigit(c);
}

bool check(std::string a, std::string b) {
    if (a != b) {
        a.erase(std::remove_if(a.begin(), a.end(),
                is_not_digit), a.end());
        if (a != b) {
            log::Logger::instance().log("User error", log::IMPORTANCE::ERROR);
            return false;
        }
        log::Logger::instance().log("Had to strip input", log::IMPORTANCE::WARNING);
    }
    log::Logger::instance().log("Check passed", log::IMPORTANCE::NORMAL);
    return true;
}

int main () {
    std::size_t tries = 3;
    while(tries) {

        std::string answer = generate();
        std::cout << "Tries:" << tries << "\n";
        std::cout << "Repeat:" << answer << "\n";

        std::string input;
        std::cin >> input;

        log::Logger::instance().log("User input:" + input, log::IMPORTANCE::NORMAL);

        if (input == "log") {
            log::Logger::instance().log("User requested logs", log::IMPORTANCE::WARNING);
            log::Logger::instance().report();
            continue ;
        }

        if ( !check(std::move(input), std::move(answer)) ) {
            tries--;
            log::Logger::instance().log("New tries:" + std::to_string(tries), log::IMPORTANCE::NORMAL);
        }
    }
    log::Logger::instance().log("ZERO TRIES, TERMINATION", log::IMPORTANCE::ERROR);
    log::Logger::instance().report();
    return 0;
}
