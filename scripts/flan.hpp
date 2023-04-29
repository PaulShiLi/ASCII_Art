#include <stdio.h>
#include <iostream>
#include <string>
#include "dotenv.h"
#include <vector>
#include <dpp/dpp.h>
#include <nlohmann/json.hpp>
#include "openai/openai.hpp"

using json = nlohmann::json;
using namespace std;
using namespace dotenv;
using namespace dpp;

// Class to handle huggingface API
class Flan
{
public:
    string TOKEN, URL, MODEL;
    json payload = {
        {
            "model", "text-davinci-003"
        },
        {
            "prompt", ""
        }
    };
    Flan() {
        env.load_dotenv();
        TOKEN = env["OPENAI_KEY"];
        URL = "https://api.openai.com/v1/completions";
        MODEL = env["MODEL"];
        openai::start(TOKEN);
    }

    // 
    string getAnswer(string prompt) {
        openai::_detail::Json response;
        try {
            payload["prompt"] = prompt;
            response = openai::completion().create(payload);
            return response["choices"][0]["text"];
        }
        catch (nlohmann::detail::type_error) {
            cout << "Please check your OpenAI API key!" << endl;
            cout << response.dump(4) << endl;
            return "Error";
        }
    }
};