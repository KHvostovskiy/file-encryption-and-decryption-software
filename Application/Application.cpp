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

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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

	string file_name = file_path;
	//char tempFileName[64]{};
	string tempFileName;
	ifstream file;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	do {

		cout << "Введите название файла, который хотите зашифровать\n";
		cin >> file_name;
		file_name.insert(0, file_path);
		file_name.append(".txt");

		file.open(file_name);


		/*for (int i = 0; i < size(file_name); i++)
			tempFileName[i] = file_name[i];*/
		tempFileName = file_name;

		file_name = "";

		if (!file.is_open())
			cout << "Неправильное имя файла\n";

	} while (!file.is_open());


	cout << "Введите ключ шифрования\n";
	cin >> input_key;



	string data;
	int maxDataSize = 500;
	char smb = 0;

	int i = 1;

	file.get(smb);
	if (smb == 0)
	{
		cout << "Извините уважаемый пользователь, в вашем файле нет текста\n";
		return;
	}
	while (smb)
	{
		data += smb;
		while (i < maxDataSize && file.get(smb))
		{
			data += smb;
			i++;
		}

		if (!file.get(smb))
			smb = 0;


		// Механика шифрования
		// create temp file in system
		string tempName;

		tempName += file_path;
		tempName += "temp.txt";

		ofstream fout(tempName, ios::app);


		fout << LogicShifr(data, input_key);


		fout.close();


		i = 0;
		data = "";
	}

	file.close();


	remove(tempFileName.c_str());


	string tempName;

	tempName += file_path;
	tempName += "temp.txt";

	rename(tempName.c_str(), tempFileName.c_str());



	//("Зашифрован файл по пути: ").append(tempFileName).append(" по ключу: ").append(input_key).append("\n");

	string v_data;
	v_data = v_data.append("Зашифрован файл по пути: ").append(tempFileName).append(" по ключу: ").append(input_key).append("\n");
	if (tempFileName != "files/data.txt")saves_data(v_data);
	cout << v_data;
}

void decoding() {
	string file_name = file_path;
	string tempFileName;
	ifstream file;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	do {

		cout << "Введите название файла, который хотите расшифровать\n";
		cin >> file_name;
		file_name.insert(0, file_path);
		file_name.append(".txt");

		file.open(file_name);


		tempFileName = file_name;

		file_name = "";

		if (!file.is_open())
			cout << "Неправильное имя файла\n";

	} while (!file.is_open());

	cout << "Введите ключ\n";
	cin >> input_key;



	string data;
	int maxDataSize = 500;
	char smb = 0;

	int i = 1;

	file.get(smb);
	if (smb == 0)
	{
		cout << "Извините уважаемый пользователь, в вашем файле нет текста\n";
		return;
	}
	while (smb)
	{
		data += smb;
		while (i < maxDataSize && file.get(smb))
		{
			data += smb;
			i++;
		}

		if (!file.get(smb))
			smb = 0;


		// Механика шифрования
		// create temp file in system
		string tempName;

		tempName += file_path;
		tempName += "temp.txt";

		ofstream fout(tempName, ios::app);


		fout << LogicReShifr(data, input_key);


		fout.close();


		i = 0;
		data = "";
	}

	file.close();


	remove(tempFileName.c_str());


	string tempName;

	tempName += file_path;
	tempName += "temp.txt";

	rename(tempName.c_str(), tempFileName.c_str());




	//("Расшифрован файл по пути: ").append(tempFileName).append(" по ключу: ").append(input_key).append("\n");
	string v_data;
	v_data = v_data.append("Расшифрован файл по пути: ").append(tempFileName).append(" по ключу: ").append(input_key).append("\n");
	if (tempFileName != "files/data.txt")saves_data(v_data);
	cout << v_data;
}
string LogicShifr(string usrData, string usrPass)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string shifrData;
	int passLenght = size(usrPass);

	//Генерация ключа цезаря
	int cezar_sdvig = 0;
	for (int i = 0; i < passLenght; i++) {
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
	for (int i = 0; i < passLenght; i++) {
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
void saves_data(string _data_) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream file(file_path_data, ios::app);
	//string _code = code; //Код от файла
	while (size(_data_) % (size(code) - 1) != 0) {
		_data_.insert(0, "!");
	}
	file.write(LogicShifr(_data_, code).c_str(), size(_data_));
	//file << LogicShifr(_data_, code);
	file.close();
}