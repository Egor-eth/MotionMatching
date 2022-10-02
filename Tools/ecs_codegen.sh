#!/bin/bash

PROJECT=${1:-MotionMatching}
CWD=$(pwd)

cd Builds/ECSCodeGen
./ECSCodeGen.exe $CWD/sources/common_systems $CWD/sources/$PROJECT
cd ../../.. 
