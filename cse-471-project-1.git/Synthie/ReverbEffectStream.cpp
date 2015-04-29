#include "stdafx.h"
#include "ReverbEffectStream.h"

#include <random>

const int delaySamples = 10000;
const double decay = 0.5;

CReverbEffectStream::CReverbEffectStream()
{
}

// Write the accumulated input sample to the buffer and advance the position within the buffer.
void CReverbEffectStream::AdvanceStream() {
	
	// channel 0
	int readPos0 = m_buffPos0 - delaySamples;

	if (readPos0 < 0)
		readPos0 = BUFF_LEN + readPos0;

	double feedback0 = m_buffer0[readPos0] * decay;

	m_buffer0[m_buffPos0] = (m_inputSample0)+(feedback0);

	// channel 1
	int readPos1 = m_buffPos1 - delaySamples;

	if (readPos1 < 0)
		readPos1 = BUFF_LEN + readPos1;

	double feedback1 = m_buffer1[readPos1] * decay;

	m_buffer1[m_buffPos1] = (m_inputSample1)+(feedback1);

	// avances the underlying stream
	CBufferedEffectStream::AdvanceStream();
	
	m_outputPos0 = m_buffPos0 - 1;
	m_outputPos1 = m_buffPos1 - 1;

	// reset input samples for accumulation of the next frame
	m_inputSample0 = 0;
	m_inputSample1 = 0;
}

CReverbEffectStream::~CReverbEffectStream()
{
}
