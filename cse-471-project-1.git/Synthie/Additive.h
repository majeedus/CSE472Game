#pragma once
#include "instrument.h"
#include "Harmonics.h"
#include "ADSR.h"
#include "Note.h"
#include "Notes.h"

class CAdditive :
	public CInstrument
{
public:
	CAdditive(void);
	~CAdditive(void);

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDuration(double d) { m_adsr.SetDuration(d); }
	void SetFreq(double f) { m_harmonics.SetFreq(f); }

	void SetAmplitude(std::vector<double> a) { m_harmonics.SetAmplitude(a); }
	void AddAmplitude(double a) { m_harmonics.AddAmplitude(a); }
	void ResetAmplitudes() { m_harmonics.ResetAmplitudes(); }

	void SetVibratoFreq(double f) { m_harmonics.SetVibratoFreq(f); }
	void SetVibratoAmplitude(double a) { m_harmonics.SetVibratoAmplitude(a); }

private:
	CADSR			m_adsr;
	double			m_time;
	CHarmonics		m_harmonics;
};