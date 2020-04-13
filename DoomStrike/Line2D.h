#ifndef DOOMSTRIKE_LINE2D_H
#define DOOMSTRIKE_LINE2D_H

#include <vector>
#include "Object2D.h"

class Line2D : public Object2D
{
public:
	Line2D();
	Line2D(Point2D _pointA, Point2D _pointB);
	Line2D(std::vector<double> _points);
	Line2D(double _x1, double _y1, double _x2, double _y2);

	void Draw(sf::RenderWindow& window, const int& world_length, const int& world_width) override;
};

#endif