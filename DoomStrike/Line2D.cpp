#include "Line2D.h"

Line2D::Line2D()
{
	for (auto point : v_points)
	{
		point = 0;
	}
	v_pointsSize = 2;
	s_texture = WALL_TEXTURE;
}

Line2D::Line2D(Point2D _pointA, Point2D _pointB)
{

}

Line2D::Line2D(std::vector<double> _points)
{
	if (_points.size() == 2)
	{
		for (unsigned int i = 0; i < 6; i += 2)
		{
			Point2D _point = { _points[i], _points[i + 1] };
			v_points.push_back(_point);
		}
	}
	else
	{
		std::cout << "Wrong vector size" << std::endl;
		std::exit(-1);
	}
	v_pointsSize = 2;
	s_texture = WALL_TEXTURE;
}

Line2D::Line2D(double _x1, double _y1, double _x2, double _y2)
{
	Point2D point1 = { _x1, _y1 };
	Point2D point2 = { _x2, _y2 };
	v_points.push_back(point1);
	v_points.push_back(point2);
	v_pointsSize = 2;
}

void Line2D::Draw(sf::RenderWindow& window, const int& world_length, const int& world_width)
{

}