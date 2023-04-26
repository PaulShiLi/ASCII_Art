#include "sleepy_discord/sleepy_discord.h"
#include "dotenv.h"

using namespace std;
using namespace SleepyDiscord;
using namespace dotenv;

class MyClientClass : public DiscordClient {
public:
	using DiscordClient::DiscordClient;
	Ready bot;
	void onMessage(Message message) override {
		cout << message.author.username << ": " << message.content << endl;
		if (message.startsWith("Hello"))
			sendMessage(message.channelID, "Hello " + message.author.username);
	}
    void onReady(Ready readyData) override {
        cout << "Logged in as " << readyData.user.username << endl;
		bot = readyData;
		// Send message as logged in using Channel ID from env["LOG_CHANNEL_ID"]
		const Snowflake<Channel> logChannel_ID = env["LOG_CHANNEL_ID"];
		sendMessage(logChannel_ID, readyData.user.username + " logged in");
    }
};

int main() {
	// Load env variables from local .env file
    env.load_dotenv();
	// Set up client class
	MyClientClass client(env["BOT_TOKEN"], USER_CONTROLED_THREADS);
	// Set discord intents to allow for message reading
	client.setIntents(Intent::SERVER_MESSAGES, Intent::SERVER_MEMBERS, Intent::SERVER_MESSAGE_TYPING);
	client.run();
}