
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;

//	ofstream - запись данных в файл
//	ifstream - чтение данных из файла
//	fstream - чтение и запись

//	Конструкторы
//	1. fstream() - создаёт поток, не открывая файл
//	2. fstream(const char* path, int mode, int filebuf::openpret) -
//				создаёт поток, открывает файл и связывает его с потоком
//				const char* path - путь к файлу
//				int mode - режим чтения
//						in = 0x01 - открывает только для чтения
//						out = 0x02 - открывает только для записи
//						ate = 0x04 - устанавливает указатель на конец файла
//						app = 0x08 - дописывать данные в конец файла
//						trunc = 0x10 - урезает файл до нулевой длины
//						_Nocreate = 0x40 - если файла не существует, то ошибка открытия
//						_Noreplace = 0x40 - если файл уже существует, то ошибка открытия
//						binary = 0x20 - открывает файл в двоичном формате
//							Ключевое слово ios:: - для использования режимов чтения
//				int filebuf::openpret - защите файла
//	3. fstream(int f) - создаёт поток и связывает с уже открытым файлом
//			int f - дескрпитор файла
//	4. fstream(int f, char* buf, int len) - то же, что и 3, но назначает буфер
//			int f - дескриптор файла
//			char* buf - буфер
//			int len - размер буфера

//						|МЕТОДЫ|
//	open(const char* filename, int mode, int protection) - присоеденить файл к определенному потоку
//	close() - закрывает поток и очищает буфер, отсоединяет поток и выключает файл
//	read(char* buf, int len) - считывает поток символов (блоками)
//	write(char* buf, int len) - производит запись блоков символов
//	get(), gets() - извелакет один символ/строку из потока
//	put(), puts() - записывает один символ/строку в поток
//	getline() - не извлекает нуль символ
//	ignore(int n = 1, int d = EOF) - извелакет символы из потока, пока не 
//									 встретит ограничитель или не извлечет все символы
//	gcount() - возращает число символов, извлеченных последней функцией безформатного ввода
//	peek() - позволяет посмотреть на очередной символ входного потока, 
//			 возращает код следующего символа, но оставляет этот символ в потоке
//	putback(char c) - помещает в поток символ, который становиться текущим 
//					  и становится следующим, извлекаемым из потока символом
//	seekg(long pos) - устанавливает позицию чтению из потока на то положение, 
//					  которое было передано в качестве параметра
//	seekp(long pos) - устанавливает абсолютное позицию записи в поток
//	tellg() - определяет текущую позицию чтения из потока
//	tellp() - определяет текущую позици записи в потоке



#define MAX_PATH 260
#define NUM_COLS 18
#define NUM_ROWS 24


int Menu(){
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите 1 для добавления структуры в файл\n"
		<< "Введите 2 для показа всех структур в файле\n"
		<< "Введите 3 для выхода\n";
	int choice; 
	cin >> choice; 
	return choice;
}

class Man {
	int age;
	char* name;
	char* surname;

public:
	Man(char* n, char* s, int a);
	Man() {};
	~Man();

	void Put();
	void Show();
	void SaveToFile();
	static void ShowFromFile();
};

Man::Man(char* n, char* s, int a) {
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);

	surname = new char[strlen(s) + 1];
	strcpy_s(surname, strlen(s) + 1, s);

	age = a;
}

Man::~Man() {
	delete[] name;
	delete[] surname;
}

void Man::Put() {
	char temp[1024];

	cout << "Введите имя -> "; cin >> temp;
	if (name) delete[] name;

	name = new char[strlen(temp) + 1];
	strcpy_s(name, strlen(temp) + 1, temp);


	cout << "Введите фамилию -> "; cin >> temp;
	if (surname) delete[] surname;

	surname = new char[strlen(temp) + 1];
	strcpy_s(surname, strlen(temp) + 1, temp);

	
	cout << "Введите возраст -> "; cin >> age;
}


void Man::Show() {
	cout << "Имя: " << name << endl;
	cout << "Фамилия: " << surname << endl;
	cout << "Возраст: " << age << endl;;
}

void Man::SaveToFile() {
	int size;
	fstream f("C:\\Test\\test.txt", ios::out | ios::binary | ios::app);
	if (!f) {
		cout << "Не удалось открыть файл\n";
		return;
	}

	f.write((char*)&age, sizeof(int));

	size = strlen(name);
	f.write((char*)&size, sizeof(int));
	f.write((char*)&name, size * sizeof(char));

	size = strlen(surname);
	f.write((char*)&size, sizeof(int));
	f.write((char*)&surname, size * sizeof(char));

	f.close();
}

