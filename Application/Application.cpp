#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

#define code "key"
#define file_path "files/"


using namespace std;


// Global
string alphabet;
int alphbetLenght = 0;


string input_key;
string eng_alp = "";
void loop();
void Initialize();
void encoding();
void decoding();
string LogicShifr(string usrData, string usrPass);
string LogicReShifr(string usrData, string usrPass);

int main()
{
	// Set Russian language
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");


	Initialize();

	// Main loop
	loop();


	return 0;
}

void Initialize()
{
	alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$ % &'()*+,-./:;<=>?@[]^_`{|}~ ";
	alphabet += char(34);
	alphabet += char(92);
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


	cout << "Введите название файла, который хотите зашифровать\n";
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
	ofstream fout(file_name);


	string shifrData = LogicShifr(data, input_key);
	fout << shifrData;
	cout << shifrData;


	fout.close();

	cout << "Зашифрован файл по пути: " << file_name << " по ключу: " << input_key << "\n";
}

void decoding() {
	string data;
	string file_name = file_path;
	ifstream file;


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
	ofstream fout(file_name);


	string shifrData = LogicReShifr(data, input_key);
	fout << shifrData;
	cout << shifrData;


	fout.close();

	cout << "Зашифрован файл по пути: " << file_name << " по ключу: " << input_key << "\n";
}
string LogicShifr(string usrData, string usrPass)
{
	string shifrData;
	int passLenght = size(usrPass);

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



		if (a > alphbetLenght)
		{
			a -= alphbetLenght;
		}


		shifrData += alphabet[a];
	}

	return shifrData;
}
string LogicReShifr(string usrData, string usrPass)
{
	string data;
	int passLenght = size(usrPass);

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



		if (a < 0)
		{
			a += alphbetLenght;
		}


		data += alphabet[a];
	}

	cout << "\n\n";

	return data;
}