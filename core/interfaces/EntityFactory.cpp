#include "EntityFactory.h"

EntityFactory::EntityFactory(ComponentManager* componentManager)
{
	this->componentManager = componentManager;
}

EntityFactory::~EntityFactory()
{
}
