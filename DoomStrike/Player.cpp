#include "Player.h"

Player::Player()
{
	world_length = 0;
	world_width = 0;
	p_position = 0;
	d_direction = 0;
	d_fieldOfView = PI / 2;
	distancesSegments = 0;
	d_walkSpeed = 0;
}

Player::Player(Point2D _position, double _direction, const int& _world_length, const int& _world_width, int _distancesSegments)
{
	world_length = _world_length;
	world_width = _world_width;
	p_position = _position;
	d_direction = _direction;
	d_fieldOfView = PI / 2;
	distancesSegments = _distancesSegments;
	d_walkSpeed = 1;
}

Player::Player(double _x, double _y, double _direction, const int& _world_length, const int& _world_width, int _distancesSegments)
{
	Point2D _position = { 0, 0 };
	world_length = _world_length;
	world_width = _world_width;
	p_position = _position;
	d_direction = _direction;
	d_fieldOfView = PI / 2;
	distancesSegments = _distancesSegments;
	d_walkSpeed = 1;
}

int sign(double number) 
{ 
	return number >= 0 ? 1 : -1; 
}

double cross(Point2D p1, Point2D p2) 
{
	return p1.x * p2.y - p1.y * p2.x;
}

double SegmentLength(const Point2D& pointA, const Point2D& pointB)
{
	return (std::sqrt(std::pow(pointA.x - pointB.x, 2) + std::pow(pointA.y - pointB.y, 2)));
}

bool areCrossing(std::pair<Point2D, Point2D>& segment1, std::pair<Point2D, Point2D>& segment2, double& distance)
{
	Point2D cut1 = segment1.second - segment1.first;
	Point2D cut2 = segment2.second - segment2.first;
	double prod1;
	double prod2;

	prod1 = cross(cut1, (segment2.first - segment1.first));
	prod2 = cross(cut1, (segment2.second - segment1.first));
	if (sign(prod1) == sign(prod2) || (prod1 == 0) || (prod2 == 0))
	{
		return false;
	}

	prod1 = cross(cut2, (segment1.first - segment2.first));
	prod2 = cross(cut2, (segment1.second - segment2.first));
	if (sign(prod1) == sign(prod2) || (prod1 == 0) || (prod2 == 0))
	{
		return false;
	}

	double x = (segment1.first.x + cut1.x * std::abs(prod1) / std::abs(prod2 - prod1));
	double y = (segment1.first.y + cut1.y * std::abs(prod1) / std::abs(prod2 - prod1));
	distance = std::sqrt(std::pow(segment1.first.x - x, 2) + std::pow(segment1.first.y - y, 2));

	return true;
}

double CrossingDistance(std::pair<Point2D, Point2D>& directionSegment, const std::vector<Object2D*>& v_objects)
{
	double distance = MAX_DISTANCE;
	for (auto object : v_objects)
	{
		for (int i = 0; i < object->getVPointsSize(); i++)
		{
			double tmpDistance;
			std::pair<Point2D, Point2D> objectSegment = { object->getPoint(i), object->getPoint(i + 1) };
			if (areCrossing(directionSegment, objectSegment, tmpDistance))
			{
				if (tmpDistance < distance)
				{
					distance = tmpDistance;
				}
			}
		}
	}
	return distance;
}

void Player::UpdateDistances(const std::vector<Object2D*>& v_objects)
{
	v_distances.clear();
	double left = d_direction - d_fieldOfView / 2;
	double right = d_direction + d_fieldOfView / 2;
	for (int i = 0; i < distancesSegments; i++)
	{
		double direction = d_direction + ((double)i / distancesSegments - 0.5) * d_fieldOfView;
		std::pair<Point2D, Point2D> directionSegment = { p_position, { p_position.x + (double)MAX_DISTANCE * cos(direction), p_position.y + (double)MAX_DISTANCE * sin(direction) } };
		double distance = CrossingDistance(directionSegment, v_objects);
		SRayCast ray = { distance };
		v_distances.push_back(ray);
	}
}

