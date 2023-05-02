#include <iostream>
#include <dpp/dpp.h>
#include "dotenv.h"
#include <cpr/cpr.h>
#include <string>
#include <fstream>

using namespace std;
using namespace dpp;

class Wordle {

    public:
    const int MAX_TRIES = 6;

    Wordle() {
        env.load_dotenv();
    }

    void initWordle(cluster &bot, message msg) {
        // Open wordle.json file
        ifstream wordleJson;
        wordleJson.open("wordle.json");

        string wordleJsonString;
        // Read wordle.json file into string
        if (wordleJson.is_open()) {
            string line;
            while (getline(wordleJson, line)) {
                // remove \n from line
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                wordleJsonString += line;
            }
            wordleJson.close();
        } else {
            cout << "Unable to open wordle.json" << endl;
        }

        auto wordleData = json::parse(wordleJsonString);

        // Check if channel already exists
        string chanName = "wordle-" + to_string(msg.author.id);
        
        channel_map chans = bot.channels_get_sync(msg.guild_id);
        
        for (const auto chan : chans) {
            // cout << "Channel name: " << chan.second.name << endl;
            // cout << "Channel id: " << chan.second.id << endl;
            // cout << "Looking for channel: " << chanName << endl;
            if (chan.second.name == chanName) {
                // Delete entry from wordle.json if exists
                if (wordleData.contains(to_string(chan.second.id))) {
                    wordleData.erase(to_string(chan.second.id));
                }
                bot.channel_delete_sync(chan.second.id);
            }
        }

        cout << "Creating channel: " << chanName << endl;
        
        channel chan;

        chan.set_name(chanName);

        chan.guild_id = msg.guild_id;

        chan.set_type(CHANNEL_TEXT);

        bot.channel_create(chan);
        
        chans = bot.channels_get_sync(msg.guild_id);

        snowflake chanID; 
        for (const auto chan : chans) {
            if (chan.second.name == chanName) {
                chanID = chan.second.id;
                // Send timestamp of channel creation
                cout << "Channel created w/ ID " << chan.second.id << endl;
                bot.message_create(message(chan.second.id, "<@" + to_string(msg.author.id) + "> created this channel at " + to_string(time(0)) + " UTC"));
            }
        }

        string selectedWord;

        // Get random word from env[RANDOM_WORD_API]
        cpr::Response r = cpr::Get(cpr::Url{env["RANDOM_WORD_API"]});
        if (r.status_code == 200) {
            auto randomWord = json::parse(r.text);
            selectedWord = randomWord[0];
        } else {
            cout << "Unable to get random word from API" << endl;
        }

        // Save word to wordle.json
        wordleData[to_string(chanID)] = {
            {"word", selectedWord},
            {"guesses", {}}
        };

        // Write wordle.json
        ofstream wordleJsonWrite;
        wordleJsonWrite.open("wordle.json");
        if (wordleJsonWrite.is_open()) {
            wordleJsonWrite << wordleData.dump(4);
            wordleJsonWrite.close();
        } else {
            cout << "Unable to open wordle.json" << endl;
        }
        greet(bot, chanID);
    }

    void greet(cluster &bot, snowflake channelId) {
        // Open wordle.json file
        ifstream wordleJson;
        wordleJson.open("wordle.json");

        string wordleJsonString;
        // Read wordle.json file into string
        if (wordleJson.is_open()) {
            string line;
            while (getline(wordleJson, line)) {
                // remove \n from line
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                wordleJsonString += line;
            }
            wordleJson.close();
        } else {
            cout << "Unable to open wordle.json" << endl;
        }

        auto wordleData = json::parse(wordleJsonString);
        string word = wordleData[to_string(channelId)]["word"].get<string>();

        embed embedGreet = embed()
            .set_color(colors::alice_blue)
            .set_title("Welcome to Wordle")
            .set_description("Guess the Wordle in " + to_string(MAX_TRIES) + " tries!\n• Each guess must be a valid " + to_string(word.length()) + " letter word.\n• The bot will describe how close your guess was to the word.")
            .add_field(
                "Example:\nYou: weary",
                "`W` is in the word and in the correct position.\n`E` is in the word but in the wrong position.\n`A` is not in the word.\n`R` is in the word and in the correct position.\n`Y` is in the word but in the wrong position.\n\nYou have " + to_string(MAX_TRIES) + " more tries to guess the word.",
                false
            )
            .set_timestamp(time(0));
        
        bot.message_create(message(channelId, embedGreet));
    }

