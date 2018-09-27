#include "flat.hpp"


bool Flat::operator < (const Flat& flat) const {
    if (flat.number == number)
        return flat.ownerName > ownerName;
    return flat.number > number;
}

bool Flat::operator == (const Flat& flat) const {
    return    flat.number          == number
           && flat.ownerName       == ownerName;

}
