#include "main.h"
#include "render_pixel.h"
#include "animation.h"
#include "input_controls.h"
#include "hitboxes.h"
#include "interface.h"
#include "world.h"
#include "config_game.h"
#include "eventlogs.h"
#include "inventory.h"
#include "seller_menu.h"
#include "training_messages.h"

event_logs eventlog;
pre_render render;
animation animationfix;
input_control_t input_system;
hitboxes_t hitboxes;
interface_t interfaces;
inventory_c inventory;
seller_c seller;
training_message_c training_message;

bool post_update = false;
void event_logs::CreateLog(const wchar_t* text, int idx) {
    eventlog.messages.push_back(CMessage(text, (float)(clock() / (float)1000.f)));
}

void animation::MoveAnims() {
    static int timer = 0;

    if (start_point) {
        timer++;
        if (timer > 5 && timer <= 10)
            animationfix.active_index = 1;
        else if (timer > 10 && timer <= 15) {
            animationfix.active_index = 2;
            timer = 0;
        }
    }
    else {
        timer++;

        if (timer > 5 && timer <= 10)
            animationfix.active_index = 1;
        else if (timer > 10 && timer <= 15) {
            animationfix.active_index = 0;
            timer = 0;
        }
    }
}

void animation::OnUpdate() {
    static int delay_attack = 0;
    if (input_system.right_move) {
        if (active_index == 0) {
            start_point = true;
            end_point = false;
        }

        if (active_index >= 2) {
            start_point = false;
            end_point = true;
        }

        MoveAnims();
    }
    else if (input_system.left_move) {
        if (active_index == 0) {
            start_point = true;
            end_point = false;
        }

        if (active_index >= 2) {
            start_point = false;
            end_point = true;
        }

        MoveAnims();
    }
    else if (input_system.attacked) {
         start_attack = true;
    }
    else {
        reset();
    }

    static int timer = 0;
    if (animationfix.start_attack) {
        timer++;

        if (timer > 10 && timer <= 20) {
            animationfix.active_index_at = 2;
        }
        else if (timer > 20) {
            animationfix.start_attack = false;
        }
        else {
            animationfix.active_index_at = 1;
        }
  
    }
    else {
        animationfix.active_index_at = 0;
        timer = 0;
    }
}



void pre_render::Platform(HDC hdc) {
    HPEN hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[FIRST_PLATFORM]);

    SelectObject(hdc, hpen);

   // Rectangle(hdc, hitboxes.platform_box[SECOND_WORLD][FIRST_PLATFORM].left, hitboxes.platform_box[SECOND_WORLD][FIRST_PLATFORM].top, hitboxes.platform_box[SECOND_WORLD][FIRST_PLATFORM].right, hitboxes.platform_box[SECOND_WORLD][FIRST_PLATFORM].bottom);


    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].left, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].top, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].right, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].bottom);
   
    DeleteObject(hpen);


   // render.GrassLeftCorner(hdc, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].left / PIXEL, hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].top / PIXEL, 0);

  //  int size_platform = hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].right - hitboxes.platform_box[MAIN_WORLD][FIRST_PLATFORM].left;

  

}

void pre_render::Platform1(HDC hdc) {

    HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));


    hpen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

    SelectObject(hdc, hpen);

 

   
    Rectangle(hdc, hitboxes.ladder_box[FIRST_LADDER].left, hitboxes.ladder_box[FIRST_LADDER].top, hitboxes.ladder_box[FIRST_LADDER].right, hitboxes.ladder_box[FIRST_LADDER].bottom);
    Rectangle(hdc, hitboxes.ladder_box[SECOND_LADDER].left, hitboxes.ladder_box[SECOND_LADDER].top, hitboxes.ladder_box[SECOND_LADDER].right, hitboxes.ladder_box[SECOND_LADDER].bottom);

    DeleteObject(hpen);

    hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[SECOND_PLATFORM]);

    SelectObject(hdc, hpen);

    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][SECOND_PLATFORM].left, hitboxes.platform_box[MAIN_WORLD][SECOND_PLATFORM].top, hitboxes.platform_box[MAIN_WORLD][SECOND_PLATFORM].right, hitboxes.platform_box[MAIN_WORLD][SECOND_PLATFORM].bottom);

    DeleteObject(hpen);




    hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[THIRD_PLATFORM]);

    SelectObject(hdc, hpen);

    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][THIRD_PLATFORM].left, hitboxes.platform_box[MAIN_WORLD][THIRD_PLATFORM].top, hitboxes.platform_box[MAIN_WORLD][THIRD_PLATFORM].right, hitboxes.platform_box[MAIN_WORLD][THIRD_PLATFORM].bottom);

    DeleteObject(hpen);

    hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[FOUR_PLATORM]);

    SelectObject(hdc, hpen);

    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][FOUR_PLATORM].left, hitboxes.platform_box[MAIN_WORLD][FOUR_PLATORM].top, hitboxes.platform_box[MAIN_WORLD][FOUR_PLATORM].right, hitboxes.platform_box[MAIN_WORLD][FOUR_PLATORM].bottom);

    DeleteObject(hpen);

    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][FIVE_PLATFORM].left, hitboxes.platform_box[MAIN_WORLD][FIVE_PLATFORM].top, hitboxes.platform_box[MAIN_WORLD][FIVE_PLATFORM].right, hitboxes.platform_box[MAIN_WORLD][FIVE_PLATFORM].bottom);
   
    Rectangle(hdc, hitboxes.platform_box[MAIN_WORLD][POST_FIVE_PLATORM].left, hitboxes.platform_box[MAIN_WORLD][POST_FIVE_PLATORM].top, hitboxes.platform_box[MAIN_WORLD][POST_FIVE_PLATORM].right, hitboxes.platform_box[MAIN_WORLD][POST_FIVE_PLATORM].bottom);
}

void pre_render::DrawHealthBar(HDC hdc, int player_index, int enemy_idx) {

    HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hpen);

    if (player_index == LOCAL_PLAYER) {
        HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));

        SelectObject(hdc, brush);

        Rectangle(hdc, hitboxes.local_box.left, hitboxes.local_box.top - 20, hitboxes.local_box.left + 120, hitboxes.local_box.top - 10);

        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(0, 255, 0));

        SelectObject(hdc, brush);

        Rectangle(hdc, hitboxes.local_box.left, hitboxes.local_box.top - 20, hitboxes.local_box.left + 120 * hitboxes.local_health, hitboxes.local_box.top - 10);
   
        DeleteObject(brush);
    }
    else if (player_index == ENEMY_PLAYER) {
        if (!hitboxes.defeated_enemy[enemy_idx]) {
            HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));

            SelectObject(hdc, brush);

            if (hitboxes.enemy_engage_procents[enemy_idx] > 0) {
               Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left + 50, hitboxes.enemy_box[enemy_idx].top - 35,
                   hitboxes.enemy_box[enemy_idx].right - 50, hitboxes.enemy_box[enemy_idx].top - 25);
            }

            Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left + 50, hitboxes.enemy_box[enemy_idx].top - 20, 
                hitboxes.enemy_box[enemy_idx].left + 50 + 100, hitboxes.enemy_box[enemy_idx].top - 10);

            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 20, 20));

            SelectObject(hdc, brush);
    
            Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left + 50, hitboxes.enemy_box[enemy_idx].top - 20, 
                hitboxes.enemy_box[enemy_idx].left + 50 + (100 * hitboxes.enemy_health[enemy_idx]),
                hitboxes.enemy_box[enemy_idx].top - 10);
        
            DeleteObject(brush);

            if (hitboxes.enemy_engage_procents[enemy_idx] > 0) {
                brush = CreateSolidBrush(RGB(243, 98, 35));

                SelectObject(hdc, brush);

                Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left + 50, hitboxes.enemy_box[enemy_idx].top - 35,
                    hitboxes.enemy_box[enemy_idx].left + 50 + (100 * hitboxes.enemy_engage_procents[enemy_idx] / 100),
                    hitboxes.enemy_box[enemy_idx].top - 25);
         
                DeleteObject(brush);
            }

        }
    }

 
    DeleteObject(hpen);
}
 

