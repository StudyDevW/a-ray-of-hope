#include "hitboxes.h"
#include "world.h"
#include "input_controls.h"
#include "interface.h"
#include "eventlogs.h"
#include "inventory.h"

extern event_logs eventlog;
world_scene world;

void hitboxes_t::OnUpdate() {
    SetupLevels(hitboxes.active_level);
}

void hitboxes_t::SetupLevels(int level) {
    CharacterHitboxes(level);
    EnemyHitboxes(level);
    EngageEnemy(level);
    PropsHitboxes(level);
    
    SellerCheck(FIRST_NPC);
}

void hitboxes_t::SellerCheck(int index_npc) {
    if (local_box.right > npc_box[index_npc].left
        && local_box.left < npc_box[index_npc].right) {
        in_seller_interface = true;
    }
    else {
        in_seller_interface = false;
    }
}

void hitboxes_t::EngageEnemy(int level) {

    if (local_player.is_alive() && level == 0) {
        CreateEngageEnemy(POST_FIVE_PLATORM, SECOND_ENEMY, 150, 300);
    }
}



bool hitboxes_t::CheckAreaOutline(int index_area, int enemy_idx) {


    if (hitboxes.enemy_box[enemy_idx].left < hitboxes.enemy_box_engage[index_area].left
        || hitboxes.enemy_box[enemy_idx].right > hitboxes.enemy_box_engage[index_area].right) {
        return true;
    }
    else 
        return false;
}

bool hitboxes_t::LocalInEnemyArea(int index_area) {
    if (hitboxes.local_box.right > hitboxes.enemy_box_engage[index_area].left
        && hitboxes.local_box.left < hitboxes.enemy_box_engage[index_area].right) {
        return true;
    }
    else
        return false;
}

void hitboxes_t::PreEngage(int index_area, int index_enemy, int space_x, int space_y) {

    if (enemy_engage_active[index_enemy]) {
        OpenEnemyArea(index_area);
        SetEnemySpeed(index_enemy, 2);
    }
    else if (!enemy_player->is_alive(index_enemy)) {
        OpenEnemyArea(index_area);
    }
    else {
        CreateEnemyArea(index_area, space_x, space_y);
        SetEnemySpeed(index_enemy, 3);
    }
}

void hitboxes_t::EngageLevel(int index_area, int index_enemy) {
    if (LocalInEnemyArea(index_area)) {
        if ((enemy_view_side[index_enemy] == ENEMY_VIEW_LEFT) && hitboxes.enemy_box[index_enemy].left > hitboxes.local_box.right) {


            enemy_engage_procents[index_enemy] += 1;

            if (enemy_engage_procents[index_enemy] == 100) {
                enemy_engage_active[index_enemy] = true;
            }

        }
        else if ((enemy_view_side[index_enemy] == ENEMY_VIEW_RIGHT) && hitboxes.enemy_box[index_enemy].right < hitboxes.local_box.left) {


            enemy_engage_procents[index_enemy] += 1;

            if (enemy_engage_procents[index_enemy] == 100) {
                enemy_engage_active[index_enemy] = true;
            }
        }


    }
    else {
        if (!enemy_engage_active[index_enemy]) {
            enemy_engage_procents[index_enemy] -= 1;
            if (enemy_engage_procents[index_enemy] <= 0) {
                enemy_engage_procents[index_enemy] = 0;
            }
        }
    }
}

void hitboxes_t::EnemyStun(int index_enemy) {
    static int timer = 0;

    enemy_move_x[index_enemy] = last_enemy_move_x[index_enemy];

    timer++;

    if (timer > 200) {
        enemy_out_stun[index_enemy] = true;
        enemy_in_stun[index_enemy] = false;
        timer = 0;
        return;
    }
    else {
        enemy_out_stun[index_enemy] = false;
    }
} 

