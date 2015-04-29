#pragma once
#include "EffectStream.h"

class CCompressorEffectStream :	public CEffectStream
{
public:
	CCompressorEffectStream();
	virtual ~CCompressorEffectStream();

	virtual std::wstring EffectName() { return L"Compressor"; }

	virtual void StreamBegin();

	// the new sample is passed in.
	virtual void StreamIn(double inputSample, int channel);

	virtual void AdvanceStream();

	// Effect sould is passed out.
	virtual double StreamOut(int channel);

	virtual void StreamEnd();

private:
	// returns the sign of the argument (1, 0, or -1)
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	double m_firstThreshold;
	double m_finalThreshold;

	double m_sample0;
	double m_sample1;
};

