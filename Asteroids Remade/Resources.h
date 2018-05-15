#include "stdafx.h"

class Resources
{
	public:		
		static Resources& GetInstance();
		
		void Initialise();
		weak<ALLEGRO_BITMAP> LoadBmp(std::string _bmpName);
		weak<ALLEGRO_FONT> LoadFont(std::string _fontName);
		weak<ALLEGRO_SAMPLE> LoadSample(std::string _sampleName);

		void Shutdown();

	private:
		std::map<std::string, shared<ALLEGRO_BITMAP>> m_bitmaps;
		std::map<std::string, shared<ALLEGRO_FONT>> m_fonts;
		std::map<std::string, shared<ALLEGRO_SAMPLE>> m_samples;

		Resources(Resources const&);              
		void operator=(Resources const&);

		Resources();
};