#pragma once
class GameData
{
private:
    static GameData* instance;
    GameData() {}

public:



    static GameData* Get()
    {
        if (instance == nullptr) instance = new GameData();
        return instance;
    }
};

