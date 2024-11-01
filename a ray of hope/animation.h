#pragma once

class animation {
public:
	void MoveAnims();

	void OnUpdate();

	int active_index = 0;
	int active_index_at = 0;
	int attack_timer = 0;
	bool end_point = false;
	bool start_point = false;
	bool redraw_window = false;

	bool start_attack = false;
	bool end_attack = false;

	void reset() {
		redraw_window = false;
	}
};

extern animation animationfix;