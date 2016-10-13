#include "BoardView.h"
#include "Board.h" 
#include "Tile.h"
#include "Entities.h"

#include <iostream>

int Entity::EntityCount = 0;

void TestWinConditions()
{
	// Initialise default board
	const Tile defaultTile = { TileType::UNNOCCUPIED, 0 };
	const int boardWidth = 6;
	const int boardHeight = 6;
	const int tilesRequiredToWin = 4;
	Board board(boardWidth, boardHeight, tilesRequiredToWin, defaultTile);
	board.Init();


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

	do
	{
		for (auto entity : entities)
		{
			view.Draw();

			if (!board.HasUnnocupiedTile()) //Yuck there is soo much wrong with this line....
			{
				break;
			}

			view.ClearOutputArea();
			entity->GetTileSelection();
		}
	} 
	while (!board.CheckWin());
	view.Draw();
	view.ClearOutputArea();

	if (board.GetWinner() == -1)
	{
		std::cout << "Stalemate. Board full" << std::endl;
	}
	else
	{
		std::cout << "Player " << board.GetWinner() << " Has won!" << std::endl;
	}

	system("pause");
	return 1;
}