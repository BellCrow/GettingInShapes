#include "ParticleManager.h"
#include "Rhombus.h"

ParticleManager::ParticleManager(int maxparticleCount, int maxAge, sp<SceneBoard> sceneBoard)
{
	m_sceneBoard = sceneBoard;
	m_maxParticleCount = maxparticleCount;
	m_maxAge = maxAge;
}

void ParticleManager::AddParticle(sp<Particle> particle)
{
	m_particles.push_back(particle);
}

void ParticleManager::Tick()
{
	std::vector<sp<Particle>> toRemove;
	if (m_particles.size() < m_maxParticleCount)
	{
		SpawnNewParticle();
	}

	for (auto particle : m_particles)
	{
		auto rand = Rand(false);
		int individualMaxAge = (int)(m_maxAge * rand);
		if (particle->GetAge() > individualMaxAge)
		{
			toRemove.push_back(particle);
		}
		else
		{
			auto diffVelocity = Eigen::Vector2f(0,0);// GetRandomVelocity();
			auto currentVel = particle->GetVelocity();
			auto newVelocity = currentVel + diffVelocity + m_globalForce;
			particle->SetVelocity(newVelocity);
			particle->Tick();
		}
	}

	for (auto remove : toRemove)
	{
		m_sceneBoard->RemoveShape(remove->GetShape());
		auto eraseIter = std::remove_if(m_particles.begin(), m_particles.end(), [&remove](sp<Particle> particle) 
			{
				auto result = remove == particle;
				return result; 
			});
		m_particles.erase(eraseIter);
		//for every removed element, we add a new particle
		SpawnNewParticle();
	}
}

void ParticleManager::SetGlobalForce(Eigen::Vector2f forceDirection)
{
	m_globalForce = forceDirection;
}

inline float ParticleManager::Rand(bool negative)
{
	auto value = (float)std::rand() / (float)RAND_MAX;
	auto multiplicator = 1;
	if (negative)
	{
		multiplicator *= std::rand() % 2 == 0 ? 1 : -1;
	}
	return value * multiplicator;
}

inline Eigen::Vector2f ParticleManager::GetRandomVelocity()
{
	auto xDir = Rand() / 1;
	auto yDir = Rand(false) / 1;

	return Eigen::Vector2f(xDir, yDir);
}

void ParticleManager::SpawnNewParticle()
{
	auto initialVelocity = GetRandomVelocity();
	auto shape = std::make_shared<Rhombus>(Point(0, 0), 15, 15, Color(1.0f, Rand(), Rand(), Rand()));
	m_sceneBoard->AddShape(shape);
	auto particle = std::make_shared<Particle>(shape);
	particle->SetVelocity(initialVelocity);

	AddParticle(particle);
}
