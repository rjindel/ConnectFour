#pragma once

class Board;

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

class Player : public Entity
{
	Board* model;
public:
	Player(Board* board) : model(board) {}
	virtual void GetTileSelection() override;
};

class AIPlayer : public Entity
{
	Board* model;
public:
	AIPlayer(Board* board) : model(board) {}
	virtual void GetTileSelection() override;
};

