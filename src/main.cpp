#include <iostream>
#include <string>

#include "Dungeon.hpp"

int main(int argc, char* argv[])
{
  if (argc <= 1)
  {
    std::cout << "Please provide a seed value.\n Example:  $ dwarfcaves 'foo'\n";

    return 0;
  }

  std::string seedVal = std::string(argv[1]);
  std::cout << seedVal << "\n";

  Dungeon d(seedVal, 50, 100);
  
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

