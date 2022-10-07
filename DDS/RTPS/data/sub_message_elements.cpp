#include "sub_message_elements.h"

#include <sstream>
#include <string>
#include <iostream>

namespace DDS::Data
{
	size_t TestSubMessageElement::GetSize()
	{
		return m_str.size();
	}

	__submessage_header_type_defines::submessage_kind_t TestSubMessageElement::GetKind()
	{
		return SubMessageKind::E_SubMessageTest;
	}

	void TestSubMessageElement::SetStr(const ::std::string& str)
	{
		m_str = str;
	}

	void TestSubMessageElement::ToString(::std::stringstream& ans) const
	{
		ans << m_str;
	}

	void TestSubMessageElement::VSetBuffer(uint8_t* buffer, size_t buffer_len)
	{
		memcpy(buffer, m_str.c_str(), m_str.size());
	}

	void TestSubMessageElement::VFromBuffer(const uint8_t* buffer, size_t buffer_len)
	{
		m_str = ::std::string((const char*)buffer, 0, buffer_len);
	}

}