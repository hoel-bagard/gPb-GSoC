On arch at least, [arpack](https://archlinux.org/packages/community/x86_64/arpack/) needs to be installed.\
To run the demo,`scikit-image` and `matplotlib` are required.\ 

I made a change to the CMA because [TBB](https://github.com/ceres-solver/ceres-solver/issues/669) changed.

# Warning
This code is borderline functional due to the underlying UCM/Normalised cut implementation of [https://github.com/HiDiYANG/gPb-GSoC]. In particular, seg-faults occur predominantly when input images are large >400x400. Feel free to suggest bug fixes/PRs.

# gPB-UCM
This method generates Ultra Metric Contour hierarchical segmentation of images as in
```
Arbelaez, Pablo, et al. "Contour detection and hierarchical image segmentation." IEEE transactions on pattern analysis and machine intelligence 33.5 (2010): 898-916.
```

It is a port from https://github.com/vrabaud/gPb.
It comes with a boost/python wrapper and uses OpenCV internally.

## Prerequisites
* [OpenCv](https://opencv.org/) > 4

To compile with python wrapper you will need:
* [Boost](http://www.boost.org/)
* [Python](https://www.python.org/)

It is tested with Boost > 1.58, OpenCV > 4, and Python > 3

## Installing

Clone repository along with submodules
```
git clone --recurse-submodules git@github.com:lejeunel/gPb-GSoC.git
```

Install the package with:
```
cd gPb-GSoC
mkdir build
cd build
```
For python wrapper:
```
cmake -DUSE_PY ..
make
python src/setup.py install
```
Without wrapper:
```
cmake ..
make
```

## Getting started

See demo.py or main

