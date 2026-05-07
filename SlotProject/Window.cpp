#include "Window.h"
Window::Window()
{
    m_reelsNum = 3;
    m_rowsNum.resize(3, 1);
}

Window::Window(int reelsNum, int rowsNum)
{
    m_reelsNum = reelsNum;
    m_rowsNum.resize(reelsNum, rowsNum);
}

Window::Window(int reelsNum, const std::vector<int>& rowsNum)
{
    m_reelsNum = reelsNum;
    m_rowsNum = rowsNum;
}

Symbol Window::GetSymbolOnLine(int reel, int row) const {
    return grid[reel][row];
}
