#ifndef DOOMSTRIKE_TRIANGLE2D_H
#define DOOMSTRIKE_TRIANGLE2D_H

#include <vector>
#include "Object2D.h"

class Triangle2D : public Object2D
{
private:

public:
	Triangle2D();
	Triangle2D(Point2D _pointA, Point2D _pointB, Point2D _pointC);
	Triangle2D(std::vector<double> _points);
	Triangle2D(const Triangle2D& _triangle);
};

#endif