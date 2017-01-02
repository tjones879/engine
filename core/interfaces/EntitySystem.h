#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <map>
#include "../structs/GameEntity.h"
#include "../structs/EntityComponent.h"

/**
* Contains all the logic necessary for executing
* each component.
*
* This class is extended by any systems defined
* and provides basic required functionality.
*/
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();
	void virtual update() = 0;
private:
	std::map<GameEntity*, EntityComponent> entityComponents;
};

#endif // !ENTITY_SYSTEM_H