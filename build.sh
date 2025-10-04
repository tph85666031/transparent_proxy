#!/bin/bash

show_usage()
{
	echo "Usage:  -d build with debug option"
	echo "        -u build as unit test app"
	echo "        -c remove all build file"
	echo ""
	exit -1
}

BUILD_TYPE="Release"
UNIT_TEST="false"
PROJECT_CLEAN= "false"

if [ x"${OS_TYPE}" == x"Darwin" ];then
    DIR_ROOT=`pwd`
else
    DIR_ROOT=`realpath $(dirname "$0")`
fi

if [ -n "$1" ];then
if [ x"${1:0:1}" != "x-" ];then
  show_usage
fi
fi

while getopts 'cdu' OPT; do
	case $OPT in
	c)
		PROJECT_CLEAN="true";;
	d)
		BUILD_TYPE="Debug";;
	u)
		UNIT_TEST="true";;  
	?)
		show_usage
	esac
done
shift $(($OPTIND - 1))

#清理环境
if [ x"${PROJECT_CLEAN}" == x"true" ];then
    rm -rf ${DIR_ROOT}/out 2>&1 > /dev/null
	echo "clean done"
	exit 0
fi

#编译
JOBS=`grep -c ^processor /proc/cpuinfo`
mkdir ${DIR_ROOT}/out
pushd ${DIR_ROOT}/out
cmake -DUNIT_TEST=${UNIT_TEST} ../
make -j${JOBS} && make install
popd
