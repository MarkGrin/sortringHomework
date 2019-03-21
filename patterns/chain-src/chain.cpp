#include "chain.hpp"

bool CommonManager::manage_concrete(const Order& order) {

    number_++; // Just add it

    Order newOrder = order;
    newOrder.number = number_;
    orders_.push_back(newOrder);

    return true;
}

bool WholesaleManager::manage_concrete(const Order& order) {
    if (order.quantity <= 100)
        return false;

    std::size_t full = order.quantity / 100; // Wholesale orders
    std::size_t add  = order.quantity % 100; // Should be divided

    for (std::size_t i = 0; i < full; i++) {
    number_++;
    Order newOrder = order;
    newOrder.number = number_;
    newOrder.quantity = 100;
    orders_.push_back(newOrder);
    }
    number_++;
    Order newOrder = order;
    newOrder.number = number_;
    newOrder.quantity = add;
    orders_.push_back(newOrder);

    return true;
}

bool ExportManager::manage_concrete(const Order& order) {
    if (order.destination.find("Russia") != std::string::npos)
        return false;

    Order newOrder = order;
    newOrder.number = number_;
    orders_.push_back(newOrder);

    number_++; // Export orders should start with 0

    return true;
}

bool ConfidentialManager::manage_concrete(const Order& order) {
    if (order.recipient.find("Sekretov") == std::string::npos)
        return false;

    number_++;

    Order newOrder = order;
    newOrder.number = number_;
    newOrder.recipient = "XXXXX"; // Making it anonymous
    orders_.push_back(newOrder);


    return true;
}

bool ForeignManager::manage_concrete(const Order& order) {
    if (order.recipient.find("son") == std::string::npos)
        return false;

    number_++;

    Order newOrder = order;
    newOrder.number = number_;
    // Proper name handling
    newOrder.recipient = "Mr\\Ms " + order.recipient;
    orders_.push_back(newOrder);

    return true;
}
