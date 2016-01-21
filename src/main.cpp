#include <iostream>
#include <string>

#include <cstdlib>

#include "Dungeon.hpp"

int main(int argc, char* argv[])
{
  if (argc <= 1)
  {
    std::cout << "Please provide a seed value. Type `dwarfcaves --help` for more information.\nExample:  $ dwarfcaves 'Alyosha K.'\n";

    return 0;
  }

  std::string seedVal = std::string(argv[1]);
  unsigned int caveSize = 50;
  unsigned int attemptCount = 100;

  if (argc > 2)
  {
    caveSize = (unsigned int)(strtoul(argv[2], NULL, 0));

    if (argc > 3)
    {
      attemptCount = (unsigned int)(strtoul(argv[3], NULL, 0));
    }
  }

  if (seedVal == "--help")
  {
    std::cout << "Dwarf Caves v1.0\nA quick 'n dirty dungeon generator by Daniel Savage.\n\nUsage:\n    dwarfcaves seed [s] [a]\n\n  s : map size in cells (map must be square; default = 50)\n  a : number of room placement attempts (default = 100)";

    return 0;
  }

  Dungeon d(seedVal, caveSize, attemptCount);
  
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
          std::cout << "d";
          break;
        case Dungeon::CellType::ROCK:
          std::cout << "▢";
          break;
      }

      std::cout << ' ';
    }

    std::cout << "\n";
  }

  return 0;
}

