#!/bin/bash

# Declare some variables
isUnzipInstall=0
installPath=""

# Check if user is root
if [ $(id -u) != "0" ]; then
    echo "Error: You must be root to run this script, please use root to install"
    exit 1
fi

# Ask for upgrade system
read -p "Do you want to upgrade system? (y/n)" isUpgrade
if [ "$isUpgrade" = "y" ]; then
    apt-get update
    apt-get upgrade -y
fi

# Install necessary dependencies
apt-get install -y g++
  # Check install success or not
if [ $? -ne 0 ]; then
    echo "Error: Install g++ failed"
    exit 1
fi
apt-get install -y make
  # Check install success or not
if [ $? -ne 0 ]; then
    echo "Error: Install make failed"
    exit 1
fi
apt-get install -y cmake
  # Check install success or not
if [ $? -ne 0 ]; then
    echo "Error: Install cmake failed"
    exit 1
fi
apt-get install -y wget
  # Check install success or not
if [ $? -ne 0 ]; then
    echo "Error: Install wget failed"
    exit 1
fi
apt-get install -y build-essential
  # Check install success or not
if [ $? -ne 0 ]; then
    echo "Error: Install build-essential failed"
    exit 1
fi

# Ask for installation path
read -p "Please input the path you want to install OpenCV (default: /usr/local/opencv): " installPath
if [ "$installPath" = "" ]; then
    installPath=/usr/local/opencv
fi

# Create installation directory
mkdir -p $installPath

# Check mkdir success or not
if [ $? -ne 0 ]; then
    echo "Error: Create directory $installPath failed"
    exit 1
fi

# Go to installation directory
cd $installPath || exit

# Download OpenCV
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
  # Check download success or not
if [ $? -ne 0 ]; then
    echo "Error: Download OpenCV failed"
    exit 1
fi
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
  # Check download success or not
if [ $? -ne 0 ]; then
    echo "Error: Download OpenCV Contrib failed"
    exit 1
fi

# Install temporary dependencies
if [ $(dpkg-query -W -f='${Status}' unzip 2>/dev/null | grep -c "ok installed") -eq 0 ]; then
    apt-get install -y unzip
      # Check install success or not
    if [ $? -ne 0 ]; then
        echo "Error: Install unzip failed"
        exit 1
    fi
    isUnzipInstall=1
fi

# Unzip OpenCV
unzip opencv.zip
  # Check unzip success or not
if [ $? -ne 0 ]; then
    echo "Error: Unzip OpenCV failed"
      # Uninstall temporary dependencies
    if [ $isUnzipInstall -eq 1 ]; then
        apt-get remove -y unzip
    fi
    exit 1
fi
unzip opencv_contrib.zip
  # Check unzip success or not
if [ $? -ne 0 ]; then
    echo "Error: Unzip OpenCV Contrib failed"
      # Uninstall temporary dependencies
    if [ $isUnzipInstall -eq 1 ]; then
        apt-get remove -y unzip
    fi
    exit 1
fi

# Uninstall temporary dependencies
if [ $isUnzipInstall -eq 1 ]; then
    apt-get remove -y unzip
fi

# Delete source files
rm opencv.zip
  # Check delete success or not
if [ $? -ne 0 ]; then
    echo "Error: Delete opencv.zip failed"
    exit 1
fi
rm opencv_contrib.zip
  # Check delete success or not
if [ $? -ne 0 ]; then
    echo "Error: Delete opencv_contrib.zip failed"
    exit 1
fi

# Create build directory
mkdir -p build
  # Check mkdir success or not
if [ $? -ne 0 ]; then
    echo "Error: Create directory build failed"
    exit 1
fi

# Go to build directory
cd build || exit

# Configure CMake
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x
  # Check configure success or not
if [ $? -ne 0 ]; then
    echo "Error: Configure CMake failed"
    exit 1
fi

# Build OpenCV
cmake --build .
  # Check build success or not
if [ $? -ne 0 ]; then
    echo "Error: Build OpenCV failed"
    exit 1
fi

echo "OpenCV build"