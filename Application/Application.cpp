#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
//тект для теста. Хай всем кстати
#define code "key"
#define file_path "files/"

using namespace std;

string input_key;
string eng_alp = "";
void loop();
void encoding();
void decoding();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    loop();
    return 0;
}
void loop() {
    short int choice;
    cout << "Выберете действие: 1 - расшифровать файл, 2 - зашифровать файл, 3 - выйти\n";
    cin >> choice;
    if (choice != 2 && choice != 1 && choice != 3) {
        cout << "Команда введена не корректно. Попробуйте еще раз\n";
        loop();
    }
    switch (choice) {
    case 1:
        decoding();
        break;
    case 2:
        encoding();
        break;
    case 3:
        exit(0);
        break;
    }
    loop();
}
void encoding() {
    string data;
    string file_name = file_path;
    ifstream file;
    cout << "Введите название файла, который хотите зашифровать\n";
    cin >> file_name;
    file_name.insert(0, file_path);
    file_name.append(".txt");
    file.open(file_name);
    if (file) {
        string line;
        while (getline(file, line))
            data += line;
        file.close();
        cout << "Файл найден\n";
    }
    else {
        while (!file) {
            cout << "Файл не найден, повторите попытку ввода имени файла, или введите q для выхода\n";
            cin >> file_name;
            if (file_name == "q")
                return;
            file_name.insert(0, file_path);
            file_name.append(".txt");
            file.open(file_name);
            string line;
            while (getline(file, line))
                data += line;
            data += '\n';
            file.close();
        }
        cout << "Файл найден\n";
    }
    cout << "Введите ключ шифрования\n";
    cin >> input_key;

    //Далее механика шифратора
    cout << "Data: " << data << endl;
    int i = 0;
    int a = 0; //Для ключа
    while (data[i] != '\0') {
        if (data[i] == '\n')
            cout << "Найден абзац\n";
        i++;
    }
    //
    cout << "Зашифрован файл по пути: " << file_name << " по ключу: " << input_key << "\n";
}
void decoding() {

}