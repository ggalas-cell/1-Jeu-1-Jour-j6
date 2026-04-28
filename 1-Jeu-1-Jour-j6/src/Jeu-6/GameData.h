#pragma once
class GameData
{
private:
    static GameData* instance;
    GameData() {}

public:
    //---- Bullet ----//
    int currencyPerKill = 1;
    int BulletDamage = 1;
    float BulletSpeed = 300.f;

    //---- Player ----//
    float PlayerSpeed = 1.f;
    float PlayerHp = 5;

    //---- Enemy ----//

    static GameData* Get()
    {
        if (instance == nullptr) instance = new GameData();
        return instance;
    }
};

