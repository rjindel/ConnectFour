//------------------------------------------------------------------------------
//
// Filename: Tile.h
//
// Define a basic tile that makes up the game board
//
//------------------------------------------------------------------------------
#pragma once

enum class TileType
{
	UNNOCCUPIED,
	UNPLAYABLE,
	PLAYER,
};

struct Tile
{
	TileType	type;
	int			value;
};
