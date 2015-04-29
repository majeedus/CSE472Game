#pragma once
#include "Instrument.h"
#include "WaveTable.h"
#include "ADSR.h"
#include "Note.h"
#include "Notes.h"
#include <vector>
class CSubtractive :
	public CInstrument
{
public:
	CSubtractive();
	~CSubtractive();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDuration(double d) { m_adsr.SetDuration(d); }
	void SetFreq(double f) { m_waveTable->SetFreq(f); }

	void SetAmplitude(double d) { m_waveTable->SetAmplitude(d); }

	void SetWaveTable(CWaveTable* wave) { m_waveTable = wave; }

private:
	CADSR			m_adsr;
	double			m_time;
	CWaveTable*		m_waveTable;
};