void hitboxes_t::EngageMovement(int index_area, int index_enemy) {
    if (!CheckAreaOutline(index_area, index_enemy) && !enemy_engage_active[index_enemy]) {
        if (!enemy_move_swap[index_enemy]) {
            enemy_move_x[index_enemy] += GetEnemySpeed(index_enemy);
            enemy_view_side[index_enemy] = ENEMY_VIEW_RIGHT;
        }
        else {
            enemy_move_x[index_enemy] -= GetEnemySpeed(index_enemy);
            enemy_view_side[index_enemy] = ENEMY_VIEW_LEFT;
        }

        enemy_move_y[index_enemy] = 0;
    }
    else if (CheckAreaOutline(index_area, index_enemy) && !enemy_engage_active[index_enemy]) {
        enemy_move_swap[index_enemy] = !enemy_move_swap[index_enemy];


        if (!enemy_move_swap[index_enemy]) {
            enemy_move_x[index_enemy] += GetEnemySpeed(index_enemy);
        }
        else {
            enemy_move_x[index_enemy] -= GetEnemySpeed(index_enemy);
        }

        enemy_move_y[index_enemy] = 0;
    }
    else if (enemy_engage_active[index_enemy] ) {
      /*  if (hitboxes.enemy_box[index_enemy].left > hitboxes.local_box.right) {
            if (input_system.w_pressed && !(enemy_in_stun[index_enemy] && !enemy_out_stun[index_enemy]) &&
                (local_attack_box.right > enemy_box[index_enemy].left
                && local_attack_box.left < enemy_box[index_enemy].right)) {
                enemy_move_x[index_enemy] += 100;
                enemy_move_y[index_enemy] -= 200;
                enemy_in_stun[index_enemy] = true;
                enemy_out_stun[index_enemy] = false;
            }
            else if (enemy_in_stun[index_enemy] && !enemy_out_stun[index_enemy]) {
                EnemyStun(index_enemy);
            }
            else {
                enemy_move_x[index_enemy] -= GetEnemySpeed(index_enemy);
            }
        }
        else*/ 
        if (hitboxes.enemy_box[index_enemy].left > hitboxes.local_box.right) {
            enemy_move_x[index_enemy] -= GetEnemySpeed(index_enemy);
        }
        else if (hitboxes.enemy_box[index_enemy].right < hitboxes.local_box.left) {
           
            enemy_move_x[index_enemy] += GetEnemySpeed(index_enemy);
        }

  

        last_enemy_move_x[index_enemy] = enemy_move_x[index_enemy];
    }
}

void hitboxes_t::CreateEngageEnemy(int index_area, int index_enemy, int space_x, int space_y) {
    PreEngage(index_area, index_enemy, space_x, space_y);

    EngageLevel(index_area, index_enemy);

    EngageMovement(index_area, index_enemy);
}


void hitboxes_t::CreateEnemyArea(int index_area, int space_x, int space_y) {
    hitboxes.enemy_box_engage[index_area] = {
           hitboxes.platform_box[MAIN_WORLD][index_area].left + space_x,
           hitboxes.platform_box[MAIN_WORLD][index_area].top - space_y,
           hitboxes.platform_box[MAIN_WORLD][index_area].right - space_x,
           hitboxes.platform_box[MAIN_WORLD][index_area].bottom + 10,
    };
}

void hitboxes_t::OpenEnemyArea(int index_area) {
    hitboxes.enemy_box_engage[index_area] = { 0, 0, 0, 0 };
}

void hitboxes_t::CreatePlatform(int index_platform, size_prop prop) {
    hitboxes.platform_box[MAIN_WORLD][index_platform] = {
        prop.x - world.player_location_x + (world.player_inverted_x - 100),
        prop.y + world.player_location_y,
        (prop.x + prop.width) - world.player_location_x + world.player_inverted_x,
        (prop.y + prop.height) + world.player_location_y
    };
}

void hitboxes_t::CreateLadder(int index_ladder, size_prop prop) {
    hitboxes.ladder_box[index_ladder] = {
        prop.x - world.player_location_x + (world.player_inverted_x - 100),
        prop.y + world.player_location_y,
        (prop.x + prop.width) - world.player_location_x + world.player_inverted_x,
        (prop.y + prop.height) + world.player_location_y
    };
}

void hitboxes_t::CreateEnemy(int index_enemy, size_prop enemy_size) {

    enemy_x[index_enemy] = enemy_size.x - world.player_location_x + (world.player_inverted_x - 100) + enemy_move_x[index_enemy];

    enemy_box[index_enemy] = {
        enemy_x[index_enemy], 
        enemy_y[index_enemy] - 15 + enemy_move_y[index_enemy],
        enemy_x[index_enemy] + enemy_size.width,
        enemy_y[index_enemy] + enemy_size.height + enemy_move_y[index_enemy]
    };
}

