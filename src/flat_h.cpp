#include "flat_h.hpp"
#include <functional>


Flat::Flat (const Flat& f) {
    number = f.number;
    ownerName = f.ownerName;
    occupantsNumber = f.occupantsNumber;
    slow_hash = f.slow_hash;
    fast_hash = f.fast_hash;
}

bool Flat::operator < (const Flat& flat) const {
    if (flat.number == number)
        return flat.ownerName > ownerName;
    return flat.number > number;
}

bool Flat::operator == (const Flat& flat) const {
    return flat.ownerName == ownerName;

}

Flat::Flat (std::string in) {
    auto get = [](std::string& str) {
        std::size_t comma = str.find(',');
        std::string result(str.begin(), str.begin() + comma);
        str.erase(0, comma + 1);
        return result;
    };
    number = atoi(get(in).c_str());
    roomsNumber = atoi(get(in).c_str());
    ownerName = get(in) + " ";
    ownerName.append (get(in) + " ");
    ownerName.append (get(in));
    occupantsNumber = atoi(in.c_str());

    slow_hash = 0;
    for (auto val : ownerName)
        slow_hash += val + val*val;
    
    std::string temp;
    fast_hash = 0;
    for (auto val : ownerName) {
        temp.push_back(val);
        if (temp.size() == sizeof(fast_hash)) {
            fast_hash = fast_hash ^ (*reinterpret_cast<const std::size_t*>(temp.data()));
            temp.clear();
        }
    }

    
}

std::string Flat::serialize () const {
    std::string result;
    result.append (std::to_string(number) + ",");
    result.append (std::to_string(roomsNumber) + ",");
    result.append (ownerName + ",");
    result.append (std::to_string(occupantsNumber));
    return result;
}

