#include "stdafx.h"
#include "SubtractiveFactory.h"


CSubtractiveFactory::CSubtractiveFactory()
{
}


CSubtractiveFactory::~CSubtractiveFactory()
{
}

CSubtractive* CSubtractiveFactory::CreateInstrument()
{
	CSubtractive *instrument = new CSubtractive();
	instrument->SetWaveTable(m_waves[currentNoteKey]);
	ConfigureInstrument(instrument);

	return instrument;
}

void CSubtractiveFactory::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "note")
		{
			// check the local map to see if we already have the bits for this file
			std::wstring key = value.bstrVal;
			std::map<std::wstring, CWaveTable*>::iterator entry = m_waves.find(key);
			if (entry != m_waves.end()) {
				// we already loaded the bits. Just use those.
			}
			else
			{
				m_waves[key] = new CWaveTable();

				double freq;
				m_waves[key]->SetWaveform((key.substr(3,std::wstring::npos)));
				if (key[2] == L' ')
					freq = NoteToFrequency(key.substr(0, 2).c_str());
				else
					freq = NoteToFrequency(key.substr(0, 3).c_str());

				m_waves[key]->SetFreq(freq);
				m_waves[key]->Populate();
			}

			currentNoteKey = key;
		
			
		}
		

	}



}