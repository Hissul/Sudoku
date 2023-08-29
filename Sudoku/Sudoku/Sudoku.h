#pragma once

using namespace std;

class Sudoku
{
	enum{EASY = 1 , NORMAL = 2 , HARD = 3 ,SIZE = 9};
	string path = "SudokuStatistic.txt";

	int field[SIZE][SIZE]; // базовое поле
	int frist_number_in_row; // первая цифра с строке
	int gameField[SIZE][SIZE]; // игровое поле

	char user_name[15];
	char game_difficult[8];
	int mistake_count; // колличество ошибок
	int game_time; // время в игре
	int hits_count; // количество использованных позсказок

	int number_open; // колличество открытых ячеек

public:
	Sudoku(); // конструктор

	void CreateFild(); // метод создания поля
	void RotateField(); // метод для поворота поля
	void SwapRows(); // метод обмена двух строк в пределах одного района
	void SwapColumns(); // метод обмена двух колонок в пределах одного района


	void CreateGameFild(); // создание игрового поля и выбор сложности	

	void Check(int frist_number_in_row); // проверка числа в поле на выход за лимиты

	void ShowField(); // метод вывода базового поля в консоль
	void ShowGameField(); // метод вывода игрового поля в консоль

	void BodyGame(); // игра
	bool IsEmpty(int user_row ,int user_col); // проверка клетки

	void ShowStatistics(); // вывод статистики в консоль для текущей игры

	void SafeStatistic(); // сохраняем статистику в файл
	void LoadStatistic(); // чтение статистики из файла

};