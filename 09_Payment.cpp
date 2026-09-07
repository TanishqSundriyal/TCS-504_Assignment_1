class Payment {
public:
    virtual ~Payment() {}
    virtual bool pay(double amount) = 0;
};