#include "stdafx.h"
#include "PianoWave.h"


CPianoWave::CPianoWave()
{
	for (int i = 0; i<12; i++)
		m_amp[i] = 1;
}


CPianoWave::~CPianoWave()
{
}

void CPianoWave::Start()
{
	m_phase = 0;
}

bool CPianoWave::Generate()
{
	double sample = 0;
	for (int i = 0; i<12; i++)
	{

	}

	m_frame[1] = m_frame[0] = sample;

	return true;
}