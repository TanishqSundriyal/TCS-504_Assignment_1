#include <string>

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    std::string seatNumber;
    SeatType type;

public:
    Seat(std::string num, SeatType t) : seatNumber(num), type(t) {}

    std::string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }
};