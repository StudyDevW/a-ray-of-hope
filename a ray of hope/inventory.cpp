#include "inventory.h"
#include "input_controls.h"
#include "eventlogs.h"
#include <string.h>
#include <sstream>
#include "hitboxes.h"
#include "render_pixel.h"
#include "a ray of hope.h"

extern event_logs eventlog;

void inventory_c::Init(HWND hwnd, HDC hdc) {
	Dock(hwnd, hdc);
}

void inventory_c::CreateItem(const wchar_t* name_item, int count_item, int index_item) {
	items.push_back(index_item);

	item_count[index_item] = count_item;
	item_name[index_item] = name_item;

}

void inventory_c::OnUpdate() {
	if (opened && Hovered(true)) {
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

	if (hitboxes.local_health < 1.f && sub_item_clicked[APPLY_ITEM][(int)items_c::FIRST_ITEM]) {
		hitboxes.local_health = 1.f;
		hitboxes.flask_count_item--;
		inventory.CreateItem(L"Фляга", hitboxes.flask_count_item, (int)items_c::FIRST_ITEM);
		eventlog.CreateLog(L"Здоровье пополнено!");
		sub_item[(int)items_c::FIRST_ITEM] = false;
		sub_item_clicked[APPLY_ITEM][(int)items_c::FIRST_ITEM] = false;
	}
	else if (sub_item_clicked[APPLY_ITEM][(int)items_c::FIRST_ITEM]) {
		eventlog.CreateLog(L"Вы и так здоровы!");
		sub_item[(int)items_c::FIRST_ITEM] = false;
		sub_item_clicked[APPLY_ITEM][(int)items_c::FIRST_ITEM] = false;
	}

	if (sub_item_clicked[DELETE_ITEM][(int)items_c::FIRST_ITEM]) {
		hitboxes.flask_count_item--;
		inventory.CreateItem(L"Фляга", hitboxes.flask_count_item, (int)items_c::FIRST_ITEM);

		eventlog.CreateLog(L"Предмет выброшен!");
		sub_item[(int)items_c::FIRST_ITEM] = false;
		sub_item_clicked[DELETE_ITEM][(int)items_c::FIRST_ITEM] = false;
	}
}

void inventory_c::GetMoney(HDC hdc) {
	RECT money_pos = { rect.right - rect.right / 4 + 10 - 200, rect.bottom - animated_y, rect.right - rect.right / 4 + 10, rect.bottom + 30 - animated_y };
	std::wstringstream ss;
	ss << money << L" монет";
	DrawText(hdc, ss.str().c_str(), -1, &money_pos, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

void inventory_c::Dock(HWND hwnd,HDC hdc ) {

	GetClientRect(hwnd, &rect);
	rect_preview = { rect.left + rect.right / 4 + 10, rect.bottom - animated_y, rect.right - rect.right / 4 + 10, rect.bottom + 30 - animated_y };
	rect_dock = { rect.left + rect.right / 4,  rect.bottom - animated_y, rect.right - rect.right / 4, rect.bottom + 300 - animated_y };
	

	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);

	
	Rectangle(hdc, rect_dock.left, rect_dock.top, rect_dock.right, rect_dock.bottom);

	DrawText(hdc, L"Инвентарь", -1, &rect_preview, DT_SINGLELINE | DT_VCENTER);
	
	GetMoney(hdc);

	GetItems(hdc);
	for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
		if (hitboxes.defeated_enemy[i]) {
			if (!add_stop[i]) {
				inventory.money += 100;
				eventlog.CreateLog(L"Враг побежден +100 монет");
				add_stop[i] = true;
			}
		}
	}

	DeleteObject(hBrush);
}

void inventory_c::ControlItem(HDC hdc, int index) {

	sub_item_rect[index] = { item_rect[index].right - 30, item_rect[index].top - 60, item_rect[index].right + 90, item_rect[index].top + 30 };
	Rectangle(hdc, sub_item_rect[index].left, sub_item_rect[index].top, sub_item_rect[index].right, sub_item_rect[index].bottom);


	sub_item_button_rect[0][index] = { sub_item_rect[index].left, sub_item_rect[index].bottom - 30, sub_item_rect[index].right, sub_item_rect[index].bottom };
	sub_item_button_rect[1][index] = { sub_item_rect[index].left, sub_item_button_rect[0][index].top - 31, sub_item_rect[index].right, sub_item_button_rect[0][index].top - 1 };
	sub_item_button_rect[2][index] = { sub_item_rect[index].left, sub_item_button_rect[1][index].top - 31, sub_item_rect[index].right, sub_item_button_rect[1][index].top - 1 };

	Rectangle(hdc, sub_item_button_rect[0][index].left, sub_item_button_rect[0][index].top, sub_item_button_rect[0][index].right, sub_item_button_rect[0][index].bottom);
	DrawText(hdc, L"Применить", -1, &sub_item_button_rect[0][index], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > sub_item_button_rect[0][index].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < sub_item_button_rect[0][index].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > sub_item_button_rect[0][index].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < sub_item_button_rect[0][index].bottom) {
		input_system.mouse_reset = true;
		sub_item_clicked[APPLY_ITEM][index] = true;
	}


	Rectangle(hdc, sub_item_button_rect[1][index].left, sub_item_button_rect[1][index].top, sub_item_button_rect[1][index].right, sub_item_button_rect[1][index].bottom);

	SetTextColor(hdc, RGB(255, 0, 0));
	DrawText(hdc, L"Выбросить", -1, &sub_item_button_rect[1][index], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	SetTextColor(hdc, RGB(0, 0, 0));

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > sub_item_button_rect[1][index].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < sub_item_button_rect[1][index].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > sub_item_button_rect[1][index].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < sub_item_button_rect[1][index].bottom) {
		input_system.mouse_reset = true;
		sub_item_clicked[DELETE_ITEM][index] = true;
	}


	Rectangle(hdc, sub_item_button_rect[2][index].left, sub_item_button_rect[2][index].top, sub_item_button_rect[2][index].right, sub_item_button_rect[2][index].bottom);
	DrawText(hdc, L"Подробнее", -1, &sub_item_button_rect[2][index], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	if (input_system.mouse_pos_x[MOUSE_INVENTORY_L] > sub_item_button_rect[2][index].left
		&& input_system.mouse_pos_x[MOUSE_INVENTORY_L] < sub_item_button_rect[2][index].right
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] > sub_item_button_rect[2][index].top
		&& input_system.mouse_pox_y[MOUSE_INVENTORY_L] < sub_item_button_rect[2][index].bottom) {
		input_system.mouse_reset = true;
		sub_item_clicked[ABOUT_ITEM][index] = true;
	}
}

void inventory_c::GetItems(HDC hdc)
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

bool inventory_c::Hovered(bool opened) {
	if (opened) {

		if (!input_system.i_pressed) {
			return true;
		}

	}
	else {

		if (input_system.i_pressed) {
			return true;
		}
	}

	return false;
}