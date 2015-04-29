#pragma once
#include "AudioNode.h"
class CADSR :
	public CAudioNode
{
public:
	CADSR();
	~CADSR();
private:
	double m_duration;
	double m_time;
	double m_attack;
	double m_decay;
	double m_release;
	double m_attackAmp;
	double m_ampMult;
	double m_dampening;
	double m_pressure;
	double m_undampen;
	double m_speed;
	CAudioNode* m_source;
public:
	void SetSource(CAudioNode* const &source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	virtual void Start();
	virtual bool Generate();
	void SetAttack(double atk) { m_attack = atk; }
	void SetRelease(double rls){ m_release = rls; }
	void SetDecay(double dc) { m_decay = dc; }
	void SetAttackAmplitude(double amp){ m_attackAmp = amp; }
	double GetAttackAmplitude(){ return m_attackAmp; }
	void SetDampening(double damp){ m_dampening = damp; }
	double GetDampening(){ return m_dampening; }
	double GetAttack(){ return m_attack; }
	void SetPressure(double press){ m_pressure = press; }
	void SetAmpMult(double mult){ m_ampMult = mult; }
	void SetUndampen(double time){ m_undampen = time; }
	void SetSpeed(double speed){ m_speed = speed; }
};

