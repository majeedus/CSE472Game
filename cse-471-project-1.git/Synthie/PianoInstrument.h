#pragma once
#include "Instrument.h"
#include "PianoPlayer.h"
#include "PianoWave.h"
#include "ADSR.h"

class CPianoInstrument :
	public CInstrument
{
public:
	CPianoInstrument();
	virtual ~CPianoInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	CPianoPlayer *GetPlayer() { return &m_pianoPlayer; }
	const double NUM_SECS_IN_MINUTE = 60.0;

private:
	CPianoPlayer m_pianoPlayer;
	CPianoWave m_waves;
	CADSR m_adsr;
	double m_time;
};