void pre_render::DrawBackground(HDC hdc, RECT rect) {
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);

    FillRect(hdc, &rect, hBrush);

    DeleteObject(hBrush);
}

void pre_render::Draw(HDC hdc) {

    HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

 //   for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
  //      hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
  //      SelectObject(hdc, hpen);
     //   Rectangle(hdc, hitboxes.enemy_box[b].left, hitboxes.enemy_box[b].top, hitboxes.enemy_box[b].right, hitboxes.enemy_box[b].bottom);
    //    DeleteObject(hpen);
  //  }



    for (int b = FIRST_NPC; b < MAXIMUM_NPC; b++) {
        hpen = CreatePen(PS_SOLID, 1, RGB(10, 10, 255));
        SelectObject(hdc, hpen);
        Rectangle(hdc, hitboxes.npc_box[b].left, hitboxes.npc_box[b].top, hitboxes.npc_box[b].right, hitboxes.npc_box[b].bottom);

        DeleteObject(hpen);
    }

    Platform(hdc);
    Platform1(hdc);

    DrawHealthBar(hdc, LOCAL_PLAYER);

    for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
        DrawHealthBar(hdc, ENEMY_PLAYER, b);

    }

    int sidemove = input_system.left_side_move ? hitboxes.local_box.left / PIXEL + 40 : hitboxes.local_box.left / PIXEL;

    if (!animationfix.start_attack)
        RenderMainCharacter(hdc, sidemove, hitboxes.local_box.top / PIXEL + 9, animationfix.active_index, input_system.left_side_move ? hitboxes.local_box.right : 0);
    else
        RenderMainCharacterAttack(hdc, sidemove, hitboxes.local_box.top / PIXEL - 6, animationfix.active_index_at, input_system.left_side_move ? hitboxes.local_box.right : 0);


    
    for (int b = FIRST_ENEMY; b < THIRD_ENEMY; b++) {

        if (!hitboxes.enemy_attacked[b])
            Slime(hdc, hitboxes.enemy_box[b].left / PIXELB, hitboxes.enemy_box[b].top / PIXELB);
        else
            SlimeAttack(hdc, hitboxes.enemy_box[b].left / PIXELB, hitboxes.enemy_box[b].top / PIXELB);

    }


    HealFlask(hdc, hitboxes.heal_flask[FIRST_FLASK].left / PIXELB, hitboxes.heal_flask[FIRST_FLASK].top / PIXELB);
}

void pre_render::Init(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

 

    int dc_width, dc_height;
    HDC mem_dc;
    HBITMAP mem_bitmap;
    RECT rect;

    GetClientRect(hWnd, &rect);

    dc_width = rect.right - rect.left;
    dc_height = rect.bottom - rect.top;

    mem_dc = CreateCompatibleDC(hdc);
    mem_bitmap = CreateCompatibleBitmap(hdc, dc_width, dc_height);
    SelectObject(mem_dc, mem_bitmap);

    DrawBackground(mem_dc, rect);

    if (interfaces.in_game && !interfaces.death_screen) {

        if (input_system.escaped) {
            interfaces.InGameInterface(mem_dc, hWnd);
        }
        else {
         

            Draw(mem_dc);

            if (!hitboxes.in_seller_interface) {
                inventory.Init(hWnd, mem_dc);
            }
    
            seller.Init(hWnd, mem_dc);

            if (hitboxes.active_level == 0)
                training_message.Init(hWnd, mem_dc);
        }
       
    }
    else {
        if (interfaces.test_preview) {
            PreviewModels(mem_dc);
        }
        else
            interfaces.Init(mem_dc, hWnd);
    }

    eventlog.Draw(mem_dc);



    BitBlt(hdc, 0, 0, dc_width, dc_height, mem_dc, 0, 0, SRCCOPY);

    DeleteObject(mem_bitmap);
    DeleteObject(mem_dc);

    EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static bool out_hitboxed = false;
    static bool out_hitboxed1 = false;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, 0);
        break;
    case WM_TIMER:
        if (!interfaces.test_preview) {

            InvalidateRect(hWnd, NULL, FALSE);

            hitboxes.OnUpdate();

            config.OnUpdate();

            if (interfaces.in_game) {
                hitboxes.Init(hWnd);
                
                inventory.OnUpdate();
                seller.OnUpdate();
            }

            animationfix.OnUpdate();
          
         

            input_system.reset();

            if (input_system.mouse_reset) {
         
                input_system.mouse_pos_x[MOUSE_IN_INTERFACE] = 0;
                input_system.mouse_pox_y[MOUSE_IN_INTERFACE] = 0;

                input_system.mouse_pos_x[MOUSE_IN_GAME] = 0;
                input_system.mouse_pox_y[MOUSE_IN_GAME] = 0;

                input_system.mouse_pos_x[MOUSE_ALWAYS] = 0;
                input_system.mouse_pox_y[MOUSE_ALWAYS] = 0;

                input_system.mouse_pos_x[MOUSE_INVENTORY] = 0;
                input_system.mouse_pox_y[MOUSE_INVENTORY] = 0;

                input_system.mouse_pos_x[MOUSE_INVENTORY_L] = 0;
                input_system.mouse_pox_y[MOUSE_INVENTORY_L] = 0;

                input_system.mouse_reset = false;
            }

            InvalidateRect(hWnd, NULL, FALSE);
        }
        else {
            if (!interfaces.updated_preview)
                RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);

            interfaces.updated_preview = true;
        }
        break;
    case WM_KEYDOWN:
        input_system.Init(wParam, lParam);
        break;
    case WM_LBUTTONDOWN:
        input_system.Mouse(lParam);
        break;
    case WM_RBUTTONDOWN:
        input_system.MouseR(lParam);
        break;
    case WM_PAINT:
        render.Init(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
 
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }


 
    return 0;
}



void pre_render::RenderPixel(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color, bool inverted) { //hdc, x, y, ширина, высота
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(color);
    SelectObject(hdc, hBrush);

    if (inverted) {
        RECT rect = { x + PIXEL - space_x, y - PIXEL + space_y, x - space_x, y + space_y };
        // RECT rect = { x + PIXEL - space_x, y - PIXEL + space_y, x - space_x, y + space_y };
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }
    else {
        RECT rect = { x - PIXEL + space_x, y - PIXEL + space_y, x + space_x, y + space_y };
        // RECT rect = { x + PIXEL - space_x, y - PIXEL + space_y, x - space_x, y + space_y };
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }

    DeleteObject(hBrush);
   // Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom); //debug pixels
}

void pre_render::RenderPixelLine(HDC hdc, pixels_other_t pix_info, int index, COLORREF color) {

    int index_;

    if (index != 0)
        index_ = PIXEL * index;
    else
        index_ = 0;

    


    if (pix_info.pix_start_pos != 0) {
        for (int i = 1; i <= pix_info.width_pix; i++) {
            RenderPixel(hdc, pix_info.pix_start_pos + ((PIXEL)*i) * (-1), PIXEL, pix_info.pix_start_pos + (PIXEL * pix_info.pix_space) * (-1), index_, color, false);
        }
    }
    else {
        for (int i = 1; i <= pix_info.width_pix; i++)
             RenderPixel(hdc,  (PIXEL)*i, PIXEL, (PIXEL * pix_info.pix_space), index_, color, false);
    }
}

