#pragma once
class SinusWave
{
public:
	SinusWave(long long periodMs, float minValue, float maxValue);
	void Tick(long long);
	float GetValue();
	bool IsExhausted();
private:
	long long m_periodLenghtMs;
	long long m_currentTimePointMs;
	float m_minValue;
	float m_maxValue;

	float MapAnimationTimeToPi(float value);
};
