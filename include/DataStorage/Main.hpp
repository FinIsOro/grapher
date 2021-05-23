#pragma once

/// <summary>
/// DataStorage namespace
/// </summary>
namespace ds
{
	/// <summary>
	/// Data info struct
	/// </summary>
	struct DataInfo
	{
		/// <summary>
		/// Length of the data
		/// </summary>
		size_t length;

		/// <summary>
		/// Pointer to the data
		/// </summary>
		const unsigned char* data;
	};

	/// <summary>
	/// Stores a specified data (copies to the heap)
	/// </summary>
	/// <param name="name">Identifier of the data</param>
	/// <param name="length">Length of the data</param>
	/// <param name="data">Pointer to the data</param>
	void store(const char* name, size_t length, const unsigned char* data);

	/// <summary>
	/// Gets data info by identifier
	/// </summary>
	/// <param name="name">Identifier of the data</param>
	/// <returns></returns>
	DataInfo& get(const char* name);
}

#define DECLARE_STORAGE(name) \
	extern const bool name;

#define START_STORAGE(name) \
	const bool name = [] \
	{

#define END_STORAGE \
		return true; \
	}();