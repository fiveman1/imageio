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
#include <sstream>

using std::unique_ptr;
using std::map;
using std::string;
using std::cout;
using std::function;
using namespace imageio;

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

    return EXIT_SUCCESS;
}