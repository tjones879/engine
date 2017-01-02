#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

typedef unsigned int familyId;

/**
* An EntityComponent contains *data only*
* for use by an EntitySystem.
*
*/
class EntityComponent
{
public:
	EntityComponent();
	~EntityComponent();
	familyId getFamily();
private:
	familyId componentFamily;
};

#endif // !ENTITY_COMPONENT_H