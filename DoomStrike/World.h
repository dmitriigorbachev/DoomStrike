#ifndef DOOMSTRIKE_WORLD_H
#define DOOMSTRIKE_WORLD_H

#include <vector>
#include <map>
#include "Line2D.h"
#include "Triangle2D.h"
#include "Quad2D.h"
#include "Circle2D.h"
#include "Player.h"

class World
{
private:
	int world_length;
	int world_width;
	std::vector<Object2D*> v_objects;
	Player* player;
public:
	World();
	World(const int& _length, const int& _width);
	World(const World& _world);

	void AddObject(Object2D& _object);
	void AddPlayer(Player& _player);

	std::vector<Object2D*>& getObjects();

	void Draw(sf::RenderWindow& window);
};

#endif