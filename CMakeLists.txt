cmake_minimum_required(VERSION 3.10...3.28)
project(image_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(io filters utils)

set(SOURCES
    image_processor.cpp
    io/bmptools.cpp
    io/image.cpp
    filters/base_filters.cpp
    filters/blur_filter.cpp
    filters/crop_filter.cpp
    filters/crystalize_filter.cpp
    filters/edgedetection_filter.cpp
    filters/filters_applier.cpp
    filters/grayscale_filter.cpp
    filters/negative_filter.cpp
    filters/sharpening_filter.cpp
    utils/help_functions.cpp
    utils/parser.cpp
)

add_executable(image_processor ${SOURCES})

add_executable(image_processor_san ${SOURCES})
target_compile_options(image_processor_san PRIVATE
    -fsanitize=address,undefined
    -fno-omit-frame-pointer
    -g
)
target_link_options(image_processor_san PRIVATE
    -fsanitize=address,undefined
)