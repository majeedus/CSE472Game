#include "stdafx.h"
#include "WaveTable.h"


CWaveTable::CWaveTable()
{
	m_amp = 1;
	m_phase = 0;
	m_index = 0;
}


CWaveTable::~CWaveTable()
{
}

void CWaveTable::Start()
{
	m_phase = 0;
	m_index = 0;
}

void CWaveTable::Populate()
{
	if (m_waveform == L"sq")
	{

		m_table.clear();
	
		short(*audio)[2];
		audio = new short[(short)((m_sampleRate * 2) / m_freq)][2];

		double time = 0.0;
		//generates the sine wave data
		for (int i = 0; i < (m_sampleRate / m_freq); i++, time += 1. / m_sampleRate)
		{
			double j = 3.;
			double harmonic1 = m_freq * j, harmonic2 = m_freq * j;
			short sample = short((m_amp)* (sin(time * 2 * 3.1415 * m_freq) + sin(time * 2 * 3.1415 * m_freq)));
			while (harmonic1 <= m_sampleRate / 2 && harmonic2 <= m_sampleRate / 2)
			{
				sample += short((m_amp / j) * (sin(time * 2 * 3.1415 * harmonic1) + sin(time * 2 * 3.1415 * harmonic2)));
				j += 2;
				harmonic1 = m_freq * j;
				harmonic2 = m_freq * j;
			}

			audio[i][0] = sample;
			audio[i][1] = sample;

		}

		//create 2 second wavetable
		for (int i = 0; i < m_freq * 2; i++)
		{
			for (int j = 0; j < (m_sampleRate / m_freq); j++)
			{
				m_frame[0] = audio[j][0];
				m_frame[1] = audio[j][1];

				m_table.push_back((m_frame[0]));

			}
		}
		return;
	}
	else if (m_waveform == L"sw")
	{
		m_table.clear();

		short(*audio)[2];
		audio = new short[(short)((m_sampleRate * 2) / m_freq)][2];

		double time = 0.0;
		//generates the sine wave data
		for (int i = 0; i < (m_sampleRate / m_freq); i++, time += 1. / m_sampleRate)
		{
			double j = 2.;
			double harmonic1 = m_freq * j, harmonic2 = m_freq * j;
			short sample = short((m_amp)* (sin(time * 2 * 3.1415 * m_freq) + sin(time * 2 * 3.1415 * m_freq)));
			while (harmonic1 <= m_sampleRate / 2 && harmonic2 <= m_sampleRate / 2)
			{
				sample += short((m_amp / j) * (sin(time * 2 * 3.1415 * harmonic1) + sin(time * 2 * 3.1415 * harmonic2)));
				j++;
				harmonic1 = m_freq * j;
				harmonic2 = m_freq * j;
			}

			audio[i][0] = sample;
			audio[i][1] = sample;

		}

		//create 2 second wavetable
		for (int i = 0; i < m_freq * 2; i++)
		{
			for (int j = 0; j < (m_sampleRate / m_freq); j++)
			{
				m_frame[0] = audio[j][0];
				m_frame[1] = audio[j][1];

				m_table.push_back((m_frame[0]));
			}
		}
		return;
	}
	else if (m_waveform == L"tr")
	{
		m_table.clear();

		short(*audio)[2];
		audio = new short[(short)((m_sampleRate * 2) / m_freq)][2];

		double time = 0.0;
		//generates the sine wave data
		for (int i = 0; i < (m_sampleRate / m_freq); i++, time += 1. / m_sampleRate)
		{
			double j = 3.;
			double harmonic1 = m_freq * j, harmonic2 = m_freq * j;
			short sample = short((m_amp)* (sin(time * 2 * 3.1415 * m_freq) + sin(time * 2 * 3.1415 * m_freq)));
			while (harmonic1 <= m_sampleRate / 2 && harmonic2 <= m_sampleRate / 2)
			{
				int sign = ((j - 1) / 2);
				if ((sign % 2) == 0)
				{
					sample += short((m_amp / (j*j)) * (sin(time * 2 * 3.1415 * harmonic1) + sin(time * 2 * 3.1415 * harmonic2)));
				}
				else
				{
					sample += short((-1 * (m_amp) / (j*j)) * (sin(time * 2 * 3.1415 * harmonic1) + sin(time * 2 * 3.1415 * harmonic2)));
				}

				j += 2;
				harmonic1 = m_freq * j;
				harmonic2 = m_freq * j;
			}

			audio[i][0] = sample;
			audio[i][1] = sample;

		}

		//create 2 second wavetable
		for (int i = 0; i < m_freq * 2; i++)
		{
			for (int j = 0; j < (m_sampleRate / m_freq); j++)
			{
				m_frame[0] = audio[j][0];
				m_frame[1] = audio[j][1];

				m_table.push_back((m_frame[0]));

			}
		}
		return ;
	}
	else
	{
		return;
	}
}

bool CWaveTable::Generate()
{
	m_index++;
	if (m_index < m_table.size())
	{
		m_frame[0] = m_frame[1] = m_table[m_index];
		return true;
	}
	else
	{
		return false;
	}
}
