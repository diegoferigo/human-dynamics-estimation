#!/bin/bash
set -e
set -u

mkdir $HOME/git

# Build and install yarp
cd $HOME/git
git clone --depth 1 -b $DEPS_BRANCH https://github.com/robotology/yarp.git
cd yarp
mkdir build && cd build
cmake .. \
    -G"$TRAVIS_CMAKE_GENERATOR" \
    -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$DEPS_CACHE \
    -DCREATE_LIB_MATH=ON
cmake --build . --config $TRAVIS_BUILD_TYPE --target install

# Build and install idyntree
cd $HOME/git
git clone --depth 1 -b $DEPS_BRANCH https://github.com/robotology/idyntree.git
cd idyntree
mkdir build && cd build
cmake .. \
    -G"$TRAVIS_CMAKE_GENERATOR" \
    -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$DEPS_CACHE
cmake --build . --config $TRAVIS_BUILD_TYPE --target install

# Build and install xsense-mvn
cd $HOME/git
git clone https://github.com/robotology-playground/xsens-mvn
cd xsens-mvn
mkdir build && cd build
cmake -G"${TRAVIS_CMAKE_GENERATOR}" \
      -DCMAKE_BUILD_TYPE=${TRAVIS_BUILD_TYPE} \
      -DENABLE_xsens_mvn=OFF \
      -DENABLE_xsens_mvn_wrapper=OFF \
      -DENABLE_xsens_mvn_remote=OFF \
      ..
cmake --build . --config ${TRAVIS_BUILD_TYPE} --target install
