#include "ObjectCounter.h"

QSet<uint16_t> ObjectCounter::held_id_set;
uint16_t ObjectCounter::minimal_held_id = 0;
