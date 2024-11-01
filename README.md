<h1>Этапы разработки</h1>

- [Первый этап](#первый-этап)
- [Второй и третий этапы](#второй---третий-этапы)



## Первый этап
Отрисовка объектов:<br>
Код самого рендера:<br>
a ray of hope.cpp

    void pre_render::RenderPixel(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color) { //hdc, x, y, ширина, высота
          HBRUSH hBrush;
          hBrush = CreateSolidBrush(color);
          SelectObject(hdc, hBrush);
      
          RECT rect = { x - PIXEL + space_x, y - PIXEL + space_y, x + space_x, y + space_y };
          FillRect(hdc, &rect, hBrush);
          DeleteObject(hBrush);
          
          // Rectangle(hdc, x - PIXEL + space_x, y - PIXEL + space_y, x + space_x, y + space_y); //debug pixels
    }
   
    void pre_render::RenderPixelLine(HDC hdc, pixels_other_t pix_info, int index, COLORREF color) {
    
        int index_;
    
        if (index != 0)
            index_ = PIXEL * index;
        else
            index_ = 0;
    
      
        for (int i = 1; i <= pix_info.width_pix; i++)
             RenderPixel(hdc,  (PIXEL)*i, PIXEL, (PIXEL * pix_info.pix_space), index_, color);
    }
a ray of hope.h

    class pre_render {
    public:
    	void RenderPixel(HDC hdc, int x, int y, int space_x, int space_y, COLORREF color);
    	
    	void RenderPixelLine(HDC hdc, pixels_other_t pix_info, int index, COLORREF color);
    	. . .
    };
    extern pre_render render;





render_pixel.h

    #pragma once
    
    //PIXEL - размер пикселей
    enum pixels {
        PIXEL = 3,
        PIXELB = 5
    };
    
    class pixels_other_t {
    public:
        int width_pix = 0;
        int pix_space = 0;
    
        pixels_other_t(int w, int space) {
            width_pix = w;
            pix_space = space;
        }
    };
    
Код главного персонажа ( 1 ):<br>
a ray of hope.cpp

    void pre_render::RenderHat(HDC hdc, int x, int y) {
        RenderPixelLine(hdc, pixels_other_t(7, 20 + x), 0 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(11, 19 + x), 1 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(13, 18 + x), 2 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(15, 17 + x), 3 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(17, 17 + x), 4 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(18, 16 + x), 5 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(14, 16 + x), 6 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 7 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(7, 14 + x), 8 + y, RGB(147, 141, 124));
        RenderPixelLine(hdc, pixels_other_t(3, 14 + x), 9 + y, RGB(147, 141, 124));
    }
    void pre_render::RenderFace(HDC hdc, int x, int y) {
        RenderPixelLine(hdc, pixels_other_t(2, 25 + x), 7 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(1, 27 + x), 7 + y, RGB(37, 39, 36));
        RenderPixelLine(hdc, pixels_other_t(1, 21 + x), 8 + y, RGB(37, 39, 36));
        RenderPixelLine(hdc, pixels_other_t(1, 22 + x), 8 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(1, 23 + x), 8 + y, RGB(37, 39, 36));
        RenderPixelLine(hdc, pixels_other_t(1, 24 + x), 8 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(1, 25 + x), 8 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 26 + x), 8 + y, RGB(202, 175, 148));
        ...  
    }
    ...



    void pre_render::RenderMainCharacter(HDC hdc, int x, int y, int index) {
    
        switch (index) {
        case 0:
            RenderHat(hdc, x, y);
            RenderFace(hdc, x, y);
            RenderArms(hdc, x, y);
            RenderBody(hdc, x, y);
            RenderLegs(hdc, x, y);
            break;
        case 1:
            . . .
            break;
        case 2:
            . . .
            break;
        }
    }
    void pre_render::PreviewModels(HDC hdc) {
        render.RenderMainCharacter(hdc, 0, 0, 0);
         . . .
    }
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }












Иллюстрация главного персонажа ( 1 ):

![image](https://github.com/user-attachments/assets/51dc69e0-dc1f-4659-838e-84e0d7b4b418)

 




Код главного персонажа ( 2 ):<br>
a ray of hope.cpp

    void pre_render::RenderLegs_1(HDC hdc, int x, int y) {
        //left - левая
        RenderPixelLine(hdc, pixels_other_t(1, 13 + x), 40 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 41 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(3, 11 + x), 42 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(3, 11 + x), 43 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(3, 11 + x), 44 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(3, 11 + x), 45 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(3, 11 + x), 46 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(2, 12 + x), 47 + y, RGB(34, 42, 44));
    
    
        RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 38 + y, RGB(80, 81, 65));
    
    
        RenderPixelLine(hdc, pixels_other_t(7, 4 + x), 43 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(7, 4 + x), 44 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(7, 4 + x), 45 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 46 + y, RGB(58, 55, 50));
    
        //right - правая
       // RenderPixelLine(hdc, pixels_other_t(2, 20), 34, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(2, 18 + x), 35 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(2, 20 + x), 34 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(3, 20 + x), 35 + y, RGB(80, 81, 65));
    
        RenderPixelLine(hdc, pixels_other_t(5, 18 + x), 36 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(6, 17 + x), 37 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(7, 16 + x), 38 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 39 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 40 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 41 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 42 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 43 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 44 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 45 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 46 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 47 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 14 + x), 48 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(8, 15 + x), 49 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(7, 15 + x), 50 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(5, 16 + x), 51 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(3, 16 + x), 52 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(2, 16 + x), 53 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 16 + x), 54 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(4, 16 + x), 55 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(4, 16 + x), 56 + y, RGB(58, 55, 50));
    }
    
    
    
    
    
    void pre_render::RenderMainCharacter(HDC hdc, int x, int y, int index) {
    
        switch (index) {
        case 0:
            ...
            break;
        case 1:
            RenderHat(hdc, x, y);
            RenderFace(hdc, x, y);
            RenderArms(hdc, x, y);
            RenderBody(hdc, x, y);
            RenderLegs_1(hdc, x, y);
            break;
        case 2:
            ...
            break;
        }
    }
    void pre_render::PreviewModels(HDC hdc) {
        . . .
        render.RenderMainCharacter(hdc, 50, 0, 1);
        . . .
    
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }
    
    











Иллюстрация главного персонажа ( 2 ):

![image](https://github.com/user-attachments/assets/b975d0d3-a85d-4919-92ad-41e2e20a2e1b)





Код главного персонажа ( 3 ):<br>
a ray of hope.cpp

    void pre_render::RenderLegs_2(HDC hdc, int x, int y) {
        //left - левая
        RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 38 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(2, 14 + x), 39 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(1, 8 + x), 40 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(5, 12 + x), 40 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(10, 8 + x), 41 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(11, 7 + x), 42 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(11, 7 + x), 43 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(11, 7 + x), 44 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(12, 6 + x), 45 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(11, 6 + x), 46 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(9, 6 + x), 47 + y, RGB(43, 50, 52));
        RenderPixelLine(hdc, pixels_other_t(7, 7 + x), 48 + y, RGB(43, 50, 52));
    
        //left foot - левая стопа (ботинок)
        RenderPixelLine(hdc, pixels_other_t(5, 1 + x), 45 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(6, 0 + x), 46 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(6, 0 + x), 47 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(4, 0 + x), 48 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 0 + x), 49 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 0 + x), 50 + y, RGB(58, 55, 50));
    
        //right - правая
        RenderPixelLine(hdc, pixels_other_t(2, 20 + x), 34 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(4, 19 + x), 35 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(6, 18 + x), 36 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(8, 17 + x), 37 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 16 + x), 38 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 16 + x), 39 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 17 + x), 40 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(11, 17 + x), 41 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 18 + x), 42 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 18 + x), 43 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(11, 18 + x), 44 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 19 + x), 45 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(10, 19 + x), 46 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(9, 20 + x), 47 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(8, 21 + x), 48 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(8, 21 + x), 49 + y, RGB(34, 42, 44));
        RenderPixelLine(hdc, pixels_other_t(7, 22 + x), 50 + y, RGB(34, 42, 44));
    
        //right foot - правая стопа (ботинок)
        RenderPixelLine(hdc, pixels_other_t(3, 25 + x), 51 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 25 + x), 52 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 25 + x), 53 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(3, 26 + x), 54 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(5, 26 + x), 55 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(5, 26 + x), 56 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(5, 26 + x), 57 + y, RGB(58, 55, 50));
        RenderPixelLine(hdc, pixels_other_t(2, 26 + x), 58 + y, RGB(58, 55, 50));
    }
    
    
    
    
    
    void pre_render::RenderMainCharacter(HDC hdc, int x, int y, int index) {
    
        switch (index) {
        case 0:
            . . .
            break;
        case 1:
            . . .
            break;
        case 2:
            RenderHat(hdc, x, y);
            RenderFace(hdc, x, y);
            RenderArms(hdc, x, y);
            RenderBody(hdc, x, y);
            RenderLegs_2(hdc, x, y);
            break;
        }
    }
    
    void pre_render::PreviewModels(HDC hdc) {
        . . .
        render.RenderMainCharacter(hdc, 100, 0, 2);
    
        . . .
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }












