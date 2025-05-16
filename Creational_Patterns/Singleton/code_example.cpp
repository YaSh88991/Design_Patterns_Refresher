// ===== Violation Example =====
// Multiple generators can produce duplicate or out-of-order numbers.

// Without Singleton Pattern

#include <iostream>

class OrderNumberGenerator
{
    int current;

public:
    OrderNumberGenerator() : current(1000) {}
    int nextOrderNumber()
    {
        return current++;
    }
};

int main()
{
    OrderNumberGenerator genA;
    OrderNumberGenerator genB;

    std::cout << "genA: " << genA.nextOrderNumber() << "\n"; // 1000
    std::cout << "genB: " << genB.nextOrderNumber() << "\n"; // 1000 (duplicate!)
    std::cout << "genA: " << genA.nextOrderNumber() << "\n"; // 1001
    std::cout << "genB: " << genB.nextOrderNumber() << "\n"; // 1001 (duplicate!)
    return 0;
}

/*
Output:
genA: 1000
genB: 1000
genA: 1001
genB: 1001
*/
// Problem: Duplicate order numbers due to multiple generators.

// ===== Singleton-Compliant Example =====
// All order numbers are assigned by the single instance.

#include <iostream>

class OrderNumberGeneratorSingleton
{
    int current;
    OrderNumberGeneratorSingleton() : current(1000)
    {
        std::cout << "OrderNumberGenerator created\n";
    }
    OrderNumberGeneratorSingleton(const OrderNumberGeneratorSingleton &) = delete;
    OrderNumberGeneratorSingleton &operator=(const OrderNumberGeneratorSingleton &) = delete;

public:
    static OrderNumberGeneratorSingleton &getInstance()     // Static ensures thread safety
    {
        static OrderNumberGeneratorSingleton instance; 
        return instance;
    }
    int nextOrderNumber()
    {
        return current++;
    }
};

int main()
{
    auto &generator = OrderNumberGeneratorSingleton::getInstance();
    std::cout << "Order number: " << generator.nextOrderNumber() << "\n"; // 1000
    std::cout << "Order number: " << generator.nextOrderNumber() << "\n"; // 1001

    auto &gen2 = OrderNumberGeneratorSingleton::getInstance();
    std::cout << "Order number: " << gen2.nextOrderNumber() << "\n"; // 1002

    // Both generator and gen2 are the same instance
    std::cout << "generator address: " << &generator << "\n";
    std::cout << "gen2 address:      " << &gen2 << "\n";

    return 0;
}

/*
Output:
OrderNumberGenerator created
Order number: 1000
Order number: 1001
Order number: 1002
generator address: 0x55a...   (same)
gen2 address:      0x55a...   (same)
*/
// Now, all order numbers are unique and sequential.
