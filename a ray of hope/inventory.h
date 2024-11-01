#pragma once
#include <wtypes.h>

#include <vector>
#include <string>
#include <wtypes.h>
#include <algorithm>
#include <thread>

enum class items_c {
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

enum sub_item_select {
	APPLY_ITEM,
	DELETE_ITEM,
	ABOUT_ITEM
};

class inventory_c {
private:
	RECT rect;
	RECT rect_preview;
	RECT item_rect[(unsigned long)items_c::MAX_ITEMS];
	RECT sub_item_rect[(unsigned long)items_c::MAX_ITEMS];
	RECT sub_item_button_rect[5][(unsigned long)items_c::MAX_ITEMS];
	RECT item_text_rect[(unsigned long)items_c::MAX_ITEMS];
	RECT item_value_rect[(unsigned long)items_c::MAX_ITEMS];
	bool sub_item[(unsigned long)items_c::MAX_ITEMS];
	bool sub_item_clicked[5][(unsigned long)items_c::MAX_ITEMS];
	const wchar_t* item_name[(unsigned long)items_c::MAX_ITEMS];
	int item_count[(unsigned long)items_c::MAX_ITEMS];
	bool opened = false;
	
public:
	bool add_stop[10];
	int money = 0;
	RECT rect_dock;
	int animated_y = 0;
	void Init(HWND hwnd, HDC hdc);
	void CreateItem(const wchar_t* name_item, int count_item, int index_item);
	void GetItems(HDC hdc);
	void Dock(HWND hwnd, HDC hdc);

	void ControlItemButton(HDC hdc, int index);

	void ControlItem(HDC hdc, int index);

	//void AddItem(const wchar_t* name_item, int count_item);

	void OnUpdate();
	void GetMoney(HDC hdc);
	bool Hovered(bool opened = false);

	std::vector<int> items;

	

};

extern inventory_c inventory;