Иллюстрация главного персонажа ( 3 ):

![image](https://github.com/user-attachments/assets/1f0e492b-98fb-448a-a9b5-48c2149391b0)


Код главного персонажа ( Атака 1 ):<br>
a ray of hope.cpp

    void pre_render::AttackAnims(HDC hdc, int x, int y) {
        RenderPixelLine(hdc, pixels_other_t(2, 2 + x), 0 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 4 + x), 1 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 2 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(3, 8 + x), 3 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 11 + x), 4 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 13 + x), 5 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 15 + x), 6 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(3, 17 + x), 7 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(2, 20 + x), 8 + y, RGB(144, 144, 144));
        RenderPixelLine(hdc, pixels_other_t(1, 22 + x), 8 + y, RGB(77, 47, 52));
    
        RenderPixelLine(hdc, pixels_other_t(2, 23 + x), 8 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(4, 22 + x), 9 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 10 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(5, 24 + x), 11 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(2, 24 + x), 12 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 27 + x), 12 + y, RGB(202, 175, 148));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 12 + y, RGB(77, 47, 52));
    
        RenderPixelLine(hdc, pixels_other_t(5, 23 + x), 13 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 28 + x), 13 + y, RGB(153, 144, 137)); //чуть темнее
    
        RenderPixelLine(hdc, pixels_other_t(4, 19 + x), 14 + y, RGB(155, 148, 130)); //кусок шляпы
        RenderPixelLine(hdc, pixels_other_t(5, 23 + x), 14 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 28 + x), 14 + y, RGB(153, 144, 137)); //чуть темнее
    
        //шляпа 139 133 117
        RenderPixelLine(hdc, pixels_other_t(5, 18 + x), 15 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 15 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 15 + y, RGB(153, 144, 137));
    
        RenderPixelLine(hdc, pixels_other_t(6, 17 + x), 16 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 16 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 16 + y, RGB(155, 148, 130));
    
        RenderPixelLine(hdc, pixels_other_t(7, 16 + x), 17 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 17 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 29 + x), 17 + y, RGB(155, 148, 130));
    RenderPixelLine(hdc, pixels_other_t(7, 16 + x), 18 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 18 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(4, 29 + x), 18 + y, RGB(155, 148, 130));
    
        RenderPixelLine(hdc, pixels_other_t(9, 15 + x), 19 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(5, 24 + x), 19 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(4, 29 + x), 19 + y, RGB(155, 148, 130));
    
        RenderPixelLine(hdc, pixels_other_t(9, 15 + x), 20 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(5, 24 + x), 20 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 20 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(10, 14 + x), 21 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(5, 24 + x), 21 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 21 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(7, 13 + x), 22 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(1, 20 + x), 22 + y, RGB(37, 39, 36));//волосы
        RenderPixelLine(hdc, pixels_other_t(1, 21 + x), 22 + y, RGB(202, 175, 148)); //лицо
        RenderPixelLine(hdc, pixels_other_t(1, 22 + x), 22 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(6, 23 + x), 22 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 29 + x), 22 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(3, 13 + x), 23 + y, RGB(155, 148, 130));
        RenderPixelLine(hdc, pixels_other_t(2, 18 + x), 23 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(2, 20 + x), 23 + y, RGB(202, 175, 148)); //лицо
        RenderPixelLine(hdc, pixels_other_t(1, 22 + x), 23 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(5, 23 + x), 23 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 28 + x), 23 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(2, 18 + x), 24 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(2, 20 + x), 24 + y, RGB(202, 175, 148)); //лицо
        RenderPixelLine(hdc, pixels_other_t(6, 22 + x), 24 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 28 + x), 24 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(4, 17 + x), 25 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(7, 21 + x), 25 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 28 + x), 25 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(5, 15 + x), 26 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(7, 20 + x), 26 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 27 + x), 26 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(1, 14 + x), 27 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(1, 16 + x), 27 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(2, 17 + x), 27 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(8, 19 + x), 27 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 27 + x), 27 + y, RGB(153, 144, 137)); //кусок руки
    //пальто 80 81 65
        RenderPixelLine(hdc, pixels_other_t(1, 15 + x), 28 + y, RGB(37, 39, 36)); //волосы
        RenderPixelLine(hdc, pixels_other_t(1, 17 + x), 28 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(8, 18 + x), 28 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(3, 26 + x), 28 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(2, 16 + x), 29 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(8, 18 + x), 29 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 26 + x), 29 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(2, 16 + x), 30 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(7, 18 + x), 30 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(3, 25 + x), 30 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(2, 16 + x), 31 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(6, 18 + x), 31 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(1, 24 + x), 31 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(2, 25 + x), 31 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(4, 15 + x), 32 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(4, 19 + x), 32 + y, RGB(179, 172, 166));
        RenderPixelLine(hdc, pixels_other_t(2, 23 + x), 32 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(1, 25 + x), 32 + y, RGB(153, 144, 137)); //кусок руки
    
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 33 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 34 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 35 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 36 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(10, 15 + x), 37 + y, RGB(80, 81, 65));
    
        RenderPixelLine(hdc, pixels_other_t(11, 14 + x), 38 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(11, 14 + x), 39 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(11, 14 + x), 40 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(11, 14 + x), 41 + y, RGB(80, 81, 65));
    
        RenderPixelLine(hdc, pixels_other_t(10, 14 + x), 42 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(11, 13 + x), 43 + y, RGB(80, 81, 65));
    
        RenderPixelLine(hdc, pixels_other_t(13, 0 + x), 44 + y, RGB(32, 32, 32));
        RenderPixelLine(hdc, pixels_other_t(11, 13 + x), 44 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(2, 24 + x), 44 + y, RGB(32, 32, 32));
    
        RenderPixelLine(hdc, pixels_other_t(10, 13 + x), 45 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(11, 12 + x), 46 + y, RGB(80, 81, 65));
    
        RenderPixelLine(hdc, pixels_other_t(9, 12 + x), 47 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(2, 21 + x), 47 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(10, 11 + x), 48 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(2, 21 + x), 48 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(10, 10 + x), 49 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(4, 20 + x), 49 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(10, 10 + x), 50 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(5, 20 + x), 50 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(11, 8 + x), 51 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(7, 19 + x), 51 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(11, 8 + x), 52 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(7, 19 + x),52 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(10, 8 + x), 53 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(9, 18 + x), 53 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(10, 8 + x), 54 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(9, 18 + x), 54 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(9, 8 + x), 55 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(10, 17 + x), 55 + y, RGB(43, 50, 52));
    RenderPixelLine(hdc, pixels_other_t(6, 10 + x), 56 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(1, 16 + x), 56 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(11, 17 + x), 56 + y, RGB(43, 50, 52));
        
        RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 57 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(3, 12 + x), 57 + y, RGB(80, 81, 65));
        RenderPixelLine(hdc, pixels_other_t(2, 15 + x), 57 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(11, 17 + x), 57 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(7, 10 + x), 58 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(11, 17 + x), 58 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(7, 10 + x), 59 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(11, 17 + x), 59 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(8, 10 + x), 60 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(10, 18 + x), 60 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(8, 10 + x), 61 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(10, 18 + x), 61 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(9, 10 + x), 62 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(9, 19 + x), 62 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(9, 10 + x), 63 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(9, 19 + x),63 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(7, 11 + x), 64 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(8, 20 + x), 64 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(2, 10 + x), 65 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(5, 12 + x), 65 + y, RGB(34, 42, 44)); //левая нога
        RenderPixelLine(hdc, pixels_other_t(7, 21 + x), 65 + y, RGB(43, 50, 52));
    
        RenderPixelLine(hdc, pixels_other_t(4, 9 + x), 66 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 66 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(4, 8 + x), 67 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 67 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(4, 7 + x), 68 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 68 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(3, 7 + x), 69 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 69 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(4, 7 + x), 70 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 70 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(4, 8 + x), 71 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(3, 23 + x), 71 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(3, 9 + x), 72 + y, RGB(58, 55, 50)); //сапоги
        RenderPixelLine(hdc, pixels_other_t(4, 23 + x), 72 + y, RGB(58, 55, 50)); //сапоги
    
        RenderPixelLine(hdc, pixels_other_t(4, 23 + x), 73 + y, RGB(58, 55, 50)); //сапоги
    }
    
    void pre_render::PreviewModels(HDC hdc) {
        . . .
        render.AttackAnims(hdc, 150, 0);
        . . .
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }









