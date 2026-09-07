#include <string>
#include <vector>

class Show {
private:
    int showId;
    std::string startTime;
    const Movie* movie;
    const Screen* screen;
    std::vector<ShowSeat> showSeats;

public:
    Show(int id, std::string time, const Movie* m, const Screen* s)
        : showId(id), startTime(time), movie(m), screen(s) {
        for (const auto& seat : s->getSeats()) {
            showSeats.push_back(ShowSeat(seat));
        }
    }

    int getId() const { return showId; }
    std::string getTime() const { return startTime; }
    const Movie* getMovie() const { return movie; }
    const Screen* getScreen() const { return screen; }
    std::vector<ShowSeat>& getShowSeats() { return showSeats; }
};