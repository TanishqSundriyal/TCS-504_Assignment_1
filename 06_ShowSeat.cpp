enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat(Seat s) : seat(s), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const { return this->status == SeatStatus::AVAILABLE; }
    
    bool lockSeat() {
        if (this->status == SeatStatus::BOOKED) return false;
        this->status = SeatStatus::BOOKED;
        return true;
    }

    void releaseSeat() {
        this->status = SeatStatus::AVAILABLE;
    }

    Seat getSeat() const { return this->seat; }
};