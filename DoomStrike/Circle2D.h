#ifndef DOOMSTRIKE_CIRCLE2D_H
#define DOOMSTRIKE_CIRCLE2D_H

#include <iostream>
#include "Object2D.h"

class Circle2D : public Object2D
{
private:
	Point2D p_centre;
	double d_radius;
public:
	Circle2D();
	Circle2D(Point2D _point, double _radius);
	Circle2D(double _x, double _y, double _radius);
	Circle2D(const Circle2D& _circle);

	bool isInArea(const int& world_length, const int& world_width) override;
	void Draw(sf::RenderWindow& window, const int& world_length, const int& world_width) override;
};

#endif