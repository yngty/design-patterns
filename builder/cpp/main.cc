#include <algorithm>
#include <iostream>
#include <vector>

class Product1 {
public:
    std::vector<std::string> parts_;
    void listParts() const {
        std::cout << "Product parts: ";
        std::for_each(parts_.begin(), parts_.end(), [&](const auto &item) {
            if (item == parts_.back()) {
                std::cout << item;
            } else {
                std::cout << item << ", ";
            }
        });
        std::cout << "\n";
    }
};

class Builder {
public:
    ~Builder() {}
    virtual void producePartA() const = 0;
    virtual void producePartB() const = 0;
    virtual void producePartC() const = 0;
};

class ConcreteBuilder1 : public Builder {
public:
    ConcreteBuilder1() { reset(); }
    ~ConcreteBuilder1() { delete product; }
    void reset() { this->product = new Product1; }
    void producePartA() const { product->parts_.push_back("PartA1"); }
    void producePartB() const { product->parts_.push_back("PartB1"); }
    void producePartC() const { product->parts_.push_back("PartC1"); }

    Product1 *getProduct() {
        Product1 *result = product;
        reset();
        return result;
    }

private:
    Product1 *product;
};

class Director {
public:
    void setBuilder(Builder *builder) { this->builder = builder; }

    void buildMinimalViableProduct() { builder->producePartA(); }

    void buildFullFeaturedProduct() {
        builder->producePartA();
        builder->producePartB();
        builder->producePartC();
    }

private:
    Builder *builder;
};

void clientCode(Director &director) {
    ConcreteBuilder1 *builder = new ConcreteBuilder1;
    director.setBuilder(builder);

    std::cout << "Standard basic product:\n";
    director.buildMinimalViableProduct();

    Product1 *p = builder->getProduct();
    p->listParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.buildFullFeaturedProduct();

    p = builder->getProduct();
    p->listParts();
    delete p;

    std::cout << "Custom product:\n";
    builder->producePartA();
    builder->producePartC();
    p = builder->getProduct();
    p->listParts();
    delete p;

    delete builder;
}

int main(int argc, char const *argv[]) {
    Director *director = new Director();
    clientCode(*director);
    delete director;
    return 0;
}