Иллюстрация главного персонажа ( Атака 1):

![image](https://github.com/user-attachments/assets/194580c4-83b3-4916-9864-78e271e2744b)







Код главного персонажа ( Атака 2 ):<br>
a ray of hope.cpp

    void pre_render::AttackAnimsT(HDC hdc, int x, int y) {
    
        RenderPixelLine(hdc, pixels_other_t(24, 10 + x), 1 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(36, 5 + x), 2 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(44, 0 + x), 3 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(27, 20 + x), 4 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(25, 25 + x), 5 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(23, 29 + x), 6 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(23, 32 + x), 7 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(23, 34 + x), 8 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(22, 37 + x), 9 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(20, 40 + x), 10 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 43 + x), 11 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 45 + x), 12 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 47 + x), 13 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 48 + x), 14 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(16, 50 + x), 15 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(16, 51 + x), 16 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 51 + x), 17 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 52 + x), 18 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 53 + x), 19 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 54 + x), 20 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 54 + x), 21 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(17, 55 + x), 22 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 55 + x), 23 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 55 + x), 24 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 56 + x), 25 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(18, 56 + x), 26 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(19, 56 + x), 27 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(19, 56 + x), 28 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(20, 56 + x), 29 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(20, 56 + x), 30 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 56 + x), 31 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 56 + x), 32 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 57 + x), 33 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 57 + x), 34 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 57 + x), 35 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(21, 57 + x), 36 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(22, 57 + x), 37 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(22, 57 + x), 38 + y, RGB(192, 192, 192));
    
        RenderPixelLine(hdc, pixels_other_t(20, 57 + x), 39 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(2, 77 + x), 39 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(18, 56 + x), 40 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(3, 74 + x), 40 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(16, 56 + x), 41 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(2, 72 + x), 41 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(13, 56 + x), 42 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(3, 69 + x), 42 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(11, 56 + x), 43 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(2, 67 + x), 43 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(8, 56 + x), 44 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(3, 64 + x), 44 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(5, 57 + x), 45 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(2, 62 + x), 45 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(3, 57 + x), 46 + y, RGB(192, 192, 192));
        RenderPixelLine(hdc, pixels_other_t(3, 60 + x), 46 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(3, 57 + x), 47 + y, RGB(144, 144, 144)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(1, 57 + x), 48 + y, RGB(144, 144, 144)); //меч
        RenderPixelLine(hdc, pixels_other_t(2, 55 + x), 48 + y, RGB(77, 47, 52)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(3, 53 + x), 49 + y, RGB(77, 47, 52)); //меч
    
        RenderPixelLine(hdc, pixels_other_t(3, 51 + x), 50 + y, RGB(77, 47, 52)); //меч
    //    RenderPixelLine(hdc, pixels_other_t(2, 50), 51, RGB(77, 47, 52)); //меч
    
        RenderHat(hdc, 16 + x, 15 + y);
        RenderFace(hdc, 16 + x, 15 + y);
        RenderArms_AT(hdc, 16 + x, 15 + y);
        RenderBody(hdc, 16 + x, 15 + y);
        RenderLegs(hdc, 16 + x, 15 + y);
    }
    void pre_render::PreviewModels(HDC hdc) {
        . . .
        render.AttackAnimsT(hdc, 200, 0);
        . . . 
    }
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }





Иллюстрация главного персонажа ( Атака 2 ):
 
![image](https://github.com/user-attachments/assets/3eeb8ad4-eb4e-44a8-8f7b-0e7b5657cc74)













Код фляги:<br>
a ray of hope.cpp

    void pre_render::HealFlask(HDC hdc, int x, int y) {
        RenderPixelLine(hdc, pixels_other_t(4, 5 + x), 0 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 5 + x), 1 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 1 + y, RGB(219, 164, 99));
        RenderPixelLine(hdc, pixels_other_t(1, 8 + x), 1 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(8, 3 + x), 2 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 4 + x), 3 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 3 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 9 + x), 3 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 4 + x), 4 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(2, 6 + x), 4 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 9 + x), 4 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 4 + x), 5 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 9 + x), 5 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 6 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 10 + x), 6 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 2 + x), 7 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 7 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 8 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 8 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 8 + y, RGB(93, 175, 141));
        RenderPixelLine(hdc, pixels_other_t(6, 4 + x), 8 + y, RGB(146, 220, 186));
        RenderPixelLine(hdc, pixels_other_t(1, 10 + x), 8 + y, RGB(93, 175, 141));
    
    
        RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 9 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 9 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 9 + y, RGB(93, 175, 141));
        RenderPixelLine(hdc, pixels_other_t(6, 4 + x), 9 + y, RGB(146, 220, 186));
        RenderPixelLine(hdc, pixels_other_t(1, 10 + x), 9 + y, RGB(93, 175, 141));
    
        RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 10 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 10 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(2, 3 + x), 10 + y, RGB(93, 175, 141));
        RenderPixelLine(hdc, pixels_other_t(4, 5 + x), 10 + y, RGB(146, 220, 186));
        RenderPixelLine(hdc, pixels_other_t(2, 9 + x), 10 + y, RGB(93, 175, 141));
    
    
        RenderPixelLine(hdc, pixels_other_t(1, 1 + x), 11 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 12 + x), 11 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(8, 3 + x), 11 + y, RGB(93, 175, 141));
    
        RenderPixelLine(hdc, pixels_other_t(1, 2 + x), 12 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 11 + x), 12 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(6, 4 + x), 12 + y, RGB(93, 175, 141));
    
        RenderPixelLine(hdc, pixels_other_t(1, 3 + x), 13 + y, RGB(0, 0, 0));
        RenderPixelLine(hdc, pixels_other_t(1, 10 + x), 13 + y, RGB(0, 0, 0));
    
        RenderPixelLine(hdc, pixels_other_t(6, 4 + x), 14 + y, RGB(0, 0, 0));
    }
    void pre_render::PreviewModels(HDC hdc) {
        . . .
        render.HealFlask(hdc, 10, 80);
        . . .
    
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .
    
            EndPaint(hWnd, &ps);
        }


Иллюстрация фляги:

![image](https://github.com/user-attachments/assets/83200217-470b-4080-bfb4-07348a1fc19d)







Код врага (слайм 1):<br>
Тут я создал доп рендер пикселя для увеличения размера<br>
a ray of hope.cpp<br>

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
    
    
        for (int i = 1; i <= pix_info.width_pix; i++)
            RenderPixelB(hdc, (PIXELB)*i, PIXELB, (PIXELB * pix_info.pix_space), index_, color);
    }
    
render_pixel.h

    #pragma once
    
    //PIXEL - размер пикселей
    enum pixels {
        PIXEL = 3,
        PIXELB = 5
    };








a ray of hope.cpp

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

Иллюстрация врага (слайм 1):
 
