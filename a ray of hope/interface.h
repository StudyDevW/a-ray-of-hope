#pragma once
#include <wtypes.h>


enum levels {
	FIRST_LEVEL,
	SECOND_LEVEL,
	MAX_LEVELS
};


class interface_t {
public:
	
	void Init(HDC hdc, HWND hwnd);
	void InSave(HDC hdc, RECT text_rect, RECT button_rect);
	void InLoad(HDC hdc, RECT text_rect, RECT button_rect);
	void InEscaped(HDC hdc, RECT text_rect, RECT button_rect);
	void Death_screen(HDC hdc, RECT text_rect, RECT button_rect);
	bool Button(HDC hdc, const wchar_t* text, int x, int y, bool in_game = false);
	void InGameInterface(HDC hdc, HWND hwnd);
	void WorldCoord(HDC hdc, HWND hwnd);
	const wchar_t* text = L"Пауза";
	bool in_game = false;
	bool in_pregame = false;
	bool in_load_game = false;
	bool death_screen = false;
	bool in_save = false;
	bool in_load = false;
	bool created = false;
	bool test_preview = false;
	
	bool updated_preview = false;
};

extern interface_t interfaces;

