#include <string>
#include <vector>

class Screen {
private:
    int screenNumber;
    std::vector<Seat> seats;

public:
    Screen(int num) : screenNumber(num) {
        // SILVER seats
        seats.push_back(Seat("A1", SeatType::SILVER));
        seats.push_back(Seat("A2", SeatType::SILVER));
        seats.push_back(Seat("A3", SeatType::SILVER));
        seats.push_back(Seat("A4", SeatType::SILVER));
        
        // GOLD seats
        seats.push_back(Seat("B1", SeatType::GOLD));
        seats.push_back(Seat("B2", SeatType::GOLD));
        seats.push_back(Seat("B3", SeatType::GOLD));
        
        // PLATINUM seats
        seats.push_back(Seat("C1", SeatType::PLATINUM));
        seats.push_back(Seat("C2", SeatType::PLATINUM));
    }

    int getScreenNumber() const { return screenNumber; }
    const std::vector<Seat>& getSeats() const { return seats; }
};