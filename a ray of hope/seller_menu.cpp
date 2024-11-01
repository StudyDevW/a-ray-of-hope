#include "seller_menu.h"
#include "input_controls.h"
#include "eventlogs.h"
#include <string.h>
#include <sstream>
#include "hitboxes.h"
#include "render_pixel.h"
#include "a ray of hope.h"
#include "inventory.h"


extern event_logs eventlog;


void seller_c::Init(HWND hwnd, HDC hdc) {

	if (!release_dock_seller)
		PreDock(hwnd, hdc);

	Dock(hwnd, hdc);
}

void seller_c::PreDock(HWND hwnd, HDC hdc) {
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);

	static float anim_y = 0.f;

	if (hitboxes.in_seller_interface) {
		anim_y += 0.1f;
		if (anim_y >= 1.f)
			anim_y = 1.f;
	}
	else {
		anim_y -= 0.1f;
		if (anim_y <= 0.f)
			anim_y = 0.f;
	}

	GetClientRect(hwnd, &pre_rect);
	rect_pre_init = { pre_rect.left + pre_rect.right / 3,  pre_rect.bottom - (int)(200 * anim_y), 
		pre_rect.right - pre_rect.right / 3, pre_rect.bottom - (int)(100 * anim_y) };
	rect_pre_init_text = { rect_pre_init.left, rect_pre_init.top, rect_pre_init.right, rect_pre_init.top + 30 };

	DrawText(hdc, L"Вы желаете заглягуть в магазин?", -1, &rect_pre_init_text, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (hitboxes.in_seller_interface) {
		PreDockButton(hwnd, hdc);
	}

	DeleteObject(hBrush);
}

void seller_c::PreDockButton(HWND hwnd, HDC hdc) {
	pre_rect_button[RECT_BUTTON] = {rect_pre_init.left + 100, rect_pre_init.top + 30,
		rect_pre_init.right - 100, rect_pre_init.bottom - 20};
	pre_rect_button[RECT_TEXT_BUTTON] = { pre_rect_button[RECT_BUTTON].left, 
		pre_rect_button[RECT_BUTTON].top + 10, pre_rect_button[RECT_BUTTON].right, pre_rect_button[RECT_BUTTON].bottom - 10 };
	Rectangle(hdc, pre_rect_button[RECT_BUTTON].left, pre_rect_button[RECT_BUTTON].top, 
		pre_rect_button[RECT_BUTTON].right, pre_rect_button[RECT_BUTTON].bottom);

	DrawText(hdc, L"Войти в магазин ->", -1, &pre_rect_button[RECT_TEXT_BUTTON], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > pre_rect_button[RECT_BUTTON].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < pre_rect_button[RECT_BUTTON].bottom) {
		input_system.mouse_reset = true;
		release_dock_seller = true;
	}

}

