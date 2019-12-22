#pragma once
#include <Eigen/Core.h>
#include "SmartPointer.h"
#include "AbstractShape.h"

class Particle
{
public:

	Particle(sp<AbstractShape> shape)
	{
		Reset();

		m_shape = shape;
	}

	Particle(Eigen::Vector2f initialPosition, sp<AbstractShape> shape)
	{
		Reset();
		
		m_shape = shape;
		m_position = initialPosition;
	}

	void SetPosition(Eigen::Vector2f newPosition)
	{
		m_position = newPosition;
	}

	void SetVelocity(Eigen::Vector2f newVelocity)
	{
		m_velocity = newVelocity;
	}

	void SetAcceleration(Eigen::Vector2f newAcceleration)
	{
		m_acceleration = newAcceleration;
	}

	Eigen::Vector2f GetPosition()
	{
		return m_position;
	}

	Eigen::Vector2f GetVelocity()
	{
		return m_velocity;
	}

	Eigen::Vector2f GetAcceleration()
	{
		return m_acceleration;
	}

	int GetAge()
	{
		return m_age;
	}

	sp<AbstractShape> GetShape()
	{
		return m_shape;
	}

	void Tick()
	{
		auto test = m_acceleration[0];
		test = m_acceleration[1];

		m_velocity += m_acceleration;
		m_position += m_velocity;

		m_shape->SetPosition(Point(m_position[0], m_position[1]));
		m_age++;
	}

private:
	void Reset()
	{
		m_age = 0;

		m_position[0] = 0;
		m_position[1] = 0;
		
		m_velocity[0] = 0;
		m_velocity[1] = 0;
		
		m_acceleration[0] = 0;
		m_acceleration[1] = 0;
	}

	int m_age;
	sp<AbstractShape> m_shape;
	Eigen::Vector2f m_position;
	Eigen::Vector2f m_velocity;
	Eigen::Vector2f m_acceleration;
};
