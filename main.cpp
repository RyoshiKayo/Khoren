#include <iostream>
#include "khoren/DiscordBotClient.cpp"

#define KHOREN_ENV_BOT_ID "KHOREN_BOT_ID"
#define KHOREN_ENV_BOT_TOKEN "KHOREN_BOT_TOKEN"

int main() {
    using namespace std;

    static string BOT_ID = "";
    static string BOT_TOKEN = "";

    if (const char* bot_id = getenv(KHOREN_ENV_BOT_ID)) {
        BOT_ID = string(bot_id);
    } else {
        throw invalid_argument(string(KHOREN_ENV_BOT_ID) + " is not set.");
    }

    if (const char* bot_token = getenv(KHOREN_ENV_BOT_TOKEN)) {
        BOT_TOKEN = string(bot_token);
    } else {
        throw invalid_argument(string(KHOREN_ENV_BOT_TOKEN) + " is not set.");
    }

    Khoren::DiscordBotClient client(&BOT_TOKEN, SleepyDiscord::USER_CONTROLED_THREADS, &BOT_ID);
    client.run();
}