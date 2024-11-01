#include "world.h"
#include "input_controls.h"
#include "hitboxes.h"

void world_scene::setup_location_world(HWND hwnd) {
	if (input_system.right_move) {
		
	    player_location_x += 35;
		
	}
	else if (input_system.left_move) {
		player_location_x -= 35;

	}
}