void seller_c::GetMoney(HDC hdc) {
	RECT money_pos = { rect.right - rect.right / 4 + 10 - 200, rect.bottom - animated_y, 
		rect.right - rect.right / 4 + 10, rect.bottom + 30 - animated_y };
	std::wstringstream ss;
	ss << inventory.money << L" монет";
	DrawText(hdc, ss.str().c_str(), -1, &money_pos, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}


void seller_c::OnUpdate() {

	if (input_system.right_move
		|| input_system.left_move
		|| input_system.jump) {
		release_dock_seller = false;
	}

	if (!release_dock_seller) {
		if (animated_y >= 0) {
			animated_y -= 50;
		}

		if (animated_y <= 0) {
			opened = false;
		}
	}
	else if (Hovered()) {
		if (animated_y < rect.bottom / 2 + 150) {
			animated_y += 50;
		}

		if (animated_y > 90)
			opened = true;

	}

	if (sub_item_clicked[BUY_ITEM][(int)items_c::FIRST_ITEM] && inventory.money >= 100) {
		flask_count_item--;
		inventory.money -= 100;
		CreateItem(L"Фляга", flask_count_item, (int)items_c::FIRST_ITEM);
		eventlog.CreateLog(L"Фляга куплена 1шт");

		hitboxes.flask_count_item++;
		inventory.CreateItem(L"Фляга", hitboxes.flask_count_item, (int)items_c::FIRST_ITEM);

		sub_item[(int)items_c::FIRST_ITEM] = false;
		sub_item_clicked[BUY_ITEM][(int)items_c::FIRST_ITEM] = false;
	}
	else if (sub_item_clicked[BUY_ITEM][(int)items_c::FIRST_ITEM] && inventory.money < 100) {
		eventlog.CreateLog(L"У вас недостаточно монет!");
		sub_item[(int)items_c::FIRST_ITEM] = false;
		sub_item_clicked[BUY_ITEM][(int)items_c::FIRST_ITEM] = false;
	}
}

void seller_c::ControlItem(HDC hdc, int index) {

	sub_item_rect[index] = { item_rect[index].right - 30, item_rect[index].top, item_rect[index].right + 90, item_rect[index].top + 30 };
	Rectangle(hdc, sub_item_rect[index].left, sub_item_rect[index].top, sub_item_rect[index].right, sub_item_rect[index].bottom);


	sub_item_button_rect[0][index] = { sub_item_rect[index].left, sub_item_rect[index].bottom - 30, sub_item_rect[index].right, sub_item_rect[index].bottom };
	sub_item_button_rect[1][index] = { sub_item_rect[index].left, sub_item_button_rect[0][index].top - 31, sub_item_rect[index].right, sub_item_button_rect[0][index].top - 1 };
	sub_item_button_rect[2][index] = { sub_item_rect[index].left, sub_item_button_rect[1][index].top - 31, sub_item_rect[index].right, sub_item_button_rect[1][index].top - 1 };

	Rectangle(hdc, sub_item_button_rect[0][index].left, sub_item_button_rect[0][index].top, sub_item_button_rect[0][index].right, sub_item_button_rect[0][index].bottom);
	DrawText(hdc, L"Купить", -1, &sub_item_button_rect[0][index], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > sub_item_button_rect[0][index].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < sub_item_button_rect[0][index].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > sub_item_button_rect[0][index].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < sub_item_button_rect[0][index].bottom) {
		input_system.mouse_reset = true;
		sub_item_clicked[BUY_ITEM][index] = true;
	}


	Rectangle(hdc, sub_item_button_rect[1][index].left, sub_item_button_rect[1][index].top, sub_item_button_rect[1][index].right, sub_item_button_rect[1][index].bottom);

	DrawText(hdc, L"Подробнее", -1, &sub_item_button_rect[1][index], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > sub_item_button_rect[1][index].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < sub_item_button_rect[1][index].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > sub_item_button_rect[1][index].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < sub_item_button_rect[1][index].bottom) {
		input_system.mouse_reset = true;
		sub_item_clicked[ABOUT_BUY_ITEM][index] = true;
	}
}

void seller_c::CreateItem(const wchar_t* name_item, int count_item, int index_item) {
	items.push_back(index_item);

	item_count[index_item] = count_item;
	item_name[index_item] = name_item;

}

void seller_c::SetupItems() {
	CreateItem(L"Фляга", flask_count_item, (int)items_c::FIRST_ITEM);
}


void seller_c::GetItems(HDC hdc)
{
	while (items.size() > 6)
		items.erase(items.begin());

	for (int i = items.size() - 1; i >= 0; i--)
	{
		int x_position = rect_dock.left + 40 + (100 * i);
		int y_position = rect_preview.bottom + 10;

		if (item_count[i] > 0) {
			HBRUSH hBrush;
			item_rect[i] = { (int)x_position,(int)y_position, (int)x_position + 90, (int)y_position + 90 };

			item_text_rect[i] = { item_rect[i].left, item_rect[i].bottom, item_rect[i].right, item_rect[i].bottom + 30 };
			item_value_rect[i] = { item_rect[i].right - 25, item_rect[i].bottom - 25, item_rect[i].right, item_rect[i].bottom };

			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);

			Rectangle(hdc, item_rect[i].left, item_rect[i].top, item_rect[i].right, item_rect[i].bottom);

			DeleteObject(hBrush);

			if (item_name[i] == L"Фляга")
				render.HealFlask(hdc, item_rect[i].left / PIXELB + 2, item_rect[i].top / PIXELB + 2);

			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);

			DrawText(hdc, item_name[i], -1, &item_text_rect[i], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

			DrawText(hdc, std::to_wstring(item_count[i]).c_str(), -1, &item_value_rect[i], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

			if (input_system.mouse_pos_x[MOUSE_INVENTORY] > item_rect[i].left
				&& input_system.mouse_pos_x[MOUSE_INVENTORY] < item_rect[i].right
				&& input_system.mouse_pox_y[MOUSE_INVENTORY] > item_rect[i].top
				&& input_system.mouse_pox_y[MOUSE_INVENTORY] < item_rect[i].bottom) {
				input_system.mouse_reset = true;
				sub_item[i] = !sub_item[i];
			}
			if (sub_item[i]) {
				ControlItem(hdc, i);
			}
			if (Hovered(true)) {
				sub_item[i] = false;
			}
			DeleteObject(hBrush);
		}
	}
}

void seller_c::Dock(HWND hwnd, HDC hdc) {
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);



	GetClientRect(hwnd, &rect);
	rect_preview = { rect.left + rect.right / 4 + 10, rect.bottom - animated_y, rect.right - rect.right / 4 + 10, rect.bottom + 30 - animated_y };
	rect_dock = { rect.left + rect.right / 4,  rect.bottom - animated_y, rect.right - rect.right / 4, rect.bottom + 300 - animated_y };

	Rectangle(hdc, rect_dock.left, rect_dock.top, rect_dock.right, rect_dock.bottom);
	//	MoveToEx(hdc, rect.left + 100, rect.bottom - animated_y, NULL);
		//LineTo(hdc, rect.right - 100, rect.bottom - animated_y);
	DrawText(hdc, L"Магазин", -1, &rect_preview, DT_SINGLELINE | DT_VCENTER );

	GetMoney(hdc);

	SetupItems();

	GetItems(hdc);

	DeleteObject(hBrush);

}


bool seller_c::Hovered(bool opened) {
	if (opened) {

		if (!release_dock_seller) {
			return true;
		}

	}
	else {

		if (release_dock_seller) {
			return true;
		}
	}

	return false;
}