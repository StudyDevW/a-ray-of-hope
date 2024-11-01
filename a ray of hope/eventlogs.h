#pragma once
#include <vector>

#include <string>
#include <wtypes.h>
#include <algorithm>
#include <thread>



class CMessage
{
public:
	CMessage(const wchar_t* str, float time)
	{
		this->str = str;
		this->time = (float)(clock() / (float)1000.f);
		alpha = 255.f;
	}
	const wchar_t* str;
	float time;
	float alpha;

	void reset() {
		this->str = L"";
		this->time = 0.f;
		alpha = 255.f;
	}

};

class event_logs {
public:




	void CreateLog(const wchar_t* text, int idx = 0);
	void OnUpdate();
	bool reset[50][10];
	int timer[50][10];
	RECT form[50];
	bool setuped[50][10];
	bool anim_i = false;
	bool anim_d = false;
	int last_y = 0;
	bool add_last_y = true;
	bool up = true;
	int idx_ = 0;
	int x, y;
	int idx_player_ = 0;
	const wchar_t* text_s;
	bool show = true;

	std::vector<CMessage> messages;

	void Draw(HDC hdc)
	{
		constexpr float showtime = 5.f;
		constexpr float animation_time = 0.250f;

		if (messages.empty())
			return;

		while (messages.size() > 10)
			messages.erase(messages.begin());

		static const auto easeOutQuad = [](float x) {
			return 1 - (1 - x) * (1 - x);
		};

		for (int i = messages.size() - 1; i >= 0; i--)
		{
		    float in_anim = std::clamp((((float)(clock() / (float)1000.f)) - messages[i].time) / animation_time, 0.01f, 1.f);
		    float out_anim = std::clamp(((((float)(clock() / (float)1000.f)) - messages[i].time) - showtime) / animation_time, 0.01f, FLT_MAX);
			messages[i].alpha = in_anim * (1.f - out_anim) * 255.f;
			if (out_anim > 1.f)
				messages[i].alpha = 0.f;

			if (in_anim > 1.f) 
				messages[i].alpha = 255.f;	
			in_anim = easeOutQuad(in_anim);
			out_anim = easeOutQuad(out_anim);

			if (messages[i].alpha > 0.f) {
				const float x_position = in_anim * 5.f - out_anim * 5.f;
				const float y_position = 5.f + (55.f * i);

				HBRUSH hBrush;
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				SelectObject(hdc, hBrush);
				RECT rect = { (int)x_position,(int)y_position, (int)x_position + 250, (int)y_position + 40 };

				Rectangle(hdc, (int)x_position, (int)y_position, (int)x_position + 250, (int)y_position + 40);

			    DrawText(hdc, messages[i].str, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				DeleteObject(hBrush);

			}
	
		}
		for (int i = messages.size() - 1; i >= 0; i--) {
			if (messages[i].alpha <= 0.f) {		
				messages.erase(messages.begin() + i);
				break;
			}
		}
	}

};



