#ifndef PHYSICS_H
#define PHYSICS_H

#include <QObject>
#include <vector>
#include <QMap>
#include <QVector3D>
#include <QQuaternion>

#include "entity.h"
#include <iostream>


//Transform component
struct Transform
{
    QVector3D position;
    QQuaternion rotation;
    QVector3D scale;
};

class PhysicsManager: public QObject
{
    Q_OBJECT


public:

    //delete copy constructor and = overload
    PhysicsManager(const PhysicsManager& obj) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    static PhysicsManager* getSingleton(){
        if (!singleton) {
           singleton = new PhysicsManager();
           return singleton;
        }
        return singleton;
    }
    //add and remove from physics system
    int addEntity(const Entity & entity);
    int removeEntity(const Entity & entity);

private:
    PhysicsManager();
    PhysicsManager(EntityManager * entityManager);
    static PhysicsManager * singleton;
    const EntityManager * e_manager;
};

#endif // PHYSICS_H
