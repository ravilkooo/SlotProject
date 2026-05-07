#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>
#include "Utils.h"
#include "Window.h"
#include "SlotMachine.h"

const char* symbolToStr(Symbol s) {
	switch (s) {
	case A: return "A";
	case B: return "B";
	case C: return "C";
	case WILD: return "W";
	}
	return "?";
}

GameConfig g_gameConfig;
// std::vector<Payline> paylines;
// std::vector<PayRule> payrules;

void FillPaylines()
{
	g_gameConfig.paylines.resize(4);
	g_gameConfig.paylines[0] = Payline({ 2,2,2,2,2 });
	g_gameConfig.paylines[1] = Payline({ 1,1,1,1,1 });
	g_gameConfig.paylines[2] = Payline({ 3,3,3,3,3 });
	g_gameConfig.paylines[3] = Payline({ 1,2,3,2,1 });
}

void FillRules()
{
	g_gameConfig.rules.resize(5);
	g_gameConfig.rules[0] = PayRule{Symbol::A, 3, 50};
	g_gameConfig.rules[1] = PayRule{Symbol::B, 3, 5};
	g_gameConfig.rules[2] = PayRule{Symbol::C, 3, 2};
	g_gameConfig.rules[3] = PayRule{Symbol::A, 2, 10};
	g_gameConfig.rules[4] = PayRule{Symbol::B, 2, 1};
}

#define ROWS_NUM 3
#define STRIP_LEN 10
#define REELS_NUM 5

void FillReels()
{
	g_gameConfig.reels.resize(5);
	g_gameConfig.reels[0] = Reel();
	g_gameConfig.reels[0].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
	g_gameConfig.reels[1] = Reel();
	g_gameConfig.reels[1].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
	g_gameConfig.reels[2] = Reel();
	g_gameConfig.reels[2].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
	g_gameConfig.reels[3] = Reel();
	g_gameConfig.reels[3].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
	g_gameConfig.reels[4] = Reel();
	g_gameConfig.reels[4].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
}

// left-to-right only
int EvaluateLine(const Window& window, const Payline& line, const std::vector<PayRule>& rules)
{
	std::vector<Symbol> symbols;

	for (int reel = 0; reel < window.m_grid.size(); reel++) {
		int row = line.rows[reel];
		symbols.push_back(window.m_grid[reel][row]);
	}

	int bestWin = 0;

	for (const PayRule& rule : rules)
	{
		int matchCount = 0;
		bool usedWild = false;

		for (int i = 0; i < symbols.size(); i++)
		{
			Symbol s = symbols[i];

			if (s == rule.symbol || s == WILD)
			{
				if (s == WILD)
					usedWild = true;

				matchCount++;
			}
			else
			{
				break;
			}
		}

		if (matchCount >= rule.count)
		{
			int win = rule.payout;

			// if payout depends on length:
			// win = rule.payout[matchCount];

			// Example wild multiplier
			if (usedWild)
			{
				// win *= 2; or something else
			}

			if (win > bestWin)
				bestWin = win;
		}
	}

	return bestWin;
}

int EvaluateAllLines(const Window& window) {
	int totalWin = 0;

	for (const Payline& line : g_gameConfig.paylines) {
		totalWin += EvaluateLine(window, line, g_gameConfig.rules);
	}

	return totalWin;
}

double Simulate(int spins) {
	std::mt19937 gen(std::time(nullptr));

	long long totalWin = 0;

	for (int i = 0; i < spins; i++) {
		Window w;
		// w.Spin(gen);	
		totalWin += EvaluateAllLines(w);
	}

	return (double)totalWin / spins;
}

struct Probabilities {
	double pA = 0.3;
	double pB = 0.3;
	double pC = 0.4;
};

Symbol spin(std::mt19937& gen, const Probabilities& p) {
	std::uniform_real_distribution<> dist(0.0, 1.0);
	double r = dist(gen);

	if (r < p.pA) return A;
	else if (r < p.pA + p.pB) return B;
	else return C;
}

int getPayout(Symbol s1, Symbol s2, Symbol s3) {
	if (s1 == A && s2 == A && s3 == A) return 50;
	if (s1 == B && s2 == B && s3 == B) return 5;
	if (s1 == C && s2 == C && s3 == C) return 2;
	return 0;
}

