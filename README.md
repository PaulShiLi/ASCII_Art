# C++ CSH CH 10 Project

---

## 🎯 MVP (Minimal Viable Product)

The MVP of this project is to create a Discord bot that provides users an interactive assistant-like bot using OpenAI’s GPT 3 Davinci model along with commands that implements the usage of previously learned functions and knowledge of C++. It is similar to Bing AI / ChatGPT but implemented in Discord. In addition, it has a wordle game built into it when calling **!wordle**.

---

## ⚠️ Important!

Before cloning and building this Repo, make sure that your OS is a **Linux-based OS** due to the code being only supported for **Ubuntu**! You will have to modify the bash file if ran on a different OS!

Windows:
To run the code, make sure to have WSL (Windows Subsystem for Linux) installed!

MacOS:
Incompatible due to MacOS not having `apt` commands

---

## 🔨 ******************Building the repo******************

1. Clone the repo and change to repo directory
    
    ```bash
    git clone "https://github.com/PaulShiLi/CSH-CPP-CH10-Project.git"
    cd "CSH-CPP-CH10-Project"
    ```
    
2. Run `build.bash` via the following command:
    
    ```bash
    bash ./build.bash
    ```
    
3. Fill in environment secrets that is in the generated `.env` file.
    
    ```bash
    BOT_TOKEN=""
    LOG_CHANNEL_ID=""
    OPENAI_KEY=""
    ```
    
4. Run `run.bash` via the following command:
    
    ```bash
    bash ./run.bash
    ```
    

---

## 💪 Challenges

Integrating external libraries was a challenge due to the attempt to build a lightweight code source and as well as to make the setup hassle-free. Setting up CMake was the biggest challenge of this project due to the lack of documentation in some of these libraries that was provided in addition with compiler problems and errors due to 3rd party dependencies that was not configured yet.

The solution to these problems was looking into these dependency’s CMake configurations to have this project’s CMake to be compatible with theirs and as well as browsing through StackOverflow to see if anyone else experience the same compiler problems (such as including cURL as part of the target link in CMake).

---

## 🤑 Most Valuable Skill

Pointers is arguably the most valuable knowledge learned in this semester of C++, where it helped us in understanding other people’s example code in C++ if there’s a memory reference made or if there’s a pointer that is declared.

---

## 📂 Complexity Management

Classes is definitely one of the biggest code redundancy savers as it both categorizes functions and makes function usage clearer and concise and as well as being able to save a lot of initializations and variable assignments if implemented without a class. Functions also serves the same purpose as well, where it would prevent code redundancy.

We also used a library ([nlohmann/json](https://github.com/nlohmann/json)) that brings dictionary types to our project as well so that we are able to easily define the payload for HTTP requests to OpenAI using a wrapper for OpenAI’s API given the time constraint of this project. 

---

## 📕 Used Libraries

This project does use 3rd party libraries to help simplify and improve the codebase for this project and as well as meet our MVP with the given deadline.

- [CPP-DotEnv](https://github.com/adeharo9/cpp-dotenv) - A C++ environment file parser that parses the `.env` file for this project.
- [D++](https://github.com/brainboxdotcc/DPP) - A C++ wrapper for Discord API
- [OpenAI C++](https://github.com/olrea/openai-cpp) - A C++ wrapper for OpenAI API
- [Json](https://github.com/nlohmann/json) - A C++ library that introduces dict types and parses json/dictionary.
- [CPR](https://github.com/libcpr/cpr) - A C++ library that is a wrapper for cURL to enable HTTP requests.

---