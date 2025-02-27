#!/bin/bash
PROJECT=${1:-MotionMatching}
BUILD_TYPE=${2:-dbg}
REBUILD=${3:-no}
ECS_CODEGEN=${4:-yes}
CMAKE=${5:-yes}
CWD=$(pwd)

cd Builds

if [ $REBUILD = "yes" ]
then
    rm -r -f $PROJECT/$BUILD_TYPE
fi

if [ $ECS_CODEGEN = "yes" ]
then
    ./ECSCodeGen/ECSCodeGen.exe $CWD/Common/Sources/Systems $CWD/sources/$PROJECT/Systems
fi

cd ../sources
if [ $CMAKE = "yes" ]
then
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
    cmake -G Ninja -DGAME=$PROJECT -DBUILD_TYPE=$BUILD_TYPE -B ../Builds/$PROJECT/$BUILD_TYPE
fi
cd $CWD/Builds/$PROJECT/$BUILD_TYPE
ninja