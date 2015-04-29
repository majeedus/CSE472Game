#pragma once
#include "EffectStream.h"

#define BUFF_LEN 44100

class CBufferedEffectStream : public CEffectStream
{
public:
	CBufferedEffectStream();
	virtual ~CBufferedEffectStream();

	virtual void StreamBegin();

	// the new sample is passed in.
	virtual void StreamIn(double inputSample, int channel);

	virtual void AdvanceStream();

	// Effect sould is passed out.
	virtual double StreamOut(int channel);

	virtual void StreamEnd();

protected:

	void ClampToBufferBounds(int* index) {
		if (*index < 0)
			*index = BUFF_LEN + *index;

		if (*index > BUFF_LEN)
			*index = *index - BUFF_LEN;
	}

	// supports 2 channels of reverb
	int m_buffPos0;
	int m_buffPos1;

	int m_outputPos0;
	int m_outputPos1;

	double m_buffer0[BUFF_LEN];
	double m_buffer1[BUFF_LEN];

	double m_inputSample0;
	double m_inputSample1;
};

