#include "sleepy_discord/sleepy_discord.h"
#include "dotenv.h"

using namespace std;
using namespace SleepyDiscord;
using namespace dotenv;

class MyClientClass : public DiscordClient {
public:
	using DiscordClient::DiscordClient;
	void onMessage(Message message) override {
		if (message.startsWith("whcg hello"))
			sendMessage(message.channelID, "Hello " + message.author.username);
	}
    void onReady(Ready readyData) override {
        cout << "Logged in as " << readyData.user.username << endl;
    }
};

int main() {
    env.load_dotenv();
	MyClientClass client(env["BOT_TOKEN"], USER_CONTROLED_THREADS);
	client.setIntents(Intent::SERVER_MESSAGES);
	client.run();
}