void Man::ShowFromFile() {
	fstream f("C:\\Test\\test.txt", ios::in | ios::binary);
	if (!f){
		cout << "Не удалось открыть файл\n";
		return;
	}
	char* n, * s;
	int a, temp;
	
	while (f.read((char*)&a, sizeof(int))) {

		cout << "Имя: ";
		f.read((char*)&temp, sizeof(int));
		n = new char[temp + 1];
		f.read((char*)n, temp * sizeof(char));
		n[temp] = '\0';
		cout << n;

		cout << "Фамилия: ";
		f.read((char*)&temp, sizeof(int));
		s = new char[temp + 1];
		f.read((char*)s, temp * sizeof(char));
		s[temp] = '\0';
		cout << s;

		cout << "Возраст: " << a << endl;

		delete[]n;
		delete[]s;
	}
	
	f.close();
}




int main()
{
	      

	/*setlocale(LC_ALL, "RUSSIAN");
	char Answer;
	const int MessageCount = 8;
	int i, j;

	enum {
		CHOICE = 3, INPUT_FILENAME, INPUT_DIMENSIONS, INPUT_ELEMENT, FILE_ERROR
	};

	char Msg[MessageCount][50] = {
		"1. Вывести данные из текстового файла\n",
		"2. Записать данные в текстовый файл\n",
		"3. Выход из программы\n",
		"Ваш выбор: ",
		"Введите имя обрабатываемого файла: ",
		"Введите размерность матрицы:\n",
		"Введите элементы матрицы:\n",
		"Невозможно открыть файл\n"
	};

	do {
		for (int i = 0; i < 4; i++) {
			cout << Msg[i];
		}
		cin >> Answer;
	} while (Answer < '1' || Answer > '3');

	if (Answer == '3') return 0;

	char FileName[50];
	int M, N, num;

	cout << "\n" << Msg[INPUT_FILENAME];
	cin >> FileName;

	if (Answer == '1') {
		ifstream inF(FileName, ios::in || ios::_Nocreate);
		if (!inF) {
			cout << endl << Msg[FILE_ERROR];
			return 0;
		}
		inF >> M;
		inF >> N; 

		for (i = 0; i < M; i++){
			for (j = 0; j < N; j++){
				inF >> num;
				cout << setw(6) << num;
			}
			cout << endl;
		}
		inF.close();
	}

	else {
		ofstream outF(FileName, ios::out);
		if (!outF) {
			cout << endl << Msg[FILE_ERROR];
			return 0;
		}
		cout << Msg[INPUT_DIMENSIONS];
		cout << "M: "; cin >> M;
		cout << "N: "; cin >> N;
		outF << M << ' ' << N << "\n";

		cout << Msg[INPUT_ELEMENT];
		for (i = 0; i < M; i++) {
			for (j = 0; j < N; j++) {
				cout << "A[" << i << "][" << j << "] = ";
				cin >> num;
				outF << num << " ";
				outF << '\n';
			}
		}
		outF.close();
	}*/

	//char path[MAX_PATH];
	//cout << "Input the path tp file: ";
	//cin.getline(path, MAX_PATH);
	//
	//int counter = 0, i = 0, j = 0;
	//char text[NUM_COLS];
	//
	//ifstream input(path, ios::in | ios::binary);
	//if (!input) {
	//	cout << "Can't open file for display!\n";
	//	return 1;
	//}
	//// Режим отображения в верхнем регистре для 16-ого вывода
	//cout.setf(ios::uppercase);
	//
	//while (!input.eof()) {
	//	for (int i = 0; i < NUM_COLS && !input.eof(); i++) {
	//		input.get(text[i]);
	//	}
	//	if (i < NUM_COLS)
	//		i--;
	//
	//	for (j = 0; j < i; j++) {
	//		if ((unsigned)text[j] < 0x10)
	//			cout << setw(2) << 0 << hex << (unsigned)text[j];
	//		else
	//			cout << setw(3) << hex << text[j];
	//	}
	//
	//	for (; j < NUM_COLS; j++)
	//		cout << "    ";
	//	cout << "\t";
	//
	//	for (j = 0; j < i; j++) {
	//		if (text[j] > 31 && text[j] <= 255)
	//			cout << text[j];
	//		else
	//			cout << ".";
	//	}
	//	cout << "\n";
	//
	//	if (++counter == NUM_ROWS) {
	//		counter = 0;
	//		cout << "Press any key to continue...\n" << flush;
	//		_getch();
	//		cout << '\n';
	//	}
	//}
	//input.close();

}


