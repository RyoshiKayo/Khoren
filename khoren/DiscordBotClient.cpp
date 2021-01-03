//
// Created by Kayo on 1/2/2021.
//

#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "sleepy_discord/sleepy_discord.h"


namespace Khoren {

    static std::queue<std::vector<std::string>> cmdQueue;

    class DiscordBotClient : public SleepyDiscord::DiscordClient {
    public:
        DiscordBotClient(const std::string* bot_token, const char threads, const std::string* bot_id)
        : SleepyDiscord::DiscordClient(*bot_token, threads),
            BOT_ID(bot_id),
            BOT_MENTIONED_IN_CONTENT("<@!" + *bot_id + ">") {}

        using SleepyDiscord::DiscordClient::DiscordClient;

        void processCommand(SleepyDiscord::Message message)
        {
            using namespace std;

            cout << "I was mentioned in " + message.content << endl;
            if (message.startsWith("ping"))
            {
                sendMessage(message.channelID, "pong");
                parseCmdArgs(message.content);
            }
        }

        void onMessage(SleepyDiscord::Message msg) override
        {
            if (msg.startsWith(BOT_MENTIONED_IN_CONTENT))
            {
                /** If the bot is mentioned at the beginning of the message, treat it like a command. */
                processCommand(msg);
            } else if (endsWith(msg.content, BOT_MENTIONED_IN_CONTENT))
            {
                /** TODO: If the bot is mentioned at the end of the message, treat it like a help command maybe? */
                std::cout << "Not implemented help message for incomming message: \"" + msg.content + "\"";
            }
        };

        static void onReady(std::string* jsonMessage)
        {
            std::cout << jsonMessage << std::endl;
        }

        static inline bool endsWith(std::string const & value, std::string const & ending)
        {
            if (ending.size() > value.size()) return false;
            return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
        }

        static void parseCmdArgs(std::string & messageContents)
        {
            using namespace std;
            vector<string> args;
            istringstream iss(messageContents);
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(args));
            cmdQueue.push(args);
            print_queue(cmdQueue);
        }

    private:
        const std::string * BOT_ID;
        std::string BOT_MENTIONED_IN_CONTENT;

        static void print_queue(std::queue<std::vector<std::string>> q)
        {
            while (!q.empty())
            {
                std::vector<std::string> v = q.front();
                for (auto const arg : v) {
                    std::cout << arg << " ";
                }
                q.pop();
            }
            std::cout << std::endl;
        }
    };
}
