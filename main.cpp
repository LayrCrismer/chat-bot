#include <iostream>
#include <fstream>
#include <limits>
#include "header.h"
using namespace std;

int main() {

    int choise;
    string botName = "Адам";
    bool running = true;
    vector<questions_and_answers> answersesbase;
    string filename = "QA_base.txt";
    char loadbase;
    string input;

    while (true) {
        cout<<"Загрузить существующую базу данных? (y/n): ";
        cin>>input;
        if (input.length()==1) {
            loadbase = input[0];
            if (loadbase == 'y' || loadbase == 'Y' || loadbase == 'n' || loadbase == 'N') break;
        }
        cout<<RED<<"Некорректный ввод!\n"<<WHITE;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout<<RED<<"Ошибка: файл "<<filename<<" не найден. Попробуйте снова.\n"<<WHITE;
            }
        } while (!fileloaded);
    }
    else if (loadbase == 'n' || loadbase == 'N') {
        cout<<GOLD<<"Создание новой базы...\n"<<WHITE;
        while (true){
            cout<<"Введите имя для нового файла базы (Например, base.txt): ";
            cin>>filename;

            size_t dot = filename.find_last_of('.');

            if (dot == string::npos) {
                filename += ".txt";
                break;
            } else {
                string extens = filename.substr(dot);
                if (extens == ".txt") {
                    break;
                } else {
                    cout<<RED<<"Ошибка: Неверное расширение "<<WHITE<<"'"<<extens<<"'. База должна быть в формате .txt\n";
                }
            }
        }
        cout<<GREEN<<"База данных успешно создана! (Будет сохранена при её изменении)\n";
        cout<<"Боту присвоено стандартное имя - Адам\n"<<WHITE;
    }
    cin.ignore();

    while(running) {
        string menuInput;

        cout<<endl;
        cout<<"===============================================\n";
        cout<<GREEN<<"     Вас приветствует чат-бот "<<botName<<"!\n"<<WHITE;
        cout<<"===============================================\n";
        cout<<"Список команд:\n";
        cout<<"1. Задать вопрос\n";
        cout<<"2. Показать все вопросы\n";
        cout<<"3. Админ-панель\n";
        cout<<"0. Выход\n";
        cout<<"===============================================\n";
        cout<<"Введите команду, чтобы продолжить: ";
        cin>>menuInput;

        if (menuInput.length() != 1 || !isdigit(menuInput[0])) {
            cout<<RED<<"\nОшибка! Введите число 0-3!\n"<<WHITE;
            continue;
        }
        choise=menuInput[0]-'0';

        try {
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
                    cout<<RED<<"\nОшибка! Введите число 0-3!\n"<<WHITE;
                    break;
            }
        } catch (exception& e) {
            cout<<RED<<"Ошибка! Такого варианта нет."<<WHITE;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}