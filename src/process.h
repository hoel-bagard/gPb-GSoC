#ifndef __process_h_
#define __process_h_

#include "globalPb.h"
#include "affinity.h"
#include "ic.h"
#include "contour2ucm.h"
#include <iostream>
#include <string>
#include <opencv2/core/mat.hpp>

void process(const cv::Mat &im, cv::Mat &gPb, cv::Mat &ucm2);

#endif
