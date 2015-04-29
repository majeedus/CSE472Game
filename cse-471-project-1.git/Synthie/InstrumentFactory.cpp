#include "stdafx.h"
#include "InstrumentFactory.h"


CInstrumentFactory::CInstrumentFactory()
{
	m_bypassGain = 1.0;
	m_effect0 = 0;
	m_effect1 = 0;
	m_effect2 = 0;
	m_effect3 = 0;
}

void CInstrumentFactory::ConfigureInstrument(CInstrument* instrument) {
	instrument->SetBypassGain(m_bypassGain);
	instrument->SetEffctGain(0, m_effect0);
	instrument->SetEffctGain(1, m_effect1);
	instrument->SetEffctGain(2, m_effect2);
	instrument->SetEffctGain(3, m_effect3);
}


CInstrumentFactory::~CInstrumentFactory()
{
}
