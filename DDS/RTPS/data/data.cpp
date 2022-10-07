#include "data.h"

#include <minclude.h>

#include <sstream>
#include <assert.h>

namespace DDS
{
	namespace Data
	{
		void Message::ToString(std::string& ans) const
		{
			std::stringstream ss;
			ss << "\n";
			MessageHeader2String(m_header, ss);
			ss << "\n\n";
			for (auto it : m_sub_messages) {
				it.second->ToString(ss);
				ss << "\n\n";
			}
			ans = ss.str();
		}
		void Message::SetBuffer(uint8_t* buffer, size_t buffer_len) const
		{
			for (const auto& it : m_sub_messages) {
				if (nullptr != it.second)
				{
					TypeToBuffer(m_header, buffer, buffer_len);
					it.second->SetBuffer(buffer + (MESSAGE_HEADER_LEN), buffer_len - MESSAGE_HEADER_LEN);
				}
			}
		}


		void Message::FromBuffer(const uint8_t* buffer, size_t buffer_len)
		{
			TypeFromBuffer(m_header, buffer, buffer_len);
			const uint8_t* tmp_buffer = buffer + MESSAGE_HEADER_LEN;
			size_t tmp_buffer_len = buffer_len - MESSAGE_HEADER_LEN;

			while (tmp_buffer_len)
			{
				// 读取buffer 
				SubMessage::ptr sub_msg(new SubMessage);
				sub_msg->FromBuffer(tmp_buffer, tmp_buffer_len);

				// guid 不能为0
				this->AddSubMessage(sub_msg);

				// buffer 位移
				size_t len_all = SUB_MESSAGE_HEADER_LEN + sub_msg->GetSize();
				tmp_buffer_len = tmp_buffer_len - len_all;
				buffer = buffer + len_all;
			}

		}

		void Message::AddSubMessage(SubMessage::ptr sub_message)
		{
			__submessage_header_type_defines::guid_sufix_t sub_guid = sub_message->GetGUIDSuffix();
			if (!sub_guid) {
				sub_guid = (__submessage_header_type_defines::guid_sufix_t)m_sub_messages.size() + 1;
			}
			m_sub_messages[sub_guid] = sub_message;
		}

		size_t Message::GetAllSize() const
		{
			size_t ans = MESSAGE_HEADER_LEN;
			ans += m_sub_messages.size() * SUB_MESSAGE_HEADER_LEN;
			for (auto it : m_sub_messages) {
				ans += it.second->GetSize();
			}

			return ans;
		}



		void SubMessage::FromBuffer(const uint8_t* buffer, size_t buffer_len)
		{
			TypeFromBuffer(m_header, buffer, buffer_len);
			m_element = SubMessageElement::ptr(Message::CreateSubMessageElement(m_header.submessage_kind));

			if (nullptr != m_element)
			{
				m_element->FromBuffer(buffer + (SUB_MESSAGE_HEADER_LEN), buffer_len - SUB_MESSAGE_HEADER_LEN);
			}
			else {
				assert(false);
			}
		}

		void SubMessage::SetElement(SubMessageElement::ptr element)
		{
			m_element = element;
			m_header.submessage_kind = m_element->GetKind();
			m_header.message_len = (__submessage_header_type_defines::message_len_t)m_element->GetSize();
		}

		void SubMessage::ToString(std::stringstream& ans)
		{
			SubMessageHeader2String(m_header, ans);
			m_element->ToString(ans);
		}

		void SubMessage::SetBuffer(uint8_t* buffer, size_t buffer_len)
		{
			if (nullptr != m_element)
			{
				m_header.message_len = (__submessage_header_type_defines::message_len_t)m_element->GetSize();

				TypeToBuffer(m_header, buffer, buffer_len);
				m_element->SetBuffer(buffer + (SUB_MESSAGE_HEADER_LEN), buffer_len - SUB_MESSAGE_HEADER_LEN);
			}
		}
	}
}