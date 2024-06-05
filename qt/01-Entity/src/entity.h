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
    enum SHAPE {CUBE, SPHERE, PYRAMID};

    Entity();
    Entity(SHAPE shape);

    void setShape(SHAPE shape);
    void setPosition(const QVector3D position);
    void setRotation(const QQuaternion rotation);

    SHAPE shape() const;
    QVector3D position() const;
    QQuaternion rotation() const;

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
    bool isFull();

    const QList<Entity*> drawables() const;
    const static int MAX_ENTITIES = 200;

protected:

};

#endif // ENTITY_H
