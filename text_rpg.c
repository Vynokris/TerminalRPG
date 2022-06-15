#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


// -------------------- CONSOLE COLORS --------------------- //
#define C_DEFAULT "\x1B[0;24m" // Removes color and underline.
#define C_NO_COLOR "\x1B[0m"
#define C_NO_UNDERLINE "\x1B[24m"
#define C_BOLD "\x1B[1m"
#define C_UNDERLINE "\x1B[4m"
#define C_RED "\x1B[91m"
#define C_GREEN "\x1B[92m"
#define C_YELLOW "\x1B[93m"
#define C_GRAY "\033[90m"
#define C_MAGENTA "\033[95m"
#define C_CYAN "\033[96m"


// -------------------- MONSTER ATTACKS --------------------- //

// Base structure for the entry of a monster attack in the monster attacks book. Stores name and damage.
typedef struct AttackEntry {
    char name[50];
    int damage;
} AttackEntry;

// All different attack names.
typedef enum AttackNames {
    AT_NONE,
    AT_BITE,
    AT_FIREBREATH,
    AT_THUNDERFANGS,
    AT_SHARPGUST
} AttackNames;

// List of all the attacks' names and damages. Corresponds to the AttackNames enum.
AttackEntry AttackBook[] = {
    { "No spell assigned to this slot", 0},
    { "Bite", 7 },
    { "Fire Breath", 14 },
    { "Thunder fangs", 20 },
    { "Sharp gust", 27 },
};

// Number of different attacks.
int AttackCount = sizeof(AttackBook) / sizeof(AttackBook[0]);


// -------------------- MONSTERS --------------------- //

// Base structure the entry of a monster in the bestiary. Stores name and hp range.
typedef struct MonsterEntry {
    char name[50];
    int hp_range[2];
    AttackNames attacks[4];
} MonsterEntry;

// All possible monsters.
typedef enum MonsterNames {
    MT_HOUND,
    MT_SPIDER,
    MT_SKELETTON,
    MT_LOSTSOUL,
    MT_WICKEDGHOST,
    MT_HADES,
} MonsterNames;

// List of all the monsters' names and health range corresponding to the MonsterNames enum.
MonsterEntry Bestiary[] = {
    { "hound" ,          {10, 20}, { AT_BITE, AT_FIREBREATH, AT_THUNDERFANGS, AT_SHARPGUST } },
    { "massive spider" , {15, 25}, { AT_BITE, AT_FIREBREATH, AT_THUNDERFANGS, AT_SHARPGUST } },
    { "skeletton",       {20, 30}, { AT_BITE, AT_FIREBREATH, AT_THUNDERFANGS, AT_SHARPGUST } },
    { "lost soul",       {25, 35}, { AT_BITE, AT_FIREBREATH, AT_THUNDERFANGS, AT_SHARPGUST } },
    { "wicked ghost",    {30, 40}, { AT_BITE, AT_FIREBREATH, AT_THUNDERFANGS, AT_SHARPGUST } },
    // { "Hades, the ruler of the Underworld", {100, 100} }
};

// Number of monster types.
int MonsterCount = sizeof(Bestiary) / sizeof(Bestiary[0]);

// Base structure for monster occurences. Stores name id in the Bestiary, HP, max HP and spells.
typedef struct Monster {
    MonsterNames id;
    int hp;
    int max_hp;
    AttackNames attacks[4];
} Monster;


// -------------------- ITEMS --------------------- //

// Base structure for an item. Stores name, description, and effect.
typedef struct Item {
    char name[50];
    char description[200];
    char options[2][100];
    char outcome[2][50];
} Item;

// All the different item names.
typedef enum ItemNames {
    IT_POTION,
    IT_BOOK,
    IT_FOUNTAIN,
    IT_STATUE,
} ItemNames;

