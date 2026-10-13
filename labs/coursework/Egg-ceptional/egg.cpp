#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>

class bad_egg : public std::exception {
    std::string msg_;
public:
    explicit bad_egg(std::string m = "Tried to eat a rotten egg!") : msg_(std::move(m)) {}
    const char* what() const noexcept override { return msg_.c_str(); }
};

class Egg {
protected:
    double size_; 
    std::string flavor_;
public:
    Egg(double size, std::string flavor) : size_(size), flavor_(std::move(flavor)) {}
    virtual ~Egg() = default;
    double size() const { return size_; }
    const std::string& flavor() const { return flavor_; }
    virtual void eat_egg() const = 0;
};

class ChickenEgg : public Egg {
public:
    ChickenEgg(double size, std::string flavor) : Egg(size, std::move(flavor)) {}
    void eat_egg() const override {
        std::cout << "You crack a chicken egg (size " << size() << "). The " << flavor() 
                  << " flavor is mild and creamy. It tastes fresh and comforting.\n";
    }
};

class DuckEgg : public Egg {
public:
    DuckEgg(double size, std::string flavor) : Egg(size, std::move(flavor)) {}
    void eat_egg() const override {
        std::cout << "You crack a duck egg (size " << size() << "). The " << flavor() 
                  << " flavor is richer and more buttery than a chicken egg. Delicious!\n";
    }
};

class RottenEgg : public Egg {
public:
    RottenEgg(double size, std::string flavor) : Egg(size, std::move(flavor)) {}
    void eat_egg() const override {
        throw bad_egg("Warning: This egg is rotten! Don't eat it.");
    }
};

class Carton {
    std::vector<std::unique_ptr<Egg>> eggs_;
public:
    Carton() { eggs_.reserve(12); }
    void add_egg(std::unique_ptr<Egg> e) {
        if (eggs_.size() < 12) eggs_.push_back(std::move(e));
        else std::cout << "Carton full\n";
    }
    void remove_and_eat() {
        if (eggs_.empty()) {
            std::cout << "Carton is empty.\n";
            return;
        }
        std::unique_ptr<Egg> e = std::move(eggs_.back());
        eggs_.pop_back();
        try {
            e->eat_egg();
        } catch (const bad_egg& ex) {
            std::cout << "BAD EGG FOUND: " << ex.what() << "\n";
        }
    }
    size_t count() const { return eggs_.size(); }
};

int main() {
    Carton carton;
    carton.add_egg(std::make_unique<ChickenEgg>(2.0, "plain"));
    carton.add_egg(std::make_unique<DuckEgg>(3.0, "buttery"));
    carton.add_egg(std::make_unique<ChickenEgg>(1.8, "herbed"));
    carton.add_egg(std::make_unique<ChickenEgg>(2.1, "free-range"));
    carton.add_egg(std::make_unique<RottenEgg>(2.0, "rotten"));
    carton.add_egg(std::make_unique<ChickenEgg>(2.0, "smoky"));
    carton.add_egg(std::make_unique<DuckEgg>(3.2, "rich"));
    carton.add_egg(std::make_unique<ChickenEgg>(1.9, "sweet"));
    carton.add_egg(std::make_unique<ChickenEgg>(2.0, "savory"));
    carton.add_egg(std::make_unique<RottenEgg>(2.5, "rotten"));
    carton.add_egg(std::make_unique<ChickenEgg>(2.0, "neutral"));
    carton.add_egg(std::make_unique<ChickenEgg>(2.0, "farm"));

    while (carton.count() > 0) {
        carton.remove_and_eat();
    }
    return 0;
}
