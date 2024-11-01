#pragma once
#include <wtypes.h>

#include <vector>
#include <string>
#include <wtypes.h>
#include <algorithm>
#include <thread>



enum class items_seller_c {
	FIRST_ITEM,
	SECOND_ITEM,
	THIRD_ITEM,
	FOUR_ITEM,
	FIVE_ITEM,
	SIX_ITEM,
	SEVEN_ITEM,
	EIGHT_ITEM,
	NINE_ITEM,
	TEN_ITEM,
	MAX_ITEMS
};

enum sub_item_seller_select {
	BUY_ITEM,
	ABOUT_BUY_ITEM
};

enum pre_button_selected {
	RECT_BUTTON,
	RECT_TEXT_BUTTON
};


class seller_c {
private:
	RECT pre_rect_button[2];
	RECT pre_rect;
	RECT rect_pre_init;
	RECT rect_pre_init_text;
	RECT rect;
	RECT rect_preview;
	bool release_dock_seller = false;
	bool opened = false;
	RECT item_rect[(unsigned long)items_seller_c::MAX_ITEMS];
	RECT sub_item_rect[(unsigned long)items_seller_c::MAX_ITEMS];
	RECT sub_item_button_rect[5][(unsigned long)items_seller_c::MAX_ITEMS];
	RECT item_text_rect[(unsigned long)items_seller_c::MAX_ITEMS];
	RECT item_value_rect[(unsigned long)items_seller_c::MAX_ITEMS];
	bool sub_item[(unsigned long)items_seller_c::MAX_ITEMS];
	bool sub_item_clicked[5][(unsigned long)items_seller_c::MAX_ITEMS];
	const wchar_t* item_name[(unsigned long)items_seller_c::MAX_ITEMS];
	int item_count[(unsigned long)items_seller_c::MAX_ITEMS];
	int flask_count_item = 3;
public:
	RECT rect_dock;
	int animated_y = 0;
	void Init(HWND hwnd, HDC hdc);
	void PreDock(HWND hwnd, HDC hdc);
	void PreDockButton(HWND hwnd, HDC hdc);
	void GetMoney(HDC hdc);
	void OnUpdate();
	void ControlItem(HDC hdc, int index);
	void CreateItem(const wchar_t* name_item, int count_item, int index_item);
	void SetupItems();
	void GetItems(HDC hdc);
	void Dock(HWND hwnd, HDC hdc);
	bool Hovered(bool opened = false);

	std::vector<int> items;
};

extern seller_c seller;