void pre_render::RenderPixelB(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color) { //hdc, x, y, ширина, высота
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(color);
    SelectObject(hdc, hBrush);

    RECT rect = { x - PIXELB + space_x, y - PIXELB + space_y, x + space_x, y + space_y };
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);
}

void pre_render::RenderPixelLineB(HDC hdc, pixels_other_t pix_info, int index, COLORREF color) {

    int index_;

    if (index != 0)
        index_ = PIXELB * index;
    else
        index_ = 0;

    if (pix_info.pix_start_pos != 0) {
        for (int i = 1; i <= pix_info.width_pix; i++) {
            RenderPixelB(hdc, pix_info.pix_start_pos + ((PIXELB)*i) * (-1), PIXELB, pix_info.pix_start_pos + (PIXELB * pix_info.pix_space) * (-1), index_, color);
        }
    }
    else {
        for (int i = 1; i <= pix_info.width_pix; i++)
            RenderPixelB(hdc, (PIXELB)*i, PIXELB, (PIXELB * pix_info.pix_space), index_, color);
    }
}

void pre_render::PreviewModels(HDC hdc) {
  //  render.EyeStorm(hdc, 0, 0);
  //  render.GrassLeftCorner(hdc, 0, 0, 0);
 //   render.GrassMiddle(hdc, 16,0);
  //  render.GrassLeftCorner(hdc, 32, 0, 40 * PIXEL);

    render.RenderMainCharacter(hdc, 0, 0, 0);
    render.RenderMainCharacter(hdc, 50, 0, 1);
    render.RenderMainCharacter(hdc, 100, 0, 2);

    render.AttackAnims(hdc, 150, 0);
    render.AttackAnimsT(hdc, 200, 0);
    render.HealFlask(hdc, 10, 80);

    render.Slime(hdc, 30, 50);
    render.SlimeAttack(hdc, 70, 50);
}

void pre_render::RenderMainCharacterAttack(HDC hdc, int x, int y, int index, int sp) {
    if (index == 1) {
        AttackAnims(hdc, x, y, sp);
    }
    else if (index == 2) {
        AttackAnimsT(hdc, x, y, sp);
    }
}

void pre_render::EyeStormBody(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(1, 6), 17, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 13), 17, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(2, 6), 18, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(2, 12), 18, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 19, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(4, 14), 19, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(9, 6), 20, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 18), 20, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(11, 5), 21, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 19), 21, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(12, 4), 22, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 19), 22, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(2, 2), 23, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(13, 4), 23, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 18), 23, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(1, 1), 24, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(13, 4), 24, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 24, RGB(12, 13, 20));//рука

    RenderPixelLineB(hdc, pixels_other_t(1, 0), 25, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(14, 3), 25, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(1, 0), 26, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(14, 3), 26, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(1, 0), 27, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(15, 3), 27, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(1, 1), 28, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(15, 3), 28, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(1, 2), 29, RGB(12, 13, 20));//рука
    RenderPixelLineB(hdc, pixels_other_t(15, 3), 29, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(15, 3), 30, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(14, 3), 31, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(13, 3), 32, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(8, 3), 33, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 11), 33, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 33, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(7, 3), 34, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(3, 10), 34, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 34, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(4, 5), 35, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(5, 9), 35, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(2, 14), 35, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(4, 5), 36, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(5, 9), 36, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(1, 15), 36, RGB(24, 28, 40));

    RenderPixelLineB(hdc, pixels_other_t(2, 6), 37, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 8), 37, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(1, 12), 37, RGB(12, 13, 20)); //штаны

    RenderPixelLineB(hdc, pixels_other_t(1, 6), 38, RGB(24, 28, 40));
    RenderPixelLineB(hdc, pixels_other_t(1, 8), 38, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(1, 12), 38, RGB(12, 13, 20)); //штаны

    RenderPixelLineB(hdc, pixels_other_t(1, 8), 39, RGB(12, 13, 20)); //штаны
    RenderPixelLineB(hdc, pixels_other_t(1, 12), 39, RGB(12, 13, 20)); //штаны
}

void pre_render::EyeStormHead(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(7, 8), 5, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 6, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 15), 6, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 7, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 8, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(6, 4), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 9, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 9, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 10, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 10, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 11, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 11, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 11, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(6, 4), 12, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 12, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 12, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 13, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 14, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 15, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 16, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_1(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 2, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 11), 3, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 3, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 4, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 4, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 5, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 5, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 6, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 18), 6, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 5), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 7, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 12), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 18), 7, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 8, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 8, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 9, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 9, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(6, 4), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 10, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 10, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(12, 4), 11, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 12, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 13, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 14, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 15, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_2(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(2, 12), 3, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 16), 4, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 5, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 5, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 6, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 6, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 19), 7, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 5), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 8, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 12), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 18), 8, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 9, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 9, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 10, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 10, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(6, 4), 11, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 11, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 11, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(12, 4), 12, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 13, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 14, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 15, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 16, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_3(HDC hdc, int x, int y) {

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 5, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 6, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 5), 7, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 5), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 10), 8, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 12), 8, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 9, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 9, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 9), 10, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(3, 13), 10, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(6, 4), 11, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 8), 11, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(4, 12), 11, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 4), 12, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 7), 12, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(5, 11), 12, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 4), 13, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 6), 13, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(6, 10), 13, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(2, 5), 14, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 7), 14, RGB(112, 211, 139));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 14, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 6), 15, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 8), 16, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 17), 16, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 16), 18, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_Attack1(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(4, 11), 5, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 11), 6, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 10), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 10), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 10), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 10), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 10), 11, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 12, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 13, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 14, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 15, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(7, 8), 16, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 7), 17, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 17, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 7), 18, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 9), 18, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 7), 19, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 10), 19, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 8), 20, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 10), 20, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 9), 21, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 10), 21, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 10), 22, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 10), 23, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 10), 24, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(2, 11), 25, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(2, 11), 26, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 9), 27, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(1, 9), 28, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_Attack2(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(8, 8), 5, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 7), 6, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(12, 6), 7, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(12, 6), 8, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(14, 4), 9, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(1, 3), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 7), 10, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 7), 11, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 10), 12, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 9), 13, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 7), 14, RGB(203, 255, 216));
}

