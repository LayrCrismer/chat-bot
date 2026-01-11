#include <iostream>
#include <limits>

#include "header.h"
using namespace std;

int main() {

    int choise;
    bool running = true;
    vector<questions_and_answers> answersesbase;
    string filename = "QA_base.txt";

    data_load_ff(answersesbase, filename);

    while(running) {
        cout<<endl;
        cout<<"Вас приветствует чат-бот для вопросов и ответов\n";
        cout<<"===============================================\n";
        cout<<"Список команд:\n";
        cout<<"1. Задать вопрос\n";
        cout<<"2. Показать все вопросы\n";
        cout<<"3. Админ-мод\n";
        cout<<"0. Выход\n";
        cout<<"===============================================\n";
        cout<<"Введите команду, чтобы продолжить: ";
        try {
            cin>>choise;
            switch(choise) {
                case 1:
                    answer(answersesbase);
                    break;
                case 2:
                    //код
                    break;
                case 3:
                    //код
                    break;
                case 0:
                    //код
                    break;
            }
        } catch (exception& e) {
            cout<<"Ошибка!";
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
}