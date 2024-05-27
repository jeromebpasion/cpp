#include "entity.h"
#include <QRandomGenerator>
#include <iostream>


Entity::Entity(){
    this->id = QRandomGenerator::system()->bounded(0,20000);
    width = 1.0;
    height = 1.0;
    static int none = 434;
//    std::cout   << "Entity size "<< sizeof(Entity)
//                << " width " << sizeof(width)
//                << " width " << sizeof(height)
//                << " id " << sizeof(id)
//                << " none " << sizeof(none)
//              << std::endl;

}

Entity::Entity(int id){
    Entity();
    this->id = id;
}
Entity::~Entity(){

}
