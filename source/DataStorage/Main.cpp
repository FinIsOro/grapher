#include <DataStorage/Main.hpp>

#include <map>
#include <string>

using namespace std;

namespace ds
{
	map<string, DataInfo> storage;

	void store(const char* name, size_t length, const unsigned char* data)
	{
		unsigned char* copy = new unsigned char[length];

		std::copy(data, data + length, copy);

		storage[name] = { length, copy };
	}

	DataInfo& get(const char* name)
	{
		return storage[name];
	}
}