#include "physics.h"

PhysicsManager * PhysicsManager::singleton = nullptr;

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::PhysicsManager( EntityManager * manager)
{
    e_manager = manager;
}

//add and remove from physics system
int PhysicsManager::addEntity(const Entity & entity){

    return 0;
}

int PhysicsManager::removeEntity(const Entity & entity){

    return 0;
}
