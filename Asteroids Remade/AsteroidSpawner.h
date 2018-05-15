#include "stdafx.h"

#include "Asteroid.h"


class AsteroidSpawner
{
	public:
		AsteroidSpawner();
		~AsteroidSpawner();

		void Start();
		void Update();
		void Render();

		void SpawnAsteroids(int _num, int _size);

	private:
		int m_maxBigAst, m_maxMedAst, m_maxSmallAst;

		float m_displayWidth, m_displayHeight;

		BigAsteroid *m_bigAsteroids;
		MedAsteroid *m_medAsteroids;
		SmallAsteroid *m_smallAsteroids;
};