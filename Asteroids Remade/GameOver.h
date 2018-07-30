#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "stdafx.h"

#include "Gamestate.h"


struct Score
{
	std::string s_name;
	int s_score;
};

// Class for getting player name input following a game over
class GameOver : public Gamestate
{
	public:
		GameOver();
		GameOver(int _score);
		~GameOver();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		bool m_gettingName;
		int m_score;

		std::string m_name;
		std::vector<Score> m_hiScores;

		weak<ALLEGRO_FONT> m_font40;
		weak<ALLEGRO_FONT> m_font70;

		static bool SortScore(const Score& _x, const Score& _y);
};

#endif