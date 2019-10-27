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

  multiscalePb(img0, input, gradients);

  // copy edge info into lattice struct
  cv::copyMakeBorder(input, boundaries->H, 1, 0, 0, 0, cv::BORDER_CONSTANT, 0.0);
  cv::copyMakeBorder(input, boundaries->V, 0, 0, 1, 0, cv::BORDER_CONSTANT, 0.0);
  cv::transpose(boundaries->H, boundaries->H);
  cv::transpose(boundaries->V, boundaries->V);
  boundaries->width = boundaries->H.rows;
  boundaries->height = boundaries->V.cols;

  Group::computeSupport(boundaries, dthresh, 1.0f, ic);

  Group::computeAffinities2(ic, sigma, dthresh, Aff);

  cv::globalPb(img0, Aff, gPb, gPb_thin, gPb_ori);

  // if you wanna conduct interactive segmentation later, choose
  // DOUBLE_SIZE, otherwise SINGLE_SIZE will do either.
  std::cout << "contour2ucm commencing ..." << std::endl;
  cv::contour2ucm(gPb, gPb_ori, ucm, SINGLE_SIZE);

  std::cout << "copying ..." << std::endl;
  ucm.copyTo(ucm2);

  std::cout << "converting ..." << std::endl;
  gPb.convertTo(gPb, CV_8UC3, 255.0);
  ucm2.convertTo(ucm2, CV_8UC3, 255.0);

  // cv::imwrite(path_gpb_out.string() , gPb, compression_params);
  // cv::imwrite(path_ucm_out.string(), ucm2, compression_params);
  std::cout << "reseting ..." << std::endl;
  reset();
  return bp::make_tuple(gPb, ucm2);
}

cv::Mat Gpb::texton(const cv::Mat &img, int n_ori, int Kmean_num,
                    double sigma_sm, double sigma_lg) {

  cv::Mat out;

  textonRun(img, out, n_ori, Kmean_num, sigma_sm, sigma_lg, 1);

  return out;
}
