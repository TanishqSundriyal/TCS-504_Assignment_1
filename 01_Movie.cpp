#include <string>

class Movie {
private:
    std::string title;
    std::string language;
    int durationMins;

public:
    Movie(std::string t, std::string l, int d) 
        : title(t), language(l), durationMins(d) {}

    std::string getTitle() const { return title; }
    std::string getLanguage() const { return language; }
    int getDuration() const { return durationMins; }
};