void pre_render::EyeStormHead_Attack3(HDC hdc, int x, int y, int sp) {
    RenderPixelLineB(hdc, pixels_other_t(1, 18 + x, sp), 5 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 17 + x, sp), 6 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 16 + x, sp), 7 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 16 + x, sp), 8 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 16 + x, sp), 9 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 15 + x, sp), 10 + y, RGB(203, 255, 216));


    RenderPixelLineB(hdc, pixels_other_t(8, 10 + x, sp), 11 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 8 + x, sp), 12 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(11, 7 + x, sp), 13 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 7 + x, sp), 14 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(12, 6 + x, sp), 15 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(12, 6 + x, sp), 16 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(12, 6 + x, sp), 17 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(12, 6 + x, sp), 18 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(10, 7 + x, sp), 19 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(10, 7 + x, sp), 20 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(8, 8 + x, sp), 21 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(4, 10 + x, sp), 22 + y, RGB(203, 255, 216));

    //правая часть
    RenderPixelLineB(hdc, pixels_other_t(3, 19 + x, sp), 10 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 19 + x, sp), 11 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 20 + x, sp), 12 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 20 + x, sp), 13 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 21 + x, sp), 14 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 21 + x, sp), 15 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 22 + x, sp), 16 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 23 + x, sp), 17 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 23 + x, sp), 18 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 24 + x, sp), 19 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 25 + x, sp), 20 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 25 + x, sp), 21 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 25 + x, sp), 22 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 26 + x, sp), 23 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 27 + x, sp), 24 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 27 + x, sp), 25 + y, RGB(203, 255, 216));

    //
    RenderPixelLineB(hdc, pixels_other_t(6, 28 + x, sp), 26 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 28 + x, sp), 27 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 28 + x, sp), 28 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 29 + x, sp), 29 + y, RGB(203, 255, 216));
    //
    //еще правее
    RenderPixelLineB(hdc, pixels_other_t(3, 32 + x, sp), 25 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 32 + x, sp), 24 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 33 + x, sp), 23 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 34 + x, sp), 22 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 34 + x, sp), 21 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 35 + x, sp), 20 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 35 + x, sp), 19 + y, RGB(203, 255, 216));

    //
    RenderPixelLineB(hdc, pixels_other_t(6, 36 + x, sp), 18 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(5, 37 + x, sp), 17 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 38 + x, sp), 16 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 38 + x, sp), 15 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 38 + x, sp), 14 + y, RGB(203, 255, 216));
    //
    //еще правее 
    RenderPixelLineB(hdc, pixels_other_t(3, 39 + x, sp), 19 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 39 + x, sp), 20 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 40 + x, sp), 21 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 40 + x, sp), 22 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 40 + x, sp), 23 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 40 + x, sp), 24 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 40 + x, sp), 25 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 41 + x, sp), 26 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 41 + x, sp), 27 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 41 + x, sp), 28 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 41 + x, sp), 29 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 41 + x, sp), 30 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 31 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 32 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 33 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 34 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 35 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 36 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 37 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 38 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 39 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 40 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 41 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 42 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 43 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 44 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 45 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 42 + x, sp), 46 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 43 + x, sp), 47 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 43 + x, sp), 48 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 43 + x, sp), 49 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 43 + x, sp), 50 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 43 + x, sp), 51 + y, RGB(203, 255, 216));
    //
    RenderPixelLineB(hdc, pixels_other_t(6, 43 + x, sp), 52 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 44 + x, sp), 53 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(2, 45 + x, sp), 54 + y, RGB(203, 255, 216));
    //

    RenderPixelLineB(hdc, pixels_other_t(3, 47 + x, sp), 51 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 48 + x, sp), 50 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 49 + x, sp), 49 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 49 + x, sp), 49 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 50 + x, sp), 48 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 51 + x, sp), 47 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 51 + x, sp), 46 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 51 + x, sp), 45 + y, RGB(203, 255, 216));

    //
    RenderPixelLineB(hdc, pixels_other_t(6, 52 + x, sp), 44 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(6, 52 + x, sp), 43 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(5, 52 + x, sp), 42 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(4, 53 + x, sp), 41 + y, RGB(203, 255, 216));
    //

    RenderPixelLineB(hdc, pixels_other_t(3, 55 + x, sp), 45 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 55 + x, sp), 46 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 55 + x, sp), 47 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 56 + x, sp), 48 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 56 + x, sp), 49 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 57 + x, sp), 50 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 57 + x, sp), 51 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 57 + x, sp), 52 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 57 + x, sp), 53 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 58 + x, sp), 54 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 58 + x, sp), 55 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 58 + x, sp), 56 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 59 + x, sp), 57 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 59 + x, sp), 58 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 59 + x, sp), 59 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 59 + x, sp), 60 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 59 + x, sp), 61 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 60 + x, sp), 62 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 60 + x, sp), 63 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 60 + x, sp), 64 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 60 + x, sp), 65 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 61 + x, sp), 66 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 61 + x, sp), 67 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 62 + x, sp), 68 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 62 + x, sp), 69 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 63 + x, sp), 70 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 63 + x, sp), 71 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 64 + x, sp), 72 + y, RGB(203, 255, 216));

    RenderPixelLineB(hdc, pixels_other_t(3, 65 + x, sp), 73 + y, RGB(203, 255, 216));
    RenderPixelLineB(hdc, pixels_other_t(3, 65 + x, sp), 74 + y, RGB(203, 255, 216));
}

void pre_render::EyeStorm(HDC hdc, int x, int y) {
    //глаз
  //  EyeStormHead(hdc, x, y);
    EyeStormHead_Attack3(hdc, 0, 0, 200);

    //тело
    //EyeStormBody(hdc, x, y);
}


void pre_render::Slime(HDC hdc, int x, int y) {

    //slime

    RenderPixelLineB(hdc, pixels_other_t(5, 17 + x), 10 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(7, 15 + x), 11 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 22 + x), 11 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(4, 14 + x), 12 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 18 + x), 12 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(3, 20 + x), 12 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 23 + x), 12 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(2, 14 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 16 + x), 13 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(3, 17 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 20 + x), 13 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(2, 22 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 13 + y, RGB(113, 128, 108));


    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 14 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 14 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 14 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 14 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 15 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 15 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 15 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 15 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 16 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 16 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 16 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 16 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 17 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 17 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 17 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 17 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 18 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 18 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 18 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 18 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(8, 14 + x), 19 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 19 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 19 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 19 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(8, 14 + x), 20 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 20 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 20 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 20 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(7, 15 + x), 21 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 21 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 21 + y, RGB(113, 128, 108));
}


void pre_render::SlimeAttack(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(1, 9 + x), 1 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 28 + x), 1 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(1, 10 + x), 2 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(2, 27 + x), 2 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(2, 26 + x), 3 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(2, 10 + x), 3 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(3, 25 + x), 4 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(2, 11 + x), 4 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(2, 11 + x), 5 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 24 + x), 5 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(2, 12 + x), 6 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 23 + x), 6 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(2, 38 + x), 6 + y, RGB(69, 69, 81));


    RenderPixelLineB(hdc, pixels_other_t(3, 12 + x), 7 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 22 + x), 7 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(3, 36 + x), 7 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(3, 13 + x), 8 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(5, 21 + x), 8 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 34 + x), 8 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(12, 13 + x), 9 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 32 + x), 9 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(3, 14 + x), 10 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(3, 22 + x), 10 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(5, 30 + x), 10 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(1, 14 + x), 11 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 11 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(6, 28 + x), 11 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(1, 13 + x), 12 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(7, 25 + x), 12 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(3, 0 + x), 13 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 13 + x), 13 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(6, 25 + x), 13 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(7, 2 + x), 14 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 14 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 26 + x), 14 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(8, 5 + x), 15 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(2, 26 + x), 15 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(6, 7 + x), 16 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 26 + x), 16 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(3, 10 + x), 17 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 26 + x), 17 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 18 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(4, 26 + x), 18 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(4, 10 + x), 19 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(12, 25 + x), 19 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(8, 6 + x), 20 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(16, 25 + x), 20 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(12, 3 + x), 21 + y, RGB(69, 69, 81));
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 21 + y, RGB(69, 69, 81));

    RenderPixelLineB(hdc, pixels_other_t(9, 15 + x), 22 + y, RGB(69, 69, 81));

    //slime

    RenderPixelLineB(hdc, pixels_other_t(5, 17 + x), 10 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(7, 15 + x), 11 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 22 + x), 11 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(4, 14 + x), 12 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 18 + x), 12 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(3, 20 + x), 12 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 23 + x), 12 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(2, 14 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 16 + x), 13 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(3, 17 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 20 + x), 13 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(2, 22 + x), 13 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 13 + y, RGB(113, 128, 108));


    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 14 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 14 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 14 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 14 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 15 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 15 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 15 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 15 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 16 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 16 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 16 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 16 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 17 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 17 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 17 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 17 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(9, 13 + x), 18 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 18 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 18 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(2, 24 + x), 18 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(8, 14 + x), 19 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 19 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 19 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 19 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(8, 14 + x), 20 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 20 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 20 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 24 + x), 20 + y, RGB(113, 128, 108));

    RenderPixelLineB(hdc, pixels_other_t(7, 15 + x), 21 + y, RGB(135, 155, 128)); //
    RenderPixelLineB(hdc, pixels_other_t(1, 22 + x), 21 + y, RGB(113, 128, 108));
    RenderPixelLineB(hdc, pixels_other_t(1, 23 + x), 21 + y, RGB(113, 128, 108));
}

