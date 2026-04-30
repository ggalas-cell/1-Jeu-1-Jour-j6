#pragma once

enum CollisionLayer
{
    NONE = 0,
    PLAYER_LAYER = 1 << 0,  // 1,
    TARGET_LAYER = 1 << 1, //2
    ENV_LAYER = 1 << 2,  // 4
    BLOCK_LAYER = 1 << 3,   // 8  - blocs poussables
    BULLET_LAYER = 1 << 4,
    ENEMY_LAYER = 1 << 5
};