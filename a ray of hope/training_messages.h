#pragma once
#include <wtypes.h>

#include <vector>
#include <string>
#include <wtypes.h>
#include <algorithm>
#include <thread>
#include "sdk.h"

enum pre_button_selected_1 {
	RECT_BUTTON_1,
	RECT_TEXT_BUTTON_1
};

enum pre_button_selected_2 {
	PLATFORM_,
	LADDER_,
	FLASK_
};

class training_message_c {
private:
	local_player_t local_player;
	RECT pre_rect[50];
	RECT rect_pre_init[50];
	RECT rect_pre_init_text[50];
	RECT pre_rect_button[3][50];
	bool animate_message[3][50];
	int timer_custom_message[2];
public:
	void Init(HWND hwnd, HDC hdc);
	void Dock(HWND hwnd, HDC hdc, int index_platform);
	void DockLadder(HWND hwnd, HDC hdc, int index_ladder);
	void DockButton(HWND hwnd, HDC hdc, int index_platform);
	void DockButtonLadder(HWND hwnd, HDC hdc, int index_ladder);
	void OnUpdate();
};
extern training_message_c training_message;