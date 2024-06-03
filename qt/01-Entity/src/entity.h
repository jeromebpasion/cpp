#ifndef ENTITY_H
#define ENTITY_H

#include <QRandomGenerator>
#include <QMap>
#include <QQueue>
#include <iostream>
#include <QVector3D>
#include <QVector2D>
#include <QQuaternion>
#include <QRandomGenerator>

class Entity
{
public:
    enum SHAPE {CUBE, SPHERE, TRIANGLE};

    Entity();
    Entity(SHAPE shape);

protected:

private:
    SHAPE _shape;
    QVector3D _position;
    QQuaternion _rotation;

};

class EntityManager
{
private:
    EntityManager();
    static EntityManager * singleton;
    QQueue<int> _availableEntities;
    QMap<int, Entity*> _assignedEntities;

    QQueue<int>::ConstIterator i_available;
    QMap<int, Entity*>::ConstIterator i_assigned;
    int MAX_ENTITIES = 200;

public:
    //delete copy constructor and = overload
    EntityManager(const EntityManager& obj) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    static EntityManager* getSingleton(){
        if (!singleton) {
           singleton = new EntityManager();
           return singleton;
        }
        return singleton;
    }
    int createEntity(const Entity::SHAPE);
    int removeEntity(const int id);
    int setIdentityProperties(const int id,const Entity::SHAPE);

    const QList<Entity*> drawables() const;

protected:

};

#endif // ENTITY_H
