#include "stdafx.h"
#include "AudioNode.h"


CAudioNode::CAudioNode()
{
	m_frame[0] = 0;
	m_frame[1] = 0;
	m_sampleRate = 44100;
	m_samplePeriod = 1.0 / 44100.0;
	m_bpm = 120;

	// by default no effects will be applied to the audio node
	// all audio will bypass the effects module
	m_bypassGain = 1.0;
	m_effectGain[0] = 0;
	m_effectGain[1] = 0;
	m_effectGain[2] = 0;
	m_effectGain[3] = 0;

}

// Constructor to set the beats per minute
CAudioNode::CAudioNode(double bpm)
{
	m_frame[0] = 0;
	m_frame[1] = 0;
	m_sampleRate = 44100;
	m_samplePeriod = 1.0 / 44100.0;
	m_bpm = bpm;

}

CAudioNode::~CAudioNode()
{
}
