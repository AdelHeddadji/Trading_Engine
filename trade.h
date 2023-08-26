#ifndef TRADE_H
#define TRADE_H

struct Trade {
    int buyOrderId;
    int sellOrderId;
    bool buy;
    double price;
    int quantity;
    // ... additional attributes
};

#endif // TRADE_H
