#include <string>
#include <vector>

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

class Booking {
private:
    std::string bookingId;
    const Show* show;
    std::vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;

    static int nextBookingId;

public:
    Booking(const Show* s, std::vector<ShowSeat*> seats, double amount)
        : show(s), bookedSeats(seats), totalAmount(amount), status(BookingStatus::PENDING) {
        bookingId = "BK" + std::to_string(++nextBookingId);
    }

    void setStatus(BookingStatus s) { status = s; }
    BookingStatus getStatus() const { return status; }
    std::string getId() const { return bookingId; }
    double getAmount() const { return totalAmount; }
    const Show* getShow() const { return show; }
    const std::vector<ShowSeat*>& getSeats() const { return bookedSeats; }
};

int Booking::nextBookingId = 1000;