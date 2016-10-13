//------------------------------------------------------------------------------
//
// Filename: BoardView.h
//
// 
//
//------------------------------------------------------------------------------
#pragma once
#include "Tile.h"
#include "Board.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class BoardView
{
	const uint32_t wallWidth;
	const uint32_t wallHeight;
	const uint32_t cellWidth;
	const uint32_t cellHeight;

	uint32_t boardWidth;
	uint32_t boardHeight;

	COORD boardPosition;

	HANDLE consoleHandle;
	const Board* model;

	char GetTileCharacter(const Tile tile) const;

	void DrawLegend();
public:
	BoardView(const Board* board);
	void Init();
	void Draw();

	void ClearOutputArea();

	COORD GetCellPosition(uint32_t x, uint32_t y);
};