#pragma once
#include "EffectStream.h"
#include "BufferedEffectStream.h"

class CReverbEffectStream :	public CBufferedEffectStream
{
public:
	CReverbEffectStream();
	virtual ~CReverbEffectStream();

	virtual std::wstring EffectName() { return L"Reverb"; }

	virtual void AdvanceStream();

private:

};