// Stores all the items of the game and their data.
Item ItemBook[] = {
    { "potion", "It looks like it could replenish some your health if you drank it.", { "Take the potion", "Leave the potion" }, { "potions++", "leave" } },
    { "dusty book", "It looks like it has been here forever.", { "Pick up the grimoire and skim through its ancient pages.", "Leave the book on the ground, fearing what knowledge it could hold." }, { "xp++", "leave" }},
    { "fountain", "The water isn't flowing anymore, but what is left in the bowl of the fountain is still clear.", { "Drink the fountain's water", "Turn back" }, { "hp++", "leave" } },
    { "ominous looking statue", "It seems to represent a man with goat horns.\nThe sculpture is holding a plate in both hands and has a knife tied around its neck.", { "Cut your finger and let the blood dop on the plate", "Leave this dangerous statue alone" }, { "max_hp++ && hp--", "leave" }},
};


// -------------------- NPCS --------------------- //

// Base structure for an npc. Stores name, description, dialogue, possible answers, reactions, and if the player has already talked to him or not.
typedef struct Npc {
    char name[50];
    char description[200];
    char dialogue[200];
    char possible_answers[3][200];
    char reactions[3][200];
    int  already_talked;
} Npc;

// All the different npc names.
typedef enum NpcNames {
    NPC_OLDMAN,
    NPC_CRYINGCHILD,
} NpcNames;

// Stores all the npcs in the game and their data.
Npc NpcBook[] = {
    { "an old man", 
      "Time has not been kind to him. His face distorted by age is a display of his wisdom.", 
      "I have seen many enter and not one ever came back. But you seem different... Young man, why would you enter this dark and cursed place?",
      { "The legends say the one who comes back will be covered in money and fame.", "I want to save someone I hold dear to my heart.", "That's none of your business!" },
      { "Hmmm... Well maybe you aren't so different from those other men.", "A noble goal indeed, but a tough challenge. May you come out victorious.", "Follow the path then, but don't say you weren't warned." },
      0,
    },
    { "a crying child",
      "She is sat there, weeping with her face in her hands. After a few seconds, you realize that she is not alive, but a soul.",
      "Snif... It's dark everywhere I don't know where to go! Mommy I'm scared where are you?",
      { "[Walk past the crying child and continue your journey]", "Hey it's fine don't worry. I'll help you find your way. Follow me, we're going to the same place.", "Stop crying! If you can't find your way, it's your problem, your mom isn't coming for you."},
      { "I'm all alone mommy come get me please!", "Oh really mister? I'll follow you then.", "Nooo mommy would never leave me! She will come to help me!" },
      0
    }
};


// -------------------- AREAS --------------------- //

// Base structure for an area. Stores description, monsters, items and npcs.
typedef struct Area
{
    char description[500];
    MonsterNames monsters[4];
    ItemNames items[4];
    NpcNames npcs[4];
} Area;

// Stores all the areas of the game and their data.
Area AreaBook[] = {
    { "You enter through the Gates of Hell.\nThe imposant doors close behind you with a sinister creak and you find yourself in complete darkness.\nYou wait for your eyes to get used to it and start your journey.", 
      { MT_HOUND, MT_SPIDER, MT_SKELETTON, MT_LOSTSOUL }, { IT_POTION, IT_BOOK, IT_FOUNTAIN, IT_STATUE }, { NPC_OLDMAN } 
    },
    { "In front of you the path leads to a large open cavern through which the river Stix flows.\nA small embarcation floats on the grey waters, moored to a dock.\nThere stands Charon the ferryman, who takes you across the Stix after you pay him with a gold coin.\nYou disembark and continue your journey along the path of Hell.",
      { MT_HOUND, MT_SPIDER, MT_SKELETTON, MT_LOSTSOUL }, { IT_POTION, IT_BOOK, IT_FOUNTAIN, IT_STATUE }, { NPC_CRYINGCHILD } 
    },
    { "In the distance, you notice Cerberus, the keeper of the underworld.\nYou are careful not to attract his attention as you walk past him and enter the Asphodel Fields.",
      { MT_HOUND, MT_SPIDER, MT_SKELETTON, MT_LOSTSOUL }, { IT_POTION, IT_BOOK, IT_FOUNTAIN, IT_STATUE }, { NPC_CRYINGCHILD } 
    },
    { "You arrive at a fork where the path splits into three.\nThere, three judges are seated, deciding meticulously of the path the souls should follow in function of their past lives.\nYou walk past the judges, and they don't try to stop you even though they can see you are alive.\nYou walk straight to to the third path, which leads to the Tartarus.",
      { MT_HOUND, MT_SPIDER, MT_SKELETTON, MT_LOSTSOUL }, { IT_POTION, IT_BOOK, IT_FOUNTAIN, IT_STATUE }, { NPC_CRYINGCHILD } 
    },
    { "Finally, the path you have been following for what feels like forever ends. You are in Tartarus, the darkest place in existence.",
      { MT_HADES }, { IT_POTION, IT_BOOK, IT_FOUNTAIN, IT_STATUE }, { NPC_CRYINGCHILD } 
    },
};


