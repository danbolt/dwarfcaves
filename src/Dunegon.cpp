#include <vector>
#include <functional>
#include <iostream>
#include <string>

#include "Dungeon.hpp"

Dungeon::Dungeon(std::string seed, unsigned int size, unsigned int roomAttempts)
{
  if (size < 1)
  {
    size = 1;
  }

  data.resize(size);

  for (auto it = data.begin(); it != data.end(); ++it)
  {
    (*it).resize(size, CellType::ROCK);
  }

  this->size = size;

  std::seed_seq sequence (seed.begin(), seed.end());

  rng.seed(sequence);

  SpawnRooms(roomAttempts);
  SpawnMazeCooridor();
  SpawnDoorways();
  CarveDeadEnds();
}

Dungeon::CellType Dungeon::GetCellAt(unsigned int x, unsigned int y)
{
  if (x >= size || y >= size)
  {
    return CellType::ROCK;
  }
  else
  {
    return data[x][y];
  }
}

unsigned int Dungeon::GetDungeonSize()
{
  return size;
}

void Dungeon::SpawnRooms(unsigned int attempts)
{
  auto twoRoomsOverlap = [](DungeonRoom& a, DungeonRoom& b)
  {
    return (a.x <= b.x + b.width && a.x + a.width >= b.x && a.y <= b.y + b.height && a.y + a.height >= b.y);
  };

  auto placeRoom = [this, twoRoomsOverlap](unsigned int x, unsigned int y, unsigned int width, unsigned int height)
  {
    if (x >= this->size || y >= this->size || x + width >= this->size || y + height >= this->size)
    {
      return;
    }

    DungeonRoom room(x, y, width, height);

    for (DungeonRoom& existingRoom : rooms)
    {
      if (twoRoomsOverlap(room, existingRoom))
      {
        return;
      }
    }

    rooms.push_back(room);
  };

  // try to place a room `attempts` number of times
  for (auto i = 0; i < attempts; i++)
  {
    auto roomX = 1 + (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * (size - (size % 2 == 1 ? 3 : 2)));
    roomX = roomX % 2 == 1 ? roomX : roomX + 1;

    auto roomY = 1 + (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * (size - (size % 2 == 1 ? 3 : 2)));
    roomY = roomY % 2 == 1 ? roomY : roomY + 1;

    auto roomWidth = minRoomWidth + (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * (maxRoomWidth - minRoomWidth));
    roomWidth = roomWidth % 2 == 1 ? roomWidth : roomWidth + 1;
    auto roomHeight = minRoomHeight + (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * (maxRoomHeight - minRoomHeight));
    roomHeight = roomHeight % 2 == 1 ? roomHeight : roomHeight + 1;

    placeRoom(roomX, roomY, roomWidth, roomHeight);
  }

  // clear out each room on the map
  for (DungeonRoom& room : rooms)
  {
    for (auto i = room.x; i < room.x + room.width; i++)
    {
      for (auto j = room.y; j < room.y + room.height; j++)
      {
        data[i][j] = CellType::FLOOR;
      }
    }
  }
}

void Dungeon::SpawnMazeCooridor()
{
  std::function<void(int, int)> floodFill = [&, this](int x, int y)
  {
    // Dont turn the surrounding walls into cooridors
    if (x < 1 || x >= this->size - 1 || y < 1 || y >= this->size - 1)
    {
      return;
    }

    // Don't perform this logic on floor cells
    if (this->GetCellAt(x, y) != CellType::ROCK)
    {
      return;
    }

    // Don't turn the corners of rooms into cooridors
    for(DungeonRoom& room : this->rooms)
    {
      if (x == room.x - 1 && y == room.y - 1) { return; }
      if (x == room.x + room.width && y == room.y - 1) { return; }
      if (x == room.x - 1 && y == room.y + room.height) { return; }
      if (x == room.x + room.width && y == room.y + room.height) { return; }
    }

    // count the number of diagonal neighbours that are floors
    auto cornerNeighbourCount = 0; 
    if (this->GetCellAt(x - 1, y - 1) == CellType::FLOOR) { cornerNeighbourCount++; }
    if (this->GetCellAt(x + 1, y - 1) == CellType::FLOOR) { cornerNeighbourCount++; }
    if (this->GetCellAt(x - 1, y + 1) == CellType::FLOOR) { cornerNeighbourCount++; }
    if (this->GetCellAt(x + 1, y + 1) == CellType::FLOOR) { cornerNeighbourCount++; }

    // count the number of neighbours that are rocks
    auto rockNeighbourCount = 0;
    if (this->GetCellAt(x - 1, y) == CellType::ROCK) { rockNeighbourCount++; }
    if (this->GetCellAt(x + 1, y) == CellType::ROCK) { rockNeighbourCount++; }
    if (this->GetCellAt(x, y - 1) == CellType::ROCK) { rockNeighbourCount++; }
    if (this->GetCellAt(x, y + 1) == CellType::ROCK) { rockNeighbourCount++; }

    // If this is rock, and the cell 
    if (rockNeighbourCount >= 3 && cornerNeighbourCount < 3)
    {
      this->data[x][y] = CellType::FLOOR;

      auto nextStepValue = this->rng() % 4;

      switch (nextStepValue)
      {
        case 0:
          floodFill(x - 1, y);
          floodFill(x + 1, y);
          floodFill(x, y - 1);
          floodFill(x, y + 1);
          break;
        case 1:
          floodFill(x + 1, y);
          floodFill(x, y - 1);
          floodFill(x, y + 1);
          floodFill(x - 1, y);
          break;
        case 2:
          floodFill(x, y - 1);
          floodFill(x, y + 1);
          floodFill(x - 1, y);
          floodFill(x + 1, y);
          break;
        case 3:
          floodFill(x, y + 1);
          floodFill(x - 1, y);
          floodFill(x + 1, y);
          floodFill(x, y - 1);
          break;
      }
    }
  };

  // find an initial point to flood-fill, then flood fill it
  for (auto initialX = 1; initialX < size - 1; initialX++)
  {
    for (auto initialY = 1; initialY < size - 1; initialY++)
    {
      if (this->GetCellAt(initialX - 1, initialY - 1) == CellType::FLOOR &&
      this->GetCellAt(initialX + 1, initialY - 1) == CellType::FLOOR &&
      this->GetCellAt(initialX - 1, initialY + 1) == CellType::FLOOR &&
      this->GetCellAt(initialX + 1, initialY + 1) == CellType::FLOOR)
      {
        continue;
      }

      if (GetCellAt(initialX, initialY) == CellType::ROCK && 
        GetCellAt(initialX + 1, initialY) == CellType::ROCK && GetCellAt(initialX - 1, initialY) == CellType::ROCK &&
        GetCellAt(initialX, initialY + 1) == CellType::ROCK && GetCellAt(initialX, initialY - 1) == CellType::ROCK)
      {
        floodFill(initialX, initialY);
      }
    }
  }

  return;
}

