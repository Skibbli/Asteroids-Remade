#include "stdafx.h"

struct Bitmap;
struct Font;
struct SFXSample;
struct MusicSample;

class Resources
{
	public:		
		static Resources& GetInstance();
		
		void Initialise();
		Bitmap LoadBmp(std::string _name);
		weak<ALLEGRO_FONT> LoadFont(std::string _name, int _size);
		weak<SFXSample> LoadSFXSample(std::string _name);
		weak<MusicSample> LoadMusicSample(std::string _name);

		void GetVolumes(float &_masterVol, float &_musicVol, float &_sfxVol);

		void SetMasterGain(float _gain);
		void SetMusicGain(float _gain);
		void SetSFXGain(float _gain);

		void Shutdown();

	private:
		std::map<std::string, shared<ALLEGRO_BITMAP>> m_bitmaps;
		std::vector<Font> m_fonts;
		std::vector<shared<SFXSample>> m_sfxSamples;
		std::vector<shared<MusicSample>> m_musicSamples;

		float m_masterVolume;
		float m_musicVolume;
		float m_sfxVolume;

		ALLEGRO_MIXER *m_musicMixer;
		ALLEGRO_MIXER *m_sfxMixer;
		ALLEGRO_VOICE *m_mainVoice;

		Resources(Resources const&);              
		void operator=(Resources const&);

		Resources();
};