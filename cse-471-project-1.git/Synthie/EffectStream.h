#pragma once

#include <vector>

class CEffectStream
{
public:
	CEffectStream();
	virtual ~CEffectStream();

	virtual std::wstring EffectName() = 0;

	virtual void StreamBegin() = 0;

	// the new sample is passed in.
	virtual void StreamIn(double inputSample, int channel) = 0;

	virtual void AdvanceStream() = 0;

	// Effect sound is passed out.
	virtual double StreamOut(int channel) = 0;

	virtual void StreamEnd() = 0;
private:

};

