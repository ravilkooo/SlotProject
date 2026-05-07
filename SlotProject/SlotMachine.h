#pragma once

#include "Utils.h"
#include "Window.h"
#include <random>

class SlotMachine
{
public:
	SlotMachine();

	SlotMachine(int reelsNum, int rowsNum);

	SlotMachine(int reelsNum, const std::vector<int>& rowsNum);

	void SetUpDistributions();

	Window Spin(std::mt19937& gen);

	GameConfig m_gameConfig;
	Window m_window;

	std::vector<std::uniform_int_distribution<>> m_reelsDist;
};

