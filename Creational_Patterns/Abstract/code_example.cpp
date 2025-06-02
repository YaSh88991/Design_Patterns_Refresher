// ===== Violation Example =====
// Direct instantiation and mixing products manually (risk of mismatched combos).

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Abstract products
class MainCourse
{
public:
    virtual string name() const = 0;
    virtual ~MainCourse() = default;
};

class Side
{
public:
    virtual string name() const = 0;
    virtual ~Side() = default;
};

class Drink
{
public:
    virtual string name() const = 0;
    virtual ~Drink() = default;
};

// Concrete products
class Paneer : public MainCourse
{
public:
    string name() const override { return "Paneer Main Course"; }
};
class Chicken : public MainCourse
{
public:
    string name() const override { return "Chicken Main Course"; }
};
class Salad : public Side
{
public:
    string name() const override { return "Salad Side"; }
};
class Fries : public Side
{
public:
    string name() const override { return "Fries Side"; }
};
class Juice : public Drink
{
public:
    string name() const override { return "Juice"; }
};
class Soda : public Drink
{
public:
    string name() const override { return "Soda"; }
};

void assembleMeal(const string &mealType)
{
    unique_ptr<MainCourse> mainC;
    unique_ptr<Side> side;
    unique_ptr<Drink> drink;
    if (mealType == "veg")
    {
        mainC = make_unique<Paneer>();
        side = make_unique<Salad>();
        drink = make_unique<Juice>();
    }
    else if (mealType == "nonveg")
    {
        mainC = make_unique<Chicken>();
        side = make_unique<Fries>();
        drink = make_unique<Soda>();
    }
    else
    {
        cout << "Unknown meal type\n";
        return;
    }

    cout << "Main: " << mainC->name() << ", Side: " << side->name()
         << ", Drink: " << drink->name() << "\n";
}

int main()
{
    assembleMeal("veg");
    assembleMeal("nonveg");
    return 0;
}

/*
Output:
Main: Paneer Main Course, Side: Salad Side, Drink: Juice
Main: Chicken Main Course, Side: Fries Side, Drink: Soda
*/
// Problem: If you add more families or products, you must edit assembleMeal() everywhere (open to mix-ups).

// ===== Abstract Factory-Compliant Example =====

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Abstract products
class MainCourse
{
public:
    virtual string name() const = 0;
    virtual ~MainCourse() = default;
};
class Side
{
public:
    virtual string name() const = 0;
    virtual ~Side() = default;
};
class Drink
{
public:
    virtual string name() const = 0;
    virtual ~Drink() = default;
};

// Concrete Veg Products
class Paneer : public MainCourse
{
public:
    string name() const override { return "Paneer Main Course"; }
};
class Salad : public Side
{
public:
    string name() const override { return "Salad Side"; }
};
class Juice : public Drink
{
public:
    string name() const override { return "Juice"; }
};

// Concrete Non-Veg Products
class Chicken : public MainCourse
{
public:
    string name() const override { return "Chicken Main Course"; }
};
class Fries : public Side
{
public:
    string name() const override { return "Fries Side"; }
};
class Soda : public Drink
{
public:
    string name() const override { return "Soda"; }
};

// Concrete Chineese Products
class Noodles : public MainCourse
{
public:
    string name() const override { return "Chineese Main Course"; }
};
class SpringRolls : public Side
{
public:
    string name() const override { return "Spring roll Side"; }
};
class IcedTea : public Drink
{
public:
    string name() const override { return "Ice Tea Drink"; }
};

// Abstract Factory
class MealFactory
{
public:
    virtual unique_ptr<MainCourse> createMainCourse() const = 0;
    virtual unique_ptr<Side> createSide() const = 0;
    virtual unique_ptr<Drink> createDrink() const = 0;
    virtual ~MealFactory() = default;
};

// Concrete Factories
class VegMealFactory : public MealFactory
{
public:
    unique_ptr<MainCourse> createMainCourse() const override
    {
        return make_unique<Paneer>();
    }
    unique_ptr<Side> createSide() const override
    {
        return make_unique<Salad>();
    }
    unique_ptr<Drink> createDrink() const override
    {
        return make_unique<Juice>();
    }
};

class NonVegMealFactory : public MealFactory
{
public:
    unique_ptr<MainCourse> createMainCourse() const override
    {
        return make_unique<Chicken>();
    }
    unique_ptr<Side> createSide() const override
    {
        return make_unique<Fries>();
    }
    unique_ptr<Drink> createDrink() const override
    {
        return make_unique<Soda>();
    }
};

class ChineeseMealFactory : public MealFactory
{
public:
    unique_ptr<MainCourse> createMainCourse() const override
    {
        return make_unique<Noodles>();
    }
    unique_ptr<Side> createSide() const override
    {
        return make_unique<SpringRolls>();
    }
    unique_ptr<Drink> createDrink() const override
    {
        return make_unique<IcedTea>();
    }
};

// Client code
void assembleMeal(const MealFactory &factory)
{
    auto mainC = factory.createMainCourse();
    auto side = factory.createSide();
    auto drink = factory.createDrink();
    cout << "Main: " << mainC->name() << ", Side: " << side->name()
         << ", Drink: " << drink->name() << "\n";
}

int main()
{
    VegMealFactory vegFactory;
    NonVegMealFactory nonVegFactory;
    ChineeseMealFactory chineeseFactory;

    assembleMeal(vegFactory);
    assembleMeal(nonVegFactory);
    assembleMeal(chineeseFactory);
    return 0;
}

/*
Output:
Main: Paneer Main Course, Side: Salad Side, Drink: Juice
Main: Chicken Main Course, Side: Fries Side, Drink: Soda
Main: Noodles Main Course, Side: SpringRolls Side, Drink: Iced Tea
*/
// Client code never mixes families, and new meal types can be added by extending factories only.
