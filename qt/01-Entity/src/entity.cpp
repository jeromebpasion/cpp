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
    if (isFull()){
        //qDebug() << "Entities full.";
        return -1;
    }

        //add some dummy data
        float x = (float) QRandomGenerator::system()->bounded(-1000,1000);
        float y = (float) QRandomGenerator::system()->bounded(-1000,1000);
        float z = (float) QRandomGenerator::system()->bounded(-1000,1000);
        QVector3D pos(x/100.0, y/100.0, z/100.0);
        QQuaternion rot(2.0, -pos);

        int id= _availableEntities.dequeue();
        Entity * ent = new Entity(shape);
        ent->setPosition(pos);
        ent->setRotation(rot.normalized());

        _assignedEntities.insert(id, ent);

    return id;
}


int EntityManager::removeEntity(const int id)
{
    //todo
    int i = -1;
    i_assigned = _assignedEntities.find(id);
    if (_assignedEntities.remove(id) ==1 ){
        delete i_assigned.value();
        _assignedEntities.remove(i_assigned.key());
        _availableEntities.push_back(id);
    }

    return i;
}

const QList<Entity*> EntityManager::drawables() const{

    return _assignedEntities.values();
}

void Entity::setShape(SHAPE shape){
    _shape = shape;
}
void Entity::setPosition(const QVector3D position){
    _position = position;
}
void Entity::setRotation(const QQuaternion rotation){
    _rotation = rotation;
}

Entity::SHAPE Entity::shape() const {
    return _shape;
}
QVector3D Entity::position() const{
    return _position;
}
QQuaternion Entity::rotation() const{
    return _rotation.normalized();
}

bool EntityManager::isFull(){
    return (_availableEntities.isEmpty() ? true : false);
}
