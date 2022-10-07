#pragma once

#include <stdint.h>
#include <map>
#include <string>
#include <memory>
#include <list>


namespace DDS
{

	static const size_t MAX_CHANGE_NUMBER = 1024 * 1024;

	using change_index_t = size_t;

	class CacheChange
	{
	public:
		using ptr = std::shared_ptr<CacheChange>;

		CacheChange() {}
		virtual ~CacheChange() {}

		change_index_t GetIndex() { return m_index; }
		void SetIndex(change_index_t index) { m_index = index; }

	private:
		change_index_t  m_index;

	};

	class HstoryCache
	{
	public:
		HstoryCache() {}
		~HstoryCache() {}

		void Init();
		void Unit();

		void addChange(CacheChange::ptr change);
		void removeChange(const change_index_t& change_idx);
		CacheChange::ptr getChange(const change_index_t& change_idx);

	private:
		std::list<change_index_t>					m_change_idxs;
		std::map<change_index_t, CacheChange::ptr>	m_changes;
	};

} // namespace DDS