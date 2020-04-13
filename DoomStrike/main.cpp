#include <chrono>
#include <iostream>
#include <array>
#include "World.h"

/*Settings*/
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

int WORLD_LENGTH = 100;
int WORLD_WIDTH = 100;

int DISTANCES_SEGMENTS = 500;

using namespace std;

int main()
{
	World world(WORLD_LENGTH, WORLD_WIDTH);
	Line2D worldEdgeTop(0, 0, WORLD_LENGTH, 0);
	Line2D worldEdgeRight(WORLD_LENGTH, 0, WORLD_LENGTH, WORLD_WIDTH);
	Line2D worldEdgeBottom(WORLD_LENGTH, WORLD_WIDTH, 0, WORLD_WIDTH);
	Line2D worldEdgeLeft(0, WORLD_WIDTH, 0, 0);
	world.AddObject(worldEdgeTop);
	world.AddObject(worldEdgeRight);
	world.AddObject(worldEdgeBottom);
	world.AddObject(worldEdgeLeft);

	Circle2D circle(50, 50, 10);

	std::vector<double> points1{ { 5.0, 5.0, 25.0, 25.0, 5.0, 25.0 } };
	Triangle2D triangle1(points1);

	std::vector<double> points2{ { 5.0, 75.0, 25.0, 75.0, 5.0, 95.0 } };
	Triangle2D triangle2(points2);

	std::vector<double> points3{ { 75.0, 40.0, 95.0, 40.0, 95.0, 60.0, 75.0, 60.0 } };
	Quad2D quad1(points3);

	std::vector<double> points4{ { 40.0, 70.0, 60.0, 70.0, 60.0, 80.0, 40.0, 80.0 } };
	Quad2D quad2(points4);

	world.AddObject(circle);
	world.AddObject(triangle1);
	world.AddObject(triangle2);
	world.AddObject(quad1);
	world.AddObject(quad2);

	Point2D ppoint;
	ppoint = { 95, 5 };
	Player player(ppoint, 0, WORLD_LENGTH, WORLD_WIDTH, DISTANCES_SEGMENTS);
	player.setWalkSpeed(0.5);
	world.AddPlayer(player);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DoomStrike");
	window.setFramerateLimit(30);

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now(); 

	while (window.isOpen())
	{
		tp2 = chrono::system_clock::now();
		chrono::duration <double> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		double d_elapsedTime = elapsedTime.count();
		std::string title = "DoomStrike " + std::to_string((double)1 / elapsedTime.count());
		window.setTitle(title);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		
		window.clear();
		player.UpdateDistances(world.getObjects());
		player.DrawPlayerView(window);
		world.Draw(window);
		if (!player.PlayerControl(window, world.getObjects())) 
		{
		}

		window.display();

	}

	return 0;
}