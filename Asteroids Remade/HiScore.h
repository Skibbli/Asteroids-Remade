#ifndef HISCORE_H
#define HISCORE_H

#include "stdafx.h"

#include "Gamestate.h"

class RectButton;

// Struct for storing scores from hiscore file
struct Score
{
	std::string s_name;
	int s_score;
};

class HiScore : public Gamestate
{
	public:
		HiScore();
		~HiScore();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		std::vector<Score> m_hiScores;

		RectButton* m_quitButton;

		weak<ALLEGRO_FONT> m_font120;
		weak<ALLEGRO_FONT> m_font64;
};

#endif