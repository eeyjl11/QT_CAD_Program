#include "ostreamfix.h"
ostream &operator<<(ostream &stream, vector3d &obj)
{
    return stream << obj.getxCoord() << ", " << obj.getyCoord() << ", " << obj.getzCoord();
}
