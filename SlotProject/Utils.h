#pragma once
#include <vector>

enum Symbol { A, B, C, WILD };

struct Reel {
    std::vector<Symbol> strip;
};

// line in window
struct Payline {
    std::vector<int> rows;

    Payline(const std::vector<int>& rows) : rows(rows) {};
};

struct PayRule {
    Symbol symbol;
    int count;
    int payout;
};

struct GameConfig {
    std::vector<Reel> reels;
    std::vector<Payline> paylines;
    std::vector<PayRule> rules;
};