void pre_render::HealFlask(HDC hdc, int x, int y) {
    RenderPixelLineB(hdc, pixels_other_t(4, 5 + x), 0 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 5 + x), 1 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(2, 6 + x), 1 + y, RGB(219, 164, 99));
    RenderPixelLineB(hdc, pixels_other_t(1, 8 + x), 1 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(8, 3 + x), 2 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 4 + x), 3 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(2, 6 + x), 3 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 9 + x), 3 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 4 + x), 4 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(2, 6 + x), 4 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 9 + x), 4 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 4 + x), 5 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 9 + x), 5 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 3 + x), 6 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 10 + x), 6 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 2 + x), 7 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 11 + x), 7 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 1 + x), 8 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 8 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 3 + x), 8 + y, RGB(93, 175, 141));
    RenderPixelLineB(hdc, pixels_other_t(6, 4 + x), 8 + y, RGB(146, 220, 186));
    RenderPixelLineB(hdc, pixels_other_t(1, 10 + x), 8 + y, RGB(93, 175, 141));


    RenderPixelLineB(hdc, pixels_other_t(1, 1 + x), 9 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 9 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(1, 3 + x), 9 + y, RGB(93, 175, 141));
    RenderPixelLineB(hdc, pixels_other_t(6, 4 + x), 9 + y, RGB(146, 220, 186));
    RenderPixelLineB(hdc, pixels_other_t(1, 10 + x), 9 + y, RGB(93, 175, 141));

    RenderPixelLineB(hdc, pixels_other_t(1, 1 + x), 10 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 10 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(2, 3 + x), 10 + y, RGB(93, 175, 141));
    RenderPixelLineB(hdc, pixels_other_t(4, 5 + x), 10 + y, RGB(146, 220, 186));
    RenderPixelLineB(hdc, pixels_other_t(2, 9 + x), 10 + y, RGB(93, 175, 141));


    RenderPixelLineB(hdc, pixels_other_t(1, 1 + x), 11 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 12 + x), 11 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(8, 3 + x), 11 + y, RGB(93, 175, 141));

    RenderPixelLineB(hdc, pixels_other_t(1, 2 + x), 12 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 11 + x), 12 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(6, 4 + x), 12 + y, RGB(93, 175, 141));

    RenderPixelLineB(hdc, pixels_other_t(1, 3 + x), 13 + y, RGB(0, 0, 0));
    RenderPixelLineB(hdc, pixels_other_t(1, 10 + x), 13 + y, RGB(0, 0, 0));

    RenderPixelLineB(hdc, pixels_other_t(6, 4 + x), 14 + y, RGB(0, 0, 0));
}

void pre_render::AttackAnims(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 0 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x, sp), 1 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x, sp), 2 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(3, 8 + x, sp), 3 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x, sp), 4 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 13 + x, sp), 5 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 15 + x, sp), 6 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(3, 17 + x, sp), 7 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 8 + y, RGB(144, 144, 144));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 8 + y, RGB(77, 47, 52));

    RenderPixelLine(hdc, pixels_other_t(2, 23 + x, sp), 8 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(4, 22 + x, sp), 9 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 10 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(5, 24 + x, sp), 11 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(2, 24 + x, sp), 12 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 27 + x, sp), 12 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 12 + y, RGB(77, 47, 52));

    RenderPixelLine(hdc, pixels_other_t(5, 23 + x, sp), 13 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 28 + x, sp), 13 + y, RGB(153, 144, 137)); //чуть темнее

    RenderPixelLine(hdc, pixels_other_t(4, 19 + x, sp), 14 + y, RGB(155, 148, 130)); //кусок шляпы
    RenderPixelLine(hdc, pixels_other_t(5, 23 + x, sp), 14 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 28 + x, sp), 14 + y, RGB(153, 144, 137)); //чуть темнее

    //шляпа 139 133 117
    RenderPixelLine(hdc, pixels_other_t(5, 18 + x, sp), 15 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 15 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 15 + y, RGB(153, 144, 137));

    RenderPixelLine(hdc, pixels_other_t(6, 17 + x, sp), 16 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 16 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 16 + y, RGB(155, 148, 130));

    RenderPixelLine(hdc, pixels_other_t(7, 16 + x, sp), 17 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 17 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 29 + x, sp), 17 + y, RGB(155, 148, 130));

    RenderPixelLine(hdc, pixels_other_t(7, 16 + x, sp), 18 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 18 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(4, 29 + x, sp), 18 + y, RGB(155, 148, 130));

    RenderPixelLine(hdc, pixels_other_t(9, 15 + x, sp), 19 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(5, 24 + x, sp), 19 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(4, 29 + x, sp), 19 + y, RGB(155, 148, 130));

    RenderPixelLine(hdc, pixels_other_t(9, 15 + x, sp), 20 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(5, 24 + x, sp), 20 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 20 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(10, 14 + x, sp), 21 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(5, 24 + x, sp), 21 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 21 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(7, 13 + x, sp), 22 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(1, 20 + x, sp), 22 + y, RGB(37, 39, 36));//волосы
    RenderPixelLine(hdc, pixels_other_t(1, 21 + x, sp), 22 + y, RGB(202, 175, 148)); //лицо
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 22 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(6, 23 + x, sp), 22 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 29 + x, sp), 22 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(3, 13 + x, sp), 23 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(2, 18 + x, sp), 23 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 23 + y, RGB(202, 175, 148)); //лицо
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 23 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(5, 23 + x, sp), 23 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 28 + x, sp), 23 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(2, 18 + x, sp), 24 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 24 + y, RGB(202, 175, 148)); //лицо
    RenderPixelLine(hdc, pixels_other_t(6, 22 + x, sp), 24 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 28 + x, sp), 24 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(4, 17 + x, sp), 25 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(7, 21 + x, sp), 25 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 28 + x, sp), 25 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(5, 15 + x, sp), 26 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(7, 20 + x, sp), 26 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 27 + x, sp), 26 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(1, 14 + x, sp), 27 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(1, 16 + x, sp), 27 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(2, 17 + x, sp), 27 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 19 + x, sp), 27 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 27 + x, sp), 27 + y, RGB(153, 144, 137)); //кусок руки
    //пальто 80 81 65
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 28 + y, RGB(37, 39, 36)); //волосы
    RenderPixelLine(hdc, pixels_other_t(1, 17 + x, sp), 28 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 18 + x, sp), 28 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(3, 26 + x, sp), 28 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 29 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 18 + x, sp), 29 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 26 + x, sp), 29 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 30 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 18 + x, sp), 30 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 30 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 31 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(6, 18 + x, sp), 31 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 24 + x, sp), 31 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 25 + x, sp), 31 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(4, 15 + x, sp), 32 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(4, 19 + x, sp), 32 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 23 + x, sp), 32 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(1, 25 + x, sp), 32 + y, RGB(153, 144, 137)); //кусок руки

    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 33 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 34 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 35 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 36 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 37 + y, RGB(80, 81, 65));

    RenderPixelLine(hdc, pixels_other_t(11, 14 + x, sp), 38 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 14 + x, sp), 39 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 14 + x, sp), 40 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 14 + x, sp), 41 + y, RGB(80, 81, 65));

    RenderPixelLine(hdc, pixels_other_t(10, 14 + x, sp), 42 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 13 + x, sp), 43 + y, RGB(80, 81, 65));

    RenderPixelLine(hdc, pixels_other_t(13, 0 + x, sp), 44 + y, RGB(32, 32, 32));
    RenderPixelLine(hdc, pixels_other_t(11, 13 + x, sp), 44 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 24 + x, sp), 44 + y, RGB(32, 32, 32));

    RenderPixelLine(hdc, pixels_other_t(10, 13 + x, sp), 45 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 12 + x, sp), 46 + y, RGB(80, 81, 65));

    RenderPixelLine(hdc, pixels_other_t(9, 12 + x, sp), 47 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 21 + x, sp), 47 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(10, 11 + x, sp), 48 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 21 + x, sp), 48 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(10, 10 + x, sp), 49 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(4, 20 + x, sp), 49 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(10, 10 + x, sp), 50 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 20 + x, sp), 50 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(11, 8 + x, sp), 51 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 19 + x, sp), 51 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(11, 8 + x, sp), 52 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 19 + x, sp),52 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(10, 8 + x, sp), 53 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 18 + x, sp), 53 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(10, 8 + x, sp), 54 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 18 + x, sp), 54 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(9, 8 + x, sp), 55 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(10, 17 + x, sp), 55 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(6, 10 + x, sp), 56 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(1, 16 + x, sp), 56 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 56 + y, RGB(43, 50, 52));
    
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 57 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(3, 12 + x, sp), 57 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 15 + x, sp), 57 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 57 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 58 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 58 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 59 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 59 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(8, 10 + x, sp), 60 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 60 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(8, 10 + x, sp), 61 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 61 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(9, 10 + x, sp), 62 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(9, 19 + x, sp), 62 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(9, 10 + x, sp), 63 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(9, 19 + x, sp),63 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(7, 11 + x, sp), 64 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(8, 20 + x, sp), 64 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(2, 10 + x, sp), 65 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(5, 12 + x, sp), 65 + y, RGB(34, 42, 44)); //левая нога
    RenderPixelLine(hdc, pixels_other_t(7, 21 + x, sp), 65 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(4, 9 + x, sp), 66 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 66 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(4, 8 + x, sp), 67 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 67 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(4, 7 + x, sp), 68 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 68 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(3, 7 + x, sp), 69 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 69 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(4, 7 + x, sp), 70 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 70 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(4, 8 + x, sp), 71 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(3, 23 + x, sp), 71 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(3, 9 + x, sp), 72 + y, RGB(58, 55, 50)); //сапоги
    RenderPixelLine(hdc, pixels_other_t(4, 23 + x, sp), 72 + y, RGB(58, 55, 50)); //сапоги

    RenderPixelLine(hdc, pixels_other_t(4, 23 + x, sp), 73 + y, RGB(58, 55, 50)); //сапоги
} 

