#include <iostream>

#include "Dungeon.hpp"

int main()
{
  Dungeon d(0, 50, 100);
  
  for (auto it = 0; it < d.GetDungeonSize(); it++)
  {
    for (auto it2 = 0; it2 < d.GetDungeonSize(); it2++)
    {
      switch (d.GetCellAt(it2, it))
      {
        case Dungeon::CellType::FLOOR:
          std::cout << " ";
          break;  
        case Dungeon::CellType::DOORWAY:
          std::cout << "🚪";
          break;
        case Dungeon::CellType::ROCK:
          std::cout << "⬜";
          break;
      }

      std::cout << ' ';
    }

    std::cout << "\n";
  }

  return 0;
}

