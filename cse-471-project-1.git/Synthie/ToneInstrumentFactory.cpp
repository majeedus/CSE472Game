#include "stdafx.h"
#include "ToneInstrumentFactory.h"


CToneInstrumentFactory::CToneInstrumentFactory()
{
	m_amplitude = 0.3;
}

CToneInstrument *CToneInstrumentFactory::CreateInstrument()
{
	CToneInstrument *instrument = new CToneInstrument();
	instrument->SetAmplitude(m_amplitude);
	ConfigureInstrument(instrument);
	return instrument;
}


void CToneInstrumentFactory::SetNote(CNote *note)
{	

}

CToneInstrumentFactory::~CToneInstrumentFactory()
{
}
