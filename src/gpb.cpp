//
//    gPb opencv implementation
//    including interactive segmentation.
//
//    Created by Di Yang, Vicent Rabaud, and Gary Bradski on 31/05/13.
//    Copyright (c) 2013 The Australian National University.
//    and Willow Garage inc.
//    All rights reserved.
//
//

#include "gpb.h"
#include "filters.h"

bp::tuple Gpb::run(const cv::Mat &img0) {

    cv::Mat gPb, ucm, gPb_thin;
    vector<cv::Mat> gPb_ori;

    cv::globalPb(img0, gPb, gPb_thin, gPb_ori);

  // if you wanna conduct interactive segmentation later, choose
  // DOUBLE_SIZE, otherwise SINGLE_SIZE will do either.
  cv::contour2ucm(gPb, gPb_ori, ucm, SINGLE_SIZE);

  ucm.copyTo(ucm2);

  gPb.convertTo(gPb, CV_8UC3, 255.0);
  ucm2.convertTo(ucm2, CV_8UC3, 255.0);

  return bp::make_tuple(gPb.clone(), ucm2.clone());
}

cv::Mat Gpb::texton(const cv::Mat &img, int n_ori, int Kmean_num,
                    double sigma_sm, double sigma_lg) {

  cv::Mat out;

  textonRun(img, out, n_ori, Kmean_num, sigma_sm, sigma_lg, 1);

  return out;
}
