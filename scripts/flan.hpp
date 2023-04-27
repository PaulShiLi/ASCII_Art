#include <stdio.h>
#include "dotenv.h"
#include <dpp/dpp.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

using namespace std;
using namespace dotenv;
using namespace dpp;

// Class to handle huggingface API
class flan {
    public:
    string token, modelUrl;
    flan() {
        token = env["HUGGINGFACE_TOKEN"];
        modelUrl = env["HUGGINGFACE_URL"];
    }

    // Send message to huggingface API

};