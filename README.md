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

To use this library you need to link it. The library files have already been provided in the 
correct location. This should be as simple as getting the updated Makefile from support-code.

**Docker**

Get the updated Dockerfile from the support-code here: https://github.umn.edu/umn-csci-3081-f21/shared-upstream/blob/support-code/Dockerfile

You will then need to rebuild the image (only once to download the files):

```shell
bin/build-env.sh
```

**Makefile**

To use the library, simply get the updated Makefile from the support-code here:
https://github.umn.edu/umn-csci-3081-f21/shared-upstream/blob/support-code/project/Makefile.

The only changes are:

Adding `-limageio` to `LIBS`

Adding `-Wl,-rpath,$(DEP_DIR)/lib` to `CXXFLAGS`

This last part must come AFTER `-include $(ROOT_DIR)/config/settings`

**Includes**

All the necessary includes are installed for you. You can still view the provided header files
to read the documentation.

To use the library in your project, simply prefix the header you want to include with the directory:
```c++
#include "imageio/image_processor.h"
```
etc.

This is also demonstrated in the demo files.

**Namespace**

This library uses the namespace `imageio`.

You can use

```c++
using namespace imageio;
```

if you find that useful.
