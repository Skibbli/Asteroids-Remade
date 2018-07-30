#include "stdafx.h"

#include "Resources.h"
#include "ResourceStructs.h"
#include "Core.h"


Resources::Resources() {}

Resources& Resources::GetInstance()
{
	static Resources instance;

	return instance;
}

void Resources::Initialise()
{
	/// Default bitmap
	ALLEGRO_BITMAP *tempBMP = nullptr;
	tempBMP = al_load_bitmap("Images/missingBMP.png");

	if (tempBMP != nullptr)
	{
		shared<ALLEGRO_BITMAP> noBMP(tempBMP, al_destroy_bitmap);
		m_bitmaps.insert(std::pair<std::string, shared<ALLEGRO_BITMAP>>("Default", noBMP));
	}

	else
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Default BITMAP Load Failed", NULL, "Default BITMAP Load Failed", NULL, 0);
	}

	/// Default font
	ALLEGRO_FONT *tempFont = nullptr;

	tempFont = al_load_font("Fonts/arial.ttf", 20, 0);

	if (tempFont != nullptr)
	{
		shared<ALLEGRO_FONT> newFont(tempFont, al_destroy_font);
		m_fonts.push_back(Font("Default", 20, newFont));
	}

	else
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Default FONT Load Failed", NULL, "Default FONT Load Failed", NULL, 0);
	}

	/// Voice
	m_mainVoice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

	if(!m_mainVoice)
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Main Voice Creation Failed", NULL, "Main Voice Creation Failed", NULL, 0);
	}

	/// Mixers
	m_musicMixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if(!m_musicMixer)
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Music Mixer Creation Failed", NULL, "Music Mixer Creation Failed", NULL, 0);
	}

	if(!al_attach_mixer_to_voice(m_musicMixer, m_mainVoice))
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Music Mixer Creation Failed", NULL, "Music Mixer Creation Failed", NULL, 0);
	}

	/// Default sample
	ALLEGRO_SAMPLE *tempSamp = nullptr;
	tempSamp = al_load_sample("Samples/Missing.ogg");

	if (tempSamp != nullptr)
	{
		shared<SFXSample> newSFXSamp = std::make_shared<SFXSample>("Default", tempSamp);
		shared<MusicSample> newMusicSamp = std::make_shared<MusicSample>("Default", tempSamp, m_musicMixer);
		
		m_sfxSamples.push_back(newSFXSamp);
		m_musicSamples.push_back(newMusicSamp);
	}

	else
	{
		al_show_native_message_box(Core::GetInstance().GetDisplay(), "Default SAMPLE Load Failed", NULL, "Default SAMPLE Load Failed", NULL, 0);
	}

	m_masterVolume = 1.00f;
	m_musicVolume = 1.00f;
	m_sfxVolume = 1.00f;

	al_reserve_samples(25);
}

// Loads the requested bitmap. If already loaded returns the existing one. If load fails returns a default bitmap
Bitmap Resources::LoadBmp(std::string _name)
{
	std::map<std::string, shared<ALLEGRO_BITMAP>>::iterator it;

	it = m_bitmaps.find(_name);
	
	if (it != m_bitmaps.end())
	{
		return Bitmap(it->second);
	}

	ALLEGRO_BITMAP *tempBMP = nullptr;

	std::string filename = "Images/" +  _name;
	tempBMP = al_load_bitmap((filename).c_str());

	if (tempBMP != nullptr)
	{
		shared<ALLEGRO_BITMAP> newBMP(al_load_bitmap(filename.c_str()), al_destroy_bitmap);

		m_bitmaps.insert(std::pair<std::string, shared<ALLEGRO_BITMAP>>(_name, newBMP));
		 
		return newBMP;
	}

	else
	{
		it = m_bitmaps.find("Default");

		return Bitmap(it->second);
	}
}

// Loads the request font. If already loaded returns the existing one. If load fails returns a default font
weak<ALLEGRO_FONT> Resources::LoadFont(std::string _name, int _size)
{
	for (Font font : m_fonts)
	{
		if (font.s_name == _name && font.s_size == _size)
		{
			return font.s_font;
		}
	}

	ALLEGRO_FONT *tempFont = nullptr;

	std::string filename = "Fonts/" + _name;
	tempFont = al_load_font((filename).c_str(), _size, 0);

	if (tempFont != nullptr)
	{
		shared<ALLEGRO_FONT> newFont(tempFont, al_destroy_font);
		m_fonts.push_back(Font(_name, _size, newFont));

		return newFont;
	}

	else
	{
		for (Font font : m_fonts)
		{
			if (font.s_name == "Default")
			{
				return font.s_font;
			}
		}
	}
}

// Loads the requested SFX. If already loaded returns the existing one. If load fails returns a default SFX
weak<SFXSample> Resources::LoadSFXSample(std::string _name)
{
	for (shared<SFXSample> samp : m_sfxSamples)
	{
		if (samp->s_name == _name)
		{
			return samp;
		}
	}

	ALLEGRO_SAMPLE *tempSamp = nullptr;

	std::string filename = "Samples/" + _name;
	tempSamp = al_load_sample((filename).c_str());

	if (tempSamp != nullptr)
	{
		shared<SFXSample> newSamp = std::make_shared<SFXSample>(_name, tempSamp);

		m_sfxSamples.push_back(newSamp);

		return newSamp;
	}

	else
	{
		for (shared<SFXSample> samp : m_sfxSamples)
		{
			if (samp->s_name == "Default")
			{
				return samp;
			}
		}
	}
}

// Loads the requested music sample. If already loaded returns the existing one. If load fails returns a default music sample
weak<MusicSample> Resources::LoadMusicSample(std::string _name)
{
	for (shared<MusicSample> samp : m_musicSamples)
	{
		if (samp->s_name == _name)
		{
			return samp;
		}
	}

	ALLEGRO_SAMPLE *tempSamp = nullptr;

	std::string filename = "Samples/" + _name;
	tempSamp = al_load_sample((filename).c_str());

	if (tempSamp != nullptr)
	{
		shared<MusicSample> newSamp = std::make_shared<MusicSample>(_name, tempSamp, m_musicMixer);

		m_musicSamples.push_back(newSamp);

		return newSamp;
	}

	else
	{
		for (shared<MusicSample> samp : m_musicSamples)
		{
			if (samp->s_name == "Default")
			{
				return samp;
			}
		}
	}
}

void Resources::GetVolumes(float &_masterVol, float &_musicVol, float &_sfxVol)
{
	_masterVol = m_masterVolume;
	_musicVol = m_musicVolume;
	_sfxVol = m_sfxVolume;
}

void Resources::SetMasterGain(float _gain)
{
	m_masterVolume = _gain;

	SetMusicGain(m_musicVolume);
	SetSFXGain(m_sfxVolume);
}

void Resources::SetMusicGain(float _gain)
{
	m_musicVolume = _gain;
	al_set_mixer_gain(m_musicMixer, _gain * m_masterVolume);

	for (shared<MusicSample> samp : m_musicSamples)
	{
		samp->SetGain(_gain * m_masterVolume);
	}
}

void Resources::SetSFXGain(float _gain)
{
	m_sfxVolume = _gain;

	for (shared<SFXSample> samp : m_sfxSamples)
	{
		samp->SetGain(_gain * m_masterVolume);
	}
}

void Resources::Shutdown()
{
	m_fonts.clear();
}