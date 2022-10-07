#pragma once

#ifndef __DATA_H__
#define __DATA_H__
#endif // !__DATA_H__


#include <stdint.h>
#include <map>
#include <memory>
#include <functional>
#include <minclude.h>

#include "structure.h"
#include "interface.h"
#include "sub_message_elements.h"

static std::map<
	DDS::Data::__submessage_header_type_defines::submessage_kind_t
	, std::function<DDS::Data::SubMessageElement* ()> >s_sub_message_creater = {

	{ SubMessageKind::E_SubMessageTest, []() { return new DDS::Data::TestSubMessageElement(); } }

};

namespace DDS::Data
{
	class SubMessage
	{
	public:
		using ptr = std::shared_ptr<SubMessage>;

		__submessage_header_type_defines::message_len_t GetGUIDSuffix() { return m_header.guid_sufix; }

		size_t GetSize() { return m_header.message_len; }

		void ToString(std::stringstream& ans);

		void SetBuffer(uint8_t* buffer, size_t buffer_len);
		void FromBuffer(const uint8_t* buffer, size_t buffer_len);

		void SetElement(SubMessageElement::ptr element);

	private:
		SubMessageHeader				m_header;
		SubMessageElement::ptr			m_element;
	};

	class Message
	{
	public:
		static SubMessageElement* CreateSubMessageElement(__submessage_header_type_defines::submessage_kind_t msg_kind)
		{
			SubMessageElement* ans = nullptr;
			//				std::cout << "msg_kind = " << msg_kind << std::endl;  // 此处依旧会有问题

			auto creater_it = s_sub_message_creater.find(msg_kind);
			if (creater_it != s_sub_message_creater.end()) {
				ans = creater_it->second();
			}
			else {
				pout << "no creater" << strval(msg_kind);
			}
			return ans;
		}

		static void AddSubMessageElementKind(__submessage_header_type_defines::submessage_kind_t msg_kind, std::function<SubMessageElement* ()> creater)
		{
			pout << strval(s_sub_message_creater.size());
			s_sub_message_creater[msg_kind] = creater;
			pout << strval(s_sub_message_creater.size());
		}

	private:

	public:
		void SetHeader(const MessageHeader& header) { m_header = header; }
		const MessageHeader& GetHeader() const { return m_header; }

		void ToString(std::string& ans) const;

		void SetBuffer(uint8_t* buffer, size_t buffer_len) const;
		void FromBuffer(const uint8_t* buffer, size_t buffer_len);

		void AddSubMessage(SubMessage::ptr sub_message);

		void ClearSubMessage() { m_sub_messages.clear(); }
		size_t GetAllSize() const;

	private:
		MessageHeader												m_header;
		std::map<__submessage_header_type_defines::guid_sufix_t, SubMessage::ptr>	m_sub_messages;


	};


}



