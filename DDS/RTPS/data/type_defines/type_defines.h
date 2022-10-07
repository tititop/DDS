#pragma once

#include <cstdint>

namespace DDS::Data
{
	struct MessageHeaderTypeDefines {
		using protocol_id_t = uint8_t;
		using protocol_version_t = uint8_t;
		using vendor_id_t = uint8_t;
		using guid_prefix_t = uint64_t;			// 全局标识
	};

	struct SubMessageHeaderTypeDefines {
		using submessage_kind_t = uint8_t;
		using message_len_t = uint16_t;
		using submessge_flag_t = uint8_t;
		using guid_sufix_t = uint32_t;
	};
}