void Dungeon::SpawnDoorways()
{

  for (DungeonRoom& room: rooms)
  {
    auto doorCount = 1 + (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * 4);

    for (auto i = 0; i < doorCount; i++)
    {
      auto doorSide = (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * 4);
      auto roll = (unsigned int)((float)(rng() - rng.min()) / (float)(rng.max() - rng.min()) * ((doorSide == 0 || doorSide == 2 ? room.height : room.width) - 2));

      auto rollX = room.x + (doorSide == 0 ? room.width : 0) + (doorSide == 2 ? -1 : 0) + (doorSide == 1 || doorSide == 3 ? 1 + roll : 0);
      auto rollY = room.y + (doorSide == 0 || doorSide == 2 ? 1 + roll : 0) + (doorSide == 1 ? -1 : 0) + (doorSide == 3 ? room.height : 0);
      
      // Don't put doors into places that don't have floors on both sides
      if (roll == 0 || roll == 2)
      {
        if (GetCellAt(rollX - 1, rollY) != CellType::FLOOR || GetCellAt(rollX + 1, rollY) != CellType::FLOOR)
        {
          i--;
          continue;
        }
      }
      else if (roll == 1 || roll == 3)
      {
        if (GetCellAt(rollX, rollY - 1) != CellType::FLOOR || GetCellAt(rollX, rollY + 1) != CellType::FLOOR)
        {
          i--;
          continue;
        }
      }

      // Don't put doors into places that lead nowhere
      auto rollRockNeighbourCount = 0;
      if (GetCellAt(rollX - 1, rollY) == CellType::ROCK) { rollRockNeighbourCount++; }
      if (GetCellAt(rollX + 1, rollY) == CellType::ROCK) { rollRockNeighbourCount++; }
      if (GetCellAt(rollX, rollY - 1) == CellType::ROCK) { rollRockNeighbourCount++; }
      if (GetCellAt(rollX, rollY + 1) == CellType::ROCK) { rollRockNeighbourCount++; }

      if (rollRockNeighbourCount > 2)
      {
        i--;
        continue;
      }

      data[rollX][rollY] = CellType::DOORWAY;
    }
  }
}

void Dungeon::CarveDeadEnds()
{
  bool deadEndsExist = false;

  do
  {
    deadEndsExist = false;

    for (auto x = 0; x < size; x++)
    {
      for (auto y = 0; y < size; y++)
      {
        if (GetCellAt(x, y) == CellType::FLOOR)
        {
          auto rollRockNeighbourCount = 0;
          if (GetCellAt(x - 1, y) == CellType::ROCK) { rollRockNeighbourCount++; }
          if (GetCellAt(x + 1, y) == CellType::ROCK) { rollRockNeighbourCount++; }
          if (GetCellAt(x, y - 1) == CellType::ROCK) { rollRockNeighbourCount++; }
          if (GetCellAt(x, y + 1) == CellType::ROCK) { rollRockNeighbourCount++; }

          if (rollRockNeighbourCount == 3)
          {
            deadEndsExist = true;
            data[x][y] = CellType::ROCK;
          }
        }
      }
    }
  }
  while (deadEndsExist);
}

DungeonRoom::DungeonRoom(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
