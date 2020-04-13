#include "Circle2D.h"

Circle2D::Circle2D()
{
	v_points = {};
	v_pointsSize = 0;
	s_texture = WALL_TEXTURE;
}

Circle2D::Circle2D(Point2D _point, double _radius)
{
	p_centre = _point;
	d_radius = _radius;
	for (int i = 0; i < CIRCLE_CONVEX_NUMBER; i++)
	{
		v_points.push_back({ p_centre.x + d_radius * cos((double)i / CIRCLE_CONVEX_NUMBER * 2 * PI - PI / 4), p_centre.y + d_radius * sin((double)i / CIRCLE_CONVEX_NUMBER * 2 * PI - PI / 4) });
	}
	v_pointsSize = CIRCLE_CONVEX_NUMBER;
	s_texture = WALL_TEXTURE;
}

Circle2D::Circle2D(double _x, double _y, double _radius)
{
	if (_radius >= 0)
	{
		p_centre = { _x, _y };
		d_radius = _radius;
		for (int i = 0; i < CIRCLE_CONVEX_NUMBER; i++)
		{
			v_points.push_back({ p_centre.x + d_radius * cos((double)i / CIRCLE_CONVEX_NUMBER * 2 * PI - PI / 4), p_centre.y + d_radius * sin((double)i / CIRCLE_CONVEX_NUMBER * 2 * PI - PI / 4) });
		}
		v_pointsSize = CIRCLE_CONVEX_NUMBER;
		s_texture = WALL_TEXTURE;
	}
	else
	{
		std::cout << "Wrong radius sign" << std::endl;
		std::exit(-1);
	}
}

Circle2D::Circle2D (const Circle2D& _circle)
{
	this->v_points = _circle.v_points;
	this->d_radius = _circle.d_radius;
	this->v_pointsSize = _circle.v_pointsSize;
	this->s_texture = _circle.s_texture;
}

bool Circle2D::isInArea(const int& world_length, const int& world_width)
{
	if ((v_points[0].x - d_radius) < 0 || (v_points[0].y - d_radius) < 0 || (v_points[0].x + d_radius) > world_length || (v_points[0].y + d_radius) > world_width)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Circle2D::Draw(sf::RenderWindow& window, const int& world_length, const int& world_width)
{
	sf::CircleShape circle;
	circle.setPosition((p_centre.x - d_radius) / world_length * window.getSize().x * SCALE, (p_centre.y - d_radius) / world_length * window.getSize().x * SCALE);
	circle.setRadius(d_radius / world_length * window.getSize().x * SCALE);
	circle.setPointCount(CIRCLE_CONVEX_NUMBER);
	circle.setFillColor(FILL_COLOR);
	circle.setOutlineColor(OUTLINE_COLOR);
	circle.setOutlineThickness(OUTLINE_THICKNESS);
	window.draw(circle);
}