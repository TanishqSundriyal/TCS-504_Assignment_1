#include <vector>
#include <unordered_map>
#include <iostream>

class BookingService {
private:
    std::unordered_map<std::string, Booking> bookings;

public:
    Booking* createBooking(Show* show, const std::vector<std::string>& seatNumbers, Payment& paymentMethod) {
        std::vector<ShowSeat*> selectedSeats;

        for (const auto& num : seatNumbers) {
            ShowSeat* found = nullptr;
            for (auto& ss : show->getShowSeats()) {
                if (ss.getSeat().getSeatNumber() == num) {
                    found = &ss;
                    break;
                }
            }
            if (!found || !found->isAvailable()) {
                std::cout << "[ERROR] Seat " << num << " is unavailable or invalid. Transaction aborted.\n";
                return nullptr;
            }
            selectedSeats.push_back(found);
        }

        for (auto* ss : selectedSeats) {
            ss->lockSeat();
        }

        double totalAmount = PriceCalculator::calculateTotal(selectedSeats);
        
        if (paymentMethod.pay(totalAmount)) {
            Booking newBooking(show, selectedSeats, totalAmount);
            newBooking.setStatus(BookingStatus::CONFIRMED);
            bookings.insert({newBooking.getId(), newBooking});
            return &bookings.at(newBooking.getId());
        } else {
            for (auto* ss : selectedSeats) {
                ss->releaseSeat();
            }
            std::cout << "[ERROR] Payment Failed! Seats released.\n";
            return nullptr;
        }
    }

    bool cancelBooking(const std::string& bookingId) {
        auto it = bookings.find(bookingId);
        if (it == bookings.end() || it->second.getStatus() == BookingStatus::CANCELLED) {
            return false;
        }

        for (auto* ss : it->second.getSeats()) {
            ss->releaseSeat();
        }
        it->second.setStatus(BookingStatus::CANCELLED);
        return true;
    }

    Booking* getBooking(const std::string& id) {
        if (bookings.count(id)) return &bookings.at(id);
        return nullptr;
    }
};