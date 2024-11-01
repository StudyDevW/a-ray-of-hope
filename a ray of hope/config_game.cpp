#include "input_controls.h"
#include "hitboxes.h"
#include "world.h"
#include "config_game.h"

#include "eventlogs.h"
extern event_logs eventlog;

extern world_scene world;

void config_game::OnUpdate() {
	for (int i = 1; i <= 101; i++) {

		if (config.pre_save[i]) {
			if (config.SaveGame(config.need_to_save[i]))
				config.saved[i] = true;
		}

		if (config.pre_load[i]) {
			if (config.LoadGame(config.need_to_load[i]))
				config.loaded[i] = true;
		}


		if (config.saved[i]) {
			input_system.escaped = false;
			config.reset_save(i);
		}

		if (config.loaded[i]) {
			input_system.escaped = false;
			config.reset_load(i);
		}
	}
}

bool config_game::SaveGame(std::string index_cfg) {
	FILE* fout;

	CreateDirectory((LPCWSTR)"c:\\Temp", NULL);

	fopen_s(&fout, index_cfg.c_str(), "wt");

	if (fout == NULL) {
		return false;
	}

	if (index_cfg == "c:\\Temp\\training_info.txt") {
		fprintf(fout, "%d \n", hitboxes.training_ended);
	}
	else {

		fprintf(fout, "%d \n", hitboxes.x);
		fprintf(fout, "%d \n", hitboxes.y);
		fprintf(fout, "%d \n", world.player_location_y);
		fprintf(fout, "%d \n", world.player_location_x);
		fprintf(fout, "%d \n", world.player_inverted_x);
		fprintf(fout, "%f \n", hitboxes.local_health);

		for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
			fprintf(fout, "%f \n", hitboxes.enemy_health[i]);
			fprintf(fout, "%d \n", hitboxes.enemy_x[i]);
			fprintf(fout, "%d \n", hitboxes.enemy_y[i]);
		}

		for (int b = FIRST_FLASK; b < MAXIMUM_FLASK; b++) {
			fprintf(fout, "%d \n", hitboxes.flask_x[b]);
			fprintf(fout, "%d \n", hitboxes.flask_y[b]);
		}
	}

	fclose(fout);

	if (index_cfg != "c:\\Temp\\training_info.txt") 
		eventlog.CreateLog(L"Игра сохранена", 0);

	return true;
}

bool config_game::LoadGame(std::string index_cfg) {
	FILE* fin;

	CreateDirectory((LPCWSTR)"c:\\Temp", NULL);

	fopen_s(&fin, index_cfg.c_str(), "rt");

	if (fin == NULL) {
		return false;
	}
	if (index_cfg == "c:\\Temp\\training_info.txt") {
		fscanf_s(fin, "%d", &hitboxes.training_ended);
	}
	else {
		fscanf_s(fin, "%d", &hitboxes.x);
		fscanf_s(fin, "%d", &hitboxes.y);
		fscanf_s(fin, "%d", &world.player_location_y);
		fscanf_s(fin, "%d", &world.player_location_x);
		fscanf_s(fin, "%d", &world.player_inverted_x);
		fscanf_s(fin, "%f", &hitboxes.local_health);

		for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
			fscanf_s(fin, "%f", &hitboxes.enemy_health[i]);
			fscanf_s(fin, "%d", &hitboxes.enemy_x[i]);
			fscanf_s(fin, "%d", &hitboxes.enemy_y[i]);
		}

		for (int b = FIRST_FLASK; b < MAXIMUM_FLASK; b++) {
			fscanf_s(fin, "%d", &hitboxes.flask_x[b]);
			fscanf_s(fin, "%d", &hitboxes.flask_y[b]);
		}
	}

	fclose(fin);
	if (index_cfg != "c:\\Temp\\training_info.txt")
		eventlog.CreateLog(L"Игра загружена", 0);
	return true;
}