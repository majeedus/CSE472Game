#pragma once
#include "InstrumentFactory.h"
#include "ToneInstrument.h"

class CToneInstrumentFactory :
	public CInstrumentFactory
{
public:
	CToneInstrumentFactory();
	virtual ~CToneInstrumentFactory();

	virtual std::wstring InstrumentName() { return L"ToneInstrument"; }
	virtual CToneInstrument* CreateInstrument();
	virtual void SetNote(CNote *note);

private:
	double m_amplitude;
};

