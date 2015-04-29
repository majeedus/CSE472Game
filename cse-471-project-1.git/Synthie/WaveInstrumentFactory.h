#pragma once
#include "WaveInstrument.h"
#include "InstrumentFactory.h"
#include <vector>

class CWaveInstrumentFactory : public CInstrumentFactory
{
public:
	CWaveInstrumentFactory(void);
	~CWaveInstrumentFactory(void);

	virtual std::wstring InstrumentName() { return L"Wave"; }

	virtual void SetNote(CNote *note);
	virtual CWaveInstrument *CreateInstrument();

	bool LoadFile(const char *filename);



private:
	std::vector<short> m_wave;
};

