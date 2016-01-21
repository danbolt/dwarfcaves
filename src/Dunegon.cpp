#include <vector>
#include <functional>

#include "Dungeon.hpp"

Dungeon::Dungeon(int seed, unsigned int size, unsigned int roomAttempts)
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

  rng.seed(seed);

  SpawnRooms(roomAttempts);
  SpawnMazeCooridor();
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
      floodFill(x - 1, y);
      floodFill(x + 1, y);
      floodFill(x, y - 1);
      floodFill(x, y + 1);
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

DungeonRoom::DungeonRoom(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}
