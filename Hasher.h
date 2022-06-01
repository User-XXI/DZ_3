#ifndef DZ_3_HASHER_H
#define DZ_3_HASHER_H


#include <string>
#include "Sotrudnik.h"

class Hasher {
public:
	size_t operator()(const Sotrudnik & ob) const;
};

#endif //DZ_3_HASHER_H
