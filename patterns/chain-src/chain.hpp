#ifndef HPP_4225D1AE4B084F38BCB22256AB9873C1

#define HPP_4225D1AE4B084F38BCB22256AB9873C1

#include <list>
#include <string>

struct Order {
    std::size_t number;
    std::size_t item_code;
    std::string destination;
    std::string recipient;
    std::size_t quantity;
};

class Manager {
    Manager* next_ = nullptr;
    public:

    Manager* next() const {
        return next_;
    }
    Manager* set_next(Manager* next) {
        next_ = next;
        return next_;
    }

    virtual bool manage_concrete(const Order& order) {
        return true;
    }

    void manage(const Order& order) {
        if (!this->manage_concrete(order) && next_)
            next_->manage(order);
    }

    virtual ~Manager() {
        delete next_;
    }
};

class CommonManager : public Manager {
    std::size_t number_ = 0;
    std::list<Order>& orders_;
    public:
    CommonManager(std::list<Order>& orders) : orders_(orders) {}
    bool manage_concrete(const Order& order) override;
};

class WholesaleManager : public Manager {
    std::size_t number_ = 0;
    std::list<Order>& orders_;
    public:
    WholesaleManager(std::list<Order>& orders) : orders_(orders) {}
    bool manage_concrete(const Order& order) override;
};

class ExportManager : public Manager {
    std::size_t number_ = 0;
    std::list<Order>& orders_;
    public:
    ExportManager(std::list<Order>& orders) : orders_(orders) {}
    bool manage_concrete(const Order& order) override;
};

class ConfidentialManager : public Manager {
    std::size_t number_ = 0;
    std::list<Order>& orders_;
    public:
    ConfidentialManager(std::list<Order>& orders) : orders_(orders) {}
    bool manage_concrete(const Order& order) override;
};

class ForeignManager : public Manager {
    std::size_t number_ = 0;
    std::list<Order>& orders_;
    public:
    ForeignManager(std::list<Order>& orders) : orders_(orders) {}
    bool manage_concrete(const Order& order) override;
};

#endif /* HPP_4225D1AE4B084F38BCB22256AB9873C1 */
