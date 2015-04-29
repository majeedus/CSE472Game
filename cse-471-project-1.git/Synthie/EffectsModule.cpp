#include "stdafx.h"
#include "EffectsModule.h"

CEffectsModule::CEffectsModule()
{
	for (int i = 0; i < 4; i++) {
		m_effectStreams[i] = NULL;
	}
}

void CEffectsModule::ProcessAudioNode(CAudioNode* node, int channel) {

	// input the sample into each effect stream at the gain specified in the node.
	for (int i = 0; i < 4; i++) {
		if (m_effectStreams[i] == NULL)
			continue;

		m_effectStreams[i]->StreamIn(node->Frame(channel) * node->GetEffectGain(i), channel);
	}
}

void CEffectsModule::ProcessBlankFrame(int channel) {
	for (int i = 0; i < 4; i++) {
		if (m_effectStreams[i] == NULL)
			continue;

		m_effectStreams[i]->StreamIn(0.0, channel);
	}
}

void CEffectsModule::AdvanceEffectStreams() {
	for (int i = 0; i < 4; i++) {
		if (m_effectStreams[i] == NULL)
			continue;

		m_effectStreams[i]->AdvanceStream();
	}
}

// The processed frame from the effecs module is the sum of the outputs of 
// each of the effect streams.
double CEffectsModule::GetProcessedFrame(int channel) {
	double sum = 0;

	for (int i = 0; i < 4; i++) {
		if (m_effectStreams[i] == NULL)
			continue;

		sum += m_effectStreams[i]->StreamOut(channel);
	}

	return sum;
}

CEffectsModule::~CEffectsModule()
{
}