void hitboxes_t::CreateNPC(int index_npc, size_prop npc_size) {

    npc_x[index_npc] = npc_size.x - world.player_location_x + (world.player_inverted_x - 100);

    npc_box[index_npc] = {
        npc_x[index_npc],
        npc_y[index_npc] - 15,
        npc_x[index_npc] + npc_size.width,
        npc_y[index_npc] + npc_size.height
    };
}

void hitboxes_t::CreateFlask(int index_flask, size_prop flask_size) {

    flask_x[index_flask] = flask_size.x + 200 - world.player_location_x + (world.player_inverted_x) ;

    heal_flask[index_flask] = {
        flask_x[index_flask],
        25 + flask_y[index_flask],
        flask_x[index_flask] + 70,
        flask_y[index_flask] + 100
    };
}

void hitboxes_t::EnemyHitboxes(int level) {

    if (level == TRAINING_LEVEL) {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {
            EnemyHealth(i);
            Physics(ENEMY_PLAYER, i);
        }

        CreateEnemy(FIRST_ENEMY, size_prop(3200, 0, 200, 100));

        CreateEnemy(SECOND_ENEMY, size_prop(5500, 0, 200, 100));

        for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++)
            Physics(FLASK, i);


        CreateFlask(FIRST_FLASK, size_prop(2200, 0));

        for (int i = FIRST_NPC; i < MAXIMUM_NPC; i++)
            Physics(NPC, i);

        CreateNPC(FIRST_NPC, size_prop(4500, 0, 200, 190));
    }


   
}


void hitboxes_t::PropsHitboxes(int level) {



    if (level == TRAINING_LEVEL) {

        for (int i = 0; i < MAXIMUM_PLATFORMS; i++)
            check_touch_floor[i] = false;

        for (int i = 0; i < MAXIMUM_LADDERS; i++)
            check_ladder[i] = false;

        CreatePlatform((int)FIRST_PLATFORM, size_prop(0, 400, 2000, 50));
        CreateLadder((int)FIRST_LADDER, size_prop(2000, 200, 50, 200));
        CreatePlatform((int)SECOND_PLATFORM, size_prop(2000, 200, 1000, 50));
        CreatePlatform((int)THIRD_PLATFORM, size_prop(3000, 200, 950, 50));
        CreateLadder((int)SECOND_LADDER, size_prop(3900, 200, 50, 100));
        CreatePlatform((int)FOUR_PLATORM, size_prop(4000, 300, 950, 50));
        CreatePlatform((int)POST_FIVE_PLATORM, size_prop(5000, 300, 1000, 50));
        CreatePlatform((int)FIVE_PLATFORM, size_prop(6000, 300, 1000, 50));

        hitboxes.reset_platform = {
             0, 1500 + world.player_location_y, world.world_size_x, 1600 + world.player_location_y
        };

        hitboxes.ConditionsSet("air");

        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++)
            hitboxes.ConditionsSet("air", ENEMY_PLAYER, i);

        for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++)
            hitboxes.ConditionsSet("air", FLASK, i);

        for (int i = FIRST_NPC; i < MAXIMUM_NPC; i++)
            hitboxes.ConditionsSet("air", NPC, i);

        CheckLadder();

        CheckPlatform();
    }
}






void hitboxes_t::Init(HWND hwnd) {
    world.setup_location_world(hwnd);
    RECT rectwindow;
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
            enemy_y[i] += 10;

        for (int i = FIRST_NPC; i < MAXIMUM_NPC; i++)
            npc_y[i] += 10;

        for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++)
            flask_y[i] += 10;
        
        y += 10;
        world.player_location_y += 10;
        resize_y_pos = false;
    }
    else if (!resize_y_pos && resize_y_neg) {
        for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) 
            enemy_y[i] -= 10;
        
        for (int i = FIRST_NPC; i < MAXIMUM_NPC; i++)
            npc_y[i] -= 10;

        for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++)
            flask_y[i] -= 10;

        y -= 10;
        world.player_location_y -= 10;
        resize_y_neg = false;
    }

    if (input_system.left_side_move) {
        if (world.player_inverted_x < (rectwindow.right) - 450)
            world.player_inverted_x += 5;
    }
    else {
        if (world.player_inverted_x > 100) {
            world.player_inverted_x -= 5;
        }
    }


    rectw_right = (rectwindow.right);
}

