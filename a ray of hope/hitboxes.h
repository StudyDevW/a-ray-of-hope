#pragma once
#include <wtypes.h>
#include "sdk.h"


enum flags_e {
	ON_GROUND,
	ON_AIR, 
	ON_JUMP, 
	ON_LADDER
};

enum platforms {
	FIRST_PLATFORM,
	SECOND_PLATFORM,
	THIRD_PLATFORM,
	FOUR_PLATORM,
	FIVE_PLATFORM,
	POST_FIVE_PLATORM,
	MAXIMUM_PLATFORMS
};

enum levels_setup {
	TRAINING_LEVEL,
	FIRST_LEVEL_SETUP
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
	ENEMY_PLAYER,
	FLASK,
	NPC
};

enum enemy_flags {
	FIRST_ENEMY,
	SECOND_ENEMY,
	THIRD_ENEMY,
	FOUR_ENEMY_EYE_STORM,
	MAXIMUM_ENEMIES
};

enum NPC_flags {
	FIRST_NPC,
	SECOND_NPC,
	THIRD_NPC,
	MAXIMUM_NPC
};

enum flask_flags {
	FIRST_FLASK,
	SECOND_FLASK,
	THIRD_FLASK,
	MAXIMUM_FLASK
};

enum stealth_flags {
	MAIN_WORLD,
	SECOND_WORLD,
	MAXIMUM_WORLDS
};

enum enemy_view {
	ENEMY_VIEW_RIGHT,
	ENEMY_VIEW_LEFT
};

class size_prop {
public:
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	size_prop(int _x, int _y, int _width, int _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}

	size_prop(int _x, int _y) {
		x = _x;
		y = _y;
		width = 0;
		height = 0;
	}

};


class hitboxes_t {
public:
	RECT local_box;
	RECT local_attack_box;
	RECT enemy_box[50];
	RECT enemy_box_engage[50];
	RECT npc_box[50];
	RECT heal_flask[50];
	RECT platform_box[3][50];
	RECT ladder_box[50];

	RECT reset_platform;
	int x;
	int y;
	int active_level = 0;
	bool training_ended = false;
	local_player_t local_player;
	player_t* enemy_player;
	bool check_touch_floor[50];
	bool check_ladder[50];
	bool flask_equip = false;
	bool damaged_enemy_tr = false;
	bool enemy_dead_tr = false;
	float local_health = 1.0f;
	float enemy_health[50] = { 1.0, 1.0, 1.0, 1.0 }; //HP!!!!!
	bool defeated_enemy[50];
	bool flask_looted[50];	
	int enemy_x[50];
	int npc_x[50];
	int npc_y[50];
	int flask_x[50];
	int flask_y[50];
	int enemy_y[50];
	bool flags[10];
	bool flags_enemies[10][50];
	bool flags_npc[10][50];
	bool enemy_move_swap[50];
	int enemy_move_speed[50];
	int enemy_move_x[50];
	int enemy_move_y[50];
	int last_enemy_move_x[50];
	bool flags_flasks[10][50];
	bool local_in_platform[50];
	bool enemy_in_platform[50][50];
	bool enemy_out_stun[50];
	bool in_seller_interface = false;
	bool enemy_in_stun[50];
	enemy_view enemy_view_side[50];
	int enemy_engage_procents[50];
	bool enemy_engage_active[50];
	bool flask_in_platform[50][50];
	bool npc_in_platform[50][50];
	bool enemy_attacked[50];
	bool local_in_ladder[50] ;
	float impulse = 100.f;
	float jump_duration = 0.1f;
	int flask_count_item = 0;
	int rectw_right;
	COLORREF prop_debug[50];
	COLORREF lad_debug[50];

	bool diagonal_move = false;
	bool in_swap = false;
	bool reversed;
	void OnUpdate();
	bool CheckDistanceToLocal(int index_area, int enemy_idx);
	bool LocalInEnemyArea(int index_area);
	void EngageEnemy(int level);

	bool CheckAreaOutline(int index_area, int enemy_idx = -1);

	void SetEnemySpeed(int index_enemy, int speed) {
		enemy_move_speed[index_enemy] = speed;
	}

	int GetEnemySpeed(int index_enemy) {
		return enemy_move_speed[index_enemy];
	}

	void ClearAllBoxes();



	void CreateEnemyArea(int index_area, int space_x, int space_y);

	void CreatePlatformOtherWorld(int index_platform, bool active);

	void Init(HWND hwnd);

	void CharacterHitboxes(int level);

	void Physics(int idx_player, int dop_idx = FIRST_ENEMY);

	void ConditionsSet(const char* steps, int idx_player = LOCAL_PLAYER, int idx_enemy = FIRST_ENEMY);

	void CreatePlatform(int index_platform, size_prop prop);

	void CreateEnemy(int index_platform, size_prop prop);

	void CreateNPC(int index_npc, size_prop npc_size);

	void CreateFlask(int index_flask, size_prop flask_size);

	void CreateLadder(int index_ladder, size_prop prop);

	void FindNewBox(RECT box, int platform_id);

	void PropsHitboxes(int level);

	void EnemyHitboxes(int level);

	void LocalHealth();

	void EnemyHealth(int index_enemy);

	void AttackBox();

	void EngageMovement(int index_area, int index_enemy);

	void CreateEngageEnemy(int index_area, int index_enemy, int space_x, int space_y);

	void CheckLadder();

	void CheckPlatform();

	void OpenEnemyArea(int index_area);

	void AllReset(bool death_screen = true);

	void PreEngage(int index_area, int index_enemy, int space_x, int space_y);

	void EngageLevel(int index_area, int index_enemy);

	void EnemyStun(int index_enemy);

	void SetupLevels(int level);

	void SellerCheck(int index_npc);
};



extern hitboxes_t hitboxes;