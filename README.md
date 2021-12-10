# Multithreaded Canny Edge Detection

Opens .png files and performs canny edge detection on them. Uses multithreading to improve performance.

Contains a variety of interfaces and implementations for use with normal image processing and concurrent image processing.

## Demo

### To run demo:

1. ``cd project``
2. ``make demo``
3. ``./demo.exe [NUM_STEPS=50]``

The ``demo`` directory has multiple files demonstrating how to use:
* `CannyEdgeDetect` (demo.h)
* `ImageProcessor` (concurrent Filter runner) (demo.h)
* `TaskObserver` (run concurrent Filters and get notified) (demo.h)
* Implement your own `Filter` (sample_filter.h)
* Implement your own `ThreadedFilter` (sample_threaded_filter.h)
* `CompositeFilter` (demo.cpp)

## Shared Library (.so)

### To compile shared library:
1. ``cd project``
2. ``make imageio``

libimageio.so will be located in the lib folder.

To use it:

```bash
g++ -Wl,-rpath,lib [other compilation args...] -Llib -limageio 
```

This assumes that libimageio.so is located in the lib folder. Do note that library flags must come last (this is due to how g++ works).

## Run main executable

### To run:

1. ``cd project``
2. ``make``
3. ``make canny``

``./image_processor [inputs] [filter-type: canny-edge-detect, gaussian, ...] [outputs]``
