#include "stdafx.h"

#include "Resources.h"

//Resources *Resources::s_resources = 0;

Resources::Resources()
{

}

Resources& Resources::GetInstance()
{
	static Resources instance;

	return instance;

	/*if (!s_resources)
	{
		s_resources = new Resources();
		return s_resources;
	}

	else
	{
		return s_resources;
	}*/
}

void Resources::Initialise()
{
	shared<ALLEGRO_BITMAP> noBMP(al_load_bitmap("Images/missingBMP.png"), al_destroy_bitmap);
	m_bitmaps.insert(std::pair<std::string, shared<ALLEGRO_BITMAP>>("default", noBMP));

	/*shared<ALLEGRO_FONT> noFont(al_load_font("arial.ttf", 20, 0), al_destroy_font);
	m_fonts.insert(std::pair<std::string, shared<ALLEGRO_FONT>>("default", noFont));

	shared<ALLEGRO_SAMPLE> noSamp(al_load_sample("Fonts/arial.png"), al_destroy_sample);
	m_samples.insert(std::pair<std::string, shared<ALLEGRO_SAMPLE>>("default", noSamp));*/
}

weak<ALLEGRO_BITMAP> Resources::LoadBmp(std::string _bmpName)
{
	std::map<std::string, shared<ALLEGRO_BITMAP>>::iterator fuckingIT;

	for (fuckingIT = m_bitmaps.begin(); fuckingIT != m_bitmaps.end(); fuckingIT++)
	{
		if (fuckingIT->first == _bmpName)
		{
			return fuckingIT->second;
		}
	}

	ALLEGRO_BITMAP *tempBMP = nullptr;

	std::string filename = "Images/" +  _bmpName;
	tempBMP = al_load_bitmap((filename).c_str());

	if (tempBMP != nullptr)
	{
		shared<ALLEGRO_BITMAP> newBMP(al_load_bitmap(filename.c_str()), al_destroy_bitmap);
		m_bitmaps.insert(std::pair<std::string, shared<ALLEGRO_BITMAP>>(_bmpName.c_str(), newBMP));
		 
		return newBMP;
	}

	else
	{
		for (fuckingIT = m_bitmaps.begin(); fuckingIT != m_bitmaps.end(); fuckingIT++)
		{
			if (fuckingIT->first == "default")
			{
				return fuckingIT->second;
			}
		}
	}
		//return m_bitmaps.begin()->second;
}

weak<ALLEGRO_FONT> Resources::LoadFont(std::string _fontName)
{
	std::map<std::string, shared<ALLEGRO_FONT>>::iterator fuckingIT;

	for (fuckingIT = m_fonts.begin(); fuckingIT != m_fonts.end(); fuckingIT++)
	{
		if (fuckingIT->first == _fontName)
		{
			return fuckingIT->second;
		}
	}

	ALLEGRO_FONT *tempFont = nullptr;

	std::string filename = "Fonts/" + _fontName;
	tempFont = al_load_font((filename).c_str(), 20, 0);

	if (tempFont != nullptr)
	{
		shared<ALLEGRO_FONT> newFont(tempFont, al_destroy_font);
		m_fonts.insert(std::pair<std::string, shared<ALLEGRO_FONT>>(_fontName.c_str(), newFont));

		return newFont;
	}

	else
		return m_fonts.begin()->second;
}

weak<ALLEGRO_SAMPLE> Resources::LoadSample(std::string _sampleName)
{
	std::map<std::string, shared<ALLEGRO_SAMPLE>>::iterator fuckingIT;

	for (fuckingIT = m_samples.begin(); fuckingIT != m_samples.end(); fuckingIT++)
	{
		if (fuckingIT->first == _sampleName)
		{
			return fuckingIT->second;
		}
	}

	ALLEGRO_SAMPLE *tempSamp = nullptr;

	std::string filename = "Sounds/" + _sampleName;
	tempSamp = al_load_sample((filename).c_str());

	if (tempSamp != nullptr)
	{
		shared<ALLEGRO_SAMPLE> newSamp(tempSamp, al_destroy_sample);
		m_samples.insert(std::pair<std::string, shared<ALLEGRO_SAMPLE>>(_sampleName.c_str(), newSamp));

		return newSamp;
	}

	else
		return m_samples.begin()->second;
}

void Resources::Shutdown()
{
	std::map<std::string, shared<ALLEGRO_BITMAP>>::iterator fuckingIT;

	for (fuckingIT = m_bitmaps.begin(); fuckingIT != m_bitmaps.end(); fuckingIT++)
	{
		al_destroy_bitmap(fuckingIT->second.get());
	}

	std::map<std::string, shared<ALLEGRO_FONT>>::iterator fuckingIT2;

	for (fuckingIT2 = m_fonts.begin(); fuckingIT2 != m_fonts.end(); fuckingIT2++)
	{
		al_destroy_font(fuckingIT2->second.get());
	}

	std::map<std::string, shared<ALLEGRO_SAMPLE>>::iterator fuckingIT3;

	for (fuckingIT3 = m_samples.begin(); fuckingIT3 != m_samples.end(); fuckingIT3++)
	{
		al_destroy_sample(fuckingIT3->second.get());
	}
}