![image](https://github.com/user-attachments/assets/c170bad3-ceb7-4803-8458-b1f750414c6f)


















Код врага (слайм 2):<br>
a ray of hope.cpp

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





Иллюстрация врага (слайм 1 (атака)):
 
![image](https://github.com/user-attachments/assets/33da853e-7615-431d-87fb-da7ec1b10600)







Общая иллюстрация объектов:

![image](https://github.com/user-attachments/assets/7f387500-3423-4988-8f8f-95a4c0fdffa7)
 
    void pre_render::PreviewModels(HDC hdc) {
        render.RenderMainCharacter(hdc, 0, 0, 0);
        render.RenderMainCharacter(hdc, 50, 0, 1);
        render.RenderMainCharacter(hdc, 100, 0, 2);
    
        render.AttackAnims(hdc, 150, 0);
        render.AttackAnimsT(hdc, 200, 0);
        render.HealFlask(hdc, 10, 80);
    
        render.Slime(hdc, 30, 50);
        render.SlimeAttack(hdc, 70, 50);
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
    	 . . .
    
            render.PreviewModels(hdc);
    
    	 . . .

        EndPaint(hWnd, &ps);
    }

## Второй - третий этапы

Так как у меня игра в 2Д стиле в один этап я уместиться не смог, поэтому сделал сразу два.<br>
Я создал класс hitboxes_t и немного enum классов для удобства.<br>
Весь код был написан мной лично с нуля.<br>
hitboxes.h <br>

    #pragma once
    #include <wtypes.h>
    
    
    enum flags_e {
    	ON_GROUND,
    	ON_AIR, 
    	ON_JUMP
    };
    
    enum platforms {
    	FIRST_PLATFORM,
    	SECOND_PLATFORM,
    	THIRD_PLATFORM,
    	FOUR_PLATORM,
    	MAXIMUM_PLATFORMS
    };
    
    enum ladders {
    	FIRST_LADDER,
    	SECOND_LADDER,
    	THIRD_LADDER,
    	FOUR_LADDER,
    	MAXIMUM_LADDERS
    };
    
    
    enum players_flags {
    	LOCAL_PLAYER,
    	ENEMY_PLAYER
    };
    
    enum enemy_flags {
    	FIRST_ENEMY,
    	SECOND_ENEMY,
    	THIRD_ENEMY,
    	MAXIMUM_ENEMIES
    };
    
    class hitboxes_t {
    public:
    	RECT local_box;
    	RECT local_attack_box;
    	RECT enemy_box[50];
    	RECT platform_box[50];
    	RECT ladder_box[50];
    	RECT reset_platform;
    	int x;
    	int y;
    	int local_health = 220;
    	float enemy_health[50] = { 1.0, 1.0, 1.0 };
    	bool defeated_enemy[50];
    
    	int enemy_x[50];
    	int enemy_y[50];
    	bool flags[10];
    	bool flags_enemies[10][50];
    	bool local_in_platform[50];
    	bool enemy_in_platform[50][50];
    	bool enemy_attacked[50];
    	bool local_in_ladder[50] ;
    	float impulse = 100.f;
    	float jump_duration = 0.1f;
    	int enemy_moving_x[50];
    	COLORREF prop_debug[50];
    	COLORREF lad_debug[50];
    
    	bool reversed;
    	void OnUpdated();
    
    	void Init(HWND hwnd);
    
    	void CharacterHitboxes();
    
    	void Physics(int idx_player, int dop_idx = FIRST_ENEMY);
    
    	void ConditionsSet(const char* steps, int idx_player = LOCAL_PLAYER, int idx_enemy = FIRST_ENEMY);
    
    	void FindNewBox(RECT box, int platform_id);
    
    	void PropsHitboxes();
    
    	void EnemyHitboxes();
    
    	void LocalHealth();
    
    	void EnemyHealth(int index_enemy);
    
    	void AttackBox();
    
    	int EnemyMovement(int x1, int x2, int enemy_idx);
    };
    
    extern hitboxes_t hitboxes;












hitboxes.cpp<br>

Для начала я сделал обновление картинки <br>

    void hitboxes_t::OnUpdated() {
        . . .
    }
    
a ray of hope.cpp<br>

    case WM_CREATE:
            SetTimer(hWnd, 1, 100, 0);
            break;
    case WM_TIMER:
    	RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    
          hitboxes.OnUpdated();
          . . .
            break;

Далее я начал делать систему управления, для этого создал класс<br>
class input_control_t в файле input_controls.h<br>
input_controls.h<br>
    
    #pragma once
    
    class input_control_t {
    public:
    	bool right_move = false;
    	bool left_move = false;
    	bool jump = false;
    	bool attacked = false;
    	bool attacked2 = false;
    	int mouse_pos_x = 0;
    	int mouse_pox_y = 0;
    	bool mouse_reset = false;
    	bool blocked = false;
    
    	void reset(bool moved = false) {
    		if (moved) {
    			jump = false;
    		}
    		else {
    			right_move = false;
    			left_move = false;
    			jump = false;
    			attacked = false;
    			attacked2 = false;
    		}
    	}
    };
    
    extern input_control_t input_system;
    
Подключил и реализовал класс в case WM_KEYDOWN:<br>
a ray of hope.cpp<br>

    case WM_KEYDOWN:
            switch (wParam) {
            case VK_LEFT:
                if (!input_system.blocked) {
                    input_system.left_move = true;
                    input_system.right_move = false;
                    input_system.jump = false;
                }
                break;
            case VK_RIGHT:
                if (!input_system.blocked) {
                    input_system.left_move = false;
                    input_system.right_move = true;
                    input_system.jump = false;
                }
                break;
            case VK_SPACE:
                if (!input_system.blocked) {
                    input_system.jump = true;
                }
                break;
            case VK_UP:
                input_system.attacked = true;
    
                if (interfaces.in_game)
                    input_system.attacked2 = true;
                break;
            }
            break;
        case WM_LBUTTONDOWN:
            if (!input_system.mouse_reset) {
                input_system.mouse_pos_x = LOWORD(lParam);
                input_system.mouse_pox_y = HIWORD(lParam);
            }
            break;
            
Далее сделал сброс как всей системы управления, так и позиции мыши в case WM_TIMER:<br>
a ray of hope.cpp<br>

    case WM_TIMER:
         . . . 
         input_system.reset();
    
         if (input_system.mouse_reset) {
             input_system.mouse_pos_x = 0;
             input_system.mouse_pox_y = 0;
             input_system.mouse_reset = false;
         }
         RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME |          RDW_ALLCHILDREN);
         break;
         
Перенесемся обратно к hitboxes.cpp<br>
Весь код на данный момент CharacterHitboxes()<br>

    void hitboxes_t::CharacterHitboxes() {
        Physics(LOCAL_PLAYER);
    
    	local_box = { 100 + x, 100 + y, 220 + x, 300 + y };
    
        AttackBox();
      
        LocalHealth();
    
    }
    
Создал хитбокс главного героя объявив RECT local_box<br>

    void hitboxes_t::CharacterHitboxes() {
          . . . 
    	local_box = { 100 + x, 100 + y, 220 + x, 300 + y };
          . . .
    }
    
Далее добавил физику (падения / прыжка)<br>

    void hitboxes_t::CharacterHitboxes() {
        Physics(LOCAL_PLAYER);
    
        . . .
    }
    void hitboxes_t::Physics(int idx_player, int dop_idx) {
    
         . . .
            if (flags[ON_AIR] && !flags[ON_GROUND]) {
                y += 50;
            }
    
            if (flags[ON_JUMP]) {
                y -= 200;
            }
        . . .
    }


Сразу после, я занялся созданием своих флагов, дабы упросить себе код и в целом правильно реализовать мою задумку в управлении персонажем<br>




    void hitboxes_t::ConditionsSet(const char* steps, int idx_player, int idx_enemy) {
    	. . .
            if (steps == "touch_floor") {
                flags[ON_GROUND] = true;
                flags[ON_AIR] = false;
                flags[ON_JUMP] = false;
            }
            else if (steps == "air") {
                flags[ON_AIR] = true;
                flags[ON_GROUND] = false;
                flags[ON_JUMP] = false;
            }
            else if (steps == "jump") {
                flags[ON_AIR] = true;
                flags[ON_GROUND] = false;
                flags[ON_JUMP] = true;
            }
            else if (steps == "ladder") {
                flags[ON_AIR] = true;
                flags[ON_GROUND] = false;
                flags[ON_JUMP] = false;
            }
            else {
                flags[ON_AIR] = true;
                flags[ON_GROUND] = false;
                flags[ON_JUMP] = false;
            }
    	. . .
        
    }
    
К этому я еще вернусь<br>
А сейчас я расскажу что такое <br>

    void hitboxes_t::CharacterHitboxes() {
        . . . 
        AttackBox();
      
        . . .
    }
    
Данная функция несет в себе лишь объявление RECT <br>
Local_attack_box, что является обычным хитбоксом для измерения расстояния атаки от главного героя до врага. Если враг находиться в этом хитбоксе, он получает урон от главного героя при нажатии клавиши.<br>

    void hitboxes_t::AttackBox() {
        
        local_attack_box = { local_box.left, local_box.top, local_box.right + 120, local_box.bottom };
        
    }



Перенесемся непосредственно к здоровью главного героя:<br>
    
    void hitboxes_t::CharacterHitboxes() {
        . . . 
        LocalHealth();
    
    }
    void hitboxes_t::LocalHealth() {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
    
            enemy_attacked[i] = false;
    
            if (local_box.bottom == enemy_box[i].bottom
                && local_box.right > enemy_box[i].left
                && local_box.left < enemy_box[i].right) {
                enemy_attacked[i] = true;
                local_health -= 10;
            }
        }
    
        if (local_health <= 100) {
            . . .
            for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                enemy_health[b] = 1.0;
                defeated_enemy[b] = false;
                enemy_y[b] = 0;
            }
            x = 0;
            y = 0;
            world.player_location_x = 0;
            world.player_location_y = 0;
            local_health = 220;
        }
        
    }
    
