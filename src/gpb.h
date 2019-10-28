#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <Python.h>
#include "process.h"


namespace bp = boost::python;
namespace bn = boost::python::numpy;
using namespace boost;

class Gpb{
    public:

        bp::tuple run(const cv::Mat& image);
        cv::Mat texton(const cv::Mat &img, int n_ori, int Kmean_num,
                      double sigma_sm, double sigma_lg);
        bp::tuple test_np_mat(const cv::Mat &in1, const cv::Mat &in2) {
            // std::cerr << "in1: " << in1 << std::endl;
            std::cerr << "size(in1): " << in1.size() << std::endl;
            // std::cerr << "in2: " << in2 << std::endl;
            std::cerr << "size(in2): " << in2.size() << std::endl;
            return bp::make_tuple(in1.clone(), in2.clone());
        }

    private:
        cv::Mat markers, ucm2, bd, ll;
        int dthresh = 5;
        float sigma = 0.1;

};
