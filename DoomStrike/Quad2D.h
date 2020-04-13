#ifndef DOOMSTRIKE_QUAD2D_H
#define DOOMSTRIKE_QUAD2D_H

#include <vector>
#include "Object2D.h"

class Quad2D : public Object2D
{
public:
	Quad2D();
	Quad2D(Point2D _pointA, Point2D _pointB, Point2D _pointC, Point2D _pointD);
	Quad2D(std::vector<double> _points);
	Quad2D(const Quad2D& _triangle);
};

#endif