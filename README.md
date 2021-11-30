# Multithreaded Canny Edge Detection

Opens .png files and performs canny edge detection on them. Uses multithreading to improve performance.

Contains a variety of interfaces and implementations for use with normal image processing and concurrent 
image processing.

## Demo

The ``demo`` directory has multiple files demonstrating how to use:
* `CannyEdgeDetect` (demo.h)
* `ImageProcessor` (concurrent Filter runner) (demo.h)
* `TaskObserver` (run concurrent Filters and get notified) (demo.h)
* Implement your own `Filter` (sample_filter.h)
* Implement your own `ThreadedFilter` (sample_threaded_filter.h)
* `CompositeFilter` (demo.cpp)

`ImageProcessor` and `TaskObserver` are designed to be used with the drone simulation as demonstrated.

## How to install

To use this library you will first want to link it. The library files have already been provided in the 
correct location.

**Docker**

If you are using docker, you will need to rebuild the image first (only once to download the library file):

```shell
bin/rebuild-env.sh
```

**Makefile**

To link the library, if you are using the provided Makefile from the support code, you will simply need to
add the library to the `LIBS` variable in your Makefile.

If you are using a CSE labs machine, you will need to use `-limageio-cse`.

If you are using Docker, you will need to use `-limageio-docker`.

```makefile
LIBS = -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread  $(OPENCV_LIBS)
```

becomes

```makefile
LIBS = -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread  $(OPENCV_LIBS) -limageio-cse
```

**Includes**

You can copy the contents of the `include` directory to your own `include` directory.

All of the necessary header files will be in their own directory named `imageio`.

To use the library in your project, simply prefix the header you want to include with the directory:
```c++
#include "imageio/image_processor.h"
```
etc.

This is also demonstrated in the demo files.