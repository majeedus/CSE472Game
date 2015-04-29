#pragma once
#include "EffectStream.h"
#include "BufferedEffectStream.h"

class CChorusEffectStream :	public CBufferedEffectStream
{
public:
	CChorusEffectStream();
	virtual ~CChorusEffectStream();

	virtual void StreamBegin();

	virtual std::wstring EffectName() { return L"Chorus"; }

	virtual void AdvanceStream();

	virtual double StreamOut(int channel);

private:
	double m_sampleRate;
	double m_time;

	int m_altPos0;
	int m_altPos1;
};

