
#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <vector>
#include <random>
#include <string>

class Dungeon;
class DungeonRoom;

class Dungeon
{
public:
  enum CellType
  {
    ROCK = 1,
    FLOOR = 0,
    DOORWAY = 2
  };

  Dungeon(std::string seed, unsigned int size, unsigned int roomAttempts);

  CellType GetCellAt(unsigned int x, unsigned int y);

  unsigned int GetDungeonSize();

private:
  std::vector<std::vector<CellType>> data;
  std::vector<DungeonRoom> rooms;

  std::mt19937 rng;

  unsigned int size;
  const unsigned int minRoomWidth = 4;
  const unsigned int minRoomHeight = 4;
  const unsigned int maxRoomWidth = 10;
  const unsigned int maxRoomHeight = 10;

  void SpawnRooms(unsigned int attempts);
  void SpawnMazeCooridor();
  void SpawnDoorways();
  void CarveDeadEnds();
};

class DungeonRoom
{
public:
  DungeonRoom(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
};

#endif
