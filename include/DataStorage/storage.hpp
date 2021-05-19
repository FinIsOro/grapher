#pragma once

namespace ds
{
	struct DataInfo
	{
		size_t length;
		const unsigned char* begin;
	};

	void store(const char* name, size_t length, const unsigned char* data);
	DataInfo& get(const char* name);
}

#define START_STORAGE(name) const bool name = [] () {

#define END_STORAGE return true; }();