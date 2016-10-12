//------------------------------------------------------------------------------
//
// Filename: Board.h
//
// Class represents the board
//
//------------------------------------------------------------------------------

#pragma once
#include "Tile.h"

#include <vector>

class Board
{
	const uint32_t		boardWidth;
	const uint32_t		boardHeight;


	const uint32_t		numTilesRequiredToWin;

	std::vector<Tile>	boardTiles;

public:
	Board(uint32_t width, uint32_t height, uint32_t tilesRequiredToWin, const Tile defaultTile) : boardWidth(width)
		, boardHeight(height)
		, numTilesRequiredToWin(tilesRequiredToWin)
		, boardTiles(width * height, defaultTile)
	{}

	void Init();

	uint32_t GetWidth() const 
	{
		return boardWidth;
	}

	uint32_t GetHeight() const 
	{
		return boardHeight;
	}

	const Tile& GetTile(uint32_t x, uint32_t y) const;
	void SetTile(uint32_t x, uint32_t y, const Tile& tile);

	bool CheckWin();
	bool CheckTile(uint32_t x, uint32_t y);

	bool CheckHorizontal(uint32_t x, uint32_t y);
	bool CheckVertical(uint32_t x, uint32_t y);
	bool CheckDiagonalLeft(uint32_t x, uint32_t y);
	bool CheckDiagonalRight(uint32_t x, uint32_t y);
};