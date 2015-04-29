#pragma once
#include "AudioNode.h"
class CPianoWave:public CAudioNode
{
public:
	CPianoWave();
	virtual ~CPianoWave();

public:
	virtual void Start();
	virtual bool Generate();

	void SetAmplitude(int i, double a) { m_amp[i] = a; }

private:
	double m_freq;
	double m_phase;
	double m_amp[12];
};

