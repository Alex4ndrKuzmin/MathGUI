#ifndef OBJECTCOUNTER_H
#define OBJECTCOUNTER_H

#include <QVector>
#include <QSet>

class ObjectCounter
{
protected:

    uint16_t id;

    static QSet<uint16_t> held_id_set;
    static uint16_t minimal_held_id;

public:

    ObjectCounter()
    {
        id = minimal_held_id;
        held_id_set.insert(minimal_held_id);
        while (held_id_set.contains(minimal_held_id))
        {
            minimal_held_id++;
        }
    }

    ~ObjectCounter()
    {
        held_id_set.erase(held_id_set.find(id));
        if (id < minimal_held_id)
            minimal_held_id = id;
    }

    uint16_t ID()
    {
        return id;
    }
};



#endif // OBJECTCOUNTER_H