void hitboxes_t::CharacterHitboxes(int level) {
    Physics(LOCAL_PLAYER);


    local_box = { 100 + world.player_inverted_x, 100 + y, 220 + world.player_inverted_x, 300 + y };
    
 
    AttackBox();
  
    LocalHealth();
}



void hitboxes_t::LocalHealth() {
    for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++) {

        enemy_attacked[i] = false;

        if (local_box.bottom == enemy_box[i].bottom
            && local_box.right > enemy_box[i].left
            && local_box.left < enemy_box[i].right && enemy_engage_active[i]) {
            enemy_attacked[i] = true;
            local_health -= 0.01f;
        }
    }

    for (int i = FIRST_FLASK; i < MAXIMUM_FLASK; i++) {

 
        if (local_box.bottom == heal_flask[i].bottom
            && local_box.right > heal_flask[i].left
            && local_box.left < heal_flask[i].right) {
            flask_equip = true;

            if (input_system.q_pressed) {
                flask_count_item++;
               
                if (heal_flask[i].bottom == reset_platform.top) 
                    hitboxes.ConditionsSet("touch_floor", FLASK, i);
                else 
                    hitboxes.ConditionsSet("defeated", FLASK, i);
                

                inventory.CreateItem(L"‘л€га", flask_count_item, (int)items_c::FIRST_ITEM);

                eventlog.CreateLog(L"ѕодобрана фл€га");

                if (hitboxes.active_level == 0) {
                    eventlog.CreateLog(L"ќткройте инвентарь клавишей i");
                }
    
                flask_looted[i] = true;
            }
        }
    }


    if (local_health <= 0.0f) {
        AllReset();
    }
    
}

void hitboxes_t::EnemyHealth(int index_enemy) {
    if (input_system.left_side_move) {
        if (local_attack_box.left > enemy_box[index_enemy].left
            && local_attack_box.right < enemy_box[index_enemy].right) {
            if (input_system.attacked) {

                if (hitboxes.active_level == 0 && index_enemy == FIRST_ENEMY)
                    damaged_enemy_tr = true;

                enemy_engage_procents[index_enemy] = 100;
                enemy_engage_active[index_enemy] = true;
                hitboxes.enemy_health[index_enemy] -= 0.1f;
            }
        }
    }
    else if (input_system.right_side_move) {
        if (local_attack_box.right > enemy_box[index_enemy].left
            && local_attack_box.left < enemy_box[index_enemy].right) {
            if (input_system.attacked) {

                if (hitboxes.active_level == 0 && index_enemy == FIRST_ENEMY)
                    damaged_enemy_tr = true;

                enemy_engage_procents[index_enemy] = 100;
                enemy_engage_active[index_enemy] = true;
                hitboxes.enemy_health[index_enemy] -= 0.1f;
            }
        }
    }

    static bool add_val = false;

    if (hitboxes.enemy_health[index_enemy] < 0.0f) {

        if (index_enemy == FIRST_ENEMY) {
            enemy_dead_tr = true;
        }

        if (enemy_box[index_enemy].bottom == reset_platform.top) {
            hitboxes.ConditionsSet("touch_floor", ENEMY_PLAYER, index_enemy);
          

        }
        else {
            hitboxes.ConditionsSet("defeated", ENEMY_PLAYER, index_enemy);
   
        }
        defeated_enemy[index_enemy] = true;

    }

 

}

void hitboxes_t::AttackBox() {
    
    if (input_system.left_side_move) {
        local_attack_box = { local_box.right, local_box.top, local_box.left - 120, local_box.bottom };
    }
    else if (input_system.right_side_move) {
        local_attack_box = { local_box.left, local_box.top, local_box.right + 120, local_box.bottom };
    }
}




void hitboxes_t::Physics(int idx_player, int dop_idx) {

    if (idx_player == ENEMY_PLAYER) {
        if (flags_enemies[ON_AIR][dop_idx] && !flags_enemies[ON_GROUND][dop_idx]) {
            enemy_y[dop_idx] += 10;
        }

        if (flags_enemies[ON_JUMP][dop_idx]) {
            enemy_y[dop_idx] -= 200;
        }
    }
    else if (idx_player == FLASK) {
        if (flags_flasks[ON_AIR][dop_idx] && !flags_flasks[ON_GROUND][dop_idx]) {
            flask_y[dop_idx] += 10;
        }
    }
    else if (idx_player == NPC) {
        if (flags_npc[ON_AIR][dop_idx] && !flags_npc[ON_GROUND][dop_idx]) {
            npc_y[dop_idx] += 10;
        }
    }
    else {
        if (flags[ON_AIR] && !flags[ON_GROUND] && !flags[ON_LADDER]) {
            y += 10;
        }

        if (flags[ON_JUMP]) {
            y -= 200;
        }
    }
}

