// ===== Violation Example =====
// Using a constructor with many parameters (hard to read, error-prone).

#include <iostream>
#include <string>
using namespace std;

class Sandwich {
    string bread, filling, sauce, extras;
public:
    Sandwich(const string& bread, const string& filling, const string& sauce, const string& extras)
        : bread(bread), filling(filling), sauce(sauce), extras(extras) {}

    void describe() const {
        cout << "Sandwich: " << bread << ", " << filling << ", " << sauce
             << ", Extras: " << extras << "\n";
    }
};

int main() {
    Sandwich s1("Wheat", "Paneer", "Mint", "Lettuce,Olives");
    Sandwich s2("White", "Chicken", "Mayo", "");
    s1.describe();
    s2.describe();
    return 0;
}

/*
Output:
Sandwich: Wheat, Paneer, Mint, Extras: Lettuce,Olives
Sandwich: White, Chicken, Mayo, Extras: 
*/
// Problem: Hard to remember parameter order, messy for many options, and error-prone.


// ===== Builder Pattern-Compliant Example =====

#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Sandwich {
    string bread, filling, sauce, extras;
public:
    Sandwich(const string& bread, const string& filling, const string& sauce, const string& extras)
        : bread(bread), filling(filling), sauce(sauce), extras(extras) {}

    void describe() const {
        cout << "Sandwich: " << bread << ", " << filling << ", " << sauce
             << ", Extras: " << extras << "\n";
    }
};

// Builder Interface
class SandwichBuilder {
protected:
    string bread, filling, sauce, extras;
public:
    virtual SandwichBuilder& addBread(const string& b) = 0;
    virtual SandwichBuilder& addFilling(const string& f) = 0;
    virtual SandwichBuilder& addSauce(const string& s) = 0;
    virtual SandwichBuilder& addExtras(const string& e) = 0;
    virtual unique_ptr<Sandwich> build() = 0;
    virtual ~SandwichBuilder() = default;
};

// Concrete Builder
class VegSandwichBuilder : public SandwichBuilder {
public:
    SandwichBuilder& addBread(const string& b) override { bread = b; return *this; }
    SandwichBuilder& addFilling(const string& f) override { filling = f; return *this; }
    SandwichBuilder& addSauce(const string& s) override { sauce = s; return *this; }
    SandwichBuilder& addExtras(const string& e) override { extras = e; return *this; }
    unique_ptr<Sandwich> build() override {
        return make_unique<Sandwich>(bread, filling, sauce, extras);
    }
};

// Client code
int main() {
    VegSandwichBuilder builder;
    auto sandwich = builder.addBread("Wheat")
                          .addFilling("Paneer")
                          .addSauce("Mint")
                          .addExtras("Lettuce,Olives")
                          .build();
    sandwich->describe();

    // Building another sandwich with different configuration
    auto sandwich2 = builder.addBread("White")
                            .addFilling("Cheese")
                            .addSauce("Mayo")
                            .addExtras("")
                            .build();
    sandwich2->describe();

    return 0;
}

/*
Output:
Sandwich: Wheat, Paneer, Mint, Extras: Lettuce,Olives
Sandwich: White, Cheese, Mayo, Extras: 
*/
// Client code is clear and flexible, even for many options or different sandwich types.
