#include "stdafx.h"
#include "Additive.h"
#include <sstream>
#include "stringhelp.h"

using namespace std;

#define NUM_SECS_IN_MINUTE 60

CAdditive::CAdditive()
{
}


CAdditive::~CAdditive()
{
}

void CAdditive::Start()
{
	m_harmonics.SetSampleRate(GetSampleRate());
	m_harmonics.Start();
	m_adsr.SetSource(&m_harmonics);

	m_adsr.SetSampleRate(GetSampleRate());
	m_adsr.Start();
	m_time = 0;



}


void CAdditive::SetNote(CNote *note)
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
			m_adsr.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
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
		else if (name == "vibratoFreq")
		{
			value.ChangeType(VT_R8);
			SetVibratoFreq(value.dblVal);
		}
		else if (name == "vibratoAmp")
		{
			value.ChangeType(VT_R8);
			SetVibratoAmplitude(value.dblVal);
		}
		else if (name == "harmonics")
		{
			string s = ConvertBSTRToMBS(value.bstrVal);
			istringstream stream(s);
			double new_amp;

			ResetAmplitudes();
			while (!stream.eof()){
				stream >> new_amp;
				AddAmplitude(new_amp);
			}

		}
	}

}


bool CAdditive::Generate()
{
	//m_harmonics.Generate();

	bool valid = m_adsr.Generate();

	m_frame[0] = m_adsr.Frame(0);
	m_frame[1] = m_adsr.Frame(1);

	m_time += GetSamplePeriod();
	return valid;
}
