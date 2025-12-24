#include <iostream>
#include "engine/world.h"


using namespace std;

int main()
{    
    WorldConfig defaultConfig = WorldConfig();
    World world(defaultConfig);
    world.runSimulation();
    return 0;
}