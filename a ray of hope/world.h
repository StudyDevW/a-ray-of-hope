#pragma once
#include <wtypes.h>

class world_scene {
public:
	int x = 0;
	int y = 0;
	int world_size_x = 100000;
	int player_location_x = 0;
	int player_inverted_x = 100;
	int player_location_y = 0;
	void setup_location_world(HWND hwnd);
};