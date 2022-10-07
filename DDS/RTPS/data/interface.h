#pragma once


#include <memory>
#include <string>
#include <sstream>

#include "structure.h"

namespace DDS::Data
{
	class SubMessageElement
	{
	public:
		using ptr = ::std::shared_ptr<SubMessageElement>;

		void SetBuffer(uint8_t* buffer, size_t buffer_len)
		{
			if (nullptr == buffer && buffer_len < GetSize()) {

				return;
			}
			VSetBuffer(buffer, buffer_len);
		}

		void FromBuffer(const uint8_t* buffer, size_t buffer_len)
		{
			if (nullptr == buffer && buffer_len < GetSize()) {

				return;
			}
			VFromBuffer(buffer, buffer_len);
		}

		virtual size_t GetSize() = 0;
		virtual __submessage_header_type_defines::submessage_kind_t GetKind() = 0;
		virtual void ToString(::std::stringstream& ans) const { ans << "no define"; }

	protected:
		virtual void VSetBuffer(uint8_t* buffer, size_t buffer_len) = 0;
		virtual void VFromBuffer(const uint8_t* buffer, size_t buffer_len) = 0;

	private:

	};
}
