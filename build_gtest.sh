#!/bin/bash

CPUCORES=$(grep -c "processor" /proc/cpuinfo)

START_DIR="$(pwd)"

git clone https://github.com/google/googletest

cd googletest && git checkout master || exit 1

cd  "${START_DIR}"

rm -fR gtest

mkdir gtest

cd gtest || exit 1

cmake ../googletest/

if make -j"${CPUCORES}"
then
   echo "Build Failed"
   cd "${START_DIR}"
   exit 1
else
   echo "Google Test Framework built!"
   cd "${START_DIR}"
   exit 0
fi
