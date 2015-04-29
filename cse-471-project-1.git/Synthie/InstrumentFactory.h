#pragma once

#include "Instrument.h"

class CInstrumentFactory
{
public:
	CInstrumentFactory();
	virtual ~CInstrumentFactory();

	// returns the name of the instrument that this factory produces
	virtual std::wstring InstrumentName() = 0;

	// returns an instrument instance
	virtual CInstrument* CreateInstrument() = 0;

	virtual void ConfigureInstrument(CInstrument* instrument);

	virtual void SetNote(CNote *note) = 0;

	void SetGainParams(double bypass, double effect0, double effect1, double effect2, double effect3) {
		m_bypassGain = bypass; m_effect0 = effect0; m_effect1 = effect1; m_effect2 = effect2; m_effect3 = effect3;
	}

private:

	double m_bypassGain;
	double m_effect0;
	double m_effect1;
	double m_effect2;
	double m_effect3;
};

