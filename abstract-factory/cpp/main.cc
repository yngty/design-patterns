#include <iostream>

class AbstractProductA
{
public:
    virtual ~AbstractProductA() {}
    virtual std::string usefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{

public:
    std::string usefulFunctionA() const
    {
        return "The result of the product A1.";
    }
};

class AbstractProductB
{
public:
    virtual ~AbstractProductB() {}
    virtual std::string usefulFunctionB() const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
    virtual std::string usefulFunctionB() const
    {
        return "The result of the product B1.";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    virtual std::string usefulFunctionB() const
    {
        return "The result of the product B2.";
    }
};

class AbstractFactory
{
public:
    virtual AbstractProductA *createProductA() const = 0;
    virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const
    {
        return new ConcreteProductA1();
    }

    AbstractProductB *createProductB() const
    {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const
    {
        return new ConcreteProductA1();
    }

    AbstractProductB *createProductB() const
    {
        return new ConcreteProductB2();
    }
};

void clientCode(const AbstractFactory &factory)
{
    const AbstractProductA *productA = factory.createProductA();
    const AbstractProductB *productB = factory.createProductB();
    std::cout << productA->usefulFunctionA() << "\n";
    std::cout << productB->usefulFunctionB() << "\n";
    delete productA;
}

int main(int argc, char const *argv[])
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    clientCode(*f1);

    std::cout << "Client: Testing client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    clientCode(*f2);
    return 0;
}
