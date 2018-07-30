#include "stdafx.h"

#include "GameOver.h"
#include "Input.h"
#include "Resources.h"
#include "Core.h"
#include "Title.h"
#include <fstream>
#include <algorithm>
#include <sstream>


GameOver::GameOver() {}

GameOver::GameOver(int _score)
{
	m_score = _score;
	m_name = "";
	m_gettingName = true;

	m_font40 = Resources::GetInstance().LoadFont("Arial.ttf", 40);
	m_font70 = Resources::GetInstance().LoadFont("Arial.ttf", 70);
	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");

	// Loads previous high scores from the high score file
	std::string input;
	std::ifstream infile;
	infile.open("HiScores.txt");
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

void GameOver::Start()
{

}

bool GameOver::Update()
{
	// Gets name input from the player
	if(m_gettingName)
	{
		std::vector<int> keys = Input::GetInstance().GetKeysPressed();

		for(int x : keys)
		{
			switch(x)
			{
				case 8:
					{
						if(!m_name.empty())
						{
							m_name.pop_back();
						}
					}
					break;
				case 13: 
					{
							m_gettingName = false;
					}
					break;
				default:
					{
						if((x <= 125) && (x >= 32))
						{
							if(0 < m_name.size() < 14)
							{
								m_name += (char)x;
							}
						}
					}
					break;
			}
		}
	}

	// When name input is finished adds the new score to the list, sorts the list and exports it to the text file
	else
	{
		if(Input::GetInstance().GetButtonDown(0))
		{
			Score newScore;
			newScore.s_name = m_name;
			newScore.s_score = m_score;

			m_hiScores.push_back(newScore);

			std::sort(m_hiScores.begin(), m_hiScores.end(), SortScore);

			std::ofstream outfile;

			outfile.open("HiScores.txt", std::ios_base::out | std::ios_base::trunc);
	
			for(unsigned int i = 0; i < m_hiScores.size() && i < 10; i++)
			{
				outfile << m_hiScores[i].s_name << " " << m_hiScores[i].s_score << "\n";
			}

			outfile.close();



			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<Title>());
		}
	}

	return true;
}

void GameOver::Render()
{
	al_draw_bitmap(m_background.GetBitmap(), 0, 0, NULL);

	al_draw_text(m_font70.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.1 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "GAME OVER");

	if(m_gettingName)
	{
		al_draw_textf(m_font40.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.45 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "You scored: %i", m_score);
		al_draw_textf(m_font40.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.55 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "Enter your name: %s", m_name.c_str());
		al_draw_textf(m_font40.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.75 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "Press Enter to finish", m_name.c_str());
	}

	else
	{
		al_draw_textf(m_font70.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.40 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "%s scored %i!", m_name.c_str(), m_score);
		al_draw_text(m_font70.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.65 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "Click to return to");
		al_draw_text(m_font70.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.72 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "the title screen");
	}
}

// Compares two scores
bool GameOver::SortScore(const Score& _x, const Score& _y)
{
	return _x.s_score > _y.s_score;
}

void GameOver::Shutdown() {}

GameOver::~GameOver() {}