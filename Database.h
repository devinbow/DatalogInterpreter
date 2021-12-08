#include "Relation.h"
#include <string>
#include <map>
#include <iterator>
#ifndef DATABASE_H
#define DATABASE_H

class Database
{
private:
    std::map<std::string, Relation*> mymap;
public:
    void addRelation(Relation* current_rel)
    {
        std::string relation_name = "";
        relation_name = current_rel->getName();
        mymap.insert(std::pair<std::string, Relation*>(relation_name, current_rel));
    }
    Relation* getRelationFromKey(std::string key)
    {
        return mymap.at(key);
    }

    std::vector<Relation*> getRelationsInDatabase()
    {
        std::vector<Relation*> database_relations;
        for (std::map<std::string, Relation*>::iterator it = mymap.begin(); it != mymap.end(); it++)
        {
            database_relations.push_back(it->second);
        }
        return database_relations;
    }

    void updateRelation(Relation* new_relation)
    {
       std::map<std::string, Relation*>::iterator it;
       for (std::map<std::string, Relation*>::iterator it = mymap.begin(); it != mymap.end(); it++)
       {
           if (it->first == new_relation->getName())
           {
               it->second = new_relation;
           }
       }
    }
};

#endif