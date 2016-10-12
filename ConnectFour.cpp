#include "BoardView.h"
#include "Board.h" 
#include "Tile.h"

#include <iostream>

class Entity
{
	static int EntityCount;
	int entityID;
public:
	Entity() : entityID(EntityCount++) {}
	int GetEntityID() const
	{
		return entityID;
	}

	virtual void GetTileSelection() = 0;
};

int Entity::EntityCount = 0;

class Player : public Entity
{
	Board* model;
public:
	Player(Board* board) : model(board) {}
	virtual void GetTileSelection() override;
};

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
			std::cout << "Invalid co-ordinate enter a value between 0 and " << model->GetWidth() - 1<< " and a value between 0 and " << model->GetHeight() - 1<< std::endl;
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

class AIPlayer : public Entity
{
	Board* model;
public:
	AIPlayer(Board* board) : model(board) {}
	virtual void GetTileSelection() override;
};

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

int main()
{
	const Tile defaultTile = { TileType::UNNOCCUPIED, 0 };
	const int boardWidth = 6;
	const int boardHeight = 6;
	const int tilesRequiredToWin = 4;
	Board board(boardWidth, boardHeight, tilesRequiredToWin, defaultTile);
	board.Init();

	BoardView view(&board);
	view.Init();

	std::vector<Entity*> entities;
	Player player1(&board);
	Player player2(&board);
	AIPlayer aiPlayer(&board);

	entities.push_back(&player1);
	entities.push_back(&player2);
	entities.push_back(&aiPlayer);

	view.Draw();
	while (!board.CheckWin())
	{
		for (auto entity : entities)
		{
			entity->GetTileSelection();
			view.Draw();
		}
	}

	return 1;
}