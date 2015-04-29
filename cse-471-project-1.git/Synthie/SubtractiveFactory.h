#pragma once
#include "InstrumentFactory.h"
#include "Subtractive.h"
#include "WaveTable.h"
#include <vector>
#include <map>
class CSubtractiveFactory :
	public CInstrumentFactory
{
public:
	CSubtractiveFactory();
	~CSubtractiveFactory();

	virtual std::wstring InstrumentName() { return L"Subtractive"; }
	virtual CSubtractive* CreateInstrument();
	virtual void SetNote(CNote *note);

private:
	short buffer[44100];
	std::map<std::wstring, CWaveTable*> m_waves;
	std::wstring currentNoteKey;

};

