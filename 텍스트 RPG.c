#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[30];
    int hp;
    int level;
    int experience;
} Player;

typedef struct {
    char name[30];
    int hp;
    int attack;
} Monster;

void battle(Player *player, Monster *monster) {
    printf("%s와 전투 시작!\n", monster->name);
    while (player->hp > 0 && monster->hp > 0) {
        // Player's turn
        int damage = rand() % 10 + 1;
        monster->hp -= damage;
        printf("%s가 %s에게 %d 피해를 주었습니다. 몬스터 HP: %d\n", player->name, monster->name, damage, monster->hp);

        if (monster->hp <= 0) {
            printf("%s를 처치했습니다!\n", monster->name);
            player->experience += 50;
            player->level = (player->experience / 100) + 1;
            printf("경험치 +50, 레벨: %d\n", player->level);
            break;
        }

        // Monster's turn
        damage = rand() % 10 + 1;
        player->hp -= damage;
        printf("%s가 %s에게 %d 피해를 주었습니다. 플레이어 HP: %d\n", monster->name, player->name, damage, player->hp);

        if (player->hp <= 0) {
            printf("%s가 쓰러졌습니다. 게임 오버!\n", player->name);
        }
    }
}

int main() {
    srand(time(NULL));
    Player player = {"Hero", 100, 1, 0};
    Monster monster = {"Goblin", 30, 5};

    printf("게임 시작!\n");
    battle(&player, &monster);

    return 0;
}
