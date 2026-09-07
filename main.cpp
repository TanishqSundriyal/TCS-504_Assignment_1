#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Include sequentially
#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "06_ShowSeat.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

void displaySeatGrid(Show& show) {
    std::cout << "\nSCREEN-" << show.getScreen()->getScreenNumber() 
              << "  " << show.getTime() << "  |  " << show.getMovie()->getTitle() << "\n";

    std::cout << "  SILVER   ";
    for (auto& ss : show.getShowSeats()) {
        if (ss.getSeat().getType() == SeatType::SILVER) {
            std::cout << ss.getSeat().getSeatNumber() << (ss.isAvailable() ? "[] " : "[X] ");
        }
    }
    std::cout << "\n  GOLD     ";
    for (auto& ss : show.getShowSeats()) {
        if (ss.getSeat().getType() == SeatType::GOLD) {
            std::cout << ss.getSeat().getSeatNumber() << (ss.isAvailable() ? "[] " : "[X] ");
        }
    }
    std::cout << "\n  PLATINUM ";
    for (auto& ss : show.getShowSeats()) {
        if (ss.getSeat().getType() == SeatType::PLATINUM) {
            std::cout << ss.getSeat().getSeatNumber() << (ss.isAvailable() ? "[] " : "[X] ");
        }
    }
    std::cout << "\n\n  ( [] = available   [X] = booked )\n\n";
}

int main() {
    Movie m1("3 Idiots", "Hindi", 170);
    Movie m2("Interstellar", "English", 169);

    Cinema cinema("PVR Cinemas");
    
    Show s1(1, "06:00 PM", &m1, &cinema.getScreens()[0]);
    Show s2(2, "09:00 PM", &m2, &cinema.getScreens()[1]);

    std::vector<Movie> movies = {m1, m2};
    std::vector<Show> shows = {s1, s2};
    BookingService bookingService;

    int option = -1;

    while (true) {
        std::cout << "===== MOVIE TICKET BOOKING =====\n";
        std::cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        std::cout << "Choose: ";
        if (!(std::cin >> option) || option == 0) break;

        if (option == 1) {
            std::cout << "\n";
            for (size_t i = 0; i < movies.size(); ++i) {
                std::cout << "  [" << (i + 1) << "] " << movies[i].getTitle() 
                          << "\t" << movies[i].getLanguage() 
                          << "  " << movies[i].getDuration() << " min\n";
            }
            std::cout << "\nChoose movie: ";
            int movieChoice;
            std::cin >> movieChoice;

            if (movieChoice >= 1 && movieChoice <= (int)movies.size()) {
                std::cout << "  [1] Screen-1  06:00 PM\n";
                std::cout << "  [2] Screen-2  09:00 PM\n";
                std::cout << "Choose show: ";
                int showChoice;
                std::cin >> showChoice;

                if (showChoice >= 1 && showChoice <= (int)shows.size()) {
                    displaySeatGrid(shows[showChoice - 1]);
                }
            }
        } 
        else if (option == 2) {
            std::cout << "\nChoose movie: ";
            int movieChoice;
            std::cin >> movieChoice;

            std::cout << "  [1] Screen-1  06:00 PM\n";
            std::cout << "  [2] Screen-2  09:00 PM\n";
            std::cout << "Choose show: ";
            int showChoice;
            std::cin >> showChoice;

            Show* selectedShow = &shows[showChoice - 1];
            displaySeatGrid(*selectedShow);

            std::cout << "Seats (e.g. A1,B2): ";
            std::string seatInput;
            std::cin >> seatInput;

            std::vector<std::string> selectedSeatCodes;
            std::stringstream ss(seatInput);
            std::string token;
            while (std::getline(ss, token, ',')) {
                selectedSeatCodes.push_back(token);
            }

            // Display itemized cost preview
            double totalPreview = 0;
            for (const auto& code : selectedSeatCodes) {
                for (auto& seatObj : selectedShow->getShowSeats()) {
                    if (seatObj.getSeat().getSeatNumber() == code) {
                        double price = 0;
                        std::string typeStr = "";
                        if (seatObj.getSeat().getType() == SeatType::SILVER) { price = 150; typeStr = "SILVER"; }
                        else if (seatObj.getSeat().getType() == SeatType::GOLD) { price = 250; typeStr = "GOLD"; }
                        else if (seatObj.getSeat().getType() == SeatType::PLATINUM) { price = 400; typeStr = "PLATINUM"; }
                        
                        std::cout << "  " << code << " " << typeStr << " Rs." << price << "\n";
                        totalPreview += price;
                    }
                }
            }
            std::cout << "  TOTAL\t\tRs." << totalPreview << "\n\n";

            std::cout << "Pay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice;
            std::cin >> payChoice;

            Payment* payment = nullptr;
            if (payChoice == 1) payment = new UpiPayment();
            else if (payChoice == 2) payment = new CardPayment();
            else payment = new CashPayment();

            Booking* b = bookingService.createBooking(selectedShow, selectedSeatCodes, *payment);
            if (b) {
                TicketPrinter::printTicket(*b);
            }
            delete payment;
        }
        else if (option == 3) {
            std::cout << "\nEnter Booking ID to cancel: ";
            std::string id;
            std::cin >> id;
            if (bookingService.cancelBooking(id)) {
                std::cout << "Booking " << id << " cancelled. Seats released.\n\n";
            } else {
                std::cout << "Invalid Booking ID.\n\n";
            }
        }
        else if (option == 4) {
            std::cout << "\nEnter Booking ID: ";
            std::string id;
            std::cin >> id;
            Booking* b = bookingService.getBooking(id);
            if (b) TicketPrinter::printTicket(*b);
            else std::cout << "Booking not found.\n\n";
        }
    }

    std::cout << "Exiting system.\n";
    return 0;
}