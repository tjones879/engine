#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "../file_parser/DataFactory.h"

/**
* The component factory handles all deserialization of
* EntityComponent schema files.
*/
class ComponentFactory : public DataFactory
{
public:
	ComponentFactory();
	~ComponentFactory();
};

#endif // !COMPONENT_FACTORY_H