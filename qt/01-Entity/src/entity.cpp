#include "entity.h"


Entity:: Entity(){


}

//===================================
//  EntityManager
//===================================

EntityManager * EntityManager::singleton = nullptr;

EntityManager::EntityManager()
{

}

int EntityManager::addEntity(const int id)
{
    Entity * entity = new Entity();
    entities.insert(id, entity);
    return 0;
}

int EntityManager::removeEntity(const int id)
{
    return 0;
}
