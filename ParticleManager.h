#pragma once
#include "SmartPointer.h"
#include "Particle.h"
#include "Eigen/Core.h"
#include "SceneBoard.h"

#include <vector>
#include <random>


class ParticleManager
{
public:
	ParticleManager(int maxparticleCount, int maxAge, sp<SceneBoard> sceneBoard);
	void AddParticle(sp<Particle> particle);
	void Tick();
	void SetGlobalForce(Eigen::Vector2f forceDirection);
private:

	Eigen::Vector2f m_globalForce;
	sp<SceneBoard> m_sceneBoard;
	int m_maxParticleCount;
	int m_maxAge;
	std::vector<sp<Particle>> m_particles;

	float Rand(bool negative = true);
	Eigen::Vector2f GetRandomVelocity();

	void SpawnNewParticle();
};

