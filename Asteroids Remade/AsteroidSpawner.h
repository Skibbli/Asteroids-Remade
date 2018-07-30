#include "stdafx.h"


#include "ResourceStructs.h"

class BigAsteroid;
class MedAsteroid;
class SmallAsteroid;
class Explosion;
class Player;


// Spawns and controls asteroids
class AsteroidSpawner
{
	public:
		AsteroidSpawner();
		~AsteroidSpawner();

		void Start(Player* _player);
		void Update();
		void Render();
		void Shutdown();

		void SpawnAsteroids(int _num, int _size, Vec2 _pos, bool _random);
		void SpawnExplosion(Vec2 _pos, float m_size);
		// Fades font for wave announcement
		void FadeFont();

	private:
		int m_maxBigAst, m_maxMedAst, m_maxSmallAst, m_maxExp;

		float m_defWinWidth, m_defWinHeight;

		bool m_waveActive;
		bool m_fadeIn;
		bool m_waveAnnounce;

		// Wave counters
		int m_waveNo;
		float m_waveCD;
		float m_waveCDCounter;
		int m_fontAlpha;

		BigAsteroid* m_bigAsteroids;
		MedAsteroid* m_medAsteroids;
		SmallAsteroid* m_smallAsteroids;

		Player* m_player;

		Explosion* m_explosions;

		weak<ALLEGRO_FONT> m_font;
};