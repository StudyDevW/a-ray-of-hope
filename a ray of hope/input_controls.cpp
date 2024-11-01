#include "input_controls.h"
#include "interface.h"

void input_control_t::Init(WPARAM wParam, LPARAM lParam) {

    
    switch (wParam) {
    case VK_LEFT:
        if (!blocked) {
            left_move = true;
            right_move = false;
            jump = false;
        }
        right_side_move = false;
        left_side_move = true;
        break;
    case VK_RIGHT:
        if (!blocked) {
            left_move = false;
            right_move = true;
            jump = false;
        }
        right_side_move = true;
        left_side_move = false;
        break;
    case VK_SPACE:
        if (!blocked) {
            jump = true;
        }
        break;
    case VK_UP:    
        if (!blocked) {
            if (!(HIWORD(lParam) & KF_REPEAT)) //Убрать повторы сообщений
                attacked = true;
        }
        break;
    case VK_ESCAPE:
        if (!blocked) {
            if (!(HIWORD(lParam) & KF_REPEAT)) //Убрать повторы сообщений
                escaped = true;
        }
        break;
    case 0x51: //q
        if (!blocked) {
            q_pressed = true;
        }
        break;
    case 0x49:
        if (!blocked) {
            i_pressed = !i_pressed;
        }
        break;
    case 0x57:
        if (!blocked) {
            w_pressed = !w_pressed;
        }
        break;
    }
}

void input_control_t::Mouse(LPARAM lParam) {
    if (!mouse_reset) {
        if (!interfaces.in_game || interfaces.death_screen) {
            mouse_pos_x[MOUSE_IN_INTERFACE] = LOWORD(lParam);
            mouse_pox_y[MOUSE_IN_INTERFACE] = HIWORD(lParam);
        }
        else if (interfaces.in_game && !interfaces.death_screen) {
            game_clicked = true;
            mouse_pos_x[MOUSE_IN_GAME] = LOWORD(lParam);
            mouse_pox_y[MOUSE_IN_GAME] = HIWORD(lParam);

            input_system.mouse_pos_x[MOUSE_INVENTORY_L] = LOWORD(lParam);
            input_system.mouse_pox_y[MOUSE_INVENTORY_L] = HIWORD(lParam);
        }

        input_system.mouse_pos_x[MOUSE_ALWAYS] = LOWORD(lParam);
        input_system.mouse_pox_y[MOUSE_ALWAYS] = HIWORD(lParam);
    }
}

void input_control_t::MouseR(LPARAM lParam) {
    input_system.mouse_pos_x[MOUSE_INVENTORY] = LOWORD(lParam);
    input_system.mouse_pox_y[MOUSE_INVENTORY] = HIWORD(lParam);
}

