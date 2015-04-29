#pragma once
#include "AudioNode.h"
#include <vector>
#include <string>
#include "Organ.h"

class CWaveTable :
	public CAudioNode
{
public:
	CWaveTable();
	~CWaveTable();

	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_freq = f; }
	void SetAmplitude(double a) { m_amp = a; }
	void SetWaveform(std::wstring form){ m_waveform = form; }
	void Populate();

private:
	double m_freq;
	double m_phase;
	double m_amp;
	std::wstring m_waveform;
	std::vector<double> m_table;
	int m_index;
};
