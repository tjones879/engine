#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

typedef unsigned int uint32;

class GameEntity
{
public:
	GameEntity(uint32 entityId);
private:
	uint32 entityId;
};

#endif // !GAME_ENTITY_H