Здесь я проверяю, что если хитбокс главного героя пересекается с хитбоксом врага, то главный герой начинает получать периодический урон в размере (– 10) - от всего здоровья.<br>

    void hitboxes_t::LocalHealth() {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
    
            . . .
    
            if (local_box.bottom == enemy_box[i].bottom
                && local_box.right > enemy_box[i].left
                && local_box.left < enemy_box[i].right) {
                . . .
                local_health -= 10;
            }
        }
    
        . . .
    }


Массив enemy_attacked просто проверяет атакует ли враг сейчас или нет
    
    . . .
       for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
    
            enemy_attacked[i] = false;
    
            if (local_box.bottom == enemy_box[i].bottom
                && local_box.right > enemy_box[i].left
                && local_box.left < enemy_box[i].right) {
                enemy_attacked[i] = true;
    		. . .
            }
        }
    . . .

Далее я сделал проверку на то если здоровье главного героя закончилось. Если оно закончилось то сбрасываю все координаты возвращая как героя так и врагов в первоначальное положение с полным запасом здоровья.

    void hitboxes_t::LocalHealth() {
        . . .
    
        if (local_health <= 100) {
            . . .
            for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                enemy_health[b] = 1.0;
                defeated_enemy[b] = false;
                enemy_y[b] = 0;
            }
            x = 0;
            y = 0;
            world.player_location_x = 0;
            world.player_location_y = 0;
            local_health = 220;
        }
        
    }

Идентично и со здоровьем врага. Если он получает урон и его хп ниже или равно 0.0f, то он становиться побежденным и по моей задумке падает под землю очищая путь главному герою
    
    void hitboxes_t::EnemyHealth(int index_enemy) {
        if (local_attack_box.right > enemy_box[index_enemy].left
            && local_attack_box.left < enemy_box[index_enemy].right) {
            if (input_system.attacked)
                hitboxes.enemy_health[index_enemy] -= 0.1f;
        }
    
        if (hitboxes.enemy_health[index_enemy] <= 0.0f) {
            hitboxes.ConditionsSet("defeated", ENEMY_PLAYER, index_enemy);
            defeated_enemy[index_enemy] = true;
        }
    }
    
    
    void hitboxes_t::EnemyHitboxes() {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
    
            EnemyHealth(i);
    
            Physics(ENEMY_PLAYER, i);
    
           
    
            enemy_x[FIRST_ENEMY] = 500 - world.player_location_x;
    
            enemy_x[SECOND_ENEMY] = 2100 - world.player_location_x;
    
            enemy_x[THIRD_ENEMY] = 3100 - world.player_location_x;
    
            enemy_box[FIRST_ENEMY] = { 200 + enemy_x[FIRST_ENEMY], 0 - 15 + enemy_y[FIRST_ENEMY], 400 + enemy_x[FIRST_ENEMY], 100 + enemy_y[FIRST_ENEMY] };
    
            if (i != FIRST_ENEMY)
                enemy_box[i] = { 200 + enemy_x[i], 0 - 100 + enemy_y[i], 320 + enemy_x[i], 100 + enemy_y[i] };
        }
    }

Класс EnemyHitboxes использует EnemyHealth(. . .) и ту же физику <br>
Physics() только уже с новыми аргументами enum,  i  <br>

Полный код void hitboxes_t::Physics(int idx_player, int dop_idx)<br>
    
    void hitboxes_t::Physics(int idx_player, int dop_idx) {
    
        if (idx_player == ENEMY_PLAYER) {
            if (flags_enemies[ON_AIR][dop_idx] && !flags_enemies[ON_GROUND][dop_idx]) {
                enemy_y[dop_idx] += 50;
            }
    
            if (flags_enemies[ON_JUMP][dop_idx]) {
                enemy_y[dop_idx] -= 200;
            }
        }
        else {
            if (flags[ON_AIR] && !flags[ON_GROUND]) {
                y += 50;
            }
    
            if (flags[ON_JUMP]) {
                y -= 200;
            }
        }
    }

Здесь вместо главного героя, физику получают враги, а именно то как враг находиться в воздухе и в прыжке (пока что не зайдействовал прыжок).


    
    void hitboxes_t::EnemyHitboxes() {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
    
            . . .
    
            enemy_x[FIRST_ENEMY] = 500 - world.player_location_x;
    
            enemy_x[SECOND_ENEMY] = 2100 - world.player_location_x;
    
            enemy_x[THIRD_ENEMY] = 3100 - world.player_location_x;
    
            enemy_box[FIRST_ENEMY] = { 200 + enemy_x[FIRST_ENEMY], 0 - 15 + enemy_y[FIRST_ENEMY], 400 + enemy_x[FIRST_ENEMY], 100 + enemy_y[FIRST_ENEMY] };
    
            if (i != FIRST_ENEMY)
                enemy_box[i] = { 200 + enemy_x[i], 0 - 100 + enemy_y[i], 320 + enemy_x[i], 100 + enemy_y[i] };
        }
    }
    
enemy_x является положением врага по координате x в мире.<br>
enemy box является хитбоксом врага, enum FIRST_ENEMY и тд. является индексом врага.<br>

До того как я перейду к платформам, хотелось бы сказать про сам мир, <br>
его я сделал использовав новый класс в world.h<br>
    
    #pragma once
    #include <wtypes.h>
    
    class world_scene {
    public:
    	int x = 0;
    	int y = 0;
    	int world_size_x = 100000;
    	int player_location_x = 0;
    	int player_location_y = 0;
    	void setup_location_world(HWND hwnd);
    };
    
В игре передвижение работает следующим образом: <br>
Двигается мир, а не главный герой. <br>
То есть если мы двигаемся вправо или в лево, мы <br>
либо прибавляем либо убавляем координаты.<br>

Файл world.cpp<br>
    
    #include "world.h"
    #include "input_controls.h"
    #include "hitboxes.h"
    
    void world_scene::setup_location_world(HWND hwnd) {
    	if (input_system.right_move) {
    		player_location_x += 100;
    	}
    	else if (input_system.left_move) {
    		player_location_x -= 100;
    	}
    
    }
     

Переходим к самому сложному. Это функция PropsHitboxes() <br>
В hitboxes.cpp<br>

Здесь я объявляю все хитбоксы платформ на которых стоит как главный герой, так и враги.<br>

    void hitboxes_t::PropsHitboxes() {
    
    hitboxes.platform_box[FIRST_PLATFORM] = {
          (30) - world.player_location_x, 400 + world.player_location_y, 1000 - world.player_location_x, 450 + world.player_location_y
        };
    
        hitboxes.platform_box[SECOND_PLATFORM] = {
          1010 - world.player_location_x, 200 + world.player_location_y, 2000 - world.player_location_x, 250 + world.player_location_y
        };
    
        hitboxes.platform_box[THIRD_PLATFORM] = {
          2010 - world.player_location_x, 600 + world.player_location_y, 3000 - world.player_location_x, 650 + world.player_location_y
        };
    
        hitboxes.platform_box[FOUR_PLATORM] = {
          3000 - world.player_location_x, 500 + world.player_location_y, 4000 - world.player_location_x, 550 + world.player_location_y
        };
    
       . . . 
    
    }

Добавляю в функцию данный код, он объявляет платформу снизу игрового мира, если игрок упадет в бездну и коснется данный платформы то придется начинать игру сначала.<br>
 
    . . .
    hitboxes.reset_platform = {
            0, 1000 + world.player_location_y, world.world_size_x, 1100 + world.player_location_y
        };
    . . .

