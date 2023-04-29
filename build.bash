echo -e "\n---------------------------------\n"

echo "Updating existing packages..."
sudo apt update -y

echo -e "\n---------------------------------\n"

echo "Checking for required packages..."
echo
reqPkg=(
    libssl-dev
    libcurl4-openssl-dev
    build-essential
    libcurl4-openssl-dev
    curl
    openssl
)
totalPkg=$(dpkg -l | awk '{print $2}')

for pkg in ${reqPkg[@]};
    do
        installed=false
        for installedPkg in ${totalPkg[@]};
            do
                installedPkg=$(echo $installedPkg | cut -d':' -f1)
                if [[ $pkg == $installedPkg ]]; then
                    echo "[=] $pkg is installed"
                    installed=$true
                fi
            done
        if [[ $installed = false ]]; then
            echo "$pkg is not installed"
            echo "Installing $pkg..."
            sudo apt install $pkg --fix-missing -y
            echo "[+] $pkg installed"
        fi
    done
echo
echo "Required packages installed"

echo -e "\n---------------------------------\n"

# Download dependencies
echo "Downloading dependencies..."
if [ ! -d "deps" ]; then
    mkdir deps
fi

cd deps

# https://github.com/adeharo9/cpp-dotenv.git
if [ ! -d "cpp-dotenv" ]; then
    git clone "https://github.com/adeharo9/cpp-dotenv.git"
fi

if [ ! -d "DPP" ]; then
    git clone https://github.com/brainboxdotcc/DPP.git
fi

if [ ! -d "../scripts/openai" ]; then
    git clone https://github.com/olrea/openai-cpp.git
    cp openai-cpp/include/openai/ ../scripts -r
    sudo rm -rf openai-cpp
fi

if [ ! -d "json" ]; then
    git clone https://github.com/nlohmann/json.git
fi

cd ..
echo "Dependencies downloaded..."

echo -e "\n---------------------------------\n"

# Create env file if not exists
if [ ! -f ".env" ]; then
    echo "Creating .env file..."
    touch .env
    ENV='
    BOT_TOKEN=""
    BOT_PREFIX="!"
    LOG_CHANNEL_ID=""
    OPENAI_KEY=""
    MODEL="text-davinci-003"
    '
    # Dedent the string
    ENV=$(echo "$ENV" | sed -e 's/^[[:space:]]*//')
    ENV=$(echo "$ENV" | cut -d$'\n' -f2-)
    echo "$ENV" >> .env
    echo ".env file created..."
    echo -e "\n---------------------------------\n"
fi

# Build the bot
echo "Building the bot..."
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake ..
make
echo -e "\n---------------------------------\n"