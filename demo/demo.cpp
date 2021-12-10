#include "demo.h"

/* Driver code */

// 1. Create and setup simulation
// 2. Add two entities to the simulation
// 3. Run update loop, loop sleeps for 0.01s then runs again
// 4. Entities will run a filter task (canny edge detection) at the start of the loop
// 5. They will be notified by the end (if they aren't then increase the amount of steps
//    given (./demo.exe [NUM_STEPS])

int main(int argc, char* argv[]) {
    int max_steps = 50;
    if (argc > 1) {
        max_steps = std::stoi(argv[1]);
    }

    // Load statue.png into static variable
    statue.reset(ImageHelper::FromFile("input/statue.png"));

    // How to use composite filter
    CompositeFilter composite;
    composite.AddFilter(new GreyScaleFilter());
    composite.AddFilter(new GaussianFilter(5, 1.6f));
    Image output;
    composite.Apply( { statue.get() }, { &output } );
    output.SaveAs("output/grey-blur.png");

    // Setup
    SimulationApp simulation;
    simulation.AddEntity(new Entity("Entity_1"));
    simulation.AddEntity(new Entity("Entity_2"));

    // Simulation loop
    int steps = 0;
    auto start = steady_clock::now(); // measure total time taken at end of loop
    auto clock = steady_clock::now(); // measure dt

    while (steps < max_steps) {
        sleep_for(milliseconds(1)); // artifical sleep for 0.01s

        // calculate time between this step and the last
        auto now = steady_clock::now();
        auto duration = duration_cast<microseconds>(now - clock).count();
        clock = now;
        float dt = static_cast<float>(duration) / 100000.0f;

        // update simulation
        simulation.Update(dt);

        // increment step
        cout << "steps: " << steps++ << ", dt: " << dt << endl;
    }
    // print total time taken
    cout << "time taken (ms): " << duration_cast<milliseconds>(steady_clock::now() - start).count() << endl;
}