void hitboxes_t::ConditionsSet(const char* steps, int idx_player, int idx_enemy) {
    if (idx_player == ENEMY_PLAYER) {
        if (steps == "touch_floor") {
            flags_enemies[ON_GROUND][idx_enemy] = true;
            flags_enemies[ON_AIR][idx_enemy] = false;
            flags_enemies[ON_JUMP][idx_enemy] = false;
        }
        else if (steps == "air") {
            flags_enemies[ON_AIR][idx_enemy] = true;
            flags_enemies[ON_GROUND][idx_enemy] = false;
            flags_enemies[ON_JUMP][idx_enemy] = false;
        }
        else if (steps == "jump") {
            flags_enemies[ON_AIR][idx_enemy] = true;
            flags_enemies[ON_GROUND][idx_enemy] = false;
            flags_enemies[ON_JUMP][idx_enemy] = true;
        }
        else if (steps == "defeated") {
            flags_enemies[ON_AIR][idx_enemy] = true;
            flags_enemies[ON_GROUND][idx_enemy] = false;
            flags_enemies[ON_JUMP][idx_enemy] = false;
        }
        else {
            flags_enemies[ON_AIR][idx_enemy] = true;
            flags_enemies[ON_GROUND][idx_enemy] = false;
            flags_enemies[ON_JUMP][idx_enemy] = false;
        }
    }
    else if (idx_player == NPC) {
        if (steps == "touch_floor") {
            flags_npc[ON_GROUND][idx_enemy] = true;
            flags_npc[ON_AIR][idx_enemy] = false;
            flags_npc[ON_JUMP][idx_enemy] = false;
        }
        else if (steps == "air") {
            flags_npc[ON_AIR][idx_enemy] = true;
            flags_npc[ON_GROUND][idx_enemy] = false;
            flags_npc[ON_JUMP][idx_enemy] = false;
        }
        else if (steps == "defeated") {
            flags_npc[ON_AIR][idx_enemy] = true;
            flags_npc[ON_GROUND][idx_enemy] = false;
            flags_npc[ON_JUMP][idx_enemy] = false;
        }
        else {
            flags_npc[ON_AIR][idx_enemy] = true;
            flags_npc[ON_GROUND][idx_enemy] = false;
            flags_npc[ON_JUMP][idx_enemy] = false;
        }
    }
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
    else {
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
        else {
            flags[ON_AIR] = true;
            flags[ON_GROUND] = false;
            flags[ON_JUMP] = false;
        }
    }
}




void hitboxes_t::CheckLadder() {
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
            check_ladder[i] = true;
            hitboxes.ConditionsSet("ladder");

            if (local_box.bottom > ladder_box[i].top) {
                input_system.blocked = true;
                y -= 25;
            }
            else {
                input_system.blocked = false;
            }
        }
    }
}



