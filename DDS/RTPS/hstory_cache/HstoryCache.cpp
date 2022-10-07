
#include "HstoryCache.h"
#include "HstoryCache.h"
#include "HstoryCache.h"

namespace DDS
{

void HstoryCache::Init()
{
	for (int i = 0; i < MAX_CHANGE_NUMBER; i++) {
		m_change_idxs.push_back(i);
	}
	m_changes.clear();
}
void HstoryCache::Unit()
{
	m_change_idxs.clear();
	m_changes.clear();
}

void HstoryCache::addChange(CacheChange::ptr change)
{
	if (m_change_idxs.size()) {
		change_index_t ci = m_change_idxs.front();
		m_change_idxs.pop_front();

		m_changes.insert({ ci , change });
	}
}

void HstoryCache::removeChange(const change_index_t& change_idx)
{
	auto change = m_changes.find(change_idx);
	if (change != m_changes.end()) {
		m_change_idxs.push_back(change_idx);
		m_changes.erase(change);
	}
}

CacheChange::ptr HstoryCache::getChange(const change_index_t& change_idx)
{
	auto change = m_changes.find(change_idx);
	if (change == m_changes.end()) {
		return nullptr;
	}
	else {
		m_change_idxs.push_back(change_idx);
		return change->second;
	}
}

} // namespace DDS