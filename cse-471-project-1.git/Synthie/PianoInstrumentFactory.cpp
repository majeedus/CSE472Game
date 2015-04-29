#include "stdafx.h"
#include "PianoInstrumentFactory.h"
#include "audio/DirSoundSource.h"
#include <cmath>


CPianoInstrumentFactory::CPianoInstrumentFactory(void)
{

}

CPianoInstrumentFactory::~CPianoInstrumentFactory()
{
}

CPianoInstrument *CPianoInstrumentFactory::CreateInstrument()
{
	CPianoInstrument *instrument = new CPianoInstrument();
	instrument->GetPlayer()->SetSamples(&m_fileBits[currentNoteKey][0], (int)m_fileBits[currentNoteKey].size());
	ConfigureInstrument(instrument);

	return instrument;
}

void CPianoInstrumentFactory::SetNote(CNote *note)
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
			std::map<std::wstring, std::vector<short>>::iterator entry = m_fileBits.find(key);
			if (entry != m_fileBits.end()) {
				// we already loaded the bits. Just use those.
			}
			else 
			{
				int j = 0;
				// load the new bits
				///LoadFile(key);
			}

			currentNoteKey = key;
		}
		
	}
}

// load the bits from the file into the local map
bool CPianoInstrumentFactory::LoadFile(std::wstring filename)
{
	CDirSoundSource m_file;
	if (!m_file.Open(filename.c_str()))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename.c_str();
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i<m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_fileBits[filename].push_back(frame[0]);
	}

	m_file.Close();
	return true;
}