void pre_render::AttackAnimsT(HDC hdc, int x, int y, int sp) {

    RenderPixelLine(hdc, pixels_other_t(24, 10 + x, sp), 1 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(36, 5 + x, sp), 2 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(44, 0 + x, sp), 3 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(27, 20 + x, sp), 4 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(25, 25 + x, sp), 5 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(23, 29 + x, sp), 6 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(23, 32 + x, sp), 7 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(23, 34 + x, sp), 8 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(22, 37 + x, sp), 9 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(20, 40 + x, sp), 10 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 43 + x, sp), 11 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 45 + x, sp), 12 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 47 + x, sp), 13 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 48 + x, sp), 14 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(16, 50 + x, sp), 15 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(16, 51 + x, sp), 16 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 51 + x, sp), 17 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 52 + x, sp), 18 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 53 + x, sp), 19 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 54 + x, sp), 20 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 54 + x, sp), 21 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(17, 55 + x, sp), 22 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 55 + x, sp), 23 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 55 + x, sp), 24 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 56 + x, sp), 25 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(18, 56 + x, sp), 26 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(19, 56 + x, sp), 27 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(19, 56 + x, sp), 28 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(20, 56 + x, sp), 29 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(20, 56 + x, sp), 30 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 56 + x, sp), 31 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 56 + x, sp), 32 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 57 + x, sp), 33 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 57 + x, sp), 34 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 57 + x, sp), 35 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(21, 57 + x, sp), 36 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(22, 57 + x, sp), 37 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(22, 57 + x, sp), 38 + y, RGB(192, 192, 192));

    RenderPixelLine(hdc, pixels_other_t(20, 57 + x, sp), 39 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(2, 77 + x, sp), 39 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(18, 56 + x, sp), 40 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(3, 74 + x, sp), 40 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(16, 56 + x, sp), 41 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(2, 72 + x, sp), 41 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(13, 56 + x, sp), 42 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(3, 69 + x, sp), 42 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(11, 56 + x, sp), 43 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(2, 67 + x, sp), 43 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(8, 56 + x, sp), 44 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(3, 64 + x, sp), 44 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(5, 57 + x, sp), 45 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(2, 62 + x, sp), 45 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(3, 57 + x, sp), 46 + y, RGB(192, 192, 192));
    RenderPixelLine(hdc, pixels_other_t(3, 60 + x, sp), 46 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(3, 57 + x, sp), 47 + y, RGB(144, 144, 144)); //меч

    RenderPixelLine(hdc, pixels_other_t(1, 57 + x, sp), 48 + y, RGB(144, 144, 144)); //меч
    RenderPixelLine(hdc, pixels_other_t(2, 55 + x, sp), 48 + y, RGB(77, 47, 52)); //меч

    RenderPixelLine(hdc, pixels_other_t(3, 53 + x, sp), 49 + y, RGB(77, 47, 52)); //меч

    RenderPixelLine(hdc, pixels_other_t(3, 51 + x, sp), 50 + y, RGB(77, 47, 52)); //меч
//    RenderPixelLine(hdc, pixels_other_t(2, 50), 51, RGB(77, 47, 52)); //меч

    RenderHat(hdc, 16 + x, 15 + y, sp);
    RenderFace(hdc, 16 + x, 15 + y, sp);
    RenderArms_AT(hdc, 16 + x, 15 + y, sp);
    RenderBody(hdc, 16 + x, 15 + y, sp);
    RenderLegs(hdc, 16 + x, 15 + y, sp);
}

void pre_render::RenderHat(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(7, 20 + x, sp), 0 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(11, 19 + x, sp), 1 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(13, 18 + x, sp), 2 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(15, 17 + x, sp), 3 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(17, 17 + x, sp), 4 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(18, 16 + x, sp), 5 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(14, 16 + x, sp), 6 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(10, 15 + x, sp), 7 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(7, 14 + x, sp), 8 + y, RGB(147, 141, 124));
    RenderPixelLine(hdc, pixels_other_t(3, 14 + x, sp), 9 + y, RGB(147, 141, 124));
}

void pre_render::RenderFace(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(2, 25 + x, sp), 7 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 27 + x, sp), 7 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(1, 21 + x, sp), 8 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 8 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 8 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(1, 24 + x, sp), 8 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 25 + x, sp), 8 + y, RGB(0, 0, 0));
    RenderPixelLine(hdc, pixels_other_t(1, 26 + x, sp), 8 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(2, 19 + x, sp), 9 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(2, 21 + x, sp), 9 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 9 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(3, 24 + x, sp), 9 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(2, 19 + x, sp), 10 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(2, 21 + x, sp), 10 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 10 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(3, 24 + x, sp), 10 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(4, 18 + x, sp), 11 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(5, 22 + x, sp), 11 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 16 + x, sp), 12 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 12 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(5, 22 + x, sp), 12 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 13 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 13 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(1, 17 + x, sp), 13 + y, RGB(37, 39, 36));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 14 + y, RGB(202, 175, 148));
}

