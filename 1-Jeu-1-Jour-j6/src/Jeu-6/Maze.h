#pragma once
#include <vector>
#include <string>

// '#' = mur solide
// ' ' = couloir libre
// 'S' = spawn joueur
// 'E' = sortie
// 'B' = bloc poussable (solide, bloque le joueur et les autres blocs)
// 'T' = target : case vide que le bloc doit combler pour créer un pont
//       (sans bloc dessus => traité comme mur)
// 'G' = gate : mur qui disparaît quand TOUS les blocs B sont sur leur T

class Maze
{
public:


    static inline std::vector<std::string> sGrid_Level1 = {
    "###################",
    "#                 #",
    "#   S      B      #",
    "#                 #",
    "#        T ########",
    "#          #      #",
    "#          G   E  #",
    "###################"
    };


    static inline std::vector<std::string> sGrid_Level2 = {
    "#########################",
    "#                       #",
    "# S #      B            #",
    "#   #                   #",
    "#####   ###########     #",
    "#                 #     #",
    "#       #    T    #     #",
    "#       #         #     #",
    "#       ###########     #",
    "#                       #",
    "#   B                   #",
    "#                       #",
    "###########   ###########",
    "#             #        E#",
    "#             #         #",
    "#             #         #",
    "#             ########GG#",
    "#T                      #",
    "#########################"
    };


    static inline std::vector<std::string> sGrid_Level3 = {
    "#################################",
    "#S    #       #   #             #",
    "#     #   B   #   #   B     B   #",
    "#     #       #   #             #",
    "### ###   #####   #####   #######",
    "#       #     #         #       #",
    "#   B   #  T  #   ###   #  T    #",
    "#       #     #   # #   #       #",
    "#########     #####B#####       #",
    "#                 #         #   #",
    "#   T   ###########   #####B#   #",
    "#       #         #   #     #   #",
    "##### ###   #####B#   #  T  #   #",
    "#   #       #     #   #     #   #",
    "#   #   #####     #####     #####",
    "#   #   #     B         B       #",
    "#   #   #   ###   #####   #######",
    "#   #   #   # T   #   #       #E#",
    "#   #####   #     #   #####   #G#",
    "#           #         #         #",
    "#################################"
    }; 
    std::vector<std::string> mGrid = sGrid_Level1;
    int mCellSize = 80;

    void LoadLevel(int level)
    {
        if (level == 1) { mGrid = sGrid_Level1; mCellSize = 100; }
        else if (level == 2) { mGrid = sGrid_Level2; mCellSize = 60; }
        else if (level == 3) { mGrid = sGrid_Level3; mCellSize = 50; }
    }

    int  GetRows() const { return (int)mGrid.size(); }
    int  GetCols() const { return (int)mGrid[0].size(); }
    char GetCell(int row, int col) const { return mGrid[row][col]; }
    void SetCell(int row, int col, char c) { mGrid[row][col] = c; }

    void GetWorldPos(int row, int col, float& x, float& y) const
    {
        x = col * mCellSize + mCellSize * 0.5f;
        y = row * mCellSize + mCellSize * 0.5f;
    }

    void WorldToGrid(float wx, float wy, int& row, int& col) const
    {
        col = (int)(wx / mCellSize);
        row = (int)(wy / mCellSize);
    }
};