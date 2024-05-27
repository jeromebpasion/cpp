#include <iostream>
#include <string>
#include <QCoreApplication>
#include <QRandomGenerator>
#include "entity.h"


template<class AnyType>
class Collection
{
private:
    std::vector<AnyType> vector;

public:
    Collection(std::initializer_list<AnyType> list) : vector(list)
    {
        std::cout << "Collection constructed with " << list.size() << std::endl;
    }

    void append(std::initializer_list<AnyType> list){
        vector.insert(vector.end(), list.begin(), list.end());
        std::cout << "Collection appended with " << list.size() << std::endl;

    }

    void remove(const int id){
        //std::vector<AnyType>::iterator iterator = vector.begin();
        auto foundIndex = 0;

        for (auto i : vector){
            if (i.id == id ){
                vector.erase(vector.begin()+foundIndex);
                std::cout << "Removed Entity " << id<< " " << vector.size() << std::endl;
            }
            ++foundIndex;
        }
    }
    std::pair<const AnyType*, std::size_t> copy_() const
    {
        return {&vector[0], vector.size()};
    }

};



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Entity * entity = new Entity();
    std::cout << entity->id <<std::endl;

    Collection<Entity> collection = {32,41};
    collection.append({55,66,77});

    collection.remove(55);

    delete entity;
    return 0;
    //return a.exec();
}
