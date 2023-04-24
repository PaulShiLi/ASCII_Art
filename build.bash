if [ ! -d "pkgs" ]; then
    mkdir pkgs
fi

cd pkgs

# Description: Build OpenCV if not installed
if [ ! -d "opencv" ]; then 
    echo "Building OpenCV"
    mkdir OpenCV
    cd OpenCV
    git clone "https://github.com/opencv/opencv.git"
    mkdir -p build && cd build
    cmake ../opencv
    cmake --build . --config Release --target install
    # sudo make -j4
    # sudo make install
    # g++ cv.cpp -o cv -I/usr/include/opencv4
    # Header files are installed in /usr/local/include/opencv4
fi
