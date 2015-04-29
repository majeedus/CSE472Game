#pragma once
#include "audionode.h"
#include <vector>

class CHarmonics :
	public CAudioNode
{
public:
	CHarmonics(void);
	~CHarmonics(void);

public:
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_freq = f; }
	void SetAmplitude(int i, double a) { m_amp[i] = a; }
	void SetAmplitude(std::vector<double> a) { m_amp = a; }
	void AddAmplitude(double a) { m_amp.push_back(a); }
	void ResetAmplitudes() { m_amp.clear(); m_amp.push_back(1); }

	void SetVibratoFreq(double f) { m_vibratoFreq = f; }
	void SetVibratoAmplitude(double a) { m_vibratoAmp = a; }

private:
	double m_freq;
	double m_time;
	std::vector<double> m_amp;

	double m_vibratoFreq;
	double m_vibratoAmp;
};