#ifndef DEMO_H
#define DEMO_H

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "imageio/canny_edge_detect.h"
#include "imageio/composite_filter.h"
#include "imageio/iimage.h"
#include "imageio/image_helper.h"
#include "imageio/image_processor.h"

using namespace std::chrono;
using namespace std::this_thread;
using std::unique_ptr;
using std::vector;
using std::cout;
using std::endl;
using std::string;

using namespace imageio; // Use the imageio namespace so we don't have to put
                         // imageio:: in front of everything

unique_ptr<IImage> statue; // static variable to hold statue.png for demo purposes

// How to override the TaskObserver class
// Implement Notify(), use RunFilter(new MyFilter(), new MyImage())
// Read documentation for TaskObserver (which can be found in image_processor.h)
// Override this class so your entities can run filters concurrently
// and received notifications (this demonstrates the observer pattern)
class Entity : public TaskObserver {
public:
    explicit Entity(string name) : name(std::move(name)) {}

    void Notify(const vector<shared_ptr<IImage>> &outputs) override {
        // When notified, print our name then save the image
        cout << "Entity (" << name << ") notified" << endl;
        outputs[0]->SaveAs("output/edges_" + name + ".png");
        run_edge_detect = false;
        filter_active = false;
    }

    void Update(float dt) {
        // start a filter task, make sure to use the result of RunFilter to check
        // if the task was started or not
        if (run_edge_detect and not filter_active) {
            // runs canny edge detection using the CannyEdgeDetect filter
            // note how the filter and image are *new* objects, these must be *new*
            filter_active = RunFilter(new CannyEdgeDetect(0.1, 0.3), { statue->Clone() });
        }
    }

protected:
    string name;
    bool run_edge_detect = true;
    bool filter_active = false;
};

// This is similar to WebApp in the project
class SimulationApp {
public:
    void AddEntity(Entity* entity) {
        entities.emplace_back(entity);
    }

    void Update(float dt) {
        // This must call this ImageProcessor singleton Update() method
        // This is what tells the ImageProcessor to send tasks/output images back to observers
        ImageProcessor::Instance().Update();
        for (const auto& entity : entities) {
            entity->Update(dt);
        }
    }

protected:
    vector<unique_ptr<Entity>> entities;
};

#endif //DEMO_H
