#include "entity.h"


Entity:: Entity(){


}

Entity:: Entity(Entity::SHAPE shape){
    _shape = shape;
}
//===================================
//  EntityManager
//===================================

EntityManager * EntityManager::singleton = nullptr;

EntityManager::EntityManager()
{
    for (int i = 0; i < MAX_ENTITIES; ++i){
        _availableEntities.push_back(i);
    }
}

int EntityManager::createEntity(Entity::SHAPE shape)
{
    int i = -1;
    bool empt = _availableEntities.isEmpty();
    if (!_availableEntities.isEmpty()){
        float x = (float) QRandomGenerator::system()->bounded(-1000,1000);
        float y = (float) QRandomGenerator::system()->bounded(-1000,1000);
        float z = (float) QRandomGenerator::system()->bounded(-1000,1000);
        QVector3D pos(x/1000.0, y/1000.0, z/1000.0);
        QQuaternion rot(2.0, -pos);

        i = _availableEntities.dequeue();
        _assignedEntities.insert(i, new Entity(shape));
    }
    return i;
}


int EntityManager::removeEntity(const int id)
{
    //todo
    int i = -1;
    i_assigned = _assignedEntities.find(id);

    if (i_assigned.key()!= _assignedEntities.end().key()){
        i = _availableEntities.dequeue();
        _availableEntities.push_back(i);
        delete i_assigned.value();
        _assignedEntities.remove(i_assigned.key());

    }

    return i;
}

const QList<Entity*> EntityManager::drawables() const{

    return _assignedEntities.values();
}