int oldSlotMachine() {
	std::mt19937 gen(std::time(nullptr));
	Probabilities prob;

	long int N = 1'000'000;
	int totalWin = 0;
	int sumSquares = 0;
	int hitCount = 0;

	std::cout << "Sample spins:\n";
	for (int i = 0; i < 10; ++i) {
		Symbol s1 = spin(gen, prob);
		Symbol s2 = spin(gen, prob);
		Symbol s3 = spin(gen, prob);
		 
		std::cout << symbolToStr(s1) << " "
			<< symbolToStr(s2) << " "
			<< symbolToStr(s3) << std::endl;
	}

	for (int i = 0; i < N; ++i) {
		Symbol s1 = spin(gen, prob);
		Symbol s2 = spin(gen, prob);
		Symbol s3 = spin(gen, prob);

		int payout = getPayout(s1, s2, s3);

		totalWin += payout;
		sumSquares += payout * payout;

		if (payout > 0)
			hitCount++;
	}

	double rtp = totalWin / N;
	double hitRate = (double)hitCount / N;

	double mean = rtp;
	double variance = (sumSquares / N) - (mean * mean);

	std::cout << "\nProbs:\n";
	std::cout << "pA =" << prob.pA << "\n";
	std::cout << "pB =" << prob.pB << "\n";
	std::cout << "pC =" << prob.pC << "\n";

	std::cout << "\nPayouts:\n";
	std::cout << "AAA =" << getPayout(Symbol::A, Symbol::A, Symbol::A) << "\n";
	std::cout << "BBB =" << getPayout(Symbol::B, Symbol::B, Symbol::B) << "\n";
	std::cout << "CCC =" << getPayout(Symbol::C, Symbol::C, Symbol::C) << "\n";

	std::cout << "\nResults:\n";
	std::cout << "RTP: " << rtp << std::endl;
	std::cout << "Hit Rate: " << hitRate << std::endl;
	std::cout << "Variance: " << variance << std::endl;

	return 0;
}

void PrintWindow(const SlotMachine& sm)
{
	int maxRowNum = 0;
	for (size_t i = 0; i < sm.m_window.m_reelsNum; i++)
	{
		maxRowNum = std::max(maxRowNum, sm.m_window.m_rowsNum[i]);
	}

	for (size_t i = 0; i < maxRowNum; i++)
	{
		for (size_t j = 0; j < sm.m_window.m_reelsNum; j++)
		{
			if (i >= sm.m_window.m_rowsNum[j])
			{
				std::cout << " ";
				continue;
			}

			std::cout << symbolToStr(sm.m_window.m_grid[j][i]);
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::vector<int> rowsNum = { 1, 3, 5, 3, 1 };
	SlotMachine sm(5, rowsNum);
	sm.m_gameConfig.paylines.resize(1);
	sm.m_gameConfig.paylines[0] = Payline({ 1,1,1 });

	sm.m_gameConfig.rules.resize(5);
	sm.m_gameConfig.rules[0] = PayRule{ Symbol::A, 3, 50 };
	sm.m_gameConfig.rules[1] = PayRule{ Symbol::B, 3, 5 };
	sm.m_gameConfig.rules[2] = PayRule{ Symbol::C, 3, 2 };

	sm.m_gameConfig.reels.resize(5);
	sm.m_gameConfig.reels[0] = Reel();
	sm.m_gameConfig.reels[0].strip = {
		Symbol::A, Symbol::A, Symbol::A,
		Symbol::B, Symbol::B, Symbol::B,
		Symbol::C, Symbol::C, Symbol::C, Symbol::WILD };
	sm.m_gameConfig.reels[1] = sm.m_gameConfig.reels[0];
	sm.m_gameConfig.reels[2] = sm.m_gameConfig.reels[0];
	sm.m_gameConfig.reels[3] = sm.m_gameConfig.reels[0];
	sm.m_gameConfig.reels[4] = sm.m_gameConfig.reels[0];

	sm.SetUpDistributions();

	std::mt19937 gen(std::time(nullptr));
	
	for (size_t i = 0; i < 10; i++)
	{
		sm.Spin(gen);
		PrintWindow(sm);
		std::cout << "------\n";
	}
}