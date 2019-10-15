#include "globalPb.h"
#include "affinity.h"
#include "ic.h"
#include "contour2ucm.h"
#include <iostream>
#include <string>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <opencv2/core/mat.hpp>
#include <Python.h>


namespace bp = boost::python;
namespace bn = boost::python::numpy;
using namespace boost;

class Gpb{
  // static boost::shared_ptr<Gpb> create () { return boost::shared_ptr<Gpb>(new Gpb); }
    public:

        bp::tuple run(const cv::Mat& image);
        cv::Mat test_np_mat(const cv::Mat &in) {
            std::cerr << "in: " << in << std::endl;
            std::cerr << "sz: " << in.size() << std::endl;
            return in.clone();
        }
        void hello(const int& a) {
            std::cout << "arg: " << a << std::endl;
        }

    private:
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

};
