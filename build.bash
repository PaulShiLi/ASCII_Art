if [ ! -d "pkgs" ]; then
    mkdir pkgs
fi

cd pkgs

# Description: Build OpenCV if not installed
if [ ! -d "opencv" ]; then 
    git clone "https://github.com/opencv/opencv.git"
    mkdir -p build && cd build
    cmake ../opencv
    sudo make -j4
    sudo make install
    # Header files are installed in /usr/local/include/opencv4
fi
