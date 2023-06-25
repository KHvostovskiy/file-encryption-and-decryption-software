#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

#define code "key"
#define file_path "files/"
#define file_path_data "files/data.txt"


using namespace std;


// Global
string alphabet;
int alphbetLenght = 0;


string input_key;
string eng_alp = "";


// Functions
void loop();
void Initialize();
void encoding();
void decoding();
void saves_data(string data);
string LogicShifr(string usrData, string usrPass);
string LogicReShifr(string usrData, string usrPass);

int main()
{
	// Set Russian language
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_ALL, "Rus");


	Initialize();

	// Main loop
	loop();


	return 0;
}

void Initialize()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$ %&'()*+,-./:;<=>?@[]^_`{|}~АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	alphabet += char(34);
	alphabet += char(92);
	//
	///
	for (int i = 1; i <= 6; i++)
		alphabet += char(i);
	for (int i = 11; i <= 22; i++)
		if (i == 13)
			continue;
		else
			alphabet += char(i);
	///
	//

	alphbetLenght = size(alphabet);
}

void loop() {
	short choice;
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

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	cout << "Введите название файла, который хотите зашифровать\n";
	cin >> file_name;
	file_name.insert(0, file_path);
	file_name.append(".txt");

	file.open(file_name);


	if (file) {
		string line;
		/*while (getline(file, line))
		{
			data += line;
			data += '\n';
		}*/
		while (getline(file, line)) {
			data += line;
			data += '\n';
		}

		file.close();
		cout << "Файл найден\n";
	}
	else {
		bool is_open = false;
		while (!is_open) {
			cout << "Файл не найден, повторите попытку ввода имени файла, или введите q для выхода\n";
			cin >> file_name;
			if (file_name == "q")
				return;

			file_name.insert(0, file_path);
			file_name.append(".txt");
			file.open(file_name);
			if (file) {
				string line;
				while (getline(file, line)) {
					data += line;
					data += '\n';
				}
				is_open = true;
			}
			file.close();
		}
		cout << "Файл найден\n";
	}
	cout << "Введите ключ шифрования\n";
	cin >> input_key;

	//Далее механика шифратора
	ofstream fout(file_name);

	// delete trash symbol
	string concept;
	for (int i = 0; i < size(data) - 1; i++)
		concept += data[i];

	string shifrData = LogicShifr(concept, input_key);
	fout << shifrData;
	//cout << shifrData;


	fout.close();

	string v_data;
	v_data = v_data.append("Зашифрован файл по пути: ").append(file_name).append(" по ключу: ").append(input_key).append("\n");
	if (file_name != "files/data.txt")saves_data(v_data);
	cout << v_data;
}

void decoding() {
	string data;
	string file_name = file_path;
	ifstream file;


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	cout << "Введите название файла, который хотите расшифровать\n";
	cin >> file_name;
	file_name.insert(0, file_path);
	file_name.append(".txt");

	file.open(file_name);


	if (file) {
		string line;
		while (getline(file, line))
		{
			data += line;
			data += '\n';
		}

		file.close();
		cout << "Файл найден\n";
	}
	else {
		bool is_open = false;
		while (!is_open) {
			cout << "Файл не найден, повторите попытку ввода имени файла, или введите q для выхода\n";
			cin >> file_name;
			if (file_name == "q")
				return;

			file_name.insert(0, file_path);
			file_name.append(".txt");
			file.open(file_name);
			if (file) {
				string line;
				while (getline(file, line)) {
					data += line;
					data += '\n';
				}
				is_open = true;
			}
			file.close();
		}
		cout << "Файл найден\n";
	}
	cout << "Введите ключ\n";
	cin >> input_key;

	//Далее механика шифратора
	ofstream fout(file_name);

	// delete trash symbol
	string concept;
	for (int i = 0; i < size(data) - 1; i++)
		concept += data[i];

	string shifrData = LogicReShifr(concept, input_key);
	fout << shifrData;
	//cout << shifrData;


	fout.close();

	string v_data;
	v_data = v_data.append("Расшифрован файл по пути: ").append(file_name).append(" по ключу: ").append(input_key).append("\n");
	cout << v_data;
	if (file_name != "files/data.txt")saves_data(v_data);
}
string LogicShifr(string usrData, string usrPass)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string shifrData;
	int passLenght = size(usrPass);

	//Генерация ключа цезаря
	int cezar_sdvig = 0;
	for (int i = 0; i < size(usrPass); i++) {
		cezar_sdvig += alphabet.find(usrPass[i]);
	}
	if (cezar_sdvig > alphbetLenght) {
		cezar_sdvig %= alphbetLenght;
	}
	//cout << "Cezar: " << cezar_sdvig << "\n";
	//

	for (int i = 0; i < size(usrData); i++)
	{
		if (usrData[i] == '\n')
		{
			shifrData += '\t';

			continue;
		}
		else if (usrData[i] == '\t')
		{
			shifrData += '\n';

			continue;
		}


		int a = alphabet.find(usrData[i]) + alphabet.find(usrPass[i % passLenght]);
		//cout << usrData[i] << '\t' << usrPass[i % passLenght] << '\n';
		//cout << alphabet.find(usrData[i]) << '\t' << alphabet.find(usrPass[i % passLenght]) << '\n';



		//шифрование Цезарем
		a += cezar_sdvig;


		a %= alphbetLenght;
		shifrData += alphabet[a];


	}

	return shifrData;
}
string LogicReShifr(string usrData, string usrPass)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string data;
	int passLenght = size(usrPass);

	//Поиск ключа цезаря
	int cezar_sdvig = 0;
	for (int i = 0; i < size(usrPass); i++) {
		cezar_sdvig += alphabet.find(usrPass[i]);
	}
	if (cezar_sdvig > alphbetLenght) {
		cezar_sdvig %= alphbetLenght;
	}
	//cout << "Cezar: " << cezar_sdvig << "\n";
	//


	for (int i = 0; i < size(usrData); i++)
	{
		if (usrData[i] == '\n')
		{
			data += '\t';

			continue;
		}
		else if (usrData[i] == '\t')
		{
			data += '\n';

			continue;
		}

		int a = alphabet.find(usrData[i]) - alphabet.find(usrPass[i % passLenght]);

		//cout << usrData[i] << '\t' << usrPass[i % passLenght] << '\n';
		//cout << alphabet.find(usrData[i]) << '\t' << alphabet.find(usrPass[i % passLenght]) << '\n';

		//Расшифрование Цезарем
		a -= cezar_sdvig;

		if (a < 0)
			a += alphbetLenght;
		//
		if (a < 0)
		{
			a += alphbetLenght;
		}


		data += alphabet[a];
	}

	//cout << "\n\n";

	return data;
}
void saves_data(string data) {
	string _code = code; //Код от файла

	// read file data
	ifstream f(file_path_data);

	// Read from file data by lines
	string line;

	// Data to work
	string _data;

	while (getline(f, line)) {
		_data += line;
		_data += '\t';
	}
	f.close();

	_data = LogicReShifr(_data, _code);
	_data += data;
	ofstream y(file_path_data);
	y << LogicShifr(_data, _code);
	y.close();
}