#ifndef DOOMSTRIKE_PLAYER_H
#define DOOMSTRIKE_PLAYER_H

#include <cmath>
#include "settings.h"
#include "Object2D.h"

struct SRayCast
{
	double d_distance;
};

class Player
{
private:
	int world_length;
	int world_width;

	Point2D p_position;
	double d_direction;
	double d_fieldOfView;

	int distancesSegments;
	std::vector<SRayCast> v_distances;

	double d_walkSpeed;
	sf::Vector2i localMousePosition;
public:
	Player();
	Player(Point2D _position, double _direction, const int& _world_length, const int& _world_width, int _distancesSegments);
	Player(double _x, double _y, double _direction, const int& _world_length, const int& _world_width, int _distancesSegments);

	void UpdateDistances(const std::vector<Object2D*>& v_objects);

	bool PlayerControl(sf::RenderWindow& window, const std::vector<Object2D*>& v_objects);

	void Draw(sf::RenderWindow& window);
	void DrawPlayerView(sf::RenderWindow& window);

	void setWalkSpeed(double _walkSpeed);
};

#endif