#include "../include/entTypeEnum.h"
#include "../mob/head/test.h"
#include <iostream>
//#include ""

EntityStdStorage::EntityStdStorage()
{
}

void EntityStdStorage::init(GlobalSys* passValue)
{
    m_globalSys = passValue;
    storageEntity[entType::player] = (new Personnage(m_globalSys->getWorld(), m_globalSys));
    storageEntitySize[entType::player] = sizeof(Personnage);
    storageEntity[entType::player]->setName("player");

    storageEntity[entType::dropeditem] = (new DropedItem(m_globalSys->getWorld(), m_globalSys));
    storageEntity[entType::dropeditem]->setName("droppedItem");
    storageEntitySize[entType::dropeditem] = sizeof(DropedItem);




storageEntity[entType::last] = (new entityError(m_globalSys->getWorld(), m_globalSys));
storageEntitySize[entType::last] = sizeof(entityError);

}

Entity EntityStdStorage::getEntityCpy(entType type)
{
    if (type >= 0 && type < entType::last)
    {
        return *storageEntity[type];
    }
    else
    {
        std::cout << "SystemWaring: une entit� hors du champ des entit� existente � �t� demand�, une entit� error a �t� renvoy�, mais une mauvaise utilisation de celle ci peut amener a des crash programme";
        return *storageEntity[entType::last];
    }
}
int EntityStdStorage::getEntitySize(entType type)
{

    if (type >= 0 && type < entType::last)
    {
        return storageEntitySize[type];
    }
    else
    {
        return storageEntitySize[entType::last];
    }
}











void EntityPtrContainer::update()
{

}
