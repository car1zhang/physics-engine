#include "simulation.h"

int main() {
    Simulation* simulation = new Simulation();
    simulation->RunLoop();
    delete simulation;

    return 0;
}
