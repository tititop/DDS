#pragma once

#include <memory>
#include <map>

namespace DDS
{
	namespace RTPS
	{

		class Entry
		{
		public:
			using ptr = std::shared_ptr<Entry>;

			Entry() {}
			virtual ~Entry() {}

		private:

		}; // class Entry 

		class EndPoint : Entry
		{
		public:
			using ptr = std::shared_ptr<EndPoint>;

			EndPoint() {}
			virtual ~EndPoint() {}

		private:

		};

		class Participant : public Entry
		{
		public:
			using ptr = std::shared_ptr<Participant>;
			using end_point_index_t = uint64_t;

			Participant() {}
			virtual ~Participant() {}

		protected:
			std::map<end_point_index_t, EndPoint::ptr> m_end_points;

		};
	}
}
