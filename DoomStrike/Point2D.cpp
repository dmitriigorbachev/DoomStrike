#include "Point2D.h"

Point2D::Point2D()
{
	d_x = 0;
	d_y = 0;
}

Point2D::Point2D(double _x, double _y)
{
	d_x = _x;
	d_y = _y;
}

Point2D::Point2D(const Point2D& _point)
{
	this->d_x = _point.d_x;
	this->d_y = _point.d_y;
}

Point2D& Point2D::operator= (const Point2D& _point)
{
	this->d_x = _point.d_x;
	this->d_y = _point.d_y;
	return *this;
}

Point2D& Point2D::operator= (const double& _point)
{
	this->d_x = _point;
	this->d_y = _point;
	return *this;
}

Point2D& Point2D::operator+= (const Point2D& _point)
{
	this->d_x += _point.d_x;
	this->d_y += _point.d_y;
	return *this;
}

Point2D Point2D::operator- (const Point2D& _point)
{
	Point2D tmp(this->d_x - _point.d_x, this->d_y - _point.d_y);
	return tmp;
}

double Point2D::getX()
{
	return d_x;
}

double Point2D::getY()
{
	return d_y;
}

void Point2D::setX(double _x)
{
	d_x = _x;
}

void Point2D::setY(double _y)
{
	d_y = _y;
}