// -------------------- PLAYER SPELLS --------------------- //

// Base structure for the entry of a spell in the spellbook. Stores name and damage.
typedef struct SpellEntry {
    char name[50];
    int damage;
} SpellEntry;

// All different spell names.
typedef enum SpellNames {
    SP_NONE,
    SP_THUNDERBOLT,
    SP_FIREBLAST,
    SP_WHIRLPOOL,
    SP_EARTHQUAKE
} SpellNames;

// List of all the spells' names and damages. Corresponds to the SpellNames enum.
SpellEntry SpellBook[] = {
    { "No spell assigned to this slot", 0},
    { "Fire Blast", 10 },
    { "Thunderbolt", 20 },
    { "Tornado", 30 },
    { "Earthquake", 40 },
};

// Number of different spells.
int SpellCount = sizeof(SpellBook) / sizeof(SpellBook[0]);


// -------------------- PLAYER --------------------- //

// Base structure for the player. Stores HP, max HP, XP, level, spells, potions and current area.
typedef struct Player {
    int hp;
    int max_hp;
    int xp;
    int lv;
    SpellNames spells[4];
    int potions;
    int current_area;
} Player;


// -------------------- BATTLE FUNCTIONS --------------------- //

// Damages the player by the given value.
void damage_player(Player* player, int damage) 
{
    player->hp -= damage;

    // Calculate the amount of hp healed in case the player healed himself.
    int healed_hp = -damage;
    if (player->hp > player->max_hp) {
        healed_hp -= player->hp - player->max_hp;
        player->hp = player->max_hp;
    }

    if (damage >= 0) {
        printf("%sYou%s have lost %s%d %shp%s ", C_GREEN, C_DEFAULT, C_CYAN, damage, C_BOLD, C_DEFAULT);
        if (player->hp > 0) {
            printf("(remaining: %s%d%s).\n", C_GREEN, player->hp, C_DEFAULT);
        }
        else {
            printf("(remaining: %s0%s).\n", C_GREEN, C_DEFAULT);
        }
    }
    else {
        printf("%sYou%s healed %s%d %shp%s (remaining: %s%d%s).\n", C_GREEN, C_DEFAULT, C_CYAN, healed_hp, C_BOLD, C_DEFAULT, C_GREEN, player->hp, C_DEFAULT);
    }
}

// Damages a monster by the given value.
void damage_monster(Monster* monster, int damage)
{
    monster->hp -= damage;

    printf("The %s%s%s lost %s%d %shp%s ", C_RED, Bestiary[monster->id].name, C_DEFAULT, C_CYAN, damage, C_BOLD, C_DEFAULT);
    if (monster->hp > 0) {
            printf("(remaining: %s%d%s).\n", C_RED, monster->hp, C_DEFAULT);
    }
    else {
        printf("(remaining: %s0%s).\n", C_RED, C_DEFAULT);
    }
}