void hitboxes_t::CheckPlatform() {

    for (int i = FIRST_PLATFORM; i < MAXIMUM_PLATFORMS; i++) {


        for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
            if (enemy_box[b].bottom == platform_box[MAIN_WORLD][i].top) {
                enemy_in_platform[i][b] = true;
            }
         
            else {
                enemy_in_platform[i][b] = false;
            }
        }

        for (int w = FIRST_FLASK; w < MAXIMUM_FLASK; w++) {
            if (heal_flask[w].bottom == platform_box[MAIN_WORLD][FIRST_PLATFORM].top) {
                flask_in_platform[FIRST_PLATFORM][w] = true;
            }
            else if (heal_flask[w].bottom == platform_box[MAIN_WORLD][SECOND_PLATFORM].top) {
                flask_in_platform[SECOND_PLATFORM][w] = true;
            }
            else if (heal_flask[w].bottom == platform_box[MAIN_WORLD][THIRD_PLATFORM].top) {
                flask_in_platform[THIRD_PLATFORM][w] = true;
            }
            else if (heal_flask[w].bottom == platform_box[MAIN_WORLD][FOUR_PLATORM].top) {
                flask_in_platform[FOUR_PLATORM][w] = true;
            }
            else {
                flask_in_platform[i][w] = false;
            }
        }

        for (int a = FIRST_NPC; a < MAXIMUM_NPC; a++) {
            if (npc_box[a].bottom == platform_box[MAIN_WORLD][FIRST_PLATFORM].top) {
                npc_in_platform[FIRST_PLATFORM][a] = true;
            }
            else if (npc_box[a].bottom == platform_box[MAIN_WORLD][SECOND_PLATFORM].top) {
                npc_in_platform[SECOND_PLATFORM][a] = true;
            }
            else if (npc_box[a].bottom == platform_box[MAIN_WORLD][THIRD_PLATFORM].top) {
                npc_in_platform[THIRD_PLATFORM][a] = true;
            }
            else if (npc_box[a].bottom == platform_box[MAIN_WORLD][FOUR_PLATORM].top) {
                npc_in_platform[FOUR_PLATORM][a] = true;
            }
            else {
                npc_in_platform[i][a] = false;
            }
        }


        if (local_box.bottom == platform_box[MAIN_WORLD][i].top && !(local_box.right < platform_box[MAIN_WORLD][i].left || local_box.left > platform_box[MAIN_WORLD][i].right)) {
            if ((local_box.right < platform_box[MAIN_WORLD][i].left || local_box.left > platform_box[MAIN_WORLD][i].right))
                hitboxes.ConditionsSet("air");
            else if (input_system.jump)
                hitboxes.ConditionsSet("jump");
            else {
                hitboxes.ConditionsSet("touch_floor");
                check_touch_floor[i] = true;
            }


        }
        else if (local_box.bottom == reset_platform.top) {
            AllReset();
        }



        for (int j = FIRST_ENEMY; j < MAXIMUM_ENEMIES; j++) {
            if (enemy_in_platform[i][j]) {

                if ((enemy_box[j].right < platform_box[MAIN_WORLD][i].left || enemy_box[j].left > platform_box[MAIN_WORLD][i].right)) {
                    hitboxes.ConditionsSet("air", ENEMY_PLAYER, j);
                }
                else {
                    hitboxes.ConditionsSet("touch_floor", ENEMY_PLAYER, j);
                }
            }
        }

        for (int L = FIRST_NPC; L < MAXIMUM_NPC; L++) {
            if (npc_in_platform[i][L]) {

                if ((npc_box[L].right < platform_box[MAIN_WORLD][i].left || npc_box[L].left > platform_box[MAIN_WORLD][i].right)) {
                    hitboxes.ConditionsSet("air", NPC, L);
                }
                else {
                    hitboxes.ConditionsSet("touch_floor", NPC, L);
                }
            }
        }

        for (int b = FIRST_FLASK; b < MAXIMUM_FLASK; b++) {
            if (flask_in_platform[i][b]) {

                if ((heal_flask[b].right < platform_box[MAIN_WORLD][i].left || heal_flask[b].left > platform_box[MAIN_WORLD][i].right)) {
                    hitboxes.ConditionsSet("air", FLASK, b);
                }
                else {
                    hitboxes.ConditionsSet("touch_floor", FLASK, b);
                }
            }
        }
    }
}

void hitboxes_t::AllReset(bool death_screen) {

    //reset hp
    if (local_health < 1.f) {
        local_health = 1.f;
    }

    if (death_screen)
        interfaces.death_screen = true;

    for (int b = FIRST_ENEMY; b < MAXIMUM_ENEMIES; b++) {
        enemy_engage_procents[b] = -1;
        enemy_engage_active[b] = false;
        enemy_move_swap[b] = false;
        enemy_move_x[b] = 0;
        enemy_health[b] = 1.0;
        defeated_enemy[b] = false;
        enemy_y[b] = 0;
    }

    for (int k = FIRST_FLASK; k < MAXIMUM_FLASK; k++)
        flask_y[k] = 0;

    for (int i = FIRST_ENEMY; i < MAXIMUM_ENEMIES; i++)
        inventory.add_stop[i] = false;

    inventory.money = 0;

    x = 0;
    y = 0;
    world.player_location_x = 0;
    world.player_location_y = 0;
}