Следующий код который я добавил это реализация соприкосновения <br>
Главного героя с платформами<br>
    
    . . .
    
    for (int i = FIRST_PLATFORM; i < MAXIMUM_PLATFORMS; i++) {
    
            if (local_box.bottom == platform_box[FIRST_PLATFORM].top) {
                local_in_platform[FIRST_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[SECOND_PLATFORM].top) {
                local_in_platform[SECOND_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[THIRD_PLATFORM].top) {
                local_in_platform[THIRD_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[FOUR_PLATORM].top) {
                local_in_platform[FOUR_PLATORM] = true;
            }
            else if (local_box.bottom == reset_platform.top) {
                //reset hp
                if (local_health < 220) {
                    local_health = 220;
                }
    
                for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                    enemy_health[b] = 1.0;
                    defeated_enemy[b] = false;
                    enemy_y[b] = 0;
                    // hitboxes.ConditionsSet("air", ENEMY_PLAYER, FIRST_ENEMY);
    
                }
    
                x = 0;
                y = 0;
                world.player_location_x = 0;
                world.player_location_y = 0;
            }
            else {
                local_in_platform[i] = false;
            }

В этом коде идет возвращения игрока и врагов в исходное состояние когда главный герой касается reset_platform о которой я говорил выше<br>

    . . . 
    
    else if (local_box.bottom == reset_platform.top) {
                //reset hp
                if (local_health < 220) {
                    local_health = 220;
                }
    
     
                for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                    enemy_health[b] = 1.0;
                    defeated_enemy[b] = false;
                    enemy_y[b] = 0;
    
                }
    
                x = 0;
                y = 0;
                world.player_location_x = 0;
                world.player_location_y = 0;
            }
    
    . . .















Еще одни проверки связанные с флагами, если главный герой коснулся платформы<br>

    . . .
    
      if (local_in_platform[i]) {
                if ((local_box.right < platform_box[i].left || local_box.left > platform_box[i].right)) {
                    hitboxes.ConditionsSet("air");
                }
                else if (input_system.jump) {
                    hitboxes.ConditionsSet("jump");
                }
                else {
                    hitboxes.ConditionsSet("touch_floor");
                }
    }
    
    . . .

То же самое я добавил и для врагов:<br>

    . . .
    
    for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                if (enemy_box[b].bottom == platform_box[FIRST_PLATFORM].top) {
                    enemy_in_platform[FIRST_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[SECOND_PLATFORM].top) {
                    enemy_in_platform[SECOND_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[THIRD_PLATFORM].top) {
                    enemy_in_platform[THIRD_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[FOUR_PLATORM].top) {
                    enemy_in_platform[FOUR_PLATORM][b] = true;
                }
                else {
                    enemy_in_platform[i][b] = false;
                }
            }
    
    . . .

    for (int j = FIRST_ENEMY; j < MAXIMUM_ENEMIES; j++) {
                if (enemy_in_platform[i][j]) {
    
                    if ((enemy_box[j].right < platform_box[i].left || enemy_box[j].left > platform_box[i].right)) {
                        hitboxes.ConditionsSet("air", ENEMY_PLAYER, j);
                    }
                    else {
                        hitboxes.ConditionsSet("touch_floor", ENEMY_PLAYER, j);
                    }
                }
            }




Далее я захотел сделать лестницы для подъема на платформы <br>
Если главный герой касается хитбокса лестницы, то он автоматически поднимается вверх.<br>


    . . .
    
    hitboxes.ladder_box[FIRST_LADDER] = {
          1000 - world.player_location_x, 200 + world.player_location_y, 1100 - world.player_location_x, 400 + world.player_location_y
        };
    
        hitboxes.ladder_box[SECOND_LADDER] = {
          1900 - world.player_location_x, 200 + world.player_location_y, 2010 - world.player_location_x, 600 + world.player_location_y
        };
    
    . . .
    
    for (int i = FIRST_LADDER; i < MAXIMUM_LADDERS; i++) {
    
            if ((local_box.right > ladder_box[FIRST_LADDER].left && local_box.left < ladder_box[FIRST_LADDER].right)) {
                local_in_ladder[FIRST_LADDER] = true;
            }
            else if (local_box.right > ladder_box[SECOND_LADDER].left && local_box.left < ladder_box[SECOND_LADDER].right) {
                local_in_ladder[SECOND_LADDER] = true;
            }
            else if (local_box.right > ladder_box[THIRD_LADDER].left && local_box.left < ladder_box[THIRD_LADDER].right) {
                local_in_ladder[THIRD_LADDER] = true;
            }
            else {
                local_in_ladder[i] = false;
            }
    
            if (local_in_ladder[i]) {
    
                hitboxes.ConditionsSet("ladder");
    
                if (local_box.bottom > ladder_box[i].top) {
                    input_system.blocked = true;
                    y -= 100;
                }
                else {
                    input_system.blocked = false;
                }
            }
        }
    
    . . .






А теперь весь код целиком void hitboxes_t::PropsHitboxes()<br>

    void hitboxes_t::PropsHitboxes() {
        for (int i = 0; i < MAXIMUM_PLATFORMS; i++)
            prop_debug[i] = RGB(0, 0, 0);
    
        hitboxes.platform_box[FIRST_PLATFORM] = {
          (30) - world.player_location_x, 400 + world.player_location_y, 1000 - world.player_location_x, 450 + world.player_location_y
        };
    
        hitboxes.platform_box[SECOND_PLATFORM] = {
          1010 - world.player_location_x, 200 + world.player_location_y, 2000 - world.player_location_x, 250 + world.player_location_y
        };
    
        hitboxes.platform_box[THIRD_PLATFORM] = {
          2010 - world.player_location_x, 600 + world.player_location_y, 3000 - world.player_location_x, 650 + world.player_location_y
        };
    
        hitboxes.platform_box[FOUR_PLATORM] = {
          3000 - world.player_location_x, 500 + world.player_location_y, 4000 - world.player_location_x, 550 + world.player_location_y
        };
    
        hitboxes.ladder_box[FIRST_LADDER] = {
          1000 - world.player_location_x, 200 + world.player_location_y, 1100 - world.player_location_x, 400 + world.player_location_y
        };
    
        hitboxes.ladder_box[SECOND_LADDER] = {
          1900 - world.player_location_x, 200 + world.player_location_y, 2010 - world.player_location_x, 600 + world.player_location_y
        };
    
    
        hitboxes.reset_platform = {
            0, 1000 + world.player_location_y, world.world_size_x, 1100 + world.player_location_y
        };
    
        hitboxes.ConditionsSet("air");
    
    
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) 
            hitboxes.ConditionsSet("air", ENEMY_PLAYER, i);
        
    
        for (int i = FIRST_LADDER; i < MAXIMUM_LADDERS; i++) {
    
            if ((local_box.right > ladder_box[FIRST_LADDER].left && local_box.left < ladder_box[FIRST_LADDER].right)) {
                local_in_ladder[FIRST_LADDER] = true;
            }
            else if (local_box.right > ladder_box[SECOND_LADDER].left && local_box.left < ladder_box[SECOND_LADDER].right) {
                local_in_ladder[SECOND_LADDER] = true;
            }
            else if (local_box.right > ladder_box[THIRD_LADDER].left && local_box.left < ladder_box[THIRD_LADDER].right) {
                local_in_ladder[THIRD_LADDER] = true;
            }
            else {
                local_in_ladder[i] = false;
            }
    
            if (local_in_ladder[i]) {
    
                hitboxes.ConditionsSet("ladder");
    
                if (local_box.bottom > ladder_box[i].top) {
                    input_system.blocked = true;
                    y -= 100;
                }
                else {
                    input_system.blocked = false;
                }
            }
        }
    
    
        for (int i = FIRST_PLATFORM; i < MAXIMUM_PLATFORMS; i++) {
    
            if (local_box.bottom == platform_box[FIRST_PLATFORM].top) {
                local_in_platform[FIRST_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[SECOND_PLATFORM].top) {
                local_in_platform[SECOND_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[THIRD_PLATFORM].top) {
                local_in_platform[THIRD_PLATFORM] = true;
            }
            else if (local_box.bottom == platform_box[FOUR_PLATORM].top) {
                local_in_platform[FOUR_PLATORM] = true;
            }
            else if (local_box.bottom == reset_platform.top) {
                //reset hp
                if (local_health < 220) {
                    local_health = 220;
                }
    
                for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                    enemy_health[b] = 1.0;
                    defeated_enemy[b] = false;
                    enemy_y[b] = 0;
                    // hitboxes.ConditionsSet("air", ENEMY_PLAYER, FIRST_ENEMY);
    
                }
    
                x = 0;
                y = 0;
                world.player_location_x = 0;
                world.player_location_y = 0;
            }
            else {
                local_in_platform[i] = false;
            }
    
    
            for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
                if (enemy_box[b].bottom == platform_box[FIRST_PLATFORM].top) {
                    enemy_in_platform[FIRST_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[SECOND_PLATFORM].top) {
                    enemy_in_platform[SECOND_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[THIRD_PLATFORM].top) {
                    enemy_in_platform[THIRD_PLATFORM][b] = true;
                }
                else if (enemy_box[b].bottom == platform_box[FOUR_PLATORM].top) {
                    enemy_in_platform[FOUR_PLATORM][b] = true;
                }
                else {
                    enemy_in_platform[i][b] = false;
                }
            }
    
            if (local_in_platform[i]) {
                if ((local_box.right < platform_box[i].left || local_box.left > platform_box[i].right)) {
                    hitboxes.ConditionsSet("air");
                }
                else if (input_system.jump) {
                    hitboxes.ConditionsSet("jump");
                }
                else {
                    hitboxes.ConditionsSet("touch_floor");
                    prop_debug[i] = RGB(10, 10, 255);
                }
            }
    
            for (int j = FIRST_ENEMY; j < MAXIMUM_ENEMIES; j++) {
                if (enemy_in_platform[i][j]) {
    
                    if ((enemy_box[j].right < platform_box[i].left || enemy_box[j].left > platform_box[i].right)) {
                        hitboxes.ConditionsSet("air", ENEMY_PLAYER, j);
                    }
                    else {
                        hitboxes.ConditionsSet("touch_floor", ENEMY_PLAYER, j);
                    }
                }
            }
        }
    }

Далее я занес все в функцию OnUpdated() <br>

    void hitboxes_t::OnUpdated() {
        CharacterHitboxes();
        EnemyHitboxes();
        PropsHitboxes();
    }
    
    
    
    










И вместе с этим я решил сделать плавную камеру которая сфокусирована на главном герое.<br>

    void hitboxes_t::Init(HWND hwnd) {
    
        world.setup_location_world(hwnd);
    
    
    
        RECT rectwindow;
        RECT new_rect;
        GetClientRect(hwnd, &rectwindow);
    
        bool resize_y_pos = false;
        bool resize_y_neg = false;
    
        if (hitboxes.local_box.top < 200) {
            resize_y_pos = true;
            resize_y_neg = false;
          
        }
        else if (hitboxes.local_box.top > 200) {
            resize_y_pos = false;
            resize_y_neg = true;
        }
    
        if (resize_y_pos && !resize_y_neg) {
            for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) 
                enemy_y[i] += 100;
            
            y += 100;
            world.player_location_y += 100;
            resize_y_pos = false;
        }
        else if (!resize_y_pos && resize_y_neg) {
            for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
                enemy_y[i] -= 100;
            }
            y -= 100;
            world.player_location_y -= 100;
            resize_y_neg = false;
        }
    
    }

То есть камера равняется по y = 200, если выше или ниже, картинка вся подстраивается чтобы было ровно 200, на какой платформе бы ты не стоял. <br>










После этого я отрисовал все по RECT которые я объявлял в hitboxes_t<br>
к примеру: <br>

a ray of hope.cpp <br>

    void pre_render::Platform(HDC hdc) {
        HPEN hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[FIRST_PLATFORM]);
    
        SelectObject(hdc, hpen);
    
        Rectangle(hdc, hitboxes.platform_box[FIRST_PLATFORM].left, hitboxes.platform_box[FIRST_PLATFORM].top, hitboxes.platform_box[FIRST_PLATFORM].right, hitboxes.platform_box[FIRST_PLATFORM].bottom);
    
        DeleteObject(hpen);
    }

Здесь рисуется первая платформа по координатам RECT platform_box.<br>

Код который я представлю ниже включает в себя платформы со второй по четвертую + две лестницы.<br>

    . . . 
    HPEN hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[SECOND_PLATFORM]);
    
    
        hpen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    
        SelectObject(hdc, hpen);
    
     
    
    
        Rectangle(hdc, hitboxes.ladder_box[FIRST_LADDER].left, hitboxes.ladder_box[FIRST_LADDER].top, hitboxes.ladder_box[FIRST_LADDER].right, hitboxes.ladder_box[FIRST_LADDER].bottom);
        Rectangle(hdc, hitboxes.ladder_box[SECOND_LADDER].left, hitboxes.ladder_box[SECOND_LADDER].top, hitboxes.ladder_box[SECOND_LADDER].right, hitboxes.ladder_box[SECOND_LADDER].bottom);
    
        DeleteObject(hpen);
    
        hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[SECOND_PLATFORM]);
    
        SelectObject(hdc, hpen);
    
        Rectangle(hdc, hitboxes.platform_box[SECOND_PLATFORM].left, hitboxes.platform_box[SECOND_PLATFORM].top, hitboxes.platform_box[SECOND_PLATFORM].right, hitboxes.platform_box[SECOND_PLATFORM].bottom);
    
        DeleteObject(hpen);
    
    
    
    
        hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[THIRD_PLATFORM]);
    
        SelectObject(hdc, hpen);
    
        Rectangle(hdc, hitboxes.platform_box[THIRD_PLATFORM].left, hitboxes.platform_box[THIRD_PLATFORM].top, hitboxes.platform_box[THIRD_PLATFORM].right, hitboxes.platform_box[THIRD_PLATFORM].bottom);
    
        DeleteObject(hpen);
    
        hpen = CreatePen(PS_SOLID, 1, hitboxes.prop_debug[FOUR_PLATORM]);
    
        SelectObject(hdc, hpen);
    
        Rectangle(hdc, hitboxes.platform_box[FOUR_PLATORM].left, hitboxes.platform_box[FOUR_PLATORM].top, hitboxes.platform_box[FOUR_PLATORM].right, hitboxes.platform_box[FOUR_PLATORM].bottom);
    
    
    
        DeleteObject(hpen);
    
    . . .

