# Description: Build OpenCV if not installed
if [ ! -f "dpp.deb" ]; then 
    echo "Downloading D++..."
    wget -O dpp.deb https://dl.dpp.dev/
    echo "D++ Downloaded"
fi

echo "Installing D++..."
sudo dpkg -i dpp.deb
echo "[+] libdpp"
rm dpp.deb