void pre_render::RenderArms(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 15 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(5, 14 + x, sp), 16 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(6, 13 + x, sp), 17 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 11 + x, sp), 18 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 10 + x, sp), 19 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 9 + x, sp), 20 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 8 + x, sp), 21 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 8 + x, sp), 22 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 8 + x, sp), 23 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 8 + x, sp), 24 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 8 + x, sp), 25 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 9 + x, sp), 26 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 9 + x, sp), 27 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 28 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 29 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 22 + x, sp), 29 + y, RGB(202, 175, 148));

    RenderPixelLine(hdc, pixels_other_t(6, 24 + x, sp), 30 + y, RGB(82, 53, 58));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 30 + y, RGB(32, 32, 32));
    RenderPixelLine(hdc, pixels_other_t(10, 0 + x, sp), 30 + y, RGB(32, 32, 32));

    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 30 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 30 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(5, 11 + x, sp), 31 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 16 + x, sp), 31 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 31 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 32 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 12 + x, sp), 32 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 33 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 34 + y, RGB(202, 175, 148));
}

void pre_render::RenderArms_AT(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 15 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(5, 14 + x, sp), 16 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(6, 13 + x, sp), 17 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 11 + x, sp), 18 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 10 + x, sp), 19 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 9 + x, sp), 20 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(9, 8 + x, sp), 21 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 8 + x, sp), 22 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(8, 8 + x, sp), 23 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 8 + x, sp), 24 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 8 + x, sp), 25 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 9 + x, sp), 26 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 9 + x, sp), 27 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 28 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 29 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(2, 22 + x, sp), 29 + y, RGB(202, 175, 148));

   // RenderPixelLine(hdc, pixels_other_t(6, 24 + x), 30 + y, RGB(82, 53, 58));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 30 + y, RGB(32, 32, 32));
    RenderPixelLine(hdc, pixels_other_t(10, 0 + x, sp), 30 + y, RGB(32, 32, 32));

    RenderPixelLine(hdc, pixels_other_t(7, 10 + x, sp), 30 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 23 + x, sp), 30 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(5, 11 + x, sp), 31 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(1, 16 + x, sp), 31 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(1, 22 + x, sp), 31 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 32 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 12 + x, sp), 32 + y, RGB(179, 172, 166));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 33 + y, RGB(202, 175, 148));
    RenderPixelLine(hdc, pixels_other_t(3, 15 + x, sp), 34 + y, RGB(202, 175, 148));
}

void pre_render::RenderBody(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(1, 19 + x, sp), 12 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 18 + x, sp), 13 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(6, 17 + x, sp), 14 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(6, 18 + x, sp), 15 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 19 + x, sp), 16 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 19 + x, sp), 17 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 19 + x, sp), 18 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 19 + x, sp), 19 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(6, 18 + x, sp), 20 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 17 + x, sp), 21 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 16 + x, sp), 22 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 16 + x, sp), 23 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 15 + x, sp), 24 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 15 + x, sp), 25 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 16 + x, sp), 26 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 16 + x, sp), 27 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(6, 17 + x, sp), 28 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 17 + x, sp), 29 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 17 + x, sp), 30 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(1, 10 + x, sp), 31 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(5, 17 + x, sp), 31 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(4, 8 + x, sp), 32 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(4, 18 + x, sp), 32 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 33 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(4, 18 + x, sp), 33 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 34 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(2, 18 + x, sp), 34 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(13, 6 + x, sp), 35 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(12, 6 + x, sp), 36 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(11, 6 + x, sp), 37 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(8, 7 + x, sp), 38 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(7, 7 + x, sp), 39 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(3, 9 + x, sp), 40 + y, RGB(80, 81, 65));
}

void pre_render::RenderLegs_2(HDC hdc, int x, int y, int sp) {
    //left - левая
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 38 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 39 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 8 + x, sp), 40 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(5, 12 + x, sp), 40 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 8 + x, sp), 41 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 42 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 43 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 44 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(12, 6 + x, sp), 45 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 6 + x, sp), 46 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 47 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(7, 7 + x, sp), 48 + y, RGB(43, 50, 52));

    //left foot - левая стопа (ботинок)
    RenderPixelLine(hdc, pixels_other_t(5, 1 + x, sp), 45 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(6, 0 + x, sp), 46 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(6, 0 + x, sp), 47 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(4, 0 + x, sp), 48 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 0 + x, sp), 49 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 0 + x, sp), 50 + y, RGB(58, 55, 50));

    //right - правая
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 34 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(4, 19 + x, sp), 35 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(6, 18 + x, sp), 36 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(8, 17 + x, sp), 37 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 16 + x, sp), 38 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 16 + x, sp), 39 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 17 + x, sp), 40 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 41 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 42 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 43 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 18 + x, sp), 44 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 19 + x, sp), 45 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 19 + x, sp), 46 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(9, 20 + x, sp), 47 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(8, 21 + x, sp), 48 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(8, 21 + x, sp), 49 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(7, 22 + x, sp), 50 + y, RGB(34, 42, 44));

    //right foot - правая стопа (ботинок)
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 51 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 52 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 53 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 26 + x, sp), 54 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 55 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 56 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 57 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(2, 26 + x, sp), 58 + y, RGB(58, 55, 50));
}

void pre_render::RenderLegs_1(HDC hdc, int x, int y, int sp) {
    //left - левая
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 40 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x, sp), 41 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(3, 11 + x, sp), 42 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(3, 11 + x, sp), 43 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(3, 11 + x, sp), 44 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(3, 11 + x, sp), 45 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(3, 11 + x, sp), 46 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x, sp), 47 + y, RGB(34, 42, 44));


    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 38 + y, RGB(80, 81, 65));


    RenderPixelLine(hdc, pixels_other_t(7, 4 + x, sp), 43 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(7, 4 + x, sp), 44 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(7, 4 + x, sp), 45 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x, sp), 46 + y, RGB(58, 55, 50));

    //right - правая
   // RenderPixelLine(hdc, pixels_other_t(2, 20), 34, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 18 + x, sp), 35 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 34 + y, RGB(80, 81, 65));
    RenderPixelLine(hdc, pixels_other_t(3, 20 + x, sp), 35 + y, RGB(80, 81, 65));

    RenderPixelLine(hdc, pixels_other_t(5, 18 + x, sp), 36 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(6, 17 + x, sp), 37 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(7, 16 + x, sp), 38 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 39 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 40 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 41 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 42 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 43 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 44 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 45 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 46 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 47 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 14 + x, sp), 48 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(8, 15 + x, sp), 49 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(7, 15 + x, sp), 50 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(5, 16 + x, sp), 51 + y, RGB(43, 50, 52));

    RenderPixelLine(hdc, pixels_other_t(3, 16 + x, sp), 52 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(2, 16 + x, sp), 53 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 16 + x, sp), 54 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(4, 16 + x, sp), 55 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(4, 16 + x, sp), 56 + y, RGB(58, 55, 50));
}

void pre_render::RenderLegs(HDC hdc, int x, int y, int sp) {
    //left - левая
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 38 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 39 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(1, 8 + x, sp), 40 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(5, 12 + x, sp), 40 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(10, 8 + x, sp), 41 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 42 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 43 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 7 + x, sp), 44 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(12, 6 + x, sp), 45 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(11, 6 + x, sp), 46 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 47 + y, RGB(34, 42, 44));
    RenderPixelLine(hdc, pixels_other_t(7, 7 + x, sp), 48 + y, RGB(34, 42, 44));

    //left foot - левая стопа (ботинок)
    RenderPixelLine(hdc, pixels_other_t(5, 1 + x, sp), 45 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(6, 0 + x, sp), 46 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(6, 0 + x, sp), 47 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(4, 0 + x, sp), 48 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 0 + x, sp), 49 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 0 + x, sp), 50 + y, RGB(58, 55, 50));

    //right - правая
    RenderPixelLine(hdc, pixels_other_t(2, 20 + x, sp), 34 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(4, 19 + x, sp), 35 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(6, 18 + x, sp), 36 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(8, 17 + x, sp), 37 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 16 + x, sp), 38 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 16 + x, sp), 39 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 17 + x, sp), 40 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 17 + x, sp), 41 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 42 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 18 + x, sp), 43 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(11, 18 + x, sp), 44 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 19 + x, sp), 45 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(10, 19 + x, sp), 46 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(9, 20 + x, sp), 47 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(8, 21 + x, sp), 48 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(8, 21 + x, sp), 49 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(7, 22 + x, sp), 50 + y, RGB(43, 50, 52));

    //right foot - правая стопа (ботинок)
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 51 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 52 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 25 + x, sp), 53 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(3, 26 + x, sp), 54 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 55 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 56 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(5, 26 + x, sp), 57 + y, RGB(58, 55, 50));
    RenderPixelLine(hdc, pixels_other_t(2, 26 + x, sp), 58 + y, RGB(58, 55, 50));
}

