#pragma once
#include "BufferedEffectStream.h"

class CFlangeEffectStream :	public CBufferedEffectStream
{
public:
	CFlangeEffectStream();
	virtual ~CFlangeEffectStream();

	virtual void StreamBegin();

	virtual std::wstring EffectName() { return L"Flange"; }

	virtual void AdvanceStream();

private:
	double m_sampleRate;
	double m_time;
};

