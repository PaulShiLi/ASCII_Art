#include <stdio.h>
#include "dotenv.h"
#include <dpp/dpp.h>
#include "../scripts/flan.hpp"

using namespace std;
using namespace dotenv;
using namespace dpp;


int main() {
	// Load env variables from local .env file
    env.load_dotenv();

	cluster bot(env["BOT_TOKEN"]);

	// Enable intents
	bot.intents = i_guild_members | i_guild_messages | i_direct_messages | i_message_content;

	// Log to console
	bot.on_log(utility::cout_logger());

	// On message event
	bot.on_message_create([&bot](const message_create_t& event) {
		cout << event.msg.author.username << ": " << event.msg.content << endl;
		// If mention bot
		for (auto mention : event.msg.mentions) {
			// Check if user part of mention == bot
			if (mention.first == bot.me) {
				// Remove discord mention from message by finding first occurence of <@ and deleting all the way until first occurence of >
				string message = event.msg.content;
				message.erase(message.find("<@"), message.find(">") - message.find("<@") + 1);

				// Create flan object
				Flan flan;

				// Get answer from flan
				string answer = flan.getAnswer(message);

				// Send message to channel
				event.reply(answer);
			} 
			
		}
	});


	bot.on_ready([&bot](const ready_t& event) {
		// Log to console when bot is readdy
		bot.log(ll_info, "Logged in as " + bot.me.username);
		// Fetch channel by id from env["LOG_CHANNEL_ID"]
		snowflake channelId = from_string<snowflake>(env["LOG_CHANNEL_ID"]);
		bot.message_create(message(channelId, bot.me.username + " logged in"));
	});

	bot.start(st_wait);
}