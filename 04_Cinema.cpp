#include <string>
#include <vector>

class Cinema {
private:
    std::string name;
    std::vector<Screen> screens;

public:
    Cinema(std::string n) : name(n) {
        screens.push_back(Screen(1));
        screens.push_back(Screen(2));
    }

    std::string getName() const { return name; }
    const std::vector<Screen>& getScreens() const { return screens; }
};