double dot(Point2D vectorA, Point2D vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

Point2D newWalkPoint(std::pair<Point2D, Point2D>& segment1, std::pair<Point2D, Point2D>& segment2)
{
	Point2D point;

	double x = 0;
	double y = 0;

	if (dot({ segment1.second - segment2.first }, {segment2.second - segment2.first}) <= 0)
	{
		x = segment2.first.x;
		y = segment2.first.y;
	}
	else
	{
		if (dot({ segment1.second - segment2.second }, { segment2.first - segment2.second }) <= 0)
		{
			x = segment2.second.x;
			y = segment2.second.y;
		}
		else
		{
			if (segment2.first.x == segment2.second.x)
			{
				x = segment2.first.x;
				y = segment1.second.y;
			}
			else
			{
				if (segment2.first.y == segment2.second.y)
				{
					x = segment1.second.x;
					y = segment2.first.y;
				}
				else
				{
					x = (segment2.first.x * pow(segment2.second.y - segment2.first.y, 2) + segment1.second.x * pow(segment2.second.x - segment2.first.x, 2) + (segment2.second.x - segment2.first.x) * (segment2.second.y - segment2.first.y) * (segment1.second.y - segment2.first.y)) / (pow(segment2.second.y - segment2.first.y, 2) + pow(segment2.second.x - segment2.first.x, 2));
					y = ((segment2.second.x - segment2.first.x) * (segment1.second.x - x)) / (segment2.second.y - segment2.first.y) + segment1.second.y;
				}
			}
		}
	}


	point.x = x + (x - segment1.second.x) * 0.25;
	point.y = y + (y - segment1.second.y) * 0.25;
	return point;
}

bool areCrossing(std::pair<Point2D, Point2D>& segment1, std::pair<Point2D, Point2D>& segment2, Point2D& walkPoint, double& distance)
{
	Point2D cut1 = segment1.second - segment1.first;
	Point2D cut2 = segment2.second - segment2.first;
	double prod1;
	double prod2;

	prod1 = cross(cut1, (segment2.first - segment1.first));
	prod2 = cross(cut1, (segment2.second - segment1.first));
	if (sign(prod1) == sign(prod2) || (prod1 == 0) || (prod2 == 0))
	{
		return false;
	}

	prod1 = cross(cut2, (segment1.first - segment2.first));
	prod2 = cross(cut2, (segment1.second - segment2.first));
	if (sign(prod1) == sign(prod2) || (prod1 == 0) || (prod2 == 0))
	{
		return false;
	}

	double x = (segment1.first.x + cut1.x * std::abs(prod1) / std::abs(prod2 - prod1));
	double y = (segment1.first.y + cut1.y * std::abs(prod1) / std::abs(prod2 - prod1));

	distance = SegmentLength(segment1.first, { x, y });

	walkPoint = newWalkPoint(segment1, segment2);

	return true;
}

bool Player::PlayerControl(sf::RenderWindow& window, const std::vector<Object2D*>& v_objects)
{
	double dx = 0;
	double dy = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx += sin(d_direction);
		dy += -cos(d_direction);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx += -sin(d_direction);
		dy += cos(d_direction);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dx += cos(d_direction);
		dy += sin(d_direction);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dx += -cos(d_direction);
		dy += -sin(d_direction);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		//std::exit(0);
		return false;
	}
	if (sf::Mouse::getPosition(window).x != localMousePosition.x) {
		double difference = sf::Mouse::getPosition(window).x - localMousePosition.x;
		sf::Mouse::setPosition({ world_length / 2, world_width / 2 });
		localMousePosition = sf::Mouse::getPosition(window);
		d_direction += 0.005 * difference;
	}

	Point2D walkPoint = {p_position.x + d_walkSpeed * dx, p_position.y + d_walkSpeed * dy };
	double distance = SegmentLength(p_position, walkPoint);
	std::pair<Point2D, Point2D> walkSegment = {p_position, walkPoint };
	for (auto object : v_objects)
	{
		for (int i = 0; i < object->getVPointsSize(); i++)
		{
			Point2D tmpWalkPoint = walkPoint;
			double tmpDistance = distance;
			std::pair<Point2D, Point2D> objectSegment = { object->getPoint(i), object->getPoint(i + 1) };
			if (areCrossing(walkSegment, objectSegment, tmpWalkPoint, tmpDistance))
			{
				if (tmpDistance < distance)
				{
					distance = tmpDistance;
					walkPoint = tmpWalkPoint;
				}
			}
		}
	}
	p_position = walkPoint;

	return true;
}

