#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
#include <fstream>
#include <sstream>

#include "imageio/image.h"
#include "imageio/filter.h"
#include "imageio/greyscale_filter.h"
#include "imageio/gaussian_filter.h"
#include "imageio/canny_edge_detect.h"
#include "imageio/image_helper.h"
#include "imageio/image_processor.h"
#include <sstream>

using std::unique_ptr;
using std::map;
using std::string;
using std::cout;
using std::function;
using namespace imageio;

class Entity : public TaskObserver {
public:
    void Notify(const vector<shared_ptr<IImage>> &outputs) override {
        int i = 1;
        for (const auto& output : outputs) {
            std::stringstream s;
            s << "output/" << i++ << ".png";
            output->SaveAs(s.str());
        }
        notified = true;
    }

    bool notified = false;
};

int main(int argc, const char* argv[]) {
    // Get input file, filter type, and output file from command line
    // argc = # of arguments
    // argv = an array of arguments
    string inputFile(argv[1]);
    string filterType(argv[2]);
    string outputFile(argv[3]);
    float low = 0.06;
    float high = 0.14;
    if (argc == 6) {
        low = std::stof(argv[4]);
        high = std::stof(argv[5]);
    }

    map<string, function<Filter*()>> filters;
    filters["greyscale"] = []() { return new GreyScaleFilter(); };
    filters["gaussian-blur"] = []() { return new GaussianFilter(5, 1.4f); };
    filters["canny-edge-detect"] = [low, high]() { return new CannyEdgeDetect(low, high); };

    auto filter_factory = filters[filterType];
    if (filter_factory == nullptr) {
        std::cout << "INVALID FILTER!" << std::endl;
        return EXIT_FAILURE;
    }

    unique_ptr<Filter> filter(filter_factory());
    unique_ptr<IImage> input(ImageHelper::FromFile(inputFile));
    Image output;
    filter->Apply({ input.get() }, { &output });
    output.SaveAs(outputFile);

    /*std::ifstream str ("input/color.txt");
    std::stringstream buffer;
    buffer << str.rdbuf();
    auto img = unique_ptr<IImage>(ImageHelper::FromString(buffer.str()));
    img->SaveAs(outputFile);*/

    // General concurrent ImageProcessor test
    /*Entity entity;
    bool ret = entity.RunFilter(filter_factory(), { ImageHelper::FromFile(inputFile) });
    ImageProcessor::Instance().Update();
    bool ret2 = entity.RunFilter(new GreyScaleFilter, { ImageHelper::FromFile(inputFile) });
    std::cout << "RESULT OF SECOND TRY: " << (ret2 ? "true" : "false") << std::endl;
    if (ret) {
        int steps = 0;
        while (not entity.notified) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            ImageProcessor::Instance().Update();
            ++steps;
        }
        std::cout << "STEPS: " << steps << std::endl;
    } else {
        std::cout << "Filter task failed!" << std::endl;
    }*/

    // ImageProcessor test with prematurely destroyed observer
    /*Entity* entity = new Entity;
    bool ret = entity->RunFilter(filter_factory(), { ImageHelper::FromFile(inputFile) });
    delete entity;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ImageProcessor::Instance().Update();*/

    return EXIT_SUCCESS;
}