Так же я решил отрисовать здоровье как врагов, так и главного персонажа <br>

    void pre_render::DrawHealthBar(HDC hdc, int player_index, int enemy_idx) {
        if (player_index == LOCAL_PLAYER) {
            HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
    
            SelectObject(hdc, brush);
    
            Rectangle(hdc, hitboxes.local_box.left, hitboxes.local_box.top - 20, hitboxes.local_box.right, hitboxes.local_box.top - 10);
    
            brush = CreateSolidBrush(RGB(0, 255, 0));
    
            SelectObject(hdc, brush);
    
            Rectangle(hdc, hitboxes.local_box.left, hitboxes.local_box.top - 20, hitboxes.local_health, hitboxes.local_box.top - 10);
        }
        else if (player_index == ENEMY_PLAYER) {
            if (!hitboxes.defeated_enemy[enemy_idx]) {
                HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
    
                SelectObject(hdc, brush);
    
                Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left, hitboxes.enemy_box[enemy_idx].top - 20, hitboxes.enemy_box[enemy_idx].right, hitboxes.enemy_box[enemy_idx].top - 10);
    
                brush = CreateSolidBrush(RGB(255, 20, 20));
    
                SelectObject(hdc, brush);
    
                if (enemy_idx == FIRST_ENEMY) {
                    Rectangle(hdc, hitboxes.enemy_box[FIRST_ENEMY].left, hitboxes.enemy_box[FIRST_ENEMY].top - 20, hitboxes.enemy_box[FIRST_ENEMY].left + 200 * hitboxes.enemy_health[FIRST_ENEMY], hitboxes.enemy_box[FIRST_ENEMY].top - 10);
                }
                else
                    Rectangle(hdc, hitboxes.enemy_box[enemy_idx].left, hitboxes.enemy_box[enemy_idx].top - 20, hitboxes.enemy_box[enemy_idx].left + 120 * hitboxes.enemy_health[enemy_idx], hitboxes.enemy_box[enemy_idx].top - 10);
            }
        }
    }



    void pre_render::Draw(HDC hdc) {
        . . .
    
    
        DrawHealthBar(hdc, LOCAL_PLAYER);
        for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
            DrawHealthBar(hdc, ENEMY_PLAYER, b);
    
        }
    
        . . .
    }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
    
            render.Draw(hdc);
    
            EndPaint(hWnd, &ps);
        }






































