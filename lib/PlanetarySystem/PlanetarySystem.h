#include <string>
#include <vector>

using namespace std;

namespace PlanetarySpace {
    struct InterstellarVec3f {
        float x;
        float y;
        float z;

        InterstellarVec3f(){};
        InterstellarVec3f(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {};
    };
    struct RelativeInterstellarVec3f: public InterstellarVec3f {
        InterstellarVec3f* origin;

        RelativeInterstellarVec3f(float p_x, float p_y, float p_z, InterstellarVec3f* p_origin) : InterstellarVec3f(p_x, p_y, p_z) {
            origin = p_origin;
        }
    };

    //PlanetarySpace::RelativeInterstellarVec3f* t = new PlanetarySpace::RelativeInterstellarVec3f(45, 32, 3, new PlanetarySpace::InterstellarVec3f(45, 3, 3));

}

namespace PlanetaryDatabase {
    
}