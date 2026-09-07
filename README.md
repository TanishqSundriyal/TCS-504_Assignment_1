# Movie Ticket Booking System (TCS-504)

A console-based C++ cinema ticket booking system, built from a formal low-level design with functional requirements, a class diagram, and sequence diagrams for booking and cancellation.

## Overview

Customers can browse movies, view showtimes, and see a live seat map (Silver / Gold / Platinum tiers with availability). Price is calculated per seat tier, and payment runs through an abstract base class with UPI, card, and cash implementations. On successful payment, a ticket is generated with booking ID, movie, showtime, seats, and total amount. Bookings can be cancelled to release seats back to the pool.

## Features

- List currently playing movies (title, language, duration)
- List available shows for a selected movie (screen, start time)
- Display seat layout with type and availability
- Tier-based pricing: SILVER = 150, GOLD = 250, PLATINUM = 400
- Ticket generation on payment confirmation
- Booking cancellation with seat release

## Design

The design separates concerns cleanly:

| Layer | Classes |
|---|---|
| Domain entities | `Movie`, `Seat`, `Screen`, `Cinema`, `Show`, `ShowSeat`, `Customer` |
| Orchestration | `BookingService` |
| Utilities | `PriceCalculator`, `TicketPrinter` |
| Payment (pluggable) | `Payment` (abstract) → `UpiPayment`, `CardPayment`, `CashPayment` |
| Transaction record | `Booking` |

### SOLID mapping

- **SRP** — `TicketPrinter` handles formatting/printing; `PriceCalculator` handles pricing math; `Booking` only tracks its own state.
- **OCP** — new payment methods (e.g. NetBanking) can be added as a new `Payment` subclass without modifying `BookingService`.
- **LSP** — any concrete `Payment` (`UpiPayment`, `CardPayment`, `CashPayment`) can substitute for `Payment&` in `BookingService::createBooking` without breaking behavior.
- **DIP** — `BookingService` depends on the abstract `Payment` interface, not on concrete payment classes.

## Relationships

- `Cinema` **owns** `Screen` (composition)
- `Screen` **owns** `Seat` (composition)
- `Show` **references** `Movie` and `Screen` (aggregation)
- `Show` **owns** `ShowSeat` (composition)
- `Booking` **references** `Customer` (association) and **holds** `ShowSeat` (aggregation)

## Build

```bash
g++ -std=c++17 -o ticket_booking src/*.cpp
./ticket_booking
```

## Project Structure

```
src/
├── Movie.h / Movie.cpp
├── Seat.h / Seat.cpp
├── Screen.h / Screen.cpp
├── Cinema.h / Cinema.cpp
├── Show.h / Show.cpp
├── ShowSeat.h / ShowSeat.cpp
├── Customer.h / Customer.cpp
├── Payment.h
├── UpiPayment.h / UpiPayment.cpp
├── CardPayment.h / CardPayment.cpp
├── CashPayment.h / CashPayment.cpp
├── PriceCalculator.h / PriceCalculator.cpp
├── TicketPrinter.h / TicketPrinter.cpp
├── Booking.h / Booking.cpp
├── BookingService.h / BookingService.cpp
└── main.cpp
```

## Requirements

- C++17 or later
- A standard-compliant compiler (g++, clang++)

## License

For educational/portfolio use.