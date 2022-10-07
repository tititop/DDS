#pragma once

#include "interface.h"

enum SubMessageKind
{
	E_SubMessageTest = 2,
	E_SubMessageEND
};

namespace DDS::Data
{
	class TestSubMessageElement : public SubMessageElement
	{
	public:
		using ptr = ::std::shared_ptr<TestSubMessageElement>;
		virtual size_t GetSize() override;
		virtual __submessage_header_type_defines::submessage_kind_t GetKind() override;

		virtual void ToString(::std::stringstream& ans) const override;

		void SetStr(const ::std::string& str);
		const ::std::string& GetStr() const { return m_str; }

	protected:
		virtual void VSetBuffer(uint8_t* buffer, size_t buffer_len) override;
		virtual void VFromBuffer(const uint8_t* buffer, size_t buffer_len) override;

	private:
		::std::string m_str;

	}; // class TestSubMessageElement
}


