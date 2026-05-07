#pragma once

#include <vector>
#include "Utils.h"


// [reel][row]
class Window
{
public:
    // -------------------------
    // | reel1 | reel2 | reel3 |
    // | reel1 | reel2 | reel3 |
    // | reel1 | reel2 | reel3 |
    // -------------------------

    //       ------------------------
    // ------ | row1 | row1 | row1 | ------
    // | row1 | row2 | row2 | row2 | row1 |
    // ------ | row3 | row3 | row3 | ------
    //       ------------------------

    int m_reelsNum;
    std::vector<int> m_rowsNum; // can be different for each reel

    // [reel][row]
    std::vector<std::vector<Symbol>> m_grid;

    Window();

    Window(int reelsNum, int rowsNum);

    Window(int reelsNum, const std::vector<int>& rowsNum);

    void InitGrid();

    Symbol GetSymbolOnLine(int reel, int row) const;
};

