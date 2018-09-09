cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenCV REQUIRED)
find_package(Arpack REQUIRED)
find_package(Boost COMPONENTS python3 numpy3 system filesystem REQUIRED)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3 REQUIRED)

message("Include dirs of Boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of Boost: " ${Boost_LIBRARIES} )

link_directories("${ARPACK_PATH}")

file(GLOB SRC
    includes/*.h
    src/*.cpp
)

add_library(gpb SHARED ${SRC} pygpb.cpp)
include_directories(includes)
include_directories("${Boost_INCLUDE_DIRS}" ${PYTHON_INCLUDE_DIRS})

target_link_libraries(gpb ${OpenCV_LIBS} arpack ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

message("Source files: " ${SRC} )

find_program(PYTHON "python3")

set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(DEPS      gpb)
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")

configure_file(${SETUP_PY_IN} ${SETUP_PY})

add_custom_command(OUTPUT ${OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/libpygpb.so"
			"${CMAKE_CURRENT_BINARY_DIR}/pygpb/libpygpb.so"
		COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/pygpb/__init__.py"
			"${CMAKE_CURRENT_BINARY_DIR}/pygpb/__init__.py"
	       DEPENDS ${DEPS})

add_custom_target(target ALL DEPENDS ${OUTPUT})
