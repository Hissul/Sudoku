
/*
Тема: Судоку
Необходимо реализовать :

● Автоматическую генерацию поля
● Разные уровни сложности
● Подсказки игроку
● “Подсветка” цифр в поле
● Кол - во ошибок
● Время выполнения уровня

Результат игры нужно сохранить в файл : 
Имя, время решения и кол - во ошибок.

В начале игры надо реализовать раздел в меню, где
будут показаны все рекорды тех, кто играл (взять данные из файла )
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <string>
#include "Sudoku.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	Sudoku s;

	s.BodyGame();	

	return 0;
}