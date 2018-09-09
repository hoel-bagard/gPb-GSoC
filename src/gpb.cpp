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

Gpb::Gpb(){
    prev_pt = cv::Point(-1, -1);
}

void Gpb::run(std:string input_frame) {
    img0 = cv::imread(input_frame, -1);

    multiscalePb(img0, input, gradients);


    // copy edge info into lattice struct
    cv::copyMakeBorder(input, boundaries.H, 1, 0, 0, 0, cv::BORDER_CONSTANT, 0.0);
    cv::copyMakeBorder(input, boundaries.V, 0, 0, 1, 0, cv::BORDER_CONSTANT, 0.0);
    cv::transpose(boundaries.H, boundaries.H);
    cv::transpose(boundaries.V, boundaries.V);
    boundaries.width = boundaries.H.rows;
    boundaries.height = boundaries.V.cols;

    Group::computeSupport(boundaries,dthresh,1.0f,ic);

    Group::computeAffinities2(ic,sigma,dthresh,&Aff);

    cv::globalPb(img0, Aff, gPb, gPb_thin, gPb_ori);

    delete Aff;

    // if you wanna conduct interactive segmentation later, choose DOUBLE_SIZE, otherwise SINGLE_SIZE will do either.
    cv::contour2ucm(gPb, gPb_ori, ucm, SINGLE_SIZE);

    ucm.copyTo(ucm2);


    // gPb.convertTo(gPb, CV_8UC3, 255.0);
    // ucm2.convertTo(ucm2, CV_8UC3, 255.0);

    // cv::imwrite(path_gpb_out.string() , gPb, compression_params);
    // cv::imwrite(path_ucm_out.string(), ucm2, compression_params);

}

