#include "stdafx.h"
#include "ADSR.h"


CADSR::CADSR()
{
	m_duration = 0.1;
	m_attack = 0.05;
	m_decay = 0.05;
	m_release = 0.05;
	m_attackAmp = 1.2;
	m_ampMult = 1.0;
	m_dampening = 0.0;
	m_pressure = 1.0;
	m_speed = 1.0;
}


CADSR::~CADSR()
{
}

void CADSR::Start()
{
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();
	m_time = 0.0;
}

bool CADSR::Generate()
{
	// Tell the component to generate an audio sample
	m_source->Generate();

	// Read the component's sample and make it our resulting frame.

	if (m_pressure != 1.0)
	{
		m_attackAmp *= m_pressure;
		m_attack /= m_pressure;
		m_decay /= m_pressure;
	}

	if (m_speed != 1.0)
	{
		m_attack /= m_speed;
	}

	double local[2];

	if (m_attack > 0 && m_time <  m_attack)
	{
		// Attack
		local[0] = m_source->Frame(0) * m_attackAmp * m_time / (m_attack);
		local[1] = m_source->Frame(1) * m_attackAmp * m_time / (m_attack);
	}
	else if (m_decay > 0 && m_time < m_decay + m_attack)
	{
		// Decay
		local[0] = m_source->Frame(0) * (m_attackAmp - ((m_attackAmp - 1) * (m_decay - m_time - m_attack)));
		local[1] = m_source->Frame(1) * (m_attackAmp - ((m_attackAmp - 1) * (m_decay - m_time - m_attack)));
	}
	else if (m_release > 0 && m_time > m_duration - m_release)
	{
		// Release
		local[0] = m_source->Frame(0) * (m_duration - m_time) / m_release;
		local[1] = m_source->Frame(1) * (m_duration - m_time) / m_release;
	}
	else
	{
		// Sustain
		local[0] = m_source->Frame(0);
		local[1] = m_source->Frame(1);
	}

	if (m_time > m_attack && m_dampening != 0)
	{
		local[0] = local[0] * exp(-m_duration*m_time);
		local[1] = local[1] * exp(-m_duration*m_time);
	}

	m_frame[0] = m_ampMult * local[0];
	m_frame[1] = m_ampMult * local[1];

	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}
