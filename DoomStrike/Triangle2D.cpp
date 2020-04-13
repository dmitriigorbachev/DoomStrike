#include "Triangle2D.h"

Triangle2D::Triangle2D()
{
	for (auto point : v_points)
	{
		point = 0;
	}
	v_pointsSize = 3;
	s_texture = WALL_TEXTURE;
}

Triangle2D::Triangle2D(Point2D _pointA, Point2D _pointB, Point2D _pointC)
{

}

Triangle2D::Triangle2D(std::vector<double> _points)
{
	if (_points.size() == 6)
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
	v_pointsSize = 3;
	s_texture = WALL_TEXTURE;
}

Triangle2D::Triangle2D(const Triangle2D& _triangle)
{

}