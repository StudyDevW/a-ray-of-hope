#include <tchar.h>
#include "hitboxes.h"
#include "input_controls.h"
#include "interface.h"
#include <string.h>
#include <sstream>
#include "config_game.h"
#include "eventlogs.h"
#include "sdk.h"

extern event_logs eventlog;

config_game config;



void interface_t::InGameInterface(HDC hdc, HWND hwnd) {
    RECT rect;
    RECT dop_rect[15];

    GetClientRect(hwnd, &rect);
    dop_rect[0] = { rect.left, rect.top, rect.right, rect.bottom / 3 };
   // dop_rect[1] = { rect.left, rect.top + 100, rect.right, rect.bottom / 3 };
  //  dop_rect[2] = { rect.left, rect.top + 300, rect.right, rect.bottom / 3 };

    if (input_system.escaped) {
        
        if (in_save) 
            InSave(hdc, dop_rect[0], rect);
        else if (in_load) 
            InLoad(hdc, dop_rect[0], rect);
        else 
            InEscaped(hdc, dop_rect[0], rect);
        
    }
}

void interface_t::Init(HDC hdc, HWND hwnd) {
    RECT rect;
    RECT dop_rect[15];
    GetClientRect(hwnd, &rect);



    dop_rect[0] = { rect.left, rect.top, rect.right, rect.bottom / 3 };

    if (!in_game) {
        if (!in_pregame) {

            config.pre_load[100] = true;
            config.need_to_load[100] = "c:\\Temp\\training_info.txt";

            DrawText(hdc, (LPCWSTR)L"Луч надежды", -1, &dop_rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            if (Button(hdc, L"Играть", rect.right / 2 - 75, rect.bottom / 2)) {
             //   hitboxes.ClearAllBoxes();
             
                in_pregame = true;
            }

            if (Button(hdc, L"Все модели", rect.right / 2 - 75, rect.bottom / 2 - 50)) {
                test_preview = true;
            }
        }
        else if (in_pregame) {
            if (!in_load_game) {
                if (!hitboxes.training_ended) {
                    if (Button(hdc, L"Обучение", rect.right / 2 - 75, rect.bottom / 2 - 50)) {
                        hitboxes.active_level = 0;
                        in_pregame = false;
                        in_game = true;

                    }
                }
                else if (hitboxes.training_ended) {
                    Button(hdc, L"ИСдо-17", rect.right / 2 - 75, rect.bottom / 2 + 50);

                    Button(hdc, L"Антон(Study)", rect.right / 2 - 75, rect.bottom / 2);

                    Button(hdc, L"Игра в разработке", rect.right / 2 - 75, rect.bottom / 2 - 50);
                }
            }
            else if (in_load_game) {
                DrawText(hdc, (LPCWSTR)L"Выберите слот", -1, &dop_rect[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

                int y = -250;

                for (int i = 1; i <= config.slots; i++) {
                    std::stringstream ss;
                    std::wstringstream button_name;
                    y += 50;

                    ss << "c:\\Temp\\slot_" << i << ".txt";
                    button_name << L"Загрузить " << std::to_wstring(i) << L" слот\n";

                    if (Button(hdc, button_name.str().c_str(), rect.right / 2 - 75, rect.bottom / 2 + y, false)) {
                        config.pre_load[i] = true;
                        config.need_to_load[i] = ss.str().c_str();
                        in_load_game = false;
                        in_pregame = false;
                        in_game = true;
                    }
                }
            }
        }
    }

    if (death_screen) 
        Death_screen(hdc, dop_rect[0], rect);
}

void interface_t::InSave(HDC hdc, RECT text_rect, RECT button_rect) {
    DrawText(hdc, (LPCWSTR)L"Выберите слот", -1, &text_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    int y = -250;

    for (int i = 1; i <= config.slots; i++) {
        std::stringstream ss;
        std::wstringstream button_name;
        y += 50;

        ss << "c:\\Temp\\slot_" << i << ".txt";
        button_name << L"Сохранить " << std::to_wstring(i) << L" слот\n";
        if (Button(hdc, button_name.str().c_str(), button_rect.right / 2 - 75, button_rect.bottom / 2 + y, true)) {
            config.pre_save[i] = true;
            config.need_to_save[i] = ss.str().c_str();
            in_save = false;
        }
    }
}

void interface_t::InLoad(HDC hdc, RECT text_rect, RECT button_rect) {
    DrawText(hdc, (LPCWSTR)L"Выберите слот", -1, &text_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    int y = -250;

    for (int i = 1; i <= config.slots; i++) {
        std::stringstream ss;
        std::wstringstream button_name;
        y += 50;

        ss << "c:\\Temp\\slot_" << i << ".txt";
        button_name << L"Загрузить " << std::to_wstring(i) << L" слот\n";
        if (Button(hdc, button_name.str().c_str(), button_rect.right / 2 - 75, button_rect.bottom / 2 + y, true)) {
            config.pre_load[i] = true;
            config.need_to_load[i] = ss.str().c_str();
            in_load = false;
        }
    }
}

void interface_t::InEscaped(HDC hdc, RECT text_rect, RECT button_rect) {
    DrawText(hdc, (LPCWSTR)text, -1, &text_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    if (Button(hdc, L"Загрузить", button_rect.right / 2 - 75, button_rect.bottom / 2 + 50, true)) 
        in_load = true;

    if (Button(hdc, L"Сохранить", button_rect.right / 2 - 75, button_rect.bottom / 2, true)) 
        in_save = true;
    
    if (Button(hdc, L"Продолжить", button_rect.right / 2 - 75, button_rect.bottom / 2 - 50, true)) {
        input_system.escaped = false;
        text = L"Пауза";
    }
}


void interface_t::Death_screen(HDC hdc, RECT text_rect, RECT button_rect) {
    DrawText(hdc, (LPCWSTR)L"Вы погибли", -1, &text_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    if (Button(hdc, L"Начать заново", button_rect.right / 2 - 75, button_rect.bottom / 2)) 
        death_screen = false;
    

    if (Button(hdc, L"Главное меню", button_rect.right / 2 - 75, button_rect.bottom / 2 - 50)) {
        death_screen = false;
        in_game = false;
    }
}



void interface_t::WorldCoord(HDC hdc, HWND hwnd) {
    RECT rect = { 0, 0, 0, 0 };
 
    GetClientRect(hwnd, &rect);

    RECT drect = { rect.left, rect.top, rect.right / 3, rect.bottom };

    if (in_game && !death_screen) {
        DrawText(hdc, (LPCWSTR)(std::to_wstring(hitboxes.local_box.top).c_str()), -1, &drect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    }
}


bool interface_t::Button(HDC hdc, const wchar_t* text, int x, int y, bool in_game) {
    RECT button_box = { 0 + x, 0 + y, 150 + x, 40 + y };
    RECT text_pos = { button_box.left, button_box.top, button_box.right, button_box.bottom };
    Rectangle(hdc, button_box.left, button_box.top, button_box.right, button_box.bottom);

    DrawText(hdc, (LPCWSTR)text, -1, &text_pos, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    if (in_game) {
        if (input_system.mouse_pos_x[MOUSE_IN_GAME] < button_box.right
            && input_system.mouse_pos_x[MOUSE_IN_GAME] > button_box.left
            && input_system.mouse_pox_y[MOUSE_IN_GAME] < button_box.bottom
            && input_system.mouse_pox_y[MOUSE_IN_GAME] > button_box.top) {
            input_system.mouse_reset = true;
            return true;
        }
    }
    else {
        if (input_system.mouse_pos_x[MOUSE_IN_INTERFACE] < button_box.right
            && input_system.mouse_pos_x[MOUSE_IN_INTERFACE] > button_box.left
            && input_system.mouse_pox_y[MOUSE_IN_INTERFACE] < button_box.bottom
            && input_system.mouse_pox_y[MOUSE_IN_INTERFACE] > button_box.top) {
            input_system.mouse_reset = true;
            return true;
        }
    }

    return false;
}


























//  dop_rect[1] = { rect.left + rect.right / 2, rect.top / 3, rect.right, rect.bottom };
  //  dop_rect[2] = { rect.left + rect.right / 2, rect.top / 3, rect.right, rect.bottom + 40 };
  //  dop_rect[3] = { rect.left + rect.right / 2, rect.top / 3, rect.right, rect.bottom + 80 };


// DrawText(hdc, (LPCWSTR)L"Разработал Cтудент", -1, &dop_rect[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
  // DrawText(hdc, (LPCWSTR)L"Группы: ИСдо-17", -1, &dop_rect[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
 //  DrawText(hdc, (LPCWSTR)L"Сыченко Антон Игоревич ", -1, &dop_rect[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);