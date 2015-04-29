#include "stdafx.h"
#include "FlangeEffectStream.h"
#define _USE_MATH_DEFINES
#include <math.h>

CFlangeEffectStream::CFlangeEffectStream()
{
	m_sampleRate = 44100;
}

void CFlangeEffectStream::StreamBegin() {
	CBufferedEffectStream::StreamBegin();

	m_time = 0;
}

// Write the accumulated input sample to the buffer and advance the position within the buffer.
void CFlangeEffectStream::AdvanceStream() {

	// channel 0
	m_buffer0[m_buffPos0] = m_inputSample0;

	int flange0 = int((0.006 + sin(0.15 * 2 * M_PI * m_time) * 0.004) * m_sampleRate);
	m_outputPos0 = (m_buffPos0 - flange0);

	if (m_outputPos0 < 0)
		m_outputPos0 = BUFF_LEN + m_outputPos0;

	if (m_outputPos0 > BUFF_LEN)
		m_outputPos0 = m_outputPos0 - BUFF_LEN;

	// channel 1
	m_buffer1[m_buffPos1] = m_inputSample1;

	int flange1 = int((0.006 + sin(0.15 * 2 * M_PI * m_time) * 0.004) * m_sampleRate);
	m_outputPos1 = (m_buffPos1 - flange1);

	if (m_outputPos1 < 0)
		m_outputPos1 = BUFF_LEN + m_outputPos1;

	if (m_outputPos1 > BUFF_LEN)
		m_outputPos1 = m_outputPos1 - BUFF_LEN;

	// avances the underlying stream
	CBufferedEffectStream::AdvanceStream();

	m_time += 1.0 / m_sampleRate;

	// reset input samples for accumulation of the next frame
	m_inputSample0 = 0;
	m_inputSample1 = 0;
}

CFlangeEffectStream::~CFlangeEffectStream()
{
}
