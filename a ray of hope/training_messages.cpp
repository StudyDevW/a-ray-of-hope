#include "training_messages.h"
#include "input_controls.h"
#include "eventlogs.h"
#include <string.h>
#include <sstream>
#include "hitboxes.h"
#include "render_pixel.h"
#include "a ray of hope.h"
#include "inventory.h"
#include "config_game.h"

void training_message_c::Init(HWND hwnd, HDC hdc) {

	 if (hitboxes.check_touch_floor[FIRST_PLATFORM])
		 Dock(hwnd, hdc, FIRST_PLATFORM);

	 if (hitboxes.check_touch_floor[THIRD_PLATFORM])
		 Dock(hwnd, hdc, THIRD_PLATFORM);
	
	

	 DockLadder(hwnd, hdc, FIRST_LADDER);

	 if (hitboxes.flask_equip)
		 Dock(hwnd, hdc, 100);

	 if (hitboxes.damaged_enemy_tr) 
		 Dock(hwnd, hdc, 101);

	 if (hitboxes.enemy_dead_tr)
		 Dock(hwnd, hdc, 102);


	 if (hitboxes.check_touch_floor[FIVE_PLATFORM])
		 Dock(hwnd, hdc, FIVE_PLATFORM);
}

void training_message_c::Dock(HWND hwnd, HDC hdc, int index_platform) {
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);

	static float anim_y[50];

	if (!animate_message[PLATFORM_][index_platform] 
		&& (index_platform != 100 ? hitboxes.check_touch_floor[index_platform] : hitboxes.flask_equip)
		&& (index_platform != 101 ? hitboxes.check_touch_floor[index_platform] : hitboxes.damaged_enemy_tr)
		&& (index_platform != 102 ? hitboxes.check_touch_floor[index_platform] : hitboxes.enemy_dead_tr)) {
		anim_y[index_platform] += 0.1f;
		if (anim_y[index_platform] >= 1.f) {
			anim_y[index_platform] = 1.f;
		}
	}
	else if (hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		anim_y[index_platform] += 0.1f;
		if (anim_y[index_platform] >= 1.f) {
			anim_y[index_platform] = 1.f;
		}
	}
	else {
		anim_y[index_platform] -= 0.1f;
		if (anim_y[index_platform] <= 0.f)
			anim_y[index_platform] = 0.f;
	}

	GetClientRect(hwnd, &pre_rect[index_platform]);
	rect_pre_init[index_platform] = { pre_rect[index_platform].left + pre_rect[index_platform].right / 3, 
		pre_rect[index_platform].bottom - (int)(200 * anim_y[index_platform]), 
		pre_rect[index_platform].right - pre_rect[index_platform].right / 3, pre_rect[index_platform].bottom - (int)(100 * anim_y[index_platform]) };
	rect_pre_init_text[index_platform] = { rect_pre_init[index_platform].left, rect_pre_init[index_platform].top, 
		rect_pre_init[index_platform].right, rect_pre_init[index_platform].top + 30 };



	if (index_platform != 100 ? hitboxes.check_touch_floor[FIRST_PLATFORM] : hitboxes.flask_equip && !animate_message[PLATFORM_][FIRST_PLATFORM]) {
		DrawText(hdc, L"Передвижение [правая и левая стрелка на клавиатуре]", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else if (index_platform != 100 && hitboxes.check_touch_floor[THIRD_PLATFORM] && !animate_message[PLATFORM_][THIRD_PLATFORM]) {
		DrawText(hdc, L"Это враг, его можно ударить [стрелка вверх]", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	else if (index_platform == 100 && hitboxes.flask_equip && !hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		DrawText(hdc, L"Это Фляга со здоровьем [ee можно подобрать нажав Q]", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else if (index_platform == 101 && hitboxes.damaged_enemy_tr && !hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		timer_custom_message[0]++;
		DrawText(hdc, timer_custom_message[0] > 100 ? L"Которая влияет на то, будет бить вас враг или нет" 
			: L"При ударе заполняется шкала агресивности", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else if (index_platform == 102 && hitboxes.enemy_dead_tr && !hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		timer_custom_message[1]++;
		DrawText(hdc, timer_custom_message[1] > 100 ? L"Которые можно будет обменять у торговца на предметы" 
			: L"Победив врага вы получаете монеты", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else if (hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		DrawText(hdc, L"На этом обучение закончено!", -1, &rect_pre_init_text[index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}



	if (!animate_message[PLATFORM_][index_platform]) {
		input_system.blocked = true;
		if (((timer_custom_message[0] > 100) && (index_platform == 101  && hitboxes.damaged_enemy_tr)) || ((timer_custom_message[1] > 100)
			&& (index_platform == 102 && hitboxes.enemy_dead_tr))) {
			DockButton(hwnd, hdc, index_platform);
		}
		else {
			DockButton(hwnd, hdc, index_platform);
		}
	}

	if (hitboxes.check_touch_floor[FIVE_PLATFORM]) {
		input_system.blocked = true;
		DockButton(hwnd, hdc, index_platform);
	}

	DeleteObject(hBrush);
}

void training_message_c::DockLadder(HWND hwnd, HDC hdc, int index_ladder) {
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);

	static float anim_y[50];

	if (!animate_message[LADDER_][index_ladder] && hitboxes.check_ladder[index_ladder]) {
		anim_y[index_ladder] += 0.1f;
		if (anim_y[index_ladder] >= 1.f) {
			anim_y[index_ladder] = 1.f;
		}
	}
	else {
		anim_y[index_ladder] -= 0.1f;
		if (anim_y[index_ladder] <= 0.f)
			anim_y[index_ladder] = 0.f;
	}

	GetClientRect(hwnd, &pre_rect[index_ladder]);
	rect_pre_init[index_ladder] = { pre_rect[index_ladder].left + pre_rect[index_ladder].right / 3, 
		pre_rect[index_ladder].bottom - (int)(200 * anim_y[index_ladder]), pre_rect[index_ladder].right - pre_rect[index_ladder].right / 3,
		pre_rect[index_ladder].bottom - (int)(100 * anim_y[index_ladder]) };
	rect_pre_init_text[index_ladder] = { rect_pre_init[index_ladder].left, rect_pre_init[index_ladder].top, 
		rect_pre_init[index_ladder].right, rect_pre_init[index_ladder].top + 30 };


	//	Rectangle(hdc, rect_pre_init.left, rect_pre_init.top, rect_pre_init.right, rect_pre_init.bottom);
	if (index_ladder == FIRST_LADDER) {
		//	if (hitboxes.check_touch_floor[index_platform])

		DrawText(hdc, L"Это лестница [она поднимает автоматически]", -1, &rect_pre_init_text[index_ladder], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	if (hitboxes.check_ladder[index_ladder] && !animate_message[LADDER_][index_ladder]) {
		input_system.blocked = true;
		DockButtonLadder(hwnd, hdc, index_ladder);
	}

	DeleteObject(hBrush);
}


void training_message_c::DockButton(HWND hwnd, HDC hdc, int index_platform) {
	pre_rect_button[RECT_BUTTON_1][index_platform] = { rect_pre_init[index_platform].left + 100, 
		rect_pre_init[index_platform].top + 30, rect_pre_init[index_platform].right - 100, rect_pre_init[index_platform].bottom - 20};
	pre_rect_button[RECT_TEXT_BUTTON_1][index_platform] = { pre_rect_button[RECT_BUTTON_1][index_platform].left,
		pre_rect_button[RECT_BUTTON_1][index_platform].top + 10, pre_rect_button[RECT_BUTTON_1][index_platform].right, pre_rect_button[RECT_BUTTON_1][index_platform].bottom - 10};
	Rectangle(hdc, pre_rect_button[RECT_BUTTON_1][index_platform].left, pre_rect_button[RECT_BUTTON_1][index_platform].top, 
		pre_rect_button[RECT_BUTTON_1][index_platform].right, pre_rect_button[RECT_BUTTON_1][index_platform].bottom);

	DrawText(hdc, L"Далее", -1, &pre_rect_button[RECT_TEXT_BUTTON_1][index_platform], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON_1][index_platform].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON_1][index_platform].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON_1][index_platform].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON_1][index_platform].bottom) {
		input_system.mouse_reset = true;
		input_system.blocked = false;

		if (index_platform == FIVE_PLATFORM) {
		
			hitboxes.training_ended = true;
			config.pre_save[100] = true;
			config.need_to_save[100] = "c:\\Temp\\training_info.txt";

			interfaces.death_screen = false;
			interfaces.in_game = false;
		}

		if (index_platform == 100)
			hitboxes.flask_equip = false;

		if (index_platform == 101) {
			hitboxes.damaged_enemy_tr = false;
			timer_custom_message[0] = 0;
		}

		if (index_platform == 102) {
			hitboxes.enemy_dead_tr = false;
			timer_custom_message[1] = 0;
		}

		animate_message[PLATFORM_][index_platform] = true;
	}
}

void training_message_c::DockButtonLadder(HWND hwnd, HDC hdc, int index_ladder) {
	pre_rect_button[RECT_BUTTON_1][index_ladder] = { rect_pre_init[index_ladder].left + 100, 
		rect_pre_init[index_ladder].top + 30, rect_pre_init[index_ladder].right - 100, rect_pre_init[index_ladder].bottom - 20 };
	pre_rect_button[RECT_TEXT_BUTTON_1][index_ladder] = { pre_rect_button[RECT_BUTTON_1][index_ladder].left, 
		pre_rect_button[RECT_BUTTON_1][index_ladder].top + 10, pre_rect_button[RECT_BUTTON_1][index_ladder].right, pre_rect_button[RECT_BUTTON_1][index_ladder].bottom - 10 };
	Rectangle(hdc, pre_rect_button[RECT_BUTTON_1][index_ladder].left, pre_rect_button[RECT_BUTTON_1][index_ladder].top, 
		pre_rect_button[RECT_BUTTON_1][index_ladder].right, pre_rect_button[RECT_BUTTON_1][index_ladder].bottom);

	DrawText(hdc, L"Далее", -1, &pre_rect_button[RECT_TEXT_BUTTON_1][index_ladder], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON_1][index_ladder].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON_1][index_ladder].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON_1][index_ladder].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON_1][index_ladder].bottom) {
		input_system.mouse_reset = true;
		input_system.blocked = false;
		animate_message[LADDER_][index_ladder] = true;
	}

}

void training_message_c::OnUpdate() {
	
}