Добавил анимацию главного героя при ходьбе и при атаке в case WM_TIMER:<br>

       . . .
            if (input_system.right_move) {
                if (animationfix.active_index == 0) {
                    animationfix.start_point = true;
                    animationfix.end_point = false;
                }

                if (animationfix.active_index >= 2) {
                    animationfix.start_point = false;
                    animationfix.end_point = true;
                }

                animationfix.setup();
            }
            else if (input_system.left_move) {
                if (animationfix.active_index == 0) {
                    animationfix.start_point = true;
                    animationfix.end_point = false;
                }

                if (animationfix.active_index >= 2) {
                    animationfix.start_point = false;
                    animationfix.end_point = true;
                }

                animationfix.setup();
            }
            else if (input_system.attacked2) {
                animationfix.start_attack = true;
              
            }	
            else {
                animationfix.reset();
            }

                   if (animationfix.start_attack) {
     
                animationfix.active_index_at++;


               if (animationfix.active_index_at > 2) {
                    animationfix.start_attack = false;
                    animationfix.active_index_at = 0;
               }
            }

       . . .

    void animation::setup() {
        animationfix.redraw_window = true;
    
        if (start_point) 
            animationfix.active_index++;
        else 
            animationfix.active_index--;
         
        
        
    }



    void pre_render::Draw(HDC hdc) {
    
    . . .  
    
    if (!animationfix.start_attack) 
            render.RenderMainCharacter(hdc, hitboxes.local_box.left / PIXEL, hitboxes.local_box.top / PIXEL + 9, animationfix.active_index);
        else
            render.RenderMainCharacterAttack(hdc, hitboxes.local_box.left / PIXEL, hitboxes.local_box.top / PIXEL - 6, animationfix.active_index_at);
    
    . . . 
    
    }

Так же и с первым врагом (слаймом)<br>


    void pre_render::Draw(HDC hdc) {
    . . .
      if (!hitboxes.enemy_attacked[FIRST_ENEMY])
            render.Slime(hdc, hitboxes.enemy_box[FIRST_ENEMY].left / PIXELB, hitboxes.enemy_box[FIRST_ENEMY].top / PIXELB);
        else 
            render.SlimeAttack(hdc, hitboxes.enemy_box[FIRST_ENEMY].left / PIXELB, hitboxes.enemy_box[FIRST_ENEMY].top / PIXELB);
    . . .
    } 



Файл animation.h<br>

    class animation {
    public:
    	void setup();
    	int active_index = 0;
    	int active_index_at = 0;
    	int attack_timer = 0;
    	bool end_point = false;
    	bool start_point = false;
    	bool redraw_window = false;
    
    	bool start_attack = false;
    	bool end_attack = false;
    
    	void reset() {
    		redraw_window = false;
    	}
    };

    extern animation animationfix;












Иллюстрация всего выше перечисленного

![image](https://github.com/user-attachments/assets/d277895a-be81-435c-8fe6-fabb62602428)

 

Если враг атакует:

![image](https://github.com/user-attachments/assets/5a93effe-8c17-4f63-94bb-d0e0790b7100)



Если главный герой атакует:

![image](https://github.com/user-attachments/assets/ee8fae45-a195-4697-b3cf-8a01e6be2f9e)

 

Если враг повержен:
 
![image](https://github.com/user-attachments/assets/311de390-7266-4bb9-be27-bbf5345f82b9)



Лечение игрока: <br>
Если у главного героя здоровья меньше полного, то найдя флягу, подойдя к ней и нажав клавишу “q”, главный герой сможет себе полностью восстановить здоровье.<br>

Код hitboxes.cpp<br>

    . . .
    
    for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++) {
            Physics(FLASK, i);
    
            flask_x[FIRST_FLASK] = 1100 - world.player_location_x;
    
            flask_x[SECOND_FLASK] = 2000 - world.player_location_x;
    
            heal_flask[i] = { 200 + flask_x[i], 25 + flask_y[i], 270 + flask_x[i], 100 + flask_y[i] };
    
        }
    . . .
    
    
    void hitboxes_t::Physics(int idx_player, int dop_idx) {
    
    . . .
    
        else if (idx_player == FLASK) {
            if (flags_flasks[ON_AIR][dop_idx] && !flags_flasks[ON_GROUND][dop_idx]) {
                flask_y[dop_idx] += 50;
            }
        }
    . . .
    
    }
    
    void hitboxes_t::ConditionsSet(const char* steps, int idx_player, int idx_enemy) {
    . . .
    
           else if (idx_player == FLASK) {
            if (steps == "touch_floor") {
                flags_flasks[ON_GROUND][idx_enemy] = true;
                flags_flasks[ON_AIR][idx_enemy] = false;
            }
            else if (steps == "air") {
                flags_flasks[ON_AIR][idx_enemy] = true;
                flags_flasks[ON_GROUND][idx_enemy] = false;
            }
            else if (steps == "defeated") {
                flags_flasks[ON_AIR][idx_enemy] = true;
                flags_flasks[ON_GROUND][idx_enemy] = false;
            }
            else {
                flags_flasks[ON_AIR][idx_enemy] = true;
                flags_flasks[ON_GROUND][idx_enemy] = false;
            }
        }
    
    . . .
    }
    
    
    
    void hitboxes_t::PropsHitboxes() { 
    . . .
    
            for (int b = FIRST_FLASK; b < MAXIMUM_FLASK; b++) {
                if (heal_flask[b].bottom == platform_box[FIRST_PLATFORM].top) {
                    flask_in_platform[FIRST_PLATFORM][b] = true;
                }
                else if (heal_flask[b].bottom == platform_box[SECOND_PLATFORM].top) {
                    flask_in_platform[SECOND_PLATFORM][b] = true;
                }
                else if (heal_flask[b].bottom == platform_box[THIRD_PLATFORM].top) {
                    flask_in_platform[THIRD_PLATFORM][b] = true;
                }
                else if (heal_flask[b].bottom == platform_box[FOUR_PLATORM].top) {
                    flask_in_platform[FOUR_PLATORM][b] = true;
                }
                else {
                    flask_in_platform[i][b] = false;
                }
            }
    
    
    
    
    
             for (int b = FIRST_FLASK; b < MAXIMUM_FLASK; b++) {
                if (flask_in_platform[i][b]) {
    
                    if ((heal_flask[b].right < platform_box[i].left || heal_flask[b].left > platform_box[i].right)) {
                        hitboxes.ConditionsSet("air", FLASK, b);
                    }
                    else {
                        hitboxes.ConditionsSet("touch_floor", FLASK, b);
                    }
                }
            }
    
    . . .
    
    }
    
    void hitboxes_t::LocalHealth() {
    
    . . .
    
         for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++) {
    
            if (local_box.bottom == heal_flask[i].bottom
                && local_box.right > heal_flask[i].left
                && local_box.left < heal_flask[i].right) {
    
                if (input_system.q_pressed) {
                    if (local_health < 220) {
                        local_health = 220;
                       
                        hitboxes.ConditionsSet("defeated", FLASK, i);
                    }
                }
            }
    
        }
    
    . . .
    
    }























a ray of hope.cpp<br>


    case WM_KEYDOWN:
            switch (wParam) {
            
            . . .        
    
            case 0x51: //q
                if (!input_system.blocked) {
                    input_system.q_pressed = true;
                }
                break;
            }
            break;
    
    
    
    void pre_render::Draw(HDC hdc) {
    
       . . .
    
        render.HealFlask(hdc, hitboxes.heal_flask[FIRST_FLASK].left / PIXELB, hitboxes.heal_flask[FIRST_FLASK].top / PIXELB);
    
        render.HealFlask(hdc, hitboxes.heal_flask[SECOND_FLASK].left / PIXELB, hitboxes.heal_flask[SECOND_FLASK].top / PIXELB);
    
    }

Иллюстрация фляг:

![image](https://github.com/user-attachments/assets/60c1257d-bf4d-4faf-b851-9498f00634aa)





Иллюстрация фляг (Если подобрал):

![image](https://github.com/user-attachments/assets/1a562c22-0ae8-4c01-80d8-69683e01d031)

 
Здоровье*<br>

Фляга изчезает, падая вниз.



