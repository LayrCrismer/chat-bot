#include <iostream>
#include "header.h"
#include <fstream>
#include <vector>
using namespace std;

void data_load_ff(vector<questions_and_answers>& db, const string& filename) {
    cout<<"Загрузка базы вопросов-ответов...\n";
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Файл не найден";
        return;
    }
    cout<<"База успешно загружена!\n";
    string q, a;
    while (getline(file, q) && getline(file, a)) {
        if (!q.empty() && q.back() == '\r') q.pop_back();
        if (!a.empty() && a.back() == '\r') a.pop_back();

        if (!q.empty()) {
            db.push_back({q,a});
        }
    }
    file.close();
}

void data_save_tf(vector<questions_and_answers>& db, const string& filename) {
    ofstream file(filename);
    for (const auto& item : db) {
        file <<item.question<<"\n"<<item.answer<<"\n";
    }
    file.close();
}

void answer(const vector<questions_and_answers>& db) {
    cout<<"\n(Введите 'back' чтобы вернуться в главное меню)\n";
    string question;
    cin.ignore();
    while (true) {
        cout<<"Ожидаю вопрос...\n";

        if (!getline(cin, question) || question == "back") {
            break;
        }

        bool found = false;
        for (const auto& item : db) {
            //cout<<"Сравниваю: ["<<item.question<<"] и ["<<question<<"]"<<endl;
            if (item.question == question) {
                cout<<"- "<<item.answer<<"\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout<<"Ответ: Я не знаю ответа на этот вопрос :( \n";
        }
    }
}
