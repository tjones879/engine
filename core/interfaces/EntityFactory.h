#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../file_parser/DataFactory.h"
#include "ComponentManager.h"

/**
* An EntityFactory handles the deserialization of
* data files that define entities specifically.
* 
* All components attached to the entity are sent
* to a ComponentManager.
*/
class EntityFactory : public DataFactory
{
public:
	EntityFactory(ComponentManager* componentFactory);
	~EntityFactory();
private:
	ComponentManager* componentManager;
};


#endif // !ENTITY_FACTORY_H

