#include <Graph/Core/Series.hpp>

#include <stdexcept>
#include <algorithm>

namespace graph
{
    const Series::Domain& Series::domain() const
    {
        return _domain;
    }

    std::vector<Series::Range>& Series::ranges()
    {
        return _ranges;
    }

    const std::vector<Series::Range>& Series::ranges() const
    {
        return _ranges;
    }

    size_t Series::length() const
    {
        return _domain._values.size();
    }

    size_t Series::width() const
    {
        return _ranges.size();
    }

    void Series::push(float key, std::vector<float> values)
    {
        auto domainBegin = _domain._values.begin();
        auto domainEnd = _domain._values.end();

        auto domainFind = std::find(domainBegin, domainEnd, key);

        if (domainFind != domainEnd)
        {
            size_t setIndex = domainFind - domainBegin;
            size_t rangeIndex = 0;

            size_t valuesAmount = values.size();

            for (auto& range : _ranges)
            {
                float value = values[rangeIndex++];

                if (rangeIndex < valuesAmount && value != NAN)
                    range._values[setIndex] = value;
            }

            return;
        }

        auto domainInsert = std::upper_bound(domainBegin, domainEnd, key);

        size_t insertIndex = domainInsert - domainBegin;

        _domain._values.insert(domainInsert, key);
        
        size_t rangeIndex = 0;
        
        for (auto& range : _ranges)
            range._values.insert(range._values.begin() + insertIndex, values[rangeIndex++]);
    }

    void Series::remove(float key)
    {
        auto domainBegin = _domain._values.begin();
        auto domainEnd = _domain._values.end();

        auto domainFind = std::find(domainBegin, domainEnd, key);

        if (domainFind == domainEnd)
            throw std::exception("not found key");

        _domain._values.erase(domainFind);

        size_t eraseIndex = domainFind - domainBegin;

        for (auto& range : _ranges)
            range._values.erase(range._values.begin() + eraseIndex);
    }

    void Series::remove(size_t index)
    {
        checkIndex(index);

        _domain._values.erase(_domain._values.begin() + index);

        for (auto& range : _ranges)
            range._values.erase(range._values.begin() + index);
    }

    void Series::set(size_t rangeIndex, float key, float value)
    {
        checkRangeIndex(rangeIndex);

        auto domainBegin = _domain._values.begin();
        auto domainEnd = _domain._values.end();

        auto domainFind = std::find(domainBegin, domainEnd, key);

        if (domainFind == domainEnd)
            throw std::exception("not found key");

        size_t setIndex = domainFind - domainBegin;

        _ranges[rangeIndex]._values[setIndex] = value;
    }

    void Series::set(size_t rangeIndex, size_t index, float value)
    {
        checkRangeIndex(rangeIndex);
        checkIndex(index);

        _ranges[rangeIndex]._values[index] = value;
    }

    void Series::addRange()
    {
        _ranges.push_back(Range());

        if (_ranges.size() != 1)
            _ranges.back()._values.resize(_ranges[0]._values.size(), NAN);
    }

    void Series::addRanges(size_t amount)
    {
        for (; amount != 0; amount--)
            addRange();
    }

    void Series::removeRange(size_t rangeIndex)
    {
        checkRangeIndex(rangeIndex);

        _ranges.erase(_ranges.begin() + rangeIndex);
    }

    void Series::removeRanges(size_t rangeIndex, size_t amount)
    {
        size_t rangesAmount = _ranges.size();

        if (rangesAmount < amount)
            throw std::out_of_range("amount of ranges out of range");
        else if (rangesAmount == amount)
            return _ranges.clear();

        for (; amount != 0; amount--)
            if (rangeIndex < rangesAmount)
                _ranges.erase(_ranges.begin() + rangeIndex);
            else
                _ranges.pop_back();
    }

    void Series::clear()
    {
        _domain._values.clear();
        _ranges.clear();
    }

    void Series::checkRangeIndex(size_t rangeIndex) const
    {
        if (rangeIndex >= _ranges.size())
            throw std::out_of_range("range index out of range");
    }

    void Series::checkIndex(size_t index) const
    {
        if (index >= length())
            throw std::out_of_range("index out of range");
    }
}