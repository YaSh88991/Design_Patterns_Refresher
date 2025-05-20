// ===== Violation Example =====
// Direct instantiation and if-else logic scattered everywhere

#include <iostream>
#include <memory>
#include <string>

class Order
{
public:
    virtual void describe() const = 0;
    virtual ~Order() = default;
};

class DeliveryOrder : public Order
{
public:
    void describe() const override
    {
        std::cout << "Delivery Order: Food will be delivered to your address.\n";
    }
};

class DineInOrder : public Order
{
public:
    void describe() const override
    {
        std::cout << "Dine-In Order: Table will be reserved for you at the restaurant.\n";
    }
};

// Client code - tightly coupled and hard to extend
std::unique_ptr<Order> createOrder(const std::string &type)
{
    if (type == "delivery")
    {
        return std::make_unique<DeliveryOrder>();
    }
    else if (type == "dinein")
    {
        return std::make_unique<DineInOrder>();
    }
    else
    {
        return nullptr;
    }
}

int main()
{
    auto order1 = createOrder("delivery");
    auto order2 = createOrder("dinein");
    if (order1)
        order1->describe();
    if (order2)
        order2->describe();
    return 0;
}

/*
Output:
Delivery Order: Food will be delivered to your address.
Dine-In Order: Table will be reserved for you at the restaurant.
*/
// Problem: Adding a new order type requires editing createOrder() everywhere.

// ===== Factory Method-Compliant Example =====

#include <iostream>
#include <memory>

// Product
class Order
{
public:
    virtual void describe() const = 0;
    virtual ~Order() = default;
};

// Concrete Products
class DeliveryOrder : public Order
{
public:
    void describe() const override
    {
        std::cout << "Delivery Order: Food will be delivered to your address.\n";
    }
};

class DineInOrder : public Order
{
public:
    void describe() const override
    {
        std::cout << "Dine-In Order: Table will be reserved for you at the restaurant.\n";
    }
};

class ScheduledOrder : public Order
{
public:
    void describe() const override{
        std::cout<<"Scheduled Order : The Order is scheduled for later";
    }
};

// Creator
class OrderCreator
{
public:
    virtual std::unique_ptr<Order> createOrder() const = 0;
    virtual ~OrderCreator() = default;
};

// Concrete Creators
class DeliveryOrderCreator : public OrderCreator
{
public:
    std::unique_ptr<Order> createOrder() const override
    {
        return std::make_unique<DeliveryOrder>();
    }
};

class DineInOrderCreator : public OrderCreator
{
public:
    std::unique_ptr<Order> createOrder() const override
    {
        return std::make_unique<DineInOrder>();
    }
};

class ScheduledOrderCreator : public OrderCreator{
public:
    std::unique_ptr<Order> createOrder() const override{
        return std::make_unique<ScheduledOrder>();
    }
};

// Client code depends on the abstract creator, not on concrete types
void placeOrder(const OrderCreator &creator)
{
    auto order = creator.createOrder();
    order->describe();
}

int main()
{
    DeliveryOrderCreator deliveryCreator;
    DineInOrderCreator dineInCreator;
    ScheduledOrderCreator scheduledCreator;

    placeOrder(deliveryCreator);
    placeOrder(dineInCreator);
    placeOrder(scheduledCreator);

    return 0;
}

/*
Output:
Delivery Order: Food will be delivered to your address.
Dine-In Order: Table will be reserved for you at the restaurant.
"Scheduled Order : The Order is scheduled for later"
*/
// New order types can be added with new Creator/Product subclasses without modifying client code.
