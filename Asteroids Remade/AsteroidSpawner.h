#include "stdafx.h"

#include "Asteroid.h"
#include "Bullet.h"


class AsteroidSpawner
{
	public:
		AsteroidSpawner();
		~AsteroidSpawner();

		void Start();
		void Update();
		void Render();

		void SpawnAsteroids(int _num, int _size, Vec2 _pos, bool _random);
		void CheckForCollisions(Bullet _bullets[], int _numBullets);

	private:
		int m_maxBigAst, m_maxMedAst, m_maxSmallAst;

		float m_displayWidth, m_displayHeight;

		BigAsteroid *m_bigAsteroids;
		MedAsteroid *m_medAsteroids;
		SmallAsteroid *m_smallAsteroids;
};