#include <iostream>
#include "header.h"
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void data_load_ff(vector<questions_and_answers>& db, const string& filename, string& botName) {
    cout<<"Загрузка базы вопросов-ответов...\n";
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Файл не найден";
        return;
    }

    getline(file, botName);
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

void data_save_tf(vector<questions_and_answers>& db, const string& filename, const string& botName) {
    ofstream file(filename);
    if (file.is_open()) {
        file<<botName<<"\n";
        for (const auto& item : db) {
            file<<item.question<<"\n"<<item.answer<<"\n";
        }
        file.close();
        cout<<"База вопросов-ответов успешно сохранена!\n";
    }
    else {
        cout<<"Ошибка. Не удалось открыть базу вопросов-ответов.\n";
    }

}

void answer(const vector<questions_and_answers>& db, const string& botName) {
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
            if (question == "Как тебя зовут?" || question == "Твоё имя?" || question == "Ты кто?") {
                cout<<botName<<": Меня зовут "<<botName<<"\n";
                found = true;
                break;
            }
            if (item.question == question) {
                cout<<botName<<": "<<item.answer<<"\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout<<"- Я не знаю ответа на этот вопрос :( \n";
        }
    }
}

void admin_mode(vector<questions_and_answers>& db, const string& filename, string& botName) {

    int action;

    while (true) {
        cout<<"===============================================\n";
        cout<<"                 Админ-панель\n";
        cout<<"===============================================\n";
        cout<<"1. Добавить вопрос-ответ\n";
        cout<<"2. Удалить вопрос\n";
        cout<<"3. Редактировать запись\n";
        cout<<"4. Изменить имя бота\n";
        cout<<"0. Выход в меню\n";
        cout<<"===============================================\n";
        cout<<"Введите команду, чтобы продолжить: ";

        cin>>action;
        if (action == 0) break;
        cin.ignore();
        if (action == 1) {
            string q,a;
            cout<<"Введите новый вопрос: ";
            getline(cin,q);
            //cin.ignore();
            cout<<"Введите ответ на него: ";
            getline(cin,a);
            db.push_back({q,a});
            data_save_tf(db,filename, botName);
        }
        else if (action==2) {
            int index;
            if (db.size()==0) {
                cout<<"\nБаза вопросов-ответов пуста.\n";
                continue;
            }
            cout<<"Введите номер вопроса для удаления: \n";
            cin>>index;
            if (index > 0 && index <= db.size()) {
                db.erase(db.begin() + (index-1));
                data_save_tf(db,filename,botName);
            } else {
                cout<<"Неверный номер!\n";
            }
        }
        else if (action == 3) {
            int index;
            if (db.size()==0) {
                cout<<"\nБаза вопросов-ответов пуста.\n";
                continue;
            }
            cout<<"Введите номер вопроса для редактирования: \n";
            cin>>index;
            if (index > 0 && index <= db.size()) {
                cin.ignore();
                cout<<"Старый вопрос: '"<<db[index-1].question<<"'\n";
                cout<<"Новый вопрос: \n";
                getline(cin,db[index-1].question);
                cout<<"Старый ответ: '"<<db[index-1].answer<<"'\n";
                cout<<"Новый ответ: \n";
                getline(cin,db[index-1].answer);
                data_save_tf(db,filename, botName);
            }
            else {
                cout<<"Неверный номер!\n";
            }
        }
        else if (action == 4) {
            cout<<"Введите новое имя бота: ";
            getline(cin,botName);
            data_save_tf(db,filename, botName);
            cout<<"Имя успешно изменено!\n";
        }
    }
}

void questions_view(vector<questions_and_answers>& db, const string& filename) {

    int action;

    while (true) {
        cout<<"\nСПИСОК ВОПРОСОВ И ОТВЕТОВ\n";
        cout<<"===============================\n";
        for (int i = 0; i < db.size(); i++) {
            cout<<i+1<<". "<<db[i].question<<"\n > Ответ: "<<db[i].answer<<endl;
        }
        cout<<"===============================\n";
        cout<<"Введите '0' для выхода в главное меню\n";
        cin>>action;
        if (action == 0) break;
    }
}