// Plays the action chosen by the player. Returns 1 if the turn should be restarted because the player input was wrong, 0 if everything's fine.
int do_player_action(Player* player, Monster* monster, int action, int turn)
{
    if (action >= 0 && action <= 3) {
        // Skip the player's turn if he used a spell that does 0 damage.
        if (SpellBook[player->spells[action]].damage == 0) {
            printf("%sYou%s did no damage to the %s%s%s.\n", C_GREEN, C_DEFAULT, C_RED, Bestiary[monster->id].name, C_DEFAULT);
        }
        // Make the player use his spell if it does damage or heal.
        else {
            printf("%sYou%s used %s. ", C_GREEN, C_DEFAULT, SpellBook[player->spells[action]].name);
            damage_monster(monster, SpellBook[player->spells[action]].damage);
        }
    }
    else if (action == 4) {
        // Skip the player's turn if they don't have any potions left.
        if (player->potions <= 0) {
            printf("%sYou%s don't have any potions left!\n", C_GREEN, C_DEFAULT);
        }
        // Use a potion if the player has some left.
        else {
            printf("%sYou%s used a potion. ", C_GREEN, C_DEFAULT);
            player->potions--;
            damage_player(player, -20 - 10 * (player->lv - 1));
        }
    }
    else {
        printf("%sYour%s choice must be between 0 and 4. Restarting turn.\n\n", C_GREEN, C_DEFAULT);
        return 1;
    }
    return 0;
}

// Resets the given monster with random values so that a new encounter can begin.
void reset_monster(Monster* monster, int lv)
{
    monster->id = rand() % MonsterCount;
    monster->hp = rand() % Bestiary[monster->id].hp_range[1] + Bestiary[monster->id].hp_range[1] - Bestiary[monster->id].hp_range[0];
    monster->max_hp = monster->hp;
    
    for (int i = 0; i < 4; i++) {
        if (lv - 1 >= i) {
            monster->attacks[i] = Bestiary[monster->id].attacks[i];
        }
        else {
            monster->attacks[i] = AT_NONE;
        }
    }
}

// Sarts an encounter with a monster.
void start_encounter(Player* player, Monster* monster)
{
    printf("%s%sMonster encounter\n%s", C_MAGENTA, C_UNDERLINE, C_DEFAULT);
    reset_monster(monster, player->lv);
    printf("%sA %s%s%s %sstands in %syour%s %sway!%s\n\n", C_BOLD, C_RED, Bestiary[monster->id].name, C_DEFAULT, C_BOLD, C_GREEN, C_DEFAULT, C_BOLD, C_DEFAULT);
}

// Plays a turn of the current combat.
void play_turn(int turn, Player* player, Monster* monster)
{
    // Show the player and the monster's health, and show the player's options.
    printf("%sYour%s health: %s%d%s, %s%s%s's health: %s%d%s.\nChoose what to do:\n", 
           C_GREEN, C_DEFAULT, C_GREEN, player->hp, C_DEFAULT, 
           C_RED, Bestiary[monster->id].name, C_DEFAULT, C_RED, monster->hp, C_DEFAULT);
    
    // Show the plqyer's spells.
    for (int i = 0; i < 4; i++) {
        printf("  %d: %s (%s%sDmg%s: %s%d%s)\n", i, SpellBook[player->spells[i]].name, C_CYAN, C_BOLD, C_DEFAULT, C_CYAN, SpellBook[player->spells[i]].damage, C_DEFAULT);
    }

    // Show the number of potions available to the player.
    printf("  4: Use a potion (remaining: %d)\n%sYour choice: ", player->potions, C_GRAY);
    
    // Get the player's choice.
    int player_choice;
    char temp[10];
    fgets(temp, 10, stdin);
    player_choice = temp[0] - '0';
    printf("%s\n", C_DEFAULT);

    // Play the player's choice. If the action can't be done, restart the turn, else continue as normal.
    if (do_player_action(player, monster, player_choice, turn) == 1) {
        play_turn(turn, player, monster);
    }

    else {
        // Get the monster's choice.
        int monster_choice = rand() % 4;
        while (monster->attacks[monster_choice] == AT_NONE) {
            monster_choice = rand() % 4;
        }

        // Play the monster's choice.
        printf("The %s%s%s used %s! ", C_RED, Bestiary[monster->id].name, C_DEFAULT, AttackBook[monster->attacks[monster_choice]].name);
        damage_player(player, AttackBook[monster->attacks[monster_choice]].damage);

        // Wait for the user to end the turn.
        printf("%sPress [enter] to continue the battle.%s", C_GRAY, C_DEFAULT);
        getchar();
        printf("\n\n");
    }
}


