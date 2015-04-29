#pragma once
#include "PianoInstrument.h"
#include "InstrumentFactory.h"
#include <map>
#include <vector>

class CPianoInstrumentFactory : public CInstrumentFactory
{
public:
	CPianoInstrumentFactory(void);
	virtual ~CPianoInstrumentFactory(void);

	virtual std::wstring InstrumentName() { return L"Piano"; }

	virtual void SetNote(CNote *note);
	virtual CPianoInstrument *CreateInstrument();

	bool LoadFile(std::wstring filename);

private:
	std::map<std::wstring, std::vector<short>> m_fileBits;

	std::wstring currentNoteKey;
};

