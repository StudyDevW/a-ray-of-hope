#pragma once
#include <cstdio>
#include <string.h>
#include <sstream>
#include "sdk.h"

class config_game {
private:
	local_player_t local_player;
public:
	bool SaveGame(std::string index_cfg);
	bool LoadGame(std::string index_cfg);
	void OnUpdate();
	const wchar_t* cfg_info = L"";
	int slots = 10;
	const wchar_t* named_slots[101];
	std::string need_to_save[101];
	std::string need_to_load[101];
	bool pre_save[101];
	bool saved[101];

	bool pre_load[101];
	bool loaded[101];

	void reset_save(int i) {
		pre_save[i] = false;
		saved[i] = false;
	}

	void reset_load(int i) {
		pre_load[i] = false;
		loaded[i] = false;
	}
};

extern config_game config;