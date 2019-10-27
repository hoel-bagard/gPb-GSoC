#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <exception>
#include <boost/python/numpy.hpp>
#include "gpb.h"
#include "np_opencv_converter.hpp"

namespace bp = boost::python;
namespace bn = boost::python::numpy;
using namespace boost;

// namespace fs { namespace python {
BOOST_PYTHON_MODULE(libgpb)
{
  Py_Initialize();
  // bn::initialize();
  fs::python::init_and_export_converters();
  bp::scope scope = bp::scope();

  bp::class_<Gpb>("Gpb")
    .def(bp::init<>())
    .def("test_np_mat", &Gpb::test_np_mat)
    .def("run", &Gpb::run)
    .def("texton", &Gpb::texton)
    ;

}

// } // namespace fs
// } // namespace python
