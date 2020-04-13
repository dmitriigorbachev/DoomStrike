#include "World.h"

World::World()
{
	world_length = 0;
	world_width = 0;
	v_objects = {};
}

World::World(const int& _length, const int& _width)
{	
	if (_length >= 0 && _width >= 0)
	{
		world_length = _length;
		world_width = _width;
	}
	else
	{
		std::cout << "Wrong world size" << std::endl;
		std::exit(-1);
	}
}

World::World (const World& _world)
{
	this->world_length = _world.world_length;
	this->world_width = _world.world_width;
	this->v_objects = _world.v_objects;
}

void World::AddObject(Object2D& _object)
{
	if (_object.isInArea(world_length, world_width))
	{
		v_objects.push_back(&_object);
	}
}

void World::AddPlayer(Player& _player)
{
	player = &_player;
}

std::vector<Object2D*>& World::getObjects()
{
	return v_objects;
}

void World::Draw(sf::RenderWindow& window)
{
	sf::ConvexShape background;
	background.setPointCount(4);

	background.setPoint(0, sf::Vector2f(0, 0));
	background.setPoint(1, sf::Vector2f(window.getSize().x * SCALE, 0));
	background.setPoint(2, sf::Vector2f(window.getSize().x * SCALE, (window.getSize().x * SCALE) / world_length * world_width));
	background.setPoint(3, sf::Vector2f(0, (window.getSize().x * SCALE) / world_length * world_width));

	background.setOutlineColor(OUTLINE_BACKGROUND_COLOR);
	background.setFillColor(FILL_BACKGROUND_COLOR);
	background.setOutlineThickness(OUTLINE_BACKGROUND_THICKNESS);

	window.draw(background);

	player->Draw(window);

	for (auto object : v_objects)
	{
		object->Draw(window, world_length, world_width);
	}
}