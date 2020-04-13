#ifndef DOOMSTRIKE_OBJECT2D_H
#define DOOMSTRIKE_OBJECT2D_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "settings.h"

struct Point2D
{
	double x = 0;
	double y = 0;

	Point2D& operator= (const Point2D& _point)
	{
		this->x = _point.x;
		this->y = _point.y;
		return *this;
	}
	Point2D& operator= (const double& _point)
	{
		this->x = _point;
		this->y = _point;
		return *this;
	}
	Point2D operator+ (const Point2D& _point)
	{
		return { this->x + _point.x, this->y + _point.y };
	}
	Point2D& operator+= (const Point2D& _point)
	{
		this->x += _point.x;
		this->y += _point.y;
		return *this;
	}
	Point2D operator- (const Point2D& _point)
	{
		return { this->x - _point.x, this->y - _point.y };
	}
	Point2D operator* (double num)
	{
		return { this->x * num, this->y * num };
	}
};

class Object2D
{
protected:
	std::vector<Point2D> v_points;
	int v_pointsSize;
	std::string s_texture;
public:
	virtual bool isInArea(const int& world_length, const int& world_width);
	virtual void Draw(sf::RenderWindow& window, const int& world_length, const int& world_width);

	int getVPointsSize() const;
	Point2D getPoint(int i);
	std::vector<Point2D>& getVPoints();
};

#endif