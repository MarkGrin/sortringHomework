#ifndef HPP_ECCF979518D94EDEAFD9B6CD60197721

#define HPP_ECCF979518D94EDEAFD9B6CD60197721

#include "singleton.hpp"
#include <string>
#include <list>
#include <chrono>

namespace log {

using timepoint_t=std::chrono::time_point<std::chrono::system_clock>;
using sclock_t=std::chrono::system_clock;

enum class IMPORTANCE {
    NORMAL,
    WARNING,
    ERROR
};

struct Entry {
    std::string message;
    IMPORTANCE level;
    timepoint_t time;
};

class Logger : public Singleton<Logger> {

    std::list<Entry> entries;

    public:

    void log (std::string message, IMPORTANCE level, timepoint_t time=timepoint_t());

    void report () const;
};

} /* log */

#endif /* HPP_ECCF979518D94EDEAFD9B6CD60197721 */
