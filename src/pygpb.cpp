#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/class.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/return_internal_reference.hpp>
#include "gpb.h"

using namespace boost::python;


BOOST_PYTHON_MODULE(libgpb)
{
  Py_Initialize();
  namespace bp = boost::python;

  class_<Gpb>("gpb")
    .def("run",&Gpb::run)
    ;
}