    void validate(cluster &bot, message_create_t event) {
        snowflake channelId = event.msg.channel_id;
        cout << channelId << ": " << event.msg.content << endl;
        
        // Open wordle.json file
        ifstream wordleJson;
        wordleJson.open("wordle.json");

        string wordleJsonString;
        // Read wordle.json file into string
        if (wordleJson.is_open()) {
            string line;
            while (getline(wordleJson, line)) {
                // remove \n from line
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                wordleJsonString += line;
            }
            wordleJson.close();
        } else {
            cout << "Unable to open wordle.json" << endl;
        }

        auto wordleData = json::parse(wordleJsonString);
        if (!wordleData.contains(to_string(channelId))) {
            // Delete channel if wordle.json does not contain channelId
            bot.channel_delete_sync(channelId);
        }
        string word = wordleData[to_string(channelId)]["word"].get<string>();;

        string guess = event.msg.content;
        string response = "";
        bool valid = true;
        embed embedGuess = embed();

        // Convert event.msg.content to lowercase
        transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

        if (wordleData[to_string(channelId)]["guesses"].size() == MAX_TRIES && valid == true) {
            valid = false;
            embedGuess.set_title("No more guesses available!")
                .set_description("You have run out of guesses. The word was `" + word + "`.")
                .set_color(colors::red);
            wordleData.erase(to_string(channelId));
        }

        // Check if guess is valid
        if (guess.length() != word.length() && valid == true) {
            cout << "Invalid length: " << guess << endl;
            valid = false;
            embedGuess.set_title("Invalid Guess!")
                .set_description("Your guess must be a valid " + to_string(word.length()) + " letter word.")
                .set_color(colors::red);
        }

        if (guess != word && valid == true){
            response = comCheck(word, guess);
            wordleData[to_string(channelId)]["guesses"].push_back(guess);
            embedGuess.set_title("Your Guess: " + guess)
                .set_description(response)
                .set_color(colors::orange);
        }
        if (guess == word && valid == true){
            response = "You guessed the word! The word was `" + word + "`.\n" + "It took you " + to_string(wordleData[to_string(channelId)]["guesses"].size()) + " guesses!\nType any message to delete this channel or generate a new channel with the command `!wordle`.";
            embedGuess.set_title("You Win!")
                .set_description(response)
                .set_color(colors::green);
            wordleData.erase(to_string(channelId));
        }

        // Write wordle.json file
        ofstream wordleJsonWrite;
        wordleJsonWrite.open("wordle.json");
        if (wordleJsonWrite.is_open()) {
            wordleJsonWrite << wordleData.dump(4);
            wordleJsonWrite.close();
        } else {
            cout << "Unable to open wordle.json" << endl;
        }

        event.reply(message(channelId, embedGuess));
    }

    string comCheck(string word, string guess) {
        string response = "";

        for (int n = 0; n < word.length(); n++) {
            if (word[n] == guess[n]) {
                response += "`" + string(1, word[n]) + "` is in the word and in the correct position.\n";
            } else if (word.find(guess[n]) != string::npos) {
                response += "`" + string(1, guess[n]) + "` is in the word but in the wrong position.\n";
            } else {
                response += "`" + string(1, guess[n]) + "` is not in the word.\n";
            }
        }

        return response;
    }

};