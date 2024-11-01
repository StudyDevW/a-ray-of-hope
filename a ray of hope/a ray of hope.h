#pragma once

#include "resource.h"
#include "render_pixel.h"
#include "sdk.h"

class pre_render {
public:
	local_player_t local_player;
	void RenderPixel(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color, bool inverted = false);
	void RenderPixelB(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color);
	void RenderPixelLine(HDC hdc, pixels_other_t pix_info, int index, COLORREF color);
	void RenderPixelLineB(HDC hdc, pixels_other_t pix_info, int index, COLORREF color);
	void RenderHat(HDC hdc, int x, int y, int sp = 0);
	void RenderFace(HDC hdc, int x, int y, int sp = 0);
	void RenderArms(HDC hdc, int x, int y, int sp = 0);
	void RenderArms_AT(HDC hdc, int x, int y, int sp = 0);
	void RenderBody(HDC hdc, int x, int y, int sp = 0);
	void RenderLegs_2(HDC hdc, int x, int y, int sp = 0);
	void RenderLegs_1(HDC hdc, int x, int y, int sp = 0);
	void RenderLegs(HDC hdc, int x, int y, int sp = 0);
	void RenderMainCharacter(HDC hdc, int x, int y, int index, int sp = 0);
	void RenderMainCharacterAttack(HDC hdc, int x, int y, int index, int sp = 0);
	void EyeStormBody(HDC hdc, int x, int y);
	void EyeStormHead(HDC hdc, int x, int y);
	void EyeStormHead_1(HDC hdc, int x, int y);
	void EyeStormHead_2(HDC hdc, int x, int y);
	void EyeStormHead_3(HDC hdc, int x, int y);
	void EyeStormHead_Attack1(HDC hdc, int x, int y);
	void EyeStormHead_Attack2(HDC hdc, int x, int y);
	void EyeStormHead_Attack3(HDC hdc, int x, int y, int sp);

	void EyeStorm(HDC hdc, int x, int y);
	void Buffer(HDC hdc);
	void Platform(HDC hdc);
	void Platform1(HDC hdc);
	void Draw(HDC hdc);
	void DrawHealthBar(HDC hdc, int player_index, int enemy_idx = 0);
	void PreviewModels(HDC hdc);
	void GrassLeftCorner(HDC hdc, int x, int y, int sp);
	
	void GrassMiddle(HDC hdc, int x, int y);
	void AttackAnims(HDC hdc, int x, int y, int sp = 0);
	void AttackAnimsT(HDC hdc, int x, int y, int sp = 0);
	void HealFlask(HDC hdc, int x, int y);
	void Slime(HDC hdc, int x, int y);
	void SlimeAttack(HDC hdc, int x, int y);
	void DrawBackground(HDC hdc, RECT rect);
	void Init(HWND hWnd);
	bool update = false;
	void TrainingLevel(HDC hdc, HWND hWnd);
};

extern pre_render render;