# Copyright 2017 Jani Arola, All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
project(unit_test_framework)

# Set googletest version.
set(GTEST_VERSION 1.10.0)
set(GTEST_PREFIX ${CMAKE_BINARY_DIR}/gtest-${GTEST_VERSION})
set(GTEST_LIBDIR ${GTEST_PREFIX}/lib)

# Configure googletest.
list(APPEND GTEST_CMAKE_ARGS "-G${CMAKE_GENERATOR}")
list(APPEND GTEST_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
list(APPEND GTEST_CMAKE_ARGS "-DCMAKE_CONFIGURATION_TYPES=Release")
list(APPEND GTEST_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${GTEST_PREFIX}")
list(APPEND GTEST_CMAKE_ARGS "-DCMAKE_INSTALL_LIBDIR=${GTEST_LIBDIR}")
list(APPEND GTEST_CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

# Download and install GTest, also disable all output from ExternalProject_Add.
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-${GTEST_VERSION}
    CMAKE_ARGS "${GTEST_CMAKE_ARGS}"
    BUILD_COMMAND ""
    BUILD_BYPRODUCTS ${GTEST_LIBDIR}/libgtest.a
    LOG_DOWNLOAD 1
    LOG_UPDATE 1
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_TEST 1
    LOG_INSTALL 1
    INSTALL_COMMAND cmake --build . --target install --config Release
)

# Define a target library for linkage.
add_library(${PROJECT_NAME} IMPORTED UNKNOWN GLOBAL)

# Add dependency to googletest to force the download and install.
add_dependencies(${PROJECT_NAME} googletest)

# Link all the required libraries to target.
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Threads::Threads
        ${GTEST_LIBDIR}/libgtest.a
)

# Create directory for the includes.
file(MAKE_DIRECTORY ${GTEST_PREFIX}/include)

# Set the target library import location and include googletest directories. See:
# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        IMPORTED_LOCATION ${GTEST_LIBDIR}/libgtest.a
        IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
        INTERFACE_INCLUDE_DIRECTORIES ${GTEST_PREFIX}/include
)
