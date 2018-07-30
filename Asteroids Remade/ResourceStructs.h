#ifndef RESOURCE_STRUCTS_H
#define RESOURCE_STRUCTS_H

#include "stdafx.h"


struct DisplayInfo
{
	float s_width, s_wOffset, s_wRatio;
	float s_height, s_hOffset, s_hRatio;
};

struct Font
{
	Font(std::string _name, int _size, shared<ALLEGRO_FONT> _font) { s_name = _name; s_size = _size; s_font = _font; }

	std::string s_name;
	int s_size;
	shared<ALLEGRO_FONT> s_font;
};

struct Bitmap
{
	Bitmap() {}
	Bitmap(shared<ALLEGRO_BITMAP> _bmp)
	{
		s_bitmap = _bmp;
		s_frameWidth = al_get_bitmap_width(_bmp.get());
		s_frameHeight = al_get_bitmap_height(_bmp.get());
	}

	ALLEGRO_BITMAP* GetBitmap() { return s_bitmap.lock().get(); }

	float s_frameWidth;
	float s_frameHeight;

	weak<ALLEGRO_BITMAP> s_bitmap;
};

struct SFXSample
{
	SFXSample() {}
	SFXSample(std::string _name, ALLEGRO_SAMPLE *_samp)
	{
		s_name = _name;
		s_sample = _samp;
		s_gain = 1.0f;
	}

	void PlaySample() { al_play_sample(s_sample, s_gain, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); }

	void SetGain(float _gain) { s_gain = _gain; }

	float s_gain;
	std::string s_name;
	ALLEGRO_SAMPLE *s_sample;
};

struct MusicSample
{
	MusicSample() {}
	MusicSample(std::string _name, ALLEGRO_SAMPLE *_samp, ALLEGRO_MIXER *_mixer)
	{
		s_name = _name;
		s_sample = _samp;
		s_instance = al_create_sample_instance(NULL);
		al_set_sample(s_instance, _samp);
		al_attach_sample_instance_to_mixer(s_instance, _mixer);
		s_gain = 1.0f;
	}

	void PlaySample() {	al_play_sample_instance(s_instance); }

	void StopSample() {	al_stop_sample_instance(s_instance); }

	void SetGain(float _gain) {	s_gain = _gain; }

	float s_gain;
	std::string s_name;
	ALLEGRO_SAMPLE *s_sample;
	ALLEGRO_SAMPLE_INSTANCE *s_instance;
};

#endif