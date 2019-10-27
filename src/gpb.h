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
        cv::Mat texton(const cv::Mat &img, int n_ori, int Kmean_num,
                      double sigma_sm, double sigma_lg);

    private:
        cv::Mat markers, ucm2, bd, ll;
        int dthresh = 5;
        float sigma = 0.1;

};
