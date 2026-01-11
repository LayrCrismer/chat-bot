#include <iostream>
#include "header.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

void data_load_ff(vector<questions_and_answers>& db, const string& filename, string& botName) {
    cout<<"\nЗагрузка базы вопросов-ответов...\n";
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<RED<<"Файл не найден"<<WHITE;
        return;
    }

    getline(file, botName);
    cout<<GREEN<<"База успешно загружена!\n"<<WHITE;
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
        cout<<GREEN<<"База вопросов-ответов успешно сохранена!\n"<<WHITE;
    }
    else {
        cout<<RED<<"Ошибка. Не удалось открыть базу вопросов-ответов.\n"<<WHITE;
    }

}

void answer(const vector<questions_and_answers>& db, const string& botName) {
    cout<<"\n(Введите 'back' чтобы вернуться в главное меню)\n";
    string question;
    cin.ignore();
    while (true) {
        cout<<MAGENTA<<"Пользователь: "<<WHITE;

        if (!getline(cin, question) || question == "back") {
            break;
        }

        bool found = false;
        for (const auto& item : db) {
            //cout<<"Сравниваю: ["<<item.question<<"] и ["<<question<<"]"<<endl;
            if (question == "Как тебя зовут?" || question == "Твоё имя?" || question == "Ты кто?") {
                cout<<CYAN<<botName<<WHITE<<": Меня зовут "<<botName<<"\n";
                found = true;
                break;
            }
            if (item.question == question) {
                cout<<CYAN<<botName<<WHITE<<": "<<item.answer<<"\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout<<CYAN<<botName<<WHITE": Я не знаю ответа на этот вопрос "<<RED<<":( \n"<<WHITE;
        }
    }
}

void add_question(vector<questions_and_answers>& db, const string& filename, const string& botName) {
    string q,a;
    cout<<"Введите новый вопрос: ";
    getline(cin,q);
    cout<<"Введите ответ на него: ";
    getline(cin,a);
    if (!q.empty() && !a.empty()) {
        db.push_back({q, a});
        data_save_tf(db, filename, botName);
    } else {
        cout<<RED<<"Ошибка: Вопрос или ответ не могут быть пустыми!\n"<<WHITE;
    }
}

void delete_question(vector<questions_and_answers>& db, const string& filename, const string& botName) {
    if (db.size()==0) {
        cout<<RED<<"\nБаза вопросов-ответов пуста.\n"<<WHITE;
    }
    int index;
    cout<<"Введите номер вопроса для удаления: \n";
    cin>>index;
    if (index > 0 && index <= db.size()) {
        db.erase(db.begin() + (index-1));
        data_save_tf(db,filename,botName);
    } else {
        cout<<RED<<"Неверный номер!\n"<<WHITE;
    }
}

void edit_question(vector<questions_and_answers>& db, const string& filename, const string& botName) {
    if (db.size()==0) {
        cout<<RED<<"\nБаза вопросов-ответов пуста.\n"<<WHITE;
        return;
    }
    int index;
    cout<<"Введите номер вопроса для редактирования: \n";
    cin>>index;
    if (index > 0 && index <= db.size()) {
        cin.ignore();
        cout<<GRAY<<"Старый вопрос: '"<<db[index-1].question<<"'\n"<<WHITE;
        cout<<"Новый вопрос: \n";
        getline(cin,db[index-1].question);
        cout<<GRAY<<"Старый ответ: '"<<db[index-1].answer<<"'\n"<<WHITE;
        cout<<"Новый ответ: \n";
        getline(cin,db[index-1].answer);
        data_save_tf(db,filename, botName);
    }
    else {
        cout<<RED<<"Неверный номер!\n"<<WHITE;
    }

}

void rename_bot(vector<questions_and_answers>& db, const string& filename, string& botName) {
    cout<<"Введите новое имя бота: ";
    getline(cin,botName);
    data_save_tf(db,filename, botName);
    cout<<GREEN<<"Имя успешно изменено!\n"<<WHITE;
}

void admin_mode(vector<questions_and_answers>& db, const string& filename, string& botName) {

    int action;

    while (true) {
        cout<<"===============================================\n";
        cout<<GOLD<<"                 Админ-панель\n"<<WHITE;
        cout<<"===============================================\n";
        cout<<"1. Добавить вопрос-ответ\n";
        cout<<"2. Удалить вопрос\n";
        cout<<"3. Редактировать запись\n";
        cout<<"4. Изменить имя бота\n";
        cout<<"0. Выход в меню\n";
        cout<<"===============================================\n";
        cout<<"Введите команду, чтобы продолжить: ";

        cin.ignore();
        if (!(cin>>action)) {
            cout<<RED<<"\nОшибка! Введите число 0-4!\n"<<WHITE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (action == 0) break;
        switch (action) {
            case 1: add_question(db, filename, botName); break;
            case 2: delete_question(db, filename, botName); break;
            case 3: edit_question(db, filename, botName); break;
            case 4: rename_bot(db, filename, botName); break;
            default: cout<<RED<<"Неверная команда!\n"<<WHITE; break;
        }
    }
}

void questions_view(vector<questions_and_answers>& db, const string& filename) {

    int action;

    while (true) {
        cout<<MAGENTA<<"\nСПИСОК ВОПРОСОВ И ОТВЕТОВ\n"<<WHITE;
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

