# Description: Build OpenCV if not installed
if [ ! -f "dpp.deb" ]; then 
    echo "Downloading D++ package..."
    wget -O dpp.deb https://dl.dpp.dev/
    echo "D++ package downloaded..."
fi

echo "Installing D++ package..."
sudo dpkg -i dpp.deb
echo "[+] libdpp"
rm dpp.deb

echo "Installing D++ dependencies..."
if [ ! -d "libs" ]; then
    mkdir libs
fi

if [ ! -d "libs/DPP" ]; then
    cd libs
    git clone https://github.com/brainboxdotcc/DPP.git
fi
echo "D++ dependencies installed..."