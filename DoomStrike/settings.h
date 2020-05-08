#ifndef DOOMSTRIKE_SETTINGS_H
#define DOOMSTRIKE_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define PI 3.1415926535897932384626433832795

#define CIRCLE_CONVEX_NUMBER 24

/*Background colors and outline thickness at map*/
#define OUTLINE_BACKGROUND_THICKNESS 5
#define OUTLINE_BACKGROUND_COLOR {255, 255, 255, 255}
#define FILL_BACKGROUND_COLOR {0, 0, 0, 255}

/*Objects colors and outline thickness at map*/
#define OUTLINE_THICKNESS 0
#define OUTLINE_COLOR {244, 92, 87, 255}
#define FILL_COLOR {210, 105, 3, 255}

/*Player colors and outline thickness at map*/
#define PLAYER_RADIUS 3
#define OUTLINE_PLAYER_THICKNESS 1
#define OUTLINE_PLAYER_COLOR {255, 255, 255, 255}
#define FILL_PLAYER_COLOR {255, 67, 67, 255}

/*Camera colors and outline thickness at map*/
#define CONVEX_NUMBER 100
#define OUTLINE_CAMERA_THICKNESS 2
#define OUTLINE_CAMERA_COLOR {255, 255, 255, 255}
#define FILL_CAMERA_COLOR {0, 0, 0, 255}

/*Ray cast settings*/
#define MAX_DISTANCE 200

/*Map settings*/
#define SCALE 0.2

/*Textures path*/
/*World textures*/
#define SKY_TEXTURE "textures/world/sky.jpg"
#define WALL_TEXTURE "textures/world/wall.jpg"

#endif
