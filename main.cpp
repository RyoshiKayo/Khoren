#include <iostream>
#include "sleepy_discord/sleepy_discord.h"

const std::string BOT_ID = "foo";
const std::string BOT_TOKEN = "bar";
const std::string BOT_MENTIONED_IN_CONTENT = "<@!" + BOT_ID + ">";

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
    using SleepyDiscord::DiscordClient::DiscordClient;

    void processCommand(SleepyDiscord::Message message) {
        std::cout << "I was mentioned!" << std::endl;
        std::cout << message.content << std::endl;
        if (message.startsWith("ping")) {
            sendMessage(message.channelID, "pong");
        }
    }

    void onMessage(SleepyDiscord::Message msg) override {
        if (msg.startsWith(BOT_MENTIONED_IN_CONTENT)) {
            /** If the bot is mentioned at the beginning of the message, treat it like a command. */
            processCommand(msg);
        } else if (ends_with(msg.content, BOT_MENTIONED_IN_CONTENT)) {
            /** TODO: If the bot is mentioned at the end of the message, treat it like a help command maybe? */
            std::cout << "Not implemented help message for incomming message: \"" + msg.content + "\"";
        }
    };


    void onReady(std::string* jsonMessage) {
        std::cout << jsonMessage << std::endl;
    }

    inline bool ends_with(std::string const & value, std::string const & ending) {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
};

int main() {
    MyClientClass client(BOT_TOKEN, SleepyDiscord::USER_CONTROLED_THREADS);
    client.run();
}