void Player::Draw(sf::RenderWindow& window)
{
	sf::CircleShape circle;
	sf::ConvexShape triangle;

	circle.setPosition((p_position.x - PLAYER_RADIUS) / world_length * window.getSize().x * SCALE, (p_position.y - PLAYER_RADIUS) / world_length * window.getSize().x * SCALE);

	circle.setRadius((double)PLAYER_RADIUS / world_length * window.getSize().x * SCALE);
	circle.setFillColor(FILL_PLAYER_COLOR);
	circle.setOutlineColor(OUTLINE_PLAYER_COLOR);
	circle.setOutlineThickness((double)OUTLINE_PLAYER_THICKNESS / world_length * window.getSize().x * SCALE);

	double left = d_direction - d_fieldOfView / 2;
	double right = d_direction + d_fieldOfView / 2;

	triangle.setPointCount(CONVEX_NUMBER + 2);

	triangle.setPoint(0, sf::Vector2f(0, 0));
	triangle.setPoint(1, sf::Vector2f((v_distances[0].d_distance * cos(left)) / world_length * window.getSize().x * SCALE, (v_distances[0].d_distance * sin(left)) / world_length * window.getSize().x * SCALE));
	triangle.setPoint(CONVEX_NUMBER + 1, sf::Vector2f((v_distances[distancesSegments - 1].d_distance * cos(right)) / world_length * window.getSize().x * SCALE, (v_distances[distancesSegments - 1].d_distance * sin(right)) / world_length * window.getSize().x * SCALE));
	for (int i = 1; i < CONVEX_NUMBER; i++)
	{
		triangle.setPoint(i + 1, sf::Vector2f((v_distances[(int)(distancesSegments / CONVEX_NUMBER * i)].d_distance * cos(left + (right - left) * i / CONVEX_NUMBER)) / world_length * window.getSize().x * SCALE, (v_distances[(int)(distancesSegments / CONVEX_NUMBER * i)].d_distance * sin(left + (right - left) * i / CONVEX_NUMBER)) / world_length * window.getSize().x * SCALE));
	}

	triangle.setOutlineColor(OUTLINE_CAMERA_COLOR);
	triangle.setFillColor(FILL_CAMERA_COLOR);
	triangle.setOutlineThickness(OUTLINE_CAMERA_THICKNESS);
	triangle.setPosition(p_position.x / world_length * window.getSize().x * SCALE, p_position.y / world_length * window.getSize().x * SCALE);

	window.draw(triangle);
	window.draw(circle);
}

void Player::DrawPlayerView(sf::RenderWindow& window)
{
	double direction = d_direction - d_fieldOfView / 2;

	for (int i = 0; i < v_distances.size() - 1; i++)
	{
		sf::ConvexShape shape;
		shape.setPointCount(4);

		double heightLeftTop = (1 - 1 / (v_distances[i].d_distance * cos(direction - d_direction))) * window.getSize().y / 2;
		double heightLeftBottom = (1 + 1 / (v_distances[i].d_distance * cos(direction - d_direction))) * window.getSize().y / 2;
		double heightRightTop = (1 - 1 / (v_distances[i + 1].d_distance * cos(direction - d_direction))) * window.getSize().y / 2;
		double heightRightBottom = (1 + 1 / (v_distances[i + 1].d_distance * cos(direction - d_direction))) * window.getSize().y / 2;

		shape.setPoint(0, sf::Vector2f(0, heightLeftTop));
		shape.setPoint(1, sf::Vector2f(0, heightLeftBottom));
		shape.setPoint(2, sf::Vector2f((double)window.getSize().x / distancesSegments, heightRightBottom));
		shape.setPoint(3, sf::Vector2f((double)window.getSize().x / distancesSegments, heightRightTop));

		int alpha = 255 * (1 - v_distances[i].d_distance / MAX_DISTANCE);
		if (alpha > 255)
			alpha = 255;
		if (alpha < 0)
			alpha = 0;

		shape.setFillColor({ 255, 174, 174, static_cast<sf::Uint8>(alpha) });
		shape.setOutlineThickness(0);
		shape.setPosition((double)i * window.getSize().x / distancesSegments, 0);

		//sf::Sprite sprite;

		window.draw(shape);

		direction += d_fieldOfView / distancesSegments;
	}
}

void Player::setWalkSpeed(double _walkSpeed)
{
	d_walkSpeed = _walkSpeed;
}