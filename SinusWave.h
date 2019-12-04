#pragma once
class SinusWave
{
public:
	SinusWave(float periodMs, float minValue, float maxValue);
	void Tick(float);
	float GetValue();
	bool IsExhausted();
private:
	float m_periodLenghtMs;
	float m_currentTimePointMs;
	float m_minValue;
	float m_maxValue;

	float MapAnimationTimeToPi(float value);
};
