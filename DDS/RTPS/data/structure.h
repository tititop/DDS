#pragma once

#include <stdint.h>
#include <string>
#include <sstream>

#include "type_defines/type_defines.h"

namespace DDS::Data
{
	using __message_header_type_defines = MessageHeaderTypeDefines;
	using __submessage_header_type_defines = SubMessageHeaderTypeDefines;


#define __STRUCT_NAME MessageHeader
#define __STRUCT_BODY \
	FIELD(__message_header_type_defines::protocol_id_t,			protocol_id,			0)		\
	FIELD(__message_header_type_defines::protocol_version_t,	protocol_version,		0)		\
	FIELD(__message_header_type_defines::vendor_id_t,			vendor_id,				0)		\
	FIELD(__message_header_type_defines::guid_prefix_t,			guid_prefix,			0)		\
//
#include <reflection/serialization/serialization.h>

#define __STRUCT_NAME SubMessageHeader
#define __STRUCT_BODY \
	FIELD(__submessage_header_type_defines::submessage_kind_t,	submessage_kind,		0)		\
	FIELD(__submessage_header_type_defines::message_len_t,		message_len,			0)		\
	FIELD(__submessage_header_type_defines::submessge_flag_t,	submessge_flag,			0)		\
	FIELD(__submessage_header_type_defines::guid_sufix_t,		guid_sufix,				0)		\
//
#include <reflection/serialization/serialization.h>

	static const int MESSAGE_HEADER_LEN = sizeof(MessageHeader);
	static const int SUB_MESSAGE_HEADER_LEN = sizeof(SubMessageHeader);


	inline void MessageHeader2String(const MessageHeader& message_header, ::std::stringstream& ans) {
		ans << message_header;
	}
	inline void SubMessageHeader2String(const SubMessageHeader& message_header, ::std::stringstream& ans) {
		ans << message_header;
	}

}