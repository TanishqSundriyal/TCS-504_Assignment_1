#include <vector>

class PriceCalculator {
public:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    static double calculateTotal(const std::vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (const auto* s : seats) {
            switch (s->getSeat().getType()) {
                case SeatType::SILVER: total += SILVER_PRICE; break;
                case SeatType::GOLD: total += GOLD_PRICE; break;
                case SeatType::PLATINUM: total += PLATINUM_PRICE; break;
            }
        }
        return total;
    }
};