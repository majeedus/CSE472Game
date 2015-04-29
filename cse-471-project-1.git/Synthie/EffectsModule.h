#pragma once

#include "AudioNode.h"
#include "EffectStream.h"

class CEffectsModule
{
public:
	CEffectsModule();
	virtual ~CEffectsModule();

	// loads the given effect into the specified slot within 
	// this effects module.
	void SetEffectSlot(CEffectStream* effect, int slot) {
		m_effectStreams[slot] = effect;
	}

	void ProcessAudioNode(CAudioNode* node, int channel);

	void ProcessBlankFrame(int channel);

	void AdvanceEffectStreams();

	double GetProcessedFrame(int chanel);

private:
	CEffectStream* m_effectStreams[4];

};