// Ends an encounter with a monster.
void end_encounter(Player* player,Monster* monster)
{
    // If the player won.
    if (monster->hp <= 0) {
        printf("%sYou%s have defeated the %s%s%s!\n", C_GREEN, C_DEFAULT, C_RED, Bestiary[monster->id].name, C_DEFAULT);
        printf("%sYou%s earned %s%d%s %s%sxp%s.\n",   C_GREEN, C_DEFAULT, C_YELLOW, monster->max_hp / 2, C_DEFAULT, C_YELLOW, C_BOLD, C_DEFAULT);
        player->xp += monster->max_hp / 2;

        // Level the player up if he gained enough XP.
        if (player->xp >= pow(2.0, player->lv + 3.0)) {
            player->xp -= pow(2.0, player->lv + 3.0);
            player->lv++;
            printf("%sYou%s leveled up! New level: %s%d%s.\n", C_GREEN, C_DEFAULT, C_YELLOW, player->lv, C_DEFAULT);
            
            // Upgrade the player's max health and give him back some hp.
            player->max_hp += (player->lv - 1) * 10;
            printf("%sYour%s %s%smax hp%s is now %s%d%s.\n", C_GREEN, C_DEFAULT, C_CYAN, C_BOLD, C_DEFAULT, C_CYAN, player->max_hp, C_DEFAULT);
            player->hp += (player->lv - 1) * 10;
            printf("%sYou%s replenished %s%d %shp%s (remaining: %s%d%s).\n", C_GREEN, C_DEFAULT, C_CYAN, (player->lv - 1) * 10, C_BOLD, C_DEFAULT, C_CYAN, player->hp, C_DEFAULT);

            // The player unlocks a spell everytime he levels up until level 5 (idk how this happened but each spell corresponds to a level of the player).
            if (player->lv < 5) {
                player->spells[player->lv-1] = player->lv;
            }
        }
        else {
            printf("Get %s%d%s more %s%sxp%s to level up.\n", C_YELLOW, (int)(pow(2, player->lv + 4) - player->xp), C_DEFAULT, C_YELLOW, C_BOLD, C_DEFAULT);
        }

        // Wait for the user to end the turn.
        printf("%sPress [enter] to go to the next encounter.%s", C_GRAY, C_DEFAULT);
        getchar();
        printf("\n\n\n\n");
    }

    // If the player was defeated.
    if (player->hp <= 0) {
        printf("%s%sGAME OVER:%s %sYou%s were defeated in battle!\nFinal level: %s%d%s.\n", C_RED, C_BOLD, C_DEFAULT, C_GREEN, C_DEFAULT, C_YELLOW, player->lv, C_DEFAULT);
    }
}


/*
// -------------------- BOSS ENCOUNTERS --------------------- //

// Starts a boss encounter.
void start_boss_encounter();

// Plays a turn of a boss battle.
void play_boss_turn();

// Ends the boss encounter.
void end_boss_encounter();
*/


// -------------------- PLOT FUNCTIONS --------------------- //

// The player discovers a new area and goes there depending on his level.
void discover_area(Player* player)
{
    if (player->lv - 1 > player->current_area) {
        // Move the player to the next area.
        player->current_area++;

        // Show the name and description of the new area.
        printf("%s%sNew area discovered%s\n", C_MAGENTA, C_UNDERLINE, C_DEFAULT);
        printf("%s\n", AreaBook[player->current_area].description);
        printf("%sPress [enter] to continue.%s", C_GRAY, C_DEFAULT);
        getchar();
        printf("\n\n");
    }
}

