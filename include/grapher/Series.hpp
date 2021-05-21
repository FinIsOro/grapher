#pragma once

#include <vector>
#include <string>

namespace grapher
{
	class Series
	{
	public:
		class RangeManager;

		class Range
		{
			friend RangeManager;

		public:
			float get(size_t index) const;

			std::string legend() const;
			size_t length() const;

		private:
			std::string name;
			std::vector<float> data;

			Range() = default;

			void insert(size_t index, float value);
			void set(size_t index, float value);
			void remove(size_t index);
		};

		class RangeManager
		{
			friend Series;

		public:
			std::vector<float> get(size_t index) const;

			size_t amount() const;
			size_t length() const;

			void add(std::string name); 

		private:
			std::vector<Range> data;

			RangeManager() = default;

			void insert(size_t index, std::vector<float> values);
			void set(size_t index, std::vector<float> values);
			void remove(size_t index);
		} ranges;

		void add(float key, std::vector<float> values);
		std::vector<float> get(float key) const;
		void remove(float key);

		const std::vector<float>& domain() const;

	private:
		std::vector<float> _domain;
	};
}