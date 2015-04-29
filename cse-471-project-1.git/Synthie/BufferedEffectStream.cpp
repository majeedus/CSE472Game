#include "stdafx.h"
#include "BufferedEffectStream.h"


CBufferedEffectStream::CBufferedEffectStream()
{
	StreamBegin();
}

void CBufferedEffectStream::StreamBegin() {
	m_buffPos0 = m_outputPos0 = 0;
	m_buffPos1 = m_outputPos1 = 0;
	memset(m_buffer0, 0, BUFF_LEN * 8); // doubles are 8 bytes each
	memset(m_buffer1, 0, BUFF_LEN * 8);
	m_inputSample0 = 0;
	m_inputSample1 = 0;
}

// the new sample is passed in.
void CBufferedEffectStream::StreamIn(double inputSample, int channel) {
	if (channel == 0) {
		m_inputSample0 += inputSample;
	}
	else if (channel == 1) {
		m_inputSample1 += inputSample;
	}
}

// advance the position within the buffer.
void CBufferedEffectStream::AdvanceStream() {

	// channel 0
	m_buffPos0++;

	if (m_buffPos0 >= BUFF_LEN)
		m_buffPos0 = 0;

	// channel 1
	m_buffPos1++;

	if (m_buffPos1 >= BUFF_LEN)
		m_buffPos1 = 0;
}

// Effect sound is passed out.
double CBufferedEffectStream::StreamOut(int channel) {

	if (channel == 0) {
		int readPos0 = m_outputPos0;
		if (readPos0 < 0)
			readPos0 = BUFF_LEN + readPos0;

		double clamped0 = m_buffer0[readPos0];
		if (clamped0 > 65535)
			clamped0 = 65535;
		if (clamped0 < -65535)
			clamped0 = -65535;

		return clamped0;
	}
	else if (channel == 1) {
		int readPos1 = m_outputPos1;
		if (readPos1 < 0)
			readPos1 = BUFF_LEN + readPos1;

		double clamped1 = m_buffer1[readPos1];
		if (clamped1 > 65535)
			clamped1 = 65535;
		if (clamped1 < -65535)
			clamped1 = -65535;

		return clamped1;
	}

	return 0;
}

// empty implementation
void CBufferedEffectStream::StreamEnd() {

}


CBufferedEffectStream::~CBufferedEffectStream()
{
}
