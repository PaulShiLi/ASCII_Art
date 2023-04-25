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
    cd ..
fi
echo "D++ dependencies installed..."

# Create env file if not exists
if [ ! -f ".env" ]; then
    echo "Creating .env file..."
    touch .env
    ENV='
    BOT_TOKEN=""
    BOT_PREFIX="!"
    '
    # Dedent the string
    ENV=$(echo "$ENV" | sed -e 's/^[[:space:]]*//')
    ENV=$(echo "$ENV" | cut -d$'\n' -f2-)
    echo "$ENV" >> .env
    echo ".env file created..."
fi