// The player finds an item and can choose to take it or not.
void find_item(Player* player)
{
    // Choose a random item to find.
    int item = AreaBook[player->current_area].items[rand() % 4];

    // Show the name and description of the item.
    printf("%s%sItem/Structure found%s\n", C_MAGENTA, C_UNDERLINE, C_DEFAULT);
    printf("%sYou%s found a %s. %s\n", C_GREEN, C_DEFAULT, ItemBook[item].name, ItemBook[item].description);

    // Show the player's options.
    printf("Choose what to do:\n");
    for (int i = 0; i < 2; i++) {
        printf("  %d: %s\n", i, ItemBook[item].options[i]);
    }

    // Get the player's choice.
    printf("%sYour choice: ", C_GRAY);
    int choice;
    char temp[10];
    fgets(temp, 10, stdin);
    choice = temp[0] - '0';
    printf("%s\n", C_DEFAULT);

    // If the player interacted with the object.
    if (choice == 0 || choice == 1) {
        if (strcmp(ItemBook[item].outcome[choice], "leave") == 0) {
            printf("%sYou%s leave the %s and get back to following the path.\n", C_GREEN, C_DEFAULT, ItemBook[item].name);
        }
        else if (strcmp(ItemBook[item].outcome[choice], "potions++") == 0) {
            player->potions++;
            printf("%sYou%s pick up the potion and store it with the others (remaining potions: %d).\n", C_GREEN, C_DEFAULT, player->potions);
        }
        else if (strcmp(ItemBook[item].outcome[choice], "hp++") == 0) {
            player->hp += 20 + 5 * (player->lv - 1);
            if (player->hp > player->max_hp) { 
                player->hp = player->max_hp;
            }
            printf("%sYou%s drink the water and feel restored.\nYou replenished %s%d %shp%s (remaining %s%shp%s: %s%d%s).\n", 
                    C_GREEN, C_DEFAULT, C_CYAN, 20 + 5 * (player->lv - 1), C_BOLD, C_DEFAULT, C_BOLD, C_CYAN, C_DEFAULT, C_CYAN, player->hp, C_DEFAULT);
        }
        else if (strcmp(ItemBook[item].outcome[choice], "max_hp++ && hp--") == 0) {
            printf("%sYou%s take the knife, cut a small slit in your finger and let some blood drops fall in the plate.\nIt hurts a little bit but it seems like %syour%s live energy was expanded.\n", 
                    C_GREEN, C_DEFAULT, C_GREEN, C_DEFAULT);
            player->hp -= 5;
            player->max_hp += 5;
            printf("%sYou%s lost %s5 %shp%s (remaining: %s%d%s) and gained %s5 %smax hp%s (new %s%smax hp%s: %s%d%s).\n", 
                    C_GREEN, C_DEFAULT, C_CYAN, C_BOLD, C_DEFAULT, C_CYAN, player->hp, C_DEFAULT, C_CYAN, C_BOLD, C_DEFAULT, C_CYAN, C_BOLD, C_DEFAULT, C_CYAN, player->max_hp, C_DEFAULT);
        }
        else if (strcmp(ItemBook[item].outcome[choice], "xp++") == 0) {
            player->xp += 10 * player->lv;
            printf("%sYou%s pick up the book and open it.\nIt starts to glow more and more until it slams shut and falls on the ground.\nYou have a small headache but you feel like your knowledge has been expanded.\nYou gained %s%d %sxp%s.\n", 
                    C_GREEN, C_DEFAULT, C_YELLOW, 10 * player->lv, C_BOLD, C_DEFAULT);
        }
    }

    // Wait for the player to continue.
    printf("%sPress [enter] to continue.%s", C_GRAY, C_DEFAULT);
    getchar();
    printf("\n\n\n");
}

