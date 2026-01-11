#include <iostream>
#include <fstream>

#include "header.h"
using namespace std;

int main() {

    int choise;
    string botName = "Адам";
    bool running = true;
    vector<questions_and_answers> answersesbase;
    string filename = "QA_base.txt";
    char loadbase;


    while (true) {
        cout<<"Загрузить существующую базу данных? (y/n): ";
        if (!(cin>>loadbase)) {
            cin.ignore();
            continue;
        }
        if (loadbase == 'y' || loadbase == 'Y' || loadbase == 'n' || loadbase == 'N') break;
        cout<<"Некорректный ввод!\n";
    }

    if (loadbase == 'y' || loadbase == 'Y') {

        bool fileloaded = false;
        do {
            cout<<"Введите название файла (name.txt): ";
            cin>>filename;

            ifstream checkfile(filename);
            if (checkfile.is_open()) {
                checkfile.close();
                data_load_ff(answersesbase, filename, botName);
                fileloaded = true;
            }
            else {
                cout<<"Ошибка: файл "<<filename<<" не найден. Попробуйте снова.\n";
            }
        } while (!fileloaded);
    }
    else if (loadbase == 'n' || loadbase == 'N') {
        cout<<"Создание новой базы...\nВведите имя для нового файла базы (Например, base.txt): ";
        cin>>filename;
    }
    cin.ignore();
    cout<<"Добро пожаловать в Чат-бота "<<botName<<"!\n";
    while(running) {
        cout<<endl;
        cout<<"===============================================\n";
        cout<<"     Вас приветствует чат-бот "<<botName<<"!\n";
        cout<<"===============================================\n";
        cout<<"Список команд:\n";
        cout<<"1. Задать вопрос\n";
        cout<<"2. Показать все вопросы\n";
        cout<<"3. Админ-панель\n";
        cout<<"0. Выход\n";
        cout<<"===============================================\n";
        cout<<"Введите команду, чтобы продолжить: ";
        try {
            if (!(cin>>choise)) {
                cout<<"\nОшибка! Введите число 0-3!\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            switch(choise) {
                case 1:
                    answer(answersesbase, botName);
                    break;
                case 2:
                    questions_view(answersesbase, filename);
                    break;
                case 3:
                    admin_mode(answersesbase, filename,botName);
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    cout<<"\nОшибка! Введите число 0-3!\n";
                    break;
            }
        } catch (exception& e) {
            cout<<"Ошибка! Такого варианта нет.";
            cin.clear();
            cin.ignore();
        }
    }
}