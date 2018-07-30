#include "stdafx.h"

#include "HiScore.h"
#include "Resources.h"
#include "Button.h"
#include "Core.h"
#include <fstream>
#include <sstream>



HiScore::HiScore()
{
	m_font64 = Resources::GetInstance().LoadFont("Orange Juice 2.0.ttf", 64);
	m_font120 = Resources::GetInstance().LoadFont("Orange Juice 2.0.ttf", 120);
	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");

	m_quitButton = new RectButton("ScoreQuitButton.png", Vec2(0.5, 0.9), 0.7, 0.14);

	// Loads high scores from high score text file and stores them
	std::string input;
	std::ifstream infile;

	infile.open("HiScores.txt", std::ifstream::in);

	if(infile.is_open())
	{
		while(std::getline(infile, input))
		{
			Score newScore;

			std::stringstream objStream(input);

			objStream >> newScore.s_name >> newScore.s_score;
			
			m_hiScores.push_back(newScore);	
		}	

		infile.close();
	}
}

void HiScore::Start()
{

}

bool HiScore::Update()
{
	// Return to title screen if button is pressed
	if(m_quitButton->Update())
	{
		Core::GetInstance().GetStateManager().RemoveLastState();
	}

	return true;
}

void HiScore::Render()
{
	al_draw_bitmap(m_background.GetBitmap(), 0, 0, NULL);

	al_draw_text(m_font120.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.05 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "High Scores");

	for(unsigned int i = 0; i < m_hiScores.size(); i++)
	{
		al_draw_textf(m_font64.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, (0.2 + i * 0.06) * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "%s %i", m_hiScores.at(i).s_name.c_str(), m_hiScores.at(i).s_score); 
	}

	m_quitButton->Render();
}

void HiScore::Shutdown()
{

}

HiScore::~HiScore() {}