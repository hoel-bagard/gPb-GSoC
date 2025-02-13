set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )
find_package(OpenCV REQUIRED)
find_package(Arpack REQUIRED)
find_package( Boost 1.58.0 REQUIRED COMPONENTS python3 numpy3)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3 REQUIRED)
# find_package(TBB  REQUIRED)

link_directories("${ARPACK_PATH}")

file(GLOB SRC
  includes/*.h
  src/*.cpp
)

set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wall -g" )

include_directories(includes)
add_executable(main main.cpp ${SRC} "process.h" "process.cpp")
target_link_libraries(main ${OpenCV_LIBS} arpack tbb)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

add_library(gpb SHARED gpb.h ${SRC} "gpb.cpp" "gpb.h" "process.h" "process.cpp" pygpb.cpp)
set_property(TARGET gpb PROPERTY CXX_STANDARD 17)
set_property(TARGET gpb PROPERTY CXX_STANDARD_REQUIRED ON)
include_directories("${Boost_INCLUDE_DIRS}" ${PYTHON_INCLUDE_DIRS})
include_directories("${numpy-opencv-converter_SOURCE_DIR}")
include_directories(${PYTHON_NUMPY_INCLUDE_DIR})
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME ON)

TARGET_LINK_LIBRARIES(gpb LINK_PUBLIC np_opencv_converter ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} arpack  tbb)


find_program(PYTHON "python3")


set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(DEPS      gpb)
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")

configure_file(${SETUP_PY_IN} ${SETUP_PY})
add_custom_command(OUTPUT ${OUTPUT}
                COMMAND ${CMAKE_COMMAND} -E copy
                        "${CMAKE_CURRENT_SOURCE_DIR}/libgpb.so"
                        "${CMAKE_CURRENT_BINARY_DIR}/pygpb/libgpb.so"
                COMMAND ${CMAKE_COMMAND} -E copy
                        "${CMAKE_CURRENT_SOURCE_DIR}/pygpb/__init__.py"
                        "${CMAKE_CURRENT_BINARY_DIR}/pygpb/__init__.py"
            DEPENDS ${DEPS})

add_custom_target(target ALL DEPENDS ${OUTPUT})
