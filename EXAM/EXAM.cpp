#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
struct vocabulary
{
	char str[150];
};
void newmas(FILE *pf, vocabulary*&MAS, int &count); 
void translate(char *&word, vocabulary*&MAS, int &count);
void correct(char *&word, vocabulary*&MAS, int &count);
void del(char *&word, vocabulary*&MAS, int &count);
void main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	char pass[100] = "1.txt";
L:
	FILE *pf;
	int count = -1;
	fopen_s(&pf, pass, "r");
	vocabulary*MAS = new vocabulary[4000];
	newmas(pf, MAS, count);
	fclose(pf);
	char choice;
	cout << "Выберите операцию:\n1. Перевод слова;\n2. Добавление нового слова;\n3. Изменение перевода слова;\n4. Удаление слова.\n";
	cin >> choice;
	char *word = new char[75];
	char *eng = new char[75];
	char *rus = new char[75];
	int chpoint = 0;
	switch (choice)
	{
	case '1':
	{
				cout << "Введите слово которое необходимо перевести\n";
				cin >> word;
				cout << "Перевод слова " << word << ": \n";
				translate(word, MAS, count);
				break;
	}
	case '2':
	{
				cout << "Введите английское слово:\n";
				cin >> eng;
				cout << "Введите его перевод:\n";
				cin >> rus;
				strcat(strcat(strcat(strcpy(MAS[count + 1].str, eng), " "), rus), "\n");
				fopen_s(&pf, pass, "a");
				fputs(MAS[count + 1].str, pf);
				fclose(pf);
				break;
	}
	case '3':{
				 cout << "Введите слово или его перевод, которые необходимо исправить\n";
				 cin >> word;
				 correct(word, MAS, count);
				 fopen_s(&pf, pass, "w");
				 for (int i = 0; i < count; i++)
					 fputs(MAS[i].str, pf);
				 fclose(pf);
				 break; }
	case '4':
	{
				cout << "Введите слово или слово с переводом, которое необходимо удалить из словаря\n";
				cin >> word;
				del(word, MAS, count);
				fopen_s(&pf, pass, "w");
				for (int i = 0; i < count; i++)
					fputs(MAS[i].str, pf);
				fclose(pf);
				break;
	}
	default:
	{
			   cout << "Такой вариант отсутствует:\n";
			   goto L;
	}
	}
	delete[]MAS;
	delete[]word;
M:
	cout << "Хотите продолжить работу с программой:\n 1. Да.\n 2. Нет.\n";
	cin >> choice;
	switch (choice)
	{
	case '1':
		goto L;
		break;
	case '2':
		break;
	default:
		cout << "Такой вариант отсутствует:\n";
		goto M;
	}

}
void newmas(FILE *pf, vocabulary*&MAS, int &count){
	char str[150];
	while (!feof(pf))
	{
		fgets(str, 150, pf);
		count++;
	}
	rewind(pf);
	for (int i = 0; i < count; i++)
	{
		fgets(MAS[i].str, 150, pf);
	}
}
void translate(char *&word, vocabulary*&MAS, int &count){
	int chpoint = 0;
	char *eng = new char[75];
	char *rus = new char[75];
	for (int i = 0; i < count; i++)
	{
		eng = strtok(MAS[i].str, " ");
		rus = strtok(NULL, "\n");
		if (strcmp(eng, word) == 0)
		{
			cout << rus << "\n";
			chpoint++;
			continue;
		}
		if (strcmp(rus, word) == 0)
		{
			cout << eng << "\n";
			chpoint++;
		}
	}
	if (!chpoint)
	{
		cout << "невозможно произвести, так как слово отсутствует в словаре \n";
	}
}
void correct(char *&word, vocabulary*&MAS, int &count){
	int chpoint = 0;
	char *eng = new char[75];
	char *rus = new char[75];
	for (int i = 0; i < count; i++)
	{
		strcpy(rus, strrchr(MAS[i].str, ' ') + 1);
		strtok(rus, "\n");
		eng = strtok(MAS[i].str, " ");
		if ((strcmp(eng, word) == 0) || (strcmp(rus, word) == 0))
		{
			cout << "Введите исправленное английское слово:\n";
			cin >> eng;
			cout << "Введите исправленный его перевод:\n";
			cin >> rus;
			chpoint++;
		}
		strcat(strcat(strcat(strcpy(MAS[i].str, eng), " "), rus), "\n");
	}
	if (!chpoint)
	{
		cout << "слово отсутствует в словаре \n";
	}
}
void del(char *&word, vocabulary*&MAS, int &count){
	int chpoint = 0;
	char choice;
	for (int i = 0; i < count; i++)
	if (strstr(MAS[i].str, word) != 0)
	{
		chpoint++;
	N:
		cout << "Вы ходите удалить это слово? " << MAS[i].str << "\n";
		cout << "Выберете 1 - Да или 2 - Нет\n";
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
					for (int j = i; j < count - 1; j++){
						strcpy(MAS[j].str, MAS[j + 1].str);
					}
					count--;
					break;
		}
		case '2':
			break;
		default:
			cout << "Такой вариант отсутствует:\n";
			goto N;
		}
	}
	if (!chpoint)
	{
		cout << "слово отсутствует в словаре \n";
	}
}

