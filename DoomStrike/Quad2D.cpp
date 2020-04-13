#include "Quad2D.h"

Quad2D::Quad2D()
{
	for (auto point : v_points)
	{
		point = 0;
	}
	v_pointsSize = 4;
	s_texture = WALL_TEXTURE;
}

Quad2D::Quad2D(std::vector<double> _points)
{
	if (_points.size() == 8)
	{
		for (unsigned int i = 0; i < 8; i += 2)
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
	v_pointsSize = 4;
	s_texture = WALL_TEXTURE;
}