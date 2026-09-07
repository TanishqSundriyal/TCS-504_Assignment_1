#include <iostream>

class TicketPrinter {
public:
    static void printTicket(const Booking& booking) {
        std::cout << "\n================= TICKET =================\n";
        std::cout << "  Booking ID : " << booking.getId() << "\n";
        std::cout << "  Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        std::cout << "  Screen     : Screen-" << booking.getShow()->getScreen()->getScreenNumber()
                  << "  " << booking.getShow()->getTime() << "\n";
        std::cout << "  Seats      : ";
        for (size_t i = 0; i < booking.getSeats().size(); ++i) {
            std::cout << booking.getSeats()[i]->getSeat().getSeatNumber() 
                      << (i + 1 < booking.getSeats().size() ? ", " : "");
        }
        std::cout << "\n  Amount     : Rs." << booking.getAmount() 
                  << "\tStatus: " << (booking.getStatus() == BookingStatus::CONFIRMED ? "CONFIRMED" : "FAILED") << "\n";
        std::cout << "==========================================\n\n";
    }
};