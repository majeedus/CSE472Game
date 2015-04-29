#pragma once
#include "InstrumentFactory.h"
#include "Additive.h"

class CAdditiveFactory :
	public CInstrumentFactory
{
public:
	CAdditiveFactory();
	virtual ~CAdditiveFactory();

	virtual std::wstring InstrumentName() { return L"Additive"; }
	virtual CAdditive* CreateInstrument();
	virtual void SetNote(CNote *note);

private:
	std::vector<double> m_amp;

};