////////// ВАЛИН ВАРИАНТ БЕЗ МАРКЕРОВ/////////////////
//
//struct str{
//	char Slov[50];//создаем структура из массива в которые будем заганять данные из файла
//};
//void menu();
//void Mas_str(FILE *pf, str *&Mas, int &count);
//void translate(char *&stroka, str *&Mas, int &count);
//void change(char *&stroka, str *&Mas, int &count);
//void Delete_Words(char *&stroka, str *&Mas, int &count);
//
//void main(){
//
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	while (true){
//		FILE*pf;
//		char *ENG = new char[50];
//		char *RUS = new char[50];
//		char *STROKA = new char[50];
//		int key, n = 0;
//
//		int count = -1;
//		fopen_s(&pf, "2.txt", "r");//открываем файл для чтения
//		if (pf == NULL) cout << "Ошибка, файл не возможно открыть файл!" << endl;
//		str*Mas = new str[3600];
//		Mas_str(pf, Mas, count);
//		fclose(pf);
//
//		menu();
//		cin >> key;
//
//		switch (key){
//		case 1://Добавление
//
//			cout << "Введите ENG слово для добавления в словарь: ";
//			cin >> ENG;
//			cout << "Введите RUS слово для добавления в словарь: ";
//			cin >> RUS;
//			strcat(strcat(strcat(strcpy(Mas[count].Slov, ENG), " "), RUS), "\n");//объединяем слова в строку
//			fopen_s(&pf, "2.txt", "a");//Открываем файл на дозапись
//			if (pf == NULL) cout << "Ошибка, файл не возможно открыть файл!" << endl;
//			//fwrite(Mas[count].Slov, strlen(Mas[count].Slov), 1, pf);
//			fputs(Mas[count].Slov, pf);
//			fflush(pf);
//			//fprintf(pf, "%s", Mas[count].Slov);//записывает слово в файл
//			fclose(pf);//закрываем файл
//			break;
//		case 2://Поиск
//			cout << "Введите слово для перевода: ";
//			cin >> STROKA;
//			cout << "Перевод: ";
//			fflush(pf);
//			translate(STROKA, Mas, count);
//			cout << "\n";
//			break;
//		case 3:
//			cout << "Введите слово для замены: ";
//			cin >> STROKA;
//			change(STROKA, Mas, count);
//			fopen_s(&pf, "2.txt", "w+");
//			if (pf == NULL) cout << "Ошибка, файл не возможно открыть файл!" << endl;
//			for (int i = 0; i < count; i++)
//				//fwrite(Mas[i].Slov, strlen(Mas[i].Slov), 1, pf);
//				fputs(Mas[i].Slov, pf);
//			fflush(pf);
//			fclose(pf);
//			break;
//		case 4://удаление
//			cout << "Введите слово: ";
//			cin >> STROKA;
//			cout << endl;
//			Delete_Words(STROKA, Mas, count);
//			fopen_s(&pf, "2.txt", "w+");
//			if (pf == NULL) cout << "Ошибка, файл не возможно открыть файл!" << endl;
//			for (int i = 0; i < count; i++)
//				fputs(Mas[i].Slov, pf);
//			//fwrite(Mas[i].Slov, strlen(Mas[i].Slov), 1, pf);
//			fflush(pf);
//
//			//fprintf(pf, "%s", Mas[i].Slov);
//			fclose(pf);
//			break;
//		case 5:
//			cout << "\tДо свидания! \n";
//			exit(0);
//		default: cout << "Ппробуйте еще раз" << endl;
//		}
//
//		delete[]Mas;
//		delete[]STROKA;
//	}
//}
//void menu(){
//
//	cout << "\tВыберите требуемое действие: \n";
//	cout << " \t1. Добавить слово в словарь, \n";
//	cout << " \t2. Найти слово в словаре \n";
//	cout << " \t3. Изменить слово в словаре \n";
//	cout << " \t4. Удалить слово!\n";
//	cout << " \t5. Выйти!\n";
//	cout << "\t";
//
//}
//void Mas_str(FILE *pf, str *&Mas, int &count){
//	char s[50];
//	while (!feof(pf)){//считаем кол-во строк в файле
//		count++;
//		fgets(s, 50, pf);
//	}rewind(pf);//ставит курсор на начала файла
//	for (int i = 0; i < count; i++){//создаем массив кол-во строк в файле
//		fgets(Mas[i].Slov, 50, pf);//заполняем строками из файла
//	}
//}
//void translate(char *&stroka, str *&Mas, int &count){
//	char *ENG = new char[50];
//	char *RUS = new char[50];
//	int  n = 0;
//	for (int i = 0; i < count; i++){
//		ENG = strtok(Mas[i].Slov, " ");
//		RUS = strtok(NULL, "\n");
//		if (strcmp(ENG, stroka) == 0){
//			cout << RUS << endl;
//			n++;
//			continue;
//		}
//		if (strcmp(RUS, stroka) == 0){
//			cout << ENG << endl;
//			n++;
//		}
//	}
//	if (n == 0)
//		cout << " Поиск окончен!Такого слова нет всловаре! \n";
//}
//void change(char *&stroka, str *&Mas, int &count)
//{
//	char *ENG = new char[50];
//	char *RUS = new char[50];
//
//	int n = 0;
//	for (int i = 0; i < count; i++)
//	{
//		strcpy(RUS, strrchr(Mas[i].Slov, ' ') + 1);
//		strtok(RUS, "\n");
//		ENG = strtok(Mas[i].Slov, " ");
//		if ((strcmp(ENG, stroka) == 0) || (strcmp(RUS, stroka) == 0))
//		{
//			cout << "Введите слово ENG: ";
//			cin >> ENG;
//			cout << endl;
//			cout << "Введите слово RUS: ";
//			cin >> RUS;
//			cout << endl;
//			n++;
//		}
//		strcat(strcat(strcat(strcpy(Mas[i].Slov, ENG), " "), RUS), "\n");
//	}
//	if (n == 0) cout << "Такого слова нет всловаре!" << endl;
//}
//void Delete_Words(char *&stroka, str *&Mas, int &count){
//
//	int n = 0;
//	for (int i = 0; i < count; i++)
//	{
//		if (strstr(Mas[i].Slov, stroka) != 0)
//		{
//			n++;
//			for (int j = i; j < count - 1; j++)
//			{
//				strcpy_s(Mas[j].Slov, Mas[j + 1].Slov);
//			}count--;
//		}
//	}
//	if (n == 0) cout << "Такого слова нет всловаре!" << endl;
//}

//
//#define name "Vasya Pupkin."
//void main()
//{
//	cout << " My name is " << name;
//}



