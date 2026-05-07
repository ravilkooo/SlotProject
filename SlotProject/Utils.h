#pragma once
#include <vector>

enum Symbol { A, B, C, WILD };

struct Reel {
    std::vector<Symbol> strip;
};

// [reel][row]
struct Window {
    // -------------------------
    // | reel1 | reel2 | reel3 |
    // | reel1 | reel2 | reel3 |
    // | reel1 | reel2 | reel3 |
    // -------------------------

    // -------------------------
    // | row1 | row1 | row1 |
    // | row2 | row2 | row2 |
    // | row3 | row3 | row3 |
    // -------------------------

    // [reel][row]
    std::vector<std::vector<Symbol>> grid;
};

// line in window
struct Payline {
    std::vector<int> rows;

    Payline(std::vector<int> rows) : rows(rows) {};
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