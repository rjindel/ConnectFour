//------------------------------------------------------------------------------
//
// Filename: BoardView.h
//
// 
//
//------------------------------------------------------------------------------
#pragma once
#include "BoardView.h"

BoardView::BoardView(const Board* board) : model(board)
	, wallWidth		(1)
	, wallHeight	(1)
	, cellWidth		(1)
	, cellHeight	(1)
	, boardPosition { 1, 1 }
{
	boardWidth = model->GetWidth() * (wallWidth + cellWidth) + wallWidth;
	boardHeight = model->GetHeight() * (wallHeight + cellHeight) + wallHeight;
}

void BoardView::Init()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo = { 0 };
	if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
	{
		printf("Error: Unknown error getting console");
		return;
	}

	if (bufferInfo.dwSize.X < (boardWidth + boardPosition.X)
		|| bufferInfo.dwSize.Y < (boardHeight + boardPosition.Y))
	{
		//TODO: This makes too many assumptions e.g. that no space is required to for asking the player where he wants to place his piece
		COORD minimumScreenSize = { boardWidth, boardHeight };
		SetConsoleScreenBufferSize(consoleHandle, minimumScreenSize);
	}
	
}

COORD BoardView::GetCellPosition(uint32_t x, uint32_t y)
{
	COORD cellPosition = boardPosition;
	cellPosition.X += x * (cellWidth + wallWidth) + wallWidth;
	cellPosition.Y += y * (cellHeight + wallHeight) + wallHeight;

	return cellPosition;
}

void BoardView::DrawLegend()
{
	COORD currentBoardPosition = boardPosition;

	//place one line above board, and align to the 1st horizontal column by adding wall width
	currentBoardPosition.X += wallWidth;
	currentBoardPosition.Y -= 1;
	for (uint32_t i = 0; i < model->GetWidth(); ++i)
	{
		SetConsoleCursorPosition(consoleHandle, currentBoardPosition);
		int legend = i + '0';
		putchar(legend);
		currentBoardPosition.X += cellWidth + wallWidth;
	}

	currentBoardPosition.X = boardPosition.X - 1;
	currentBoardPosition.Y += 1 + wallHeight;
	for (uint32_t i = 0; i < model->GetHeight(); ++i)
	{
		SetConsoleCursorPosition(consoleHandle, currentBoardPosition);
		int legend = i + '0';
		putchar(legend);
		currentBoardPosition.Y += cellHeight + cellHeight;
	}
}

void BoardView::Draw()
{
	DrawLegend();

	char wallCharacter = '*';
	COORD currentBoardPosition = boardPosition;

	for (uint32_t i = 0; i < boardHeight; ++i, ++currentBoardPosition.Y)
	{
		DWORD numCharsWritten = 0;
		FillConsoleOutputCharacter(consoleHandle, wallCharacter, boardWidth, currentBoardPosition, &numCharsWritten );
	}

	for (uint32_t y = 0; y < model->GetHeight(); ++y)
	{
		for (uint32_t x = 0; x < model->GetWidth(); ++x)
		{
			COORD cellPosition = GetCellPosition(x, y);
			SetConsoleCursorPosition(consoleHandle, cellPosition);

			Tile currentTile = model->GetTile(x, y);
			char tileCharacter = GetTileCharacter(currentTile);
			putchar(tileCharacter);
		}
	}

	//Move cursor to after the board so it isn't accidently overwritten
	currentBoardPosition.X = 0;
	currentBoardPosition.Y = boardPosition.Y + boardHeight;
	SetConsoleCursorPosition(consoleHandle, currentBoardPosition);
}

char BoardView::GetTileCharacter(const Tile tile) const
{
	switch (tile.type)
	{
	case TileType::UNPLAYABLE:
		return 'x';
	case TileType::PLAYER:
		return tile.value + '0';
	case TileType::UNNOCCUPIED:
	default:
		return ' ';
	}
	
	return ' ';
}