// The player meets someome and can talk to them.
void meet_npc(Player* player)
{
    // Choose a random npc to encounter.
    int npc = AreaBook[player->current_area].npcs[rand() % 4];
    for (int i = 0; i < 10 && NpcBook[npc].already_talked; i++) {
        npc = AreaBook[player->current_area].npcs[rand() % 4];
    }

    if (!NpcBook[npc].already_talked) {
        // Show the name and description of the npc.
        printf("%s%sNpc encountered%s\n" ,C_MAGENTA, C_UNDERLINE, C_DEFAULT);
        printf("%sYou%s are face to face with %s. %s\n", C_GREEN, C_DEFAULT, NpcBook[npc].name, NpcBook[npc].description);

        // Start the dialogue.
        printf("\n\"%s\"\n\n", NpcBook[npc].dialogue);

        // Show the player's possible answers.
        printf("Possible answers:\n");
        for (int i = 0; i < 3; i++) {
            printf("  %d: \"%s\"\n", i, NpcBook[npc].possible_answers[i]);
        }

        // Get the player's choice.
        printf("%sYour choice: ", C_GRAY);
        int choice;
        char temp[10];
        fgets(temp, 10, stdin);
        choice = temp[0] - '0';
        printf("%s\n", C_DEFAULT);

        // Show the npc's reaction.
        printf("\"%s\"\n", NpcBook[npc].reactions[choice]);

        // Save the fact that you have talked to this npc.
        NpcBook[npc].already_talked = 1;

        // Wait for the player to continue.
        printf("%sPress [enter] to continue.%s", C_GRAY, C_DEFAULT);
        getchar();
        printf("\n\n\n");
    }
}

// Called between encounters. The player can discover a new area, find items, talk to people.
void plot_event(Player* player)
{
    int event = rand() % 5;

    if (event > 3)
        return;
    else if (event > 1)
        find_item(player);
    else if (event == 1)
        meet_npc(player);
    else if (event == 0)
        discover_area(player);
}


// -------------------- GAME LOOP --------------------- //

int main()
{
    // Initialisation of the rng with a unique seed.
    srand(time(NULL));

    int playing = 1;
    while (playing) {
        // Start the game.
        printf("%s%sNEW GAME:\n%s", C_BOLD, C_UNDERLINE, C_DEFAULT);

        // Stores the player's data.
        Player player = {
            100,
            100,
            0,
            1,
            { SP_THUNDERBOLT, SP_NONE, SP_NONE, SP_NONE },
            5,
            -1,
        };

        // Make the player enter the first area.
        discover_area(&player);

        Monster monster;

        // Game loop.
        while (player.hp > 0 && player.current_area < 4) 
        {
            // Make the player meet the old man.
            meet_npc(&player);

            // The player can discover a new area, find items, talk to people.
            if (player.lv < player.current_area + 3) {
                plot_event(&player);
            }
            else {
                discover_area(&player);
            }

            // Encounter monster.
            start_encounter(&player, &monster);

            // Fight monster.
            int turn = 0; // The number of the current turn.
            while (monster.hp > 0 && player.hp > 0) 
            {
                printf("%s%sTurn %d:\n%s%s", C_BOLD, C_UNDERLINE, turn + 1, C_DEFAULT, C_NO_UNDERLINE);
                play_turn(turn, &player, &monster);
                turn++;
            }
            printf("%s%sTurn %d:\n%s%s", C_BOLD, C_UNDERLINE, turn + 1, C_DEFAULT, C_NO_UNDERLINE);

            // Give the player some rewards for the battle or do a game over if the player is dead.
            end_encounter(&player, &monster);
        }

        // The player wins if his level is 5 or higher.
        if (player.current_area >= 4) {
            printf("Congratulations! %sYou%s have learned all the spells and slain all the monsters %syou%s encountered.\nThank %syou%s for playing :)\n", C_GREEN, C_DEFAULT, C_GREEN, C_DEFAULT, C_GREEN, C_DEFAULT);
        }
        
        printf("%sPress [enter] to restart or [q] to quit. ", C_GRAY);
        char input = getchar();
        if (input == 'Q' || input == 'q') {
            playing = 0;
            printf("Extiting game.%s\n", C_DEFAULT);
        }
        else {
            printf("\n\n\n");
        }
    }

    return 0;
}
