//------------------------------------------------------------------------------
//
// Filename: Board.h
//
// Class represents the board
//
//------------------------------------------------------------------------------
#include "Board.h"

#include <assert.h>
#include <time.h>
#include <iostream>

void Board::Init()
{
	srand(time(nullptr));

	Tile unplayableTile = { TileType::UNPLAYABLE, 0 };
	const uint32_t unplayableTileCount = 4;
	for (uint32_t i = 0; i < unplayableTileCount;)
	{
		int x = rand() % boardWidth;
		int y = rand() % boardHeight;
		const Tile& randomTile = GetTile(x, y);

		if (randomTile.type != TileType::UNPLAYABLE)
		{
			SetTile(x, y, unplayableTile);
			++i;
		}
	}
};

const Tile& Board::GetTile(uint32_t x, uint32_t y) const
{
	assert(x < boardWidth && y < boardHeight);
	return boardTiles[y * boardWidth + x];
}

void Board::SetTile(uint32_t x, uint32_t y, const Tile& tile)
{
	assert(x < boardWidth && y < boardHeight);
	boardTiles[y * boardWidth + x] = tile;
}

bool Board::HasUnnocupiedTile() const
{
	for (uint32_t x = 0; x < boardWidth; ++x)
	{
		for (uint32_t y = 0; y < boardHeight; ++y)
		{
			Tile currentTile = GetTile(x, y);
			if (currentTile.type == TileType::UNNOCCUPIED)
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::CheckWin()
{
	for (uint32_t x = 0; x < boardWidth; ++x)
	{
		for (uint32_t y = 0; y < boardHeight; ++y)
		{
			if (CheckTile(x, y))
			{
				Tile currentTile = GetTile(x, y);
				winningPlayer = currentTile.value;

				return true;
			}
		}
	}

	return false;
}

bool Board::CheckTile(uint32_t x, uint32_t y)
{
	Tile currentTile = GetTile(x, y);
	if (currentTile.type != TileType::PLAYER)
	{
		return false;
	}

	//Check Horizontal
	if (x + numTilesRequiredToWin <= boardWidth 
		&& CheckHorizontal(x, y))
	{
		return true;
	}

	if (y + numTilesRequiredToWin <= boardHeight)
	{
		//Check Diagonal Left
		if (x + 1 >= numTilesRequiredToWin
			&& CheckDiagonalLeft(x, y))
		{
			return true;
		}

		if (CheckVertical(x, y))
		{
			return true;
		}

		if (x + numTilesRequiredToWin <= boardWidth
			&& CheckDiagonalRight(x, y))
		{
			return true;
		}
	}

	return false;
}

bool Board::CheckHorizontal(uint32_t x, uint32_t y)
{
	Tile currentTile = GetTile(x, y);
	for (uint32_t i = 1; i < numTilesRequiredToWin; i++)
	{
		Tile nextTile = GetTile(x + i, y);
		if (currentTile.value != nextTile.value || nextTile.type != TileType::PLAYER)
		{
			return false;
		}
	}

	std::cout << "Player " << currentTile.value << " won by getting a horizontal line" << std::endl;
	return true;
}

bool Board::CheckVertical(uint32_t x, uint32_t y)
{
	Tile currentTile = GetTile(x, y);
	for (uint32_t i = 1; i < numTilesRequiredToWin; i++)
	{
		Tile nextTile = GetTile(x, y + i);
		if (currentTile.value != nextTile.value || nextTile.type != TileType::PLAYER)
		{
			return false;
		}
	}

	std::cout << "Player " << currentTile.value << " won by getting a vertical line" << std::endl;
	return true;
}

bool Board::CheckDiagonalLeft(uint32_t x, uint32_t y)
{
	Tile currentTile = GetTile(x, y);
	for (uint32_t i = 1; i < numTilesRequiredToWin; i++)
	{
		Tile nextTile = GetTile(x - i, y + i);
		if (currentTile.value != nextTile.value || nextTile.type != TileType::PLAYER)
		{
			return false;
		}
	}

	std::cout << "Player " << currentTile.value << " won by getting a diagonal left line" << std::endl;
	return true;
}

bool Board::CheckDiagonalRight(uint32_t x, uint32_t y)
{
	Tile currentTile = GetTile(x, y);
	for (uint32_t i = 1; i < numTilesRequiredToWin; i++)
	{
		Tile nextTile = GetTile(x + i, y + i);
		if (currentTile.value != nextTile.value || nextTile.type != TileType::PLAYER)
		{
			return false;
		}
	}

	std::cout << "Player " << currentTile.value << " won by getting a diagonal right line" << std::endl;
	return true;
}
