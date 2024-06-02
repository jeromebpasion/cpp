#ifndef ENTITY_H
#define ENTITY_H

#include <QRandomGenerator>
#include <QMap>
#include <iostream>
#include <QVector3D>
#include <QVector2D>


class Entity
{
public:
    Entity();

protected:

private:


};

class EntityManager
{
private:
    EntityManager();
    static EntityManager * singleton;
    QMap<int, Entity*> entities;

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
    int addEntity(const int id);
    int removeEntity(const int id);

protected:

};

#endif // ENTITY_H
