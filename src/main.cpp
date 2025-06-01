#include "simulation.h"
#include <GLFW/glfw3.h>

int main()
{
    Simulation* simulation = new Simulation();
    simulation->run_loop();

    return 0;
}
