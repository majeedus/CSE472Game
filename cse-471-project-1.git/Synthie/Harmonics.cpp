#include "StdAfx.h"
#include "Harmonics.h"
#include <cmath>

CHarmonics::CHarmonics(void)
{
	m_vibratoFreq = 0;
	m_vibratoAmp = 0;
}

CHarmonics::~CHarmonics(void)
{
}


void CHarmonics::Start()
{
	m_time = 0;
}

bool CHarmonics::Generate()
{
	int num_harmonics = m_sampleRate / (2 * m_freq);

	double sample = 0;

	double diff = m_vibratoAmp * sin(m_time * 2 * PI * m_vibratoFreq);  // For vibrato

	for (int i = 0; i < num_harmonics && i < m_amp.size(); i++)
	{
		sample = sample + m_amp[i] * sin((i + 1) * (m_time * 2 * PI * m_freq + diff));
	}
	
	m_frame[1] = m_frame[0] = sample;

	m_time += GetSamplePeriod();

	return true;
}