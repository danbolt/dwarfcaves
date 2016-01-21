
#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <vector>
#include <random>

class Dungeon;
class DungeonRoom;

class Dungeon
{
public:
  enum CellType
  {
    ROCK = 1,
    FLOOR = 0
  };

  Dungeon(int seed, unsigned int size, unsigned int roomAttempts);

  CellType GetCellAt(unsigned int x, unsigned int y);

  unsigned int GetDungeonSize();

private:
  std::vector<std::vector<CellType>> data;
  std::vector<DungeonRoom> rooms;

  std::minstd_rand0 rng;

  void SpawnRooms(unsigned int attempts);

  unsigned int size;
  unsigned int minRoomWidth = 3;
  unsigned int minRoomHeight = 3;
  unsigned int maxRoomWidth = 10;
  unsigned int maxRoomHeight = 10;
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
