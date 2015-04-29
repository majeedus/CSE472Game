#include "stdafx.h"
#include "CompressorEffectStream.h"


CCompressorEffectStream::CCompressorEffectStream()
{
	m_firstThreshold = .5;
	m_finalThreshold = .75;
}

void CCompressorEffectStream::StreamBegin() {
	m_sample0 = 0;
	m_sample1 = 0;
}

// the new sample is passed in.
void CCompressorEffectStream::StreamIn(double inputSample, int channel) {
	if (channel == 0) {
		m_sample0 += inputSample;
	}
	if (channel == 1) {
		m_sample1 += inputSample;
	}
}

void CCompressorEffectStream::AdvanceStream() {
	double gain0 = 1.0;
	double base0 = 0;
	double gain1 = 1.0;
	double base1 = 0;
	
	if (m_sample0 > m_firstThreshold || m_sample0 < -m_firstThreshold) {
		gain0 *= 0.5;
		base0 = m_firstThreshold * m_firstThreshold * sgn(m_sample0);
	}
	/*
	if (m_sample0 > m_finalThreshold || m_sample0 < -m_finalThreshold) {
		gain0 *= 0.5;
		base0 = 0.45 * sgn(m_sample0);
	}
	*/
	if (m_sample1 > m_firstThreshold || m_sample1 < -m_firstThreshold) {
		gain1 *= 0.5;
		base1 = m_firstThreshold * m_firstThreshold * sgn(m_sample1);
	}
	/*
	if (m_sample1 > m_finalThreshold || m_sample1 < -m_finalThreshold) {
		gain1 *= 0.5;
		base1 = 0.45 * sgn(m_sample1);
	}
	*/
	m_sample0 = (m_sample0 * gain0) + base0;
	m_sample1 = (m_sample1 * gain1) + base1;
}

// Effect sound is passed out.
double CCompressorEffectStream::StreamOut(int channel) {
	double sample = 0;
	if (channel == 0) {
		sample = m_sample0;
		m_sample0 = 0;
	}
	if (channel == 1) {
		sample = m_sample1;
		m_sample1 = 0;
	}
	return sample;
}

void CCompressorEffectStream::StreamEnd() {

}

CCompressorEffectStream::~CCompressorEffectStream()
{
}
