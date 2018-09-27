#ifndef H_0FEEF34F911140989F4966DABD2201B9

#define H_0FEEF34F911140989F4966DABD2201B9

#include <string>

struct Flat {
    std::size_t number;
    std::size_t roomsNumber;
    std::string ownerName;
    std::size_t occupantsNumber;

    bool operator < (const Flat& flat) const;
    bool operator == (const Flat& flat) const;
    bool operator != (const Flat& flat)  const {
        return !(*this == flat);
    }

    bool operator > (const Flat& flat) const {
        return !(*this < flat) && *this != flat;
    }

    bool operator <= (const Flat& flat) const {
        return !(*this > flat);
    }

    bool operator >= (const Flat& flat) const {
        return !(*this < flat);
    }
};

# endif /* 0FEEF34F911140989F4966DABD2201B9 */
