#include <Graph/Graphics/Chart.hpp>
#include <Graph/Utils/UI.hpp>

#include <sstream>

using namespace sf;
using namespace std;

namespace graph
{
	Color hsv(float h, float s, float v)
	{
		float r, g, b;

		const int hi = static_cast<int>(h / 60.0f) % 6;

		const float f = (h / 60.0f) - hi;
		const float p = v * (1.0f - s);
		const float q = v * (1.0f - s * f);
		const float t = v * (1.0f - s * (1.0f - f));

		switch (hi) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
		}
		
		return {
			static_cast<unsigned char>(r * 255),
			static_cast<unsigned char>(g * 255),
			static_cast<unsigned char>(b * 255)
		};
	}

	template <typename T>
	int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	Chart::Chart()
	{
		font.loadFromFile("arial.ttf");
	}

	const Vector2f& Chart::getPosition() const
	{
		return position;
	}

	void Chart::setPosition(const Vector2f& position)
	{
		this->position = position;
	}

	const Vector2f& Chart::getSize() const
	{
		return size;
	}

	void Chart::setSize(const Vector2f& size)
	{
		this->size = size;
	}

	ViewArea& Chart::viewArea()
	{
		return _viewArea;
	}

	const vector<Series>& Chart::series() const
	{
		return _series;
	}

	void Chart::add(const Series& series)
	{
		_series.push_back(series);

		srand(static_cast<unsigned>(time(nullptr)) / 2);

		for (size_t index = 0; index < series.width(); index++)
			colors.emplace_back(hsv(colors.size() * 195 % 360, .8f, 1.f));
	}

	void Chart::remove(size_t index)
	{
		checkIndex(index);

		_series.erase(_series.begin() + index);
	}

	const Series& Chart::get(size_t index) const
	{
		checkIndex(index);

		return _series[index];
	}

	void Chart::defaultView()
	{
		float minX = INFINITY, maxX = -INFINITY;
		float minY = INFINITY, maxY = -INFINITY;

		for (auto& series : _series)
		{
			for (float domainValue : series.domain().values())
			{
				if (domainValue > maxX)
					maxX = domainValue;

				if (domainValue < minX)
					minX = domainValue;
			}
			
			for (auto& range : series.ranges())
				for (float rangeValue : range.values())
				{
					if (rangeValue > maxY)
						maxY = rangeValue;

					if (rangeValue < minY)
						minY = rangeValue;
				}
		}

		if (isinf(minX) || isinf(maxX) || isinf(minY) || isinf(maxY))
			return;

		float width = maxX - minX;
		float height = maxY - minY;

		Vector2 viewAreaSize = scale({ 1.f, 1.f }, { width * 1.1f, height * 1.1f }, true);
		Vector2f viewAreaPosition = Vector2f((maxX + minX) / 2, (maxY + minY) / 2) - viewAreaSize / 2.f;

		_viewArea.width = viewAreaSize.x;
		_viewArea.height = viewAreaSize.x;
		_viewArea.x = viewAreaPosition.x;
		_viewArea.y = viewAreaPosition.y;
	}

	void Chart::update()
	{
		_viewArea.height = _viewArea.width * size.y / size.x;
	}

	size_t Chart::length() const
	{
		return _series.size();
	}

	void Chart::checkIndex(size_t index) const
	{
		if (index >= length())
			throw std::out_of_range("index out of range");
	}

	void Chart::draw(RenderTarget& target, RenderStates states) const
	{
		Vector2f viewAreaSize = size;
		Vector2f viewAreaPosition = { 0,  0};

		Vector2f center = _viewArea.transform(
			0, 0,
			viewAreaPosition.x, viewAreaPosition.y,
			viewAreaSize.x, viewAreaSize.y
		);

		size_t colorIndex = 0;
		size_t rangeColorCircleIndex = 0;

		CircleShape rangeColorCircle(5);
		Text rangeNameText("", font, 12);
		Text divisionText("", font, 12);

		rangeColorCircle.setOrigin(rangeColorCircle.getRadius(), rangeColorCircle.getRadius());
		rangeNameText.setOrigin(0, rangeNameText.getCharacterSize() / 2 + 1);

		double rank = pow(10, floor(log10(_viewArea.width)) - 1);
		double number = _viewArea.width / rank;
		double delta;

		int maxNumbers = viewAreaSize.x / 100;
		
		if (number < maxNumbers)
			delta = rank;
		else if (number / 2 < maxNumbers)
			delta = rank * 2;
		else
			delta = rank * 5;

		double xDivisionX = _viewArea.x - fmod(_viewArea.x, delta) - delta;
		double xDivisionEndX = _viewArea.x + _viewArea.width + delta;

		double yDivisionY = _viewArea.y - fmod(_viewArea.y, delta) - delta;
		double yDivisionEndY = _viewArea.y + _viewArea.height + delta;

		VertexArray subAxis(Lines);
		Color subAxisColor(255, 255, 255, 100);
		
		while (xDivisionX < xDivisionEndX)
		{
			Vector2f xDivisionPosition = _viewArea.transform(
				xDivisionX, 0,
				viewAreaPosition.x, viewAreaPosition.y,
				viewAreaSize.x, viewAreaSize.y
			);

			Vector2f xDivisionPositionLocal = xDivisionPosition - center;

			if (xDivisionPositionLocal.x * xDivisionPositionLocal.x + xDivisionPositionLocal.y * xDivisionPositionLocal.y < 9)
			{
				xDivisionX += delta;

				continue;
			}

			subAxis.append({ { xDivisionPosition.x, position.y }, subAxisColor });
			subAxis.append({ { xDivisionPosition.x, position.y + size.y }, subAxisColor });

			ostringstream ss;

			ss << xDivisionX;
			
			string xDivisionTextString(ss.str());
			
			divisionText.setString(xDivisionTextString);
			divisionText.setOrigin(floor(divisionText.getLocalBounds().width / 2), 0);
			divisionText.setPosition(floor(xDivisionPosition.x), floor(xDivisionPosition.y) + 8);

			target.draw(subAxis);
			target.draw(divisionText);

			subAxis.clear();
			
			xDivisionX += delta;
		}

		while (yDivisionY < yDivisionEndY)
		{
			Vector2f yDivisionPosition = _viewArea.transform(
				0, yDivisionY,
				viewAreaPosition.x, viewAreaPosition.y,
				viewAreaSize.x, viewAreaSize.y
			);

			Vector2f yDivisionPositionLocal = yDivisionPosition - center;

			if (yDivisionPositionLocal.x * yDivisionPositionLocal.x + yDivisionPositionLocal.y * yDivisionPositionLocal.y < 9)
			{
				yDivisionY += delta;

				continue;
			}

			subAxis.append({ { position.x, yDivisionPosition.y }, subAxisColor });
			subAxis.append({ { position.x + size.x, yDivisionPosition.y }, subAxisColor });

			ostringstream ss;

			ss << yDivisionY;

			string yDivisionTextString(ss.str());

			divisionText.setString(yDivisionTextString);
			divisionText.setOrigin(divisionText.getLocalBounds().width, floor(divisionText.getLocalBounds().width / 2));
			divisionText.setPosition(floor(yDivisionPosition.x) - 8, floor(yDivisionPosition.y));

			target.draw(subAxis);
			target.draw(divisionText);

			subAxis.clear();

			yDivisionY += delta;
		}

		VertexArray axises(Lines);

		axises.append({ { position.x, center.y } });
		axises.append({ { position.x + size.x, center.y } });

		axises.append({ { center.x, position.y } });
		axises.append({ { center.x, position.y + size.y } });

		divisionText.setString("0");
		divisionText.setOrigin(divisionText.getLocalBounds().width, 0);
		divisionText.setPosition(floor(center.x) - 8, floor(center.y) + 8);

		target.draw(axises);
		target.draw(divisionText);
		
		for (auto& series : _series)
		{
			auto& domainValues = series.domain().values();
			auto& ranges = series.ranges();

			size_t length = series.length();

			for (auto& range : ranges)
			{
				auto& rangeColor = colors[colorIndex++];
				
				if (!range.name.empty())
				{
					float x = 20;
					float y = 20 + rangeColorCircleIndex++ * 30;
					
					rangeColorCircle.setFillColor(rangeColor);
					rangeColorCircle.setPosition(x, y);

					rangeNameText.setPosition(x + 15, y);
					rangeNameText.setString(range.name);
					
					target.draw(rangeColorCircle);
					target.draw(rangeNameText);
				}

				VertexArray vertices(LinesStrip);

				auto& rangeValues = range.values();

				for (size_t index = 0; index < length; index++)
					vertices.append({
						_viewArea.transform(
							domainValues[index], rangeValues[index],
							viewAreaPosition.x, viewAreaPosition.y,
							viewAreaSize.x, viewAreaSize.y
						),
						rangeColor
					});

				target.draw(vertices);
			}
		}
	}
}