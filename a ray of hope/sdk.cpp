#include "sdk.h"
#include "hitboxes.h"


bool local_player_t::is_alive() {
	if ((hitboxes.local_health > 0.0f) && interfaces.in_game && !interfaces.death_screen)
		return true;
	else 
		return false;
}


bool player_t::is_alive(int index_enemy) {
	if (hitboxes.defeated_enemy[index_enemy])
		return false;

	return true;
}
