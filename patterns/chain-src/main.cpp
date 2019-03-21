#include "chain.hpp"
#include <iostream>

Manager* makeChain (std::list<Order>& wholesale,
                    std::list<Order>& common,
                    std::list<Order>& exports,
                    std::list<Order>& confidential,
                    std::list<Order>& foreign
                    ) {
    Manager* manager = new WholesaleManager(wholesale);
    manager
    ->set_next(new ExportManager(exports))
    ->set_next(new ForeignManager(foreign))
    ->set_next(new ConfidentialManager(confidential))
    ->set_next(new CommonManager(common));
    return manager;
}

Order getOrder() {
    Order order;
    std::cout << "Item code:";
    std::cin >> order.item_code;
    std::cout << "Destination:";
    std::cin >> order.destination;
    std::cout << "Recipient:";
    std::cin >> order.recipient;
    std::cout << "Quantity:";
    std::cin >> order.quantity;

    return order;
}

void print_order(const std::list<Order> orders, const char* name) {
    std::cout << "ORDER LIST:" << name << "\n";
    for (const auto& order : orders) {
        std::cout << "Order number:";
        std::cout << order.number;
        std::cout << "\nItem code:";
        std::cout << order.item_code;
        std::cout << "\nDestination:";
        std::cout << order.destination;
        std::cout << "\nRecipient:";
        std::cout << order.recipient;
        std::cout << "\nQuantity:";
        std::cout << order.quantity;
        std::cout << "\n-\n";
    }
    std::cout << "---\n";
}

int main () {
    std::list<Order> wholesale;
    std::list<Order> common;
    std::list<Order> exports;
    std::list<Order> confidential;
    std::list<Order> foreign;
    auto manager = makeChain(wholesale, common, exports, confidential, foreign);

    while(true) {
        std::cout << "Finished?(yes,no):";
        std::string input;
        std::cin >> input;
        if ( input != "no" )
            break;
        auto order = getOrder();
        manager->manage(order);
    }
    std::cout << "DONE:\n\n";
    print_order(common, "COMMON");
    print_order(exports, "EXPORTS");
    print_order(wholesale, "WHOLESALE");
    print_order(confidential, "CONFIDENTIAL");
    print_order(foreign, "FOREIGN");

    delete manager;
}
