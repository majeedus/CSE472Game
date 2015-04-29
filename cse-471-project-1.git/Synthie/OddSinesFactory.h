#pragma once

#include "OddSinesInstrument.h"
#include "InstrumentFactory.h"

class COddSinesFactory : public CInstrumentFactory
{
public:
	COddSinesFactory();
	virtual ~COddSinesFactory();

	virtual std::wstring InstrumentName() { return L"OddSines"; }
	virtual COddSinesInstrument* CreateInstrument();
	virtual void SetNote(CNote *note);

private: 
	double m_amps[4];
};

