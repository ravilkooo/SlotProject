#include "Window.h"
Window::Window()
{
    m_reelsNum = 3;
    m_rowsNum.resize(3, 1);
    InitGrid();
}

Window::Window(int reelsNum, int rowsNum)
{
    m_reelsNum = reelsNum;
    m_rowsNum.resize(reelsNum, rowsNum);
    InitGrid();
}

Window::Window(int reelsNum, const std::vector<int>& rowsNum)
{
    m_reelsNum = reelsNum;
    m_rowsNum = rowsNum;
    InitGrid();
}

void Window::InitGrid()
{
    for (size_t i = 0; i < m_reelsNum; i++)
    {
        m_grid.push_back(std::vector<Symbol>(m_rowsNum[i]));
    }
}

Symbol Window::GetSymbolOnLine(int reel, int row) const {
    return m_grid[reel][row];
}
