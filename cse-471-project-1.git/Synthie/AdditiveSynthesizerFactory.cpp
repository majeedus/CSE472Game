#include "stdafx.h"
#include "AdditiveSynthersizerFactory.h"
#include <sstream>
#include "stringhelp.h"

using namespace std;


CAdditiveFactory::CAdditiveFactory()
{
}

CAdditive *CAdditiveFactory::CreateInstrument()
{
	CAdditive *instrument = new CAdditive();
	instrument->SetAmplitude(m_amp);
	ConfigureInstrument(instrument);
	return instrument;
}


void CAdditiveFactory::SetNote(CNote *note)
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

		if (name == "harmonics")
		{
			string s = ConvertBSTRToMBS(value.bstrVal);
			istringstream stream(s);
			double new_amp;

			m_amp.clear();
			while (!stream.eof()){
				stream >> new_amp;
				m_amp.push_back(new_amp);
			}

		}
	}
}

CAdditiveFactory::~CAdditiveFactory()
{
}
