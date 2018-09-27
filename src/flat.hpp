#ifndef H_0FEEF34F911140989F4966DABD2201B9

#define H_0FEEF34F911140989F4966DABD2201B9

#include <string>

/**
 * Structure representing information about a flat
 */
struct Flat {
    std::size_t number; /* Number of the flat */
    std::size_t roomsNumber; /* Number of rooms in the flat */
    std::string ownerName; /* Full name of the flat owner */
    std::size_t occupantsNumber; /* Number of occupants of the flat */

    /**
     * Converts Flat to string object
     *
     * @return string representing a flat
     */
    std::string serialize () const;
    Flat (std::string str); /* Constructs flat from a string */
    Flat () = default;
    
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
