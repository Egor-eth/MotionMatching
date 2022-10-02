#!/bin/bash
PROJECT=${1:-MotionMatching}
BUILD_TYPE=${2:-dev}
DEBUG=${3:-no}

cd ./${PROJECT}
if [ $DEBUG = "yes" ]
then
	gdb --args ../Builds/${PROJECT}/${BUILD_TYPE}/${PROJECT}-${BUILD_TYPE} "-project -${PROJECT}"
else
	../Builds/${PROJECT}/${BUILD_TYPE}/${PROJECT}-${BUILD_TYPE} "-project -${PROJECT}"
fi
