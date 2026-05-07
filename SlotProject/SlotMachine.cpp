#include "SlotMachine.h"

SlotMachine::SlotMachine()
{
	m_window = Window();
}

SlotMachine::SlotMachine(int reelsNum, int rowsNum)
{
	m_window = Window(reelsNum, rowsNum);
}

SlotMachine::SlotMachine(int reelsNum, const std::vector<int>& rowsNum)
{
    m_window = Window(reelsNum, rowsNum);
}

void SlotMachine::SetUpDistributions()
{
    for (size_t i = 0; i < m_window.m_reelsNum; i++)
    {
        int reelLen = m_gameConfig.reels[i].strip.size();
        m_reelsDist.push_back(std::uniform_int_distribution<>(0, reelLen - 1));
    }
}

Window SlotMachine::Spin(std::mt19937& gen)
{
    // Fill every reel
    for (int reel = 0; reel < m_window.m_reelsNum; reel++) {

        int reelLen = m_gameConfig.reels[reel].strip.size();
        auto first_idx = m_reelsDist[reel](gen);

        // Fill slots in reel
        for (int row = 0; row < m_window.m_rowsNum[reel]; row++)
        {
            m_window.grid[reel][row] = m_gameConfig.reels[reel].strip[(first_idx + row) % reelLen];
        }
    }
}
