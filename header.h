
#ifndef CHAT_BOT_HEADER_H
#define CHAT_BOT_HEADER_H
#define WHITE "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define GOLD "\033[33m"
#define MAGENTA "\033[35m"

#include <string>
#include <vector>

using namespace std;
struct questions_and_answers {
    string question;
    string answer;
};

void answer(const vector<questions_and_answers>& db, const string& botName);
void data_load_ff(vector<questions_and_answers>& db, const string& filename, string& botName);
void data_save_tf(vector<questions_and_answers>& db, const string& filename, const string& botName);
void admin_mode(vector<questions_and_answers>& db, const string& filename, string& botName);
void questions_view(vector<questions_and_answers>& db, const string& filename);

#endif //CHAT_BOT_HEADER_H