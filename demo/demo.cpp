#include <iostream>
#include <memory>
#include <string>

#include "imageio/canny_edge_detect.h"
#include "imageio/iimage.h"
#include "imageio/image_helper.h"
#include "imageio/composite_filter.h"
#include "imageio/greyscale_filter.h"
#include "imageio/gaussian_filter.h"

// Load an input and perform some filtering, then save the outputs

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./demo.exe inputfile.png" << std::endl;
        return 1;
    }
    std::string inputFile(argv[1]);
    // Load input/statue.png
    std::unique_ptr<imageio::IImage> statue(imageio::ImageHelper::FromFile(inputFile));

    // Alternatively:
    // imageio::Image statue;
    // statue.Load("input/statue.png");

    // How to use composite filter
    imageio::CompositeFilter composite;
    composite.AddFilter(new imageio::GreyScaleFilter());
    composite.AddFilter(new imageio::GaussianFilter(5, 1.6f));
    imageio::Image output;
    composite.Apply( { statue.get() }, { &output } );
    output.SaveAs("grey-blur.png");

    // How to use canny edge detection
    imageio::Image cannyOutput;
    imageio::CannyEdgeDetect canny;
    canny.Apply( { statue.get() }, { &cannyOutput } );
    cannyOutput.SaveAs("edges.png");
    return 0;
}
