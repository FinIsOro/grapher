#include <Grapher/Series.hpp>

#include <stdexcept>
#include <algorithm>

namespace grapher
{
	void Series::add(float key, std::vector<float> values)
	{
		auto domainBegin = _domain.begin();
		auto domainEnd = _domain.end();

		auto domainKey = std::find(domainBegin, domainEnd, key);

		if (domainKey != domainEnd)
		{
			ranges.set(domainKey - domainBegin, values);

			return;
		}

		auto domainInsert = std::upper_bound(domainBegin, domainEnd, key);

		size_t insertIndex = domainInsert - domainBegin;

		_domain.insert(domainInsert, key);
		ranges.insert(insertIndex, values);
	}

	std::vector<float> Series::get(float key) const
	{
		auto domainBegin = _domain.begin();
		auto domainEnd = _domain.end();

		auto domainKey = std::find(domainBegin, domainEnd, key);

		if (domainKey == domainEnd)
			return std::vector<float>();

		return ranges.get(domainKey - domainBegin);
	}

	void Series::remove(float key)
	{
		auto domainBegin = _domain.begin();
		auto domainEnd = _domain.end();

		auto domainInsert = std::upper_bound(domainBegin, domainEnd, key);

		_domain.erase(domainInsert);
		ranges.remove(domainInsert - domainBegin);
	}

	const std::vector<float>& Series::domain() const
	{
		return _domain;
	}

	float Series::Range::get(size_t index) const
	{
		if (length() < index)
			throw std::out_of_range("Range::get index out of range");

		return data[index];
	}

	std::string Series::Range::legend() const
	{
		return name;
	}

	size_t Series::Range::length() const
	{
		return data.size();
	}

	void Series::Range::insert(size_t index, float value)
	{
		if (index > length())
			throw std::out_of_range("Range::insert index out of range");

		data.insert(data.begin() + index, value);
	}

	void Series::Range::set(size_t index, float value)
	{
		if (length() < index)
			throw std::out_of_range("Range::set index out of range");

		data[index] = value;
	}

	void Series::Range::remove(size_t index)
	{
		data.erase(data.begin() + index);
	}

	std::vector<float> Series::RangeManager::get(size_t index) const
	{
		if (length() < index)
			throw std::out_of_range("RangeManager::get index out of range");

		std::vector<float> result;

		for (auto& range : data)
			result.push_back(range.get(index));

		return result;
	}

	size_t Series::RangeManager::amount() const
	{
		return data.size();
	}

	size_t Series::RangeManager::length() const
	{
		if (data.empty())
			return 0;

		return data[0].length();
	}

	void Series::RangeManager::add(std::string name)
	{
		Range range;

		range.name = name;
		range.data.resize(length(), NAN);

		data.push_back(range);
	}

	void Series::RangeManager::insert(size_t index, std::vector<float> values)
	{
		if (index > length())
			throw std::out_of_range("RangeManager::insert index out of range");

		size_t valuesAmount = values.size();

		auto currentRange = data.begin();
		auto endRange = data.end();

		for (size_t valueIndex = 0; currentRange != endRange; currentRange++, valueIndex++)
			currentRange->insert(index, valueIndex < valuesAmount ? values[valueIndex] : NAN);
	}

	void Series::RangeManager::set(size_t index, std::vector<float> values)
	{
		if (index > length())
			throw std::out_of_range("RangeManager::insert index out of range");

		size_t valuesAmount = values.size();

		auto currentRange = data.begin();
		auto endRange = data.end();

		for (size_t valueIndex = 0; currentRange != endRange; currentRange++, valueIndex++)
			currentRange->set(index, valueIndex < valuesAmount ? values[valueIndex] : NAN);
	}

	void Series::RangeManager::remove(size_t index)
	{
		if (length() < index)
			return;

		for (auto& range : data)
			range.remove(index);
	}
}