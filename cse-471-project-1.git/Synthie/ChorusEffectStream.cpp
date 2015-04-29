#include "stdafx.h"
#include "ChorusEffectStream.h"
#define _USE_MATH_DEFINES
#include <math.h>

CChorusEffectStream::CChorusEffectStream()
{
	m_sampleRate = 44100;
}

void CChorusEffectStream::StreamBegin() {
	CBufferedEffectStream::StreamBegin();
	m_altPos0 = m_altPos1 = 0;
	m_time = 0;
}

// Write the accumulated input sample to the buffer and advance the position within the buffer.
void CChorusEffectStream::AdvanceStream() {

	// channel 0
	m_buffer0[m_buffPos0] = m_inputSample0;

	int flange0 = int((0.006 + sin(0.30 * 2 * M_PI * m_time) * 0.004) * m_sampleRate);
	int altFlange0 = int((0.006 + sin(0.40 * 2 * M_PI * m_time - (M_PI / 2)) * 0.004) * m_sampleRate);
	m_outputPos0 = (m_buffPos0 - flange0);
	m_altPos0 = m_buffPos0 - altFlange0;

	ClampToBufferBounds(&m_outputPos0);
	ClampToBufferBounds(&m_altPos0);

	// channel 1
	m_buffer1[m_buffPos1] = m_inputSample1;

	int flange1 = int((0.006 + sin(0.30 * 2 * M_PI * m_time) * 0.004) * m_sampleRate);
	int altFlange1 = int((0.006 + sin(0.40 * 2 * M_PI * m_time - (M_PI / 2)) * 0.004) * m_sampleRate);
	m_outputPos1 = (m_buffPos1 - flange1);
	m_altPos1 = m_buffPos1 - altFlange1;

	ClampToBufferBounds(&m_outputPos1);
	ClampToBufferBounds(&m_altPos1);

	// avances the underlying stream
	CBufferedEffectStream::AdvanceStream();

	m_time += 1.0 / m_sampleRate;

	// reset input samples for accumulation of the next frame
	m_inputSample0 = 0;
	m_inputSample1 = 0;
}

double CChorusEffectStream::StreamOut(int channel) {

	if (channel == 0) {
		double clamped0 = m_buffer0[m_outputPos0] * 0.5 + m_buffer0[m_altPos0] * 0.5;
		if (clamped0 > 65535)
			clamped0 = 65535;
		if (clamped0 < -65535)
			clamped0 = -65535;

		return clamped0;
	}
	else if (channel == 1) {
		double clamped1 = m_buffer1[m_outputPos1] * 0.5 + m_buffer1[m_altPos1] * 0.5;
		if (clamped1 > 65535)
			clamped1 = 65535;
		if (clamped1 < -65535)
			clamped1 = -65535;

		return clamped1;
	}

	return 0;
}

CChorusEffectStream::~CChorusEffectStream()
{
}
