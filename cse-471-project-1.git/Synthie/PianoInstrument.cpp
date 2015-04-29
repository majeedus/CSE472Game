#include "stdafx.h"
#include "PianoInstrument.h"


CPianoInstrument::CPianoInstrument()
{
}


CPianoInstrument::~CPianoInstrument()
{
}

void CPianoInstrument::Start()
{
	m_pianoPlayer.SetSampleRate(GetSampleRate());
	m_pianoPlayer.Start();

	m_adsr.SetSource(&m_pianoPlayer);
	m_adsr.SetSampleRate(GetSampleRate());
	m_adsr.Start();
	m_time = 0;
}


void CPianoInstrument::SetNote(CNote *note)
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

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetDuration(value.dblVal);
		}
		else if (name == "keypressure")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetPressure(value.dblVal);
		}
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetAttack(value.dblVal);
		}
		else if (name == "decay")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetDecay(value.dblVal);
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetRelease(value.dblVal);
		}
		else if (name == "setdampening")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetDampening(abs(m_adsr.GetDampening() - 1.0));
		}
		else if (name == "amplitude")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetAmpMult(value.dblVal);
		}
		else if (name == "undampen")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetUndampen(value.dblVal);
		}
		else if (name == "speed")
		{
			value.ChangeType(VT_R8);
			m_adsr.SetSpeed(value.dblVal);
		}

	}

}


bool CPianoInstrument::Generate()
{
	///bool valid = m_pianoPlayer.Generate();
	///m_frame[0] = m_pianoPlayer.Frame(0);

	bool valid = m_adsr.Generate();
	m_frame[0] = m_adsr.Frame(0);
	m_frame[1] = m_frame[0];

	return valid;
}

