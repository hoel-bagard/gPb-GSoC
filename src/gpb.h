#include "globalPb.h"
#include "affinity.h"
#include "ic.h"
#include "contour2ucm.h"
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;
namespace bn = boost::python::numpy;
namespace bp = boost::python;

struct Gpb{
    cv::Mat markers, ucm2, bd, ll;
    cv::Mat img0, gPb_thin;
    cv::Mat gPb, ucm;
    cv::Mat input;
    vector<cv::Mat> gPb_ori;
    cv::Point prev_pt;
    double c;
    int dthresh = 5;
    float sigma = 0.1;
    vector<vector<cv::Mat> > gradients;
    Group::SupportMap ic;
    Group::DualLattice boundaries;
    SMatrix* Aff = NULL;
    vector<int> compression_params;

    std::string input_frame;

    void run();
};
