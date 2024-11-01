#pragma once
#include <wtypes.h>

enum mouse_set {
	MOUSE_IN_GAME,
	MOUSE_IN_INTERFACE,
	MOUSE_ALWAYS,
	MOUSE_INVENTORY, 
	MOUSE_INVENTORY_L
};

class input_control_t {
public:
	bool right_move = false;
	bool right_side_move = true;
	bool left_side_move = false;
	bool left_move = false;
	bool jump = false;
	bool escaped = false;
	bool attacked = false;
	bool attacked2 = false;
	bool game_clicked = false;
	int mouse_pos_x[5];
	int mouse_pox_y[5];
	bool mouse_reset = false;
	bool blocked = false;
	bool q_pressed = false;
	bool i_pressed = false;
	bool w_pressed = false;
	
	void Init(WPARAM wParam, LPARAM lParam);

	void Mouse(LPARAM lParam);

	void MouseR(LPARAM lParam);

	void reset(bool moved = false) {
		if (moved) {
			attacked2 = false;
		}
		else {
			right_move = false;
			left_move = false;
			jump = false;
			attacked = false;
			q_pressed = false;
			w_pressed = false;
			game_clicked = false;
		}
	}
};

extern input_control_t input_system;