void pre_render::RenderMainCharacter(HDC hdc, int x, int y, int index, int sp) {

    switch (index) {
    case 0:
        RenderHat(hdc, x, y, sp);
        RenderFace(hdc, x, y, sp);
        RenderArms(hdc, x, y, sp);
        RenderBody(hdc, x, y, sp);
        RenderLegs(hdc, x, y, sp);
        break;
    case 1:
        RenderHat(hdc, x, y, sp);
        RenderFace(hdc, x, y, sp);
        RenderArms(hdc, x, y, sp);
        RenderBody(hdc, x, y, sp);
        RenderLegs_1(hdc, x, y, sp);
        break;
    case 2:
        RenderHat(hdc, x, y, sp);
        RenderFace(hdc, x, y, sp);
        RenderArms(hdc, x, y, sp);
        RenderBody(hdc, x, y, sp);
        RenderLegs_2(hdc, x, y, sp);
        break;
    }
}

/*
void pre_render::GrassLeftCorner(HDC hdc, int x, int y, int sp) {
    RenderPixelLine(hdc, pixels_other_t(5, 2 + x, sp), 0 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(4, 7 + x, sp), 0 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x, sp), 0 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(3, 13 + x, sp), 0 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 1 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 1 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(2, 3 + x, sp), 1 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 5 + x, sp), 1 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(4, 7 + x, sp), 1 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 1 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x, sp), 1 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 1 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 2 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 2 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 2 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(2, 3 + x, sp), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 5 + x, sp), 2 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(4, 7 + x, sp), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x, sp), 2 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 2 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 3 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 3 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 3 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 3 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 4 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 4 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 4 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 5 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 5 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(9, 6 + x, sp), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 5 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 6 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 6 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 6 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x, sp), 6 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(3, 4 + x, sp), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 7 + x, sp), 6 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 6 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(3, 12 + x, sp), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 6 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x, sp), 7 + y, RGB(26, 122, 62));
    RenderPixelLine(hdc, pixels_other_t(2, 1 + x, sp), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x, sp), 7 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x, sp), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 7 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x, sp), 7 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 13 + x, sp), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 7 + y, RGB(36, 82, 59));


    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x, sp), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 8 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x, sp), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 8 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 2 + x, sp), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x, sp), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 9 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(4, 11 + x, sp), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x, sp), 9 + y, RGB(66, 57, 52));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 3 + x, sp), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 12 + x, sp), 10 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 10 + y, RGB(66, 57, 52));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 3 + x, sp), 11 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 9 + x, sp), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 10 + x, sp), 11 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x, sp), 11 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 11 + y, RGB(160, 134, 98));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 12 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 12 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 3 + x, sp), 12 + y, RGB(36, 82, 59));
  //  RenderPixelLine(hdc, pixels_other_t(1, 5), 12, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 12 + y, RGB(20, 160, 46));
  //  RenderPixelLine(hdc, pixels_other_t(1, 9), 12, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x, sp), 12 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x, sp), 12 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 12 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 12 + y, RGB(199, 176, 139));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 13 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 13 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x, sp), 13 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 13 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 13 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 9 + x, sp), 13 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 10 + x, sp), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 12 + x, sp), 13 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 13 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 13 + y, RGB(199, 176, 139));

    RenderPixelLine(hdc, pixels_other_t(1, 1 + x, sp), 14 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x, sp), 14 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x, sp), 14 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x, sp), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x, sp), 14 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 9 + x, sp), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 10 + x, sp), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x, sp), 14 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(1, 12 + x, sp), 14 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x, sp), 14 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x, sp), 14 + y, RGB(199, 176, 139));


    RenderPixelLine(hdc, pixels_other_t(3, 1 + x, sp), 15 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x, sp), 15 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(5, 5 + x, sp), 15 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 10 + x, sp), 15 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(5, 11 + x, sp), 15 + y, RGB(199, 176, 139));
}

void pre_render::GrassMiddle(HDC hdc, int x, int y) {
    RenderPixelLine(hdc, pixels_other_t(7, 0 + x), 0 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(4, 7 + x), 0 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 0 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(3, 13 + x), 0 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(5, 0 + x), 1 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 5 + x), 1 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(5, 7 + x), 1 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 1 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x), 1 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(3, 0 + x), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(5, 3 + x), 2 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(5, 7 + x), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 2 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x), 2 + y, RGB(20, 160, 46));

    RenderPixelLine(hdc, pixels_other_t(2, 0 + x), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(5, 2 + x), 3 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(6, 6 + x), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 3 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 3 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(6, 1 + x), 4 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(6, 6 + x), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 4 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 4 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(6, 1 + x), 5 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(6, 6 + x), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 5 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 5 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(2, 0 + x), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x), 6 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 6 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(3, 4 + x), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 7 + x), 6 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 6 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(3, 12 + x), 6 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 6 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 7 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 1 + x), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 7 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x), 7 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 7 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 13 + x), 7 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 7 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 1 + x), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 8 + y, RGB(89, 193, 53));
    RenderPixelLine(hdc, pixels_other_t(3, 8 + x), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 8 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x), 8 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 14 + x), 8 + y, RGB(36, 82, 59));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 9 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 1 + x), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 8 + x), 9 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 9 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 9 + y, RGB(66, 57, 52));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 10 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 10 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(3, 2 + x), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(3, 8 + x), 10 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 10 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x), 10 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 10 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 10 + y, RGB(66, 57, 52));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 11 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(3, 1 + x), 11 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x), 11 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(1, 5 + x), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 8 + x), 11 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 10 + x), 11 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 11 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 11 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 11 + y, RGB(160, 134, 98));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 12 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(2, 1 + x), 12 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 12 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 12 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 12 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(1, 8 + x), 12 + y, RGB(20, 160, 46));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x), 12 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 12 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 13 + x), 12 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 12 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 12 + y, RGB(199, 176, 139));

    RenderPixelLine(hdc, pixels_other_t(1, 0 + x), 13 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x), 13 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(2, 3 + x), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(5, 5 + x), 13 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 10 + x), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 13 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(2, 13 + x), 13 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 13 + y, RGB(199, 176, 139));

    RenderPixelLine(hdc, pixels_other_t(2, 0 + x), 14 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(1, 2 + x), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 14 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(3, 6 + x), 14 + y, RGB(36, 82, 59));
    RenderPixelLine(hdc, pixels_other_t(2, 9 + x), 14 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 14 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(4, 12 + x), 14 + y, RGB(199, 176, 139));

    RenderPixelLine(hdc, pixels_other_t(4, 0 + x), 15 + y, RGB(199, 176, 139));
    RenderPixelLine(hdc, pixels_other_t(1, 4 + x), 15 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(5, 5 + x), 15 + y, RGB(66, 57, 52));
    RenderPixelLine(hdc, pixels_other_t(1, 10 + x), 15 + y, RGB(160, 134, 98));
    RenderPixelLine(hdc, pixels_other_t(5, 11 + x), 15 + y, RGB(199, 176, 139));
}
*/