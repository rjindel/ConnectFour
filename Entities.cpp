#include "Entities.h"
#include "Tile.h"
#include "Board.h"

#include <iostream>

void Player::GetTileSelection()
{
	bool validResponse = false;
	while (!validResponse)
	{
		std::cout << "Player " << GetEntityID() << " Select a tile" << std::endl;
		uint32_t x = 0;
		uint32_t y = 0;
		std::cin >> x >> y;

		if (x >= model->GetWidth() || y >= model->GetHeight())
		{
			std::cout << "Invalid co-ordinate enter a value between 0 and " << model->GetWidth() - 1 << " and a value between 0 and " << model->GetHeight() - 1 << std::endl;
			continue;
		}

		Tile tile = model->GetTile(x, y);
		if (tile.type != TileType::UNNOCCUPIED)
		{
			std::cout << "Tile Occupied. Please choose an unoccupied tile" << std::endl;
			continue;
		}

		tile.type = TileType::PLAYER;
		tile.value = GetEntityID();
		model->SetTile(x, y, tile);
		validResponse = true;

		std::cout << "Adding Player " << GetEntityID() << " tile to " << x << "," << y << std::endl;
	}
}

void AIPlayer::GetTileSelection()
{
	bool unnoccupiedSpace = false;

	while (!unnoccupiedSpace)
	{
		uint32_t x = rand() % model->GetWidth();
		uint32_t y = rand() % model->GetHeight();

		Tile tile = model->GetTile(x, y);
		if (tile.type != TileType::UNNOCCUPIED)
		{
			continue;
		}
		tile.type = TileType::PLAYER;
		tile.value = GetEntityID();
		model->SetTile(x, y, tile);
		unnoccupiedSpace = true;
		std::cout << "Adding Player " << GetEntityID() << " tile to " << x << "," << y << std::endl;
	}
}

