#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "Personnage.hpp"
#include "GlobalSys.hpp"
#include <vector>
#include "allEnum.h"

class EntityStdStorage //les nom des entity que vous creez ici doivent etre identique a leurs nom dans l'enum
{
public:
    EntityStdStorage();
    void init(GlobalSys* passValue);
    Entity getEntityCpy(entType type);
    int getEntitySize(entType type);
    Entity* storageEntity[entType::last+1];
    int storageEntitySize[entType::last+1];

private:


protected:
    GlobalSys* m_globalSys;
};

struct EntityPtrContainer
{
    void update();
    std::vector<Entity*> entityList;
};
