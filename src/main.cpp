#include <iostream>

#include "Dungeon.hpp"

int main()
{
  Dungeon d(0, 50, 100);
  
  for (auto it = 0; it < d.GetDungeonSize(); it++)
  {
    for (auto it2 = 0; it2 < d.GetDungeonSize(); it2++)
    {
      std::cout << ((int)(d.GetCellAt(it2, it)) == 1 ? "⬜" : " ") << " ";
    }

    std::cout << "\n";
  }

  return 0;
}

