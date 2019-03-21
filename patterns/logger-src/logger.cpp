#include "logger.hpp"

#include <iostream>
#include <ctime>

namespace log {

namespace {

    const char* level_to_string (IMPORTANCE level) {
        if (level == IMPORTANCE::WARNING)
            return "WARNING";
        else if (level == IMPORTANCE::ERROR)
            return "ERROR";
        else if (level == IMPORTANCE::NORMAL)
            return "NORMAL";
        return "UNKNOWN";
    }

} /* namespace */

void Logger::log (std::string message, IMPORTANCE level, timepoint_t time) {

    if (time == timepoint_t())
        time = sclock_t::now();

    auto it  = entries.begin();
    auto end = entries.end();
    while (it != end) {
        if (it->time < time)
            break;
        it++;
    }
    entries.insert(it, {std::move(message), level, time});
}
void Logger::report () const {

    std::size_t i = 0;
    auto it  = entries.begin();
    auto end = entries.end();
    std::cout << "---\nLOG:\n";
    while (i < 10 && it != end) {

        std::cout << "[" << level_to_string(it->level) << "] at ";

        std::time_t ctime_point = sclock_t::to_time_t(it->time);
        std::cout << std::ctime(&ctime_point) << "entry: ";

        std::cout << it->message << "\n";

        it++;
        i++;
    }
    std::cout << "---\n";
}

} /* namespace log */
