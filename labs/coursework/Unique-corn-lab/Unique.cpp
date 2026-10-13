#include <iostream>
#include <string>
#include <set>
#include <stdexcept>

class Unicorn {
private:
    std::string name;
    static std::set<std::string> takenNames;

public:
    Unicorn(const std::string& name) : name(name) {
        if (takenNames.find(name) != takenNames.end()) {
            throw std::runtime_error("A unicorn with this name already exists: " + name);
        }
        takenNames.insert(name);
        std::cout << "✨ Unicorn " << name << " has been created!\n";
    }

    ~Unicorn() {
        takenNames.erase(name);
        std::cout << "💀 Unicorn " << name << " has vanished, freeing the name.\n";
    }

    std::string getName() const { return name; }
};

std::set<std::string> Unicorn::takenNames;

int main() {
    try {
        Unicorn u1("Starlight");
        Unicorn u2("Twilight");
        // Unicorn u3("Starlight"); // duplicate name would throw
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    Unicorn u4("Starlight");
    return 0;
}
