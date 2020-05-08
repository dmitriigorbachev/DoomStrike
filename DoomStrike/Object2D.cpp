#include "Object2D.h"

Point2D Object2D::getPoint(int i)
{
	if (i < v_pointsSize)
	{
		return v_points[i];
	}
	else
	{
		return v_points[i - v_pointsSize];
	}
}

bool Object2D::isInArea(const int& world_length,const int& world_width)
{
	for (auto point : v_points)
	{
		if (point.x < 0 || point.y < 0 || point.x > world_length || point.y > world_width)
		{
			return false;
		}
	}
	return true;
}

void Object2D::Draw(sf::RenderWindow& window, const int& world_length, const int& world_width)
{
	sf::ConvexShape object;
	object.setPointCount(v_points.size());
	int i = 0;
	for (auto point : v_points)
	{
		object.setPoint(i++, sf::Vector2f(point.x / world_length * window.getSize().x * SCALE, point.y / world_length * window.getSize().x * SCALE));
	}
	object.setOutlineColor(OUTLINE_COLOR);
	object.setFillColor(FILL_COLOR);
	object.setOutlineThickness(OUTLINE_THICKNESS);
	window.draw(object);
}

int Object2D::getVPointsSize() const
{
	return v_pointsSize;
}

std::vector<Point2D>& Object2D::getVPoints()
{
	return v_points;
}

sf::Texture& Object2D::loadTexture(bool& b_textures)
{
	if (texture_loaded)
	{
		return T_texture;
	}
	else
	{
		texture_loaded = true;
		if (!T_texture.loadFromFile(s_texture)) 
		{
			texture_loaded = false;
			b_textures = false;
		}
		T_texture.setRepeated(true);
		return T_texture;
	}
}