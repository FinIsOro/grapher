#include <DataStorage/storage.hpp>

#include <map>
#include <string>

using namespace std;

namespace ds
{
	map<string, DataInfo> storage;

	void store(const char* name, size_t length, const unsigned char* data)
	{
		storage[name] = { length, data };
	}

	DataInfo& get(const char* name)
	{
		return storage[name];
	}
}