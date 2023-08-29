
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Sudoku.h"

using namespace std;

// конструктор
Sudoku::Sudoku()
{
	CreateFild();
	//CreateGameFild();

	this->game_time = 0;
	this->mistake_count = 0;
	this->number_open = 0;
	this->hits_count = 0;
}

// метод создания поля
void Sudoku::CreateFild()
{
	srand(time(NULL));

	int frist_number = rand() % 9 + 1;
	int tmp_field[SIZE][SIZE];

	for (int row = 0; row < SIZE; ++row) {
		// Размещаем в первую строку 1 2… 8 9
		// в строках ниже смещаем на 3 позиции влево, т.е. 4 5… 2 3 и 7 8… 5 6.	
		if (row == 0)
			frist_number_in_row = frist_number;
		else if (row == 1 || row == 2) {
			frist_number_in_row += 3;
			Check(frist_number_in_row); // проверка числа в поле
		}		
		else if (row == 3) { // Далее переходя в следующий район по вертикали смещаем на 1 позицию влево предыдущий район.
			frist_number_in_row = frist_number + 1;
			Check(frist_number_in_row); // проверка числа в поле
		}
		else if (row == 4 || row == 5) {
			frist_number_in_row += 3;// в строках ниже смещаем на 3 позиции влево
			Check(frist_number_in_row); // проверка числа в поле
		}		
		else if (row == 6) { // переход в следующий район
			frist_number_in_row = frist_number + 2;
			Check(frist_number_in_row); // проверка числа в поле
		}
		else  {
			frist_number_in_row += 3;
			Check(frist_number_in_row); // проверка числа в поле
		}		

		for (int col = 0; col < SIZE; ++col) {

			field[row][col] = frist_number_in_row++; // заполняем массив и увеличиваем значение frist_number_in_row			

			if (frist_number_in_row > 9) // проверка значения frist_number_in_row
				frist_number_in_row = 1;
		}
	}
	 	
	RotateField();	
	SwapRows();
	SwapColumns();	

	ShowField(); // УБРАТЬ
}

// метод для поворота поля
void Sudoku::RotateField()
{
	int tmp_field[SIZE][SIZE]; // массив для временного хранения данных

	for (int col = 0; col < SIZE; ++col) { // переворачиваем поле 
		// переписываем значения во временный массив
		for (int row = 0; row < SIZE; ++row) {
			tmp_field[row][col] = field[col][row];			
		}
	}

	for (int row = 0; row < SIZE; ++row) { // копируем из временного в основной
		for (int col = 0; col < SIZE; ++col) {
			field[col][row] = tmp_field[col][row];
		}
	}

}

// метод обмена двух строк в пределах одного района
void Sudoku::SwapRows()
{
	srand(time(NULL));
	
	int row_for_swap_1 = 0, row_for_swap_2 = 0;

	for (int row = 0; row < SIZE; ++row) { 		

			if (row == 2) { // получаем номера строк для обмена
				row_for_swap_1 = rand() % 2;

				if (row_for_swap_1 == 2)
					row_for_swap_2 = 0;
				else
					row_for_swap_2 = row_for_swap_1 + 1;				

				swap(field[row_for_swap_1], field[row_for_swap_2]);

			}else if (row == 5) {				

				row_for_swap_1 += 3;

				if (row_for_swap_1 == 5)
					row_for_swap_2 = 3;
				else
					row_for_swap_2 = row_for_swap_1 + 1;				

				swap(field[row_for_swap_1], field[row_for_swap_2]);

			}else if(row == 8) {				

				row_for_swap_1 += 3;

				if (row_for_swap_1 == 8)
					row_for_swap_2 = 6;
				else
					row_for_swap_2 = row_for_swap_1 + 1;			

				swap(field[row_for_swap_1], field[row_for_swap_2]);
			}		
	}
}

// метод обмена двух колонок в пределах одного района
void Sudoku::SwapColumns()
{
	srand(time(NULL));

	// выбор столбцов для обмена
	// выбор столбцов в первом районе
	int col_for_swap_1_1 = rand() % 2;
	int col_for_swap_1_2 = 0;	

	if (col_for_swap_1_1 == 2)
		col_for_swap_1_2 = 0;
	else
		col_for_swap_1_2 = col_for_swap_1_1 + 1;

	// выбор столбцов во втором районе
	int col_for_swap_2_1 = col_for_swap_1_1 + 3; 
	int col_for_swap_2_2 = 0;

	if (col_for_swap_2_1 == 5)
		col_for_swap_2_2 = 3;
	else
		col_for_swap_2_2 = col_for_swap_2_1 + 1;

	// выбор столбцов в третьем районе
	int col_for_swap_3_1 = col_for_swap_2_1 + 3;
	int col_for_swap_3_2 = 0;

	if (col_for_swap_3_1 == 8)
		col_for_swap_3_2 = 6;
	else
		col_for_swap_3_2 = col_for_swap_3_1 + 1;		

	// свап столбцов
	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {			

				swap(field[row][col_for_swap_1_1], field[row][col_for_swap_1_2]);
			
				swap(field[row][col_for_swap_2_1], field[row][col_for_swap_2_2]);

				swap(field[row][col_for_swap_3_1], field[row][col_for_swap_3_2]);	
		}
	}
}

// создание игрового поля и выбор сложности	
void Sudoku::CreateGameFild()
{

	int difficult;
point:
	cout << "Выбор сложности : \n1 - Легко\n2 - Средне\n3 - Трудно \n";
	cin >> difficult;

	int position1, position2, position3, position4;

	switch (difficult) {
	case EASY: // открыто 4 в каждой строке		

		for (int row = 0; row < SIZE; ++row) {

			strcpy_s(game_difficult,"Легко");

			position1 = rand() % 3;
			position2 = position1 + 2;
			position3 = position2 +2;
			position4 = position3 + 2;

			for (int col = 0; col < SIZE; ++col) {

				if (col == position1 || col == position2 || col == position3 || col == position4) {

					gameField[row][col] = field[row][col]; // открываем часть ячеек
					++number_open; // увеличиваем количество открытых ячеек
				}
				else {
					gameField[row][col] = 0; // закрытые ячейки
				}
			}
		}
		break;

	case NORMAL: // открыто 3 в каждой строке	

		strcpy_s(game_difficult, "Средне");

		for (int row = 0; row < SIZE; ++row) {

			position1 = rand() % 3;			
			position2 = position1 + 3;
			position3 = position2 + 3;

			for (int col = 0; col < SIZE; ++col) {

				if (col == position1 || col == position2 || col == position3 ) {

					gameField[row][col] = field[row][col];// открываем часть ячеек
					++number_open; // увеличиваем количество открытых ячеек
				}
				else
					gameField[row][col] = 0; // закрытые ячейки
			}
		}
		break;

	case HARD: // открыто 2 в каждой строке		

		strcpy_s(game_difficult, "Трудно");

		for (int row = 0; row < SIZE; ++row) {

			position1 = rand() % 4;
			position2 = position1 + 4;

			for (int col = 0; col < SIZE; ++col) {

				if (col == position1 || col == position2) {

					gameField[row][col] = field[row][col];// открываем часть ячеек
					++number_open; // увеличиваем количество открытых ячеек
				}
				else
					gameField[row][col] = 0; // закрытые ячейки
			}
		}
		break;

	default:
		cout << "Внимательней !\n";
		goto point;
		break;
	}	

	cout << "\nСоздано игровое поле !\n\n\n";	
}

// проверка числа в поле на выход за лимиты
void Sudoku::Check(int frist_number_in_row)
{
	if (frist_number_in_row > 9)
		this->frist_number_in_row = frist_number_in_row - 9;	
}

// метод вывода базового поля в консоль
void Sudoku::ShowField()
{
	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {
			cout << field[row][col] << ' ';
		}
		cout << endl;
	}
}

// метод вывода игрового поля в консоль
void Sudoku::ShowGameField()
{
	cout << "   0 1 2   3 4 5   6 7 8 \n\n";
	for (int row = 0; row < SIZE; ++row) {
		
		if (row == 3 || row == 6)
			cout << "  ----------------------\n"<< row << "  ";
		else 
			cout << row << "  ";
		for (int col = 0; col < SIZE; ++col) {

			if (col == 3 || col == 6) {
				cout << "| " << gameField[row][col] << ' ';
			}
			else 
				cout << gameField[row][col] << ' ';
		}		
		cout << endl;
	}
}

// игра
void Sudoku::BodyGame()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\tИгра Сюдоку\n\n- Игровое поле представляет собой квадрат размером 9x9 ячеек.\n- Вписывать в них можно только цифры от 1 до 9.\n- Каждый блок 3x3 содержит 9 цифр — от 1 до 9.\n- Каждый вертикальный столбец тоже содержит 9 цифр — и тоже от 1 до 9.\n- Каждая горизонтальная строка тоже содержит 9 цифр от 1 до 9.\n- Каждая цифра может встречаться в квадрате 3x3, в столбце и в строке только один раз.\n- Как только вы заполните верными цифрами все поле — игра окончена.\n\n";

	CreateGameFild(); 
	ShowGameField();

	cout << "\n\nЧто бы поставить число : \n- укажи сначала номер строки (эти номера записаны слева от игрового поля)\n- затем номер колонки (эти номера записаны сверху игрового поля ) \n";
	

	int user_row = 0, user_col = 0; // переменные для координат
	int user_number; // число которое ставит игрок

	int for_hint;

	// Функция clock() возвращает время, пройденное с момента запуска программы, вызвавшей фун­кцию clock()
	clock_t start, stop; // переменные для подсчета времени игры
	start = clock(); // время начала игры

	while (number_open != 81) { // пока не заполним все поле		

	point:

		cout << "\n\nКуда ставим цифру ? : ";
		cin >> user_row >> user_col; // получаем координаты от пользователя
		// проверка правильности ввода
		if (user_row < 0 || user_row > 8 || user_col < 0 || user_col > 8) {
			cout << "Некоректные данные !\n";
			goto point;
		}

		cout << "Цифра : ";
		cin >> user_number; // получаем цифру от пользователя
		// проверка правильности ввода
		if (user_number < 1 || user_number > 9) {
			cout << "Некоректные данные !\n";
			goto point;
		}

		if (field[user_row][user_col] == user_number) { // если цифра верная

			if (IsEmpty(user_row, user_col)) { // проверяем клетку (пустая или нет)
				gameField[user_row][user_col] = user_number; // записываем результат в игровое поле
				++number_open; // увеличиваем количество открытых ячеек

				cout << "\n\n";
				ShowGameField();
			}
			else
				cout << "Клетка " << user_row << " ; " << user_col << " заполнена !";
		}
		else {
			cout << "Не верно !\n";
			++mistake_count; // увеличиваем количество ошибок

			// когда игрок много ошибается , ему предлагается подсказка
			if (mistake_count % 3 == 0) {  

				cout << "\n\nТы много ошибаешься !\n\nТебе доступна подсказка.\nВнимание! Подсказка откроет все ячейки с цифрой указанной игроком.\n\nНужна подсказка ? \n1 - Да\n2 - Нет\n";
				cin >> for_hint;

				switch (for_hint) {
				case 1:
					int hint;
					cout << "\nКакую цифру открыть ? ";			
					cin >> hint;
					cout << "\n\n";

					// проверяем базовое поле и выносим результат на игровое поле
					for (int row = 0; row < SIZE; ++row) {
						for (int col = 0; col < SIZE; ++col) {
							
							if (field[row][col] == hint && gameField[row][col] != hint) {

								gameField[row][col] = hint;
								++number_open; // увеличиваем колличество открытых ячеек
							}
						}						
					}

					ShowGameField();
					++hits_count;
					break;
				case 2:
					cout << "Ок ! Продолжай \n";
					break;
				}
				
			}
		}		
	}

	stop = clock(); // время завершения игры

	game_time = (stop - start)/CLK_TCK;// Для преобразования возвращаемой ве­личины в секунды надо разделить ее на макрос CLK_TCK.

	cout << "\n\n\tВы выиграли!\n\n";

	ShowStatistics(); // сохранение статистики	

	cout << "\n\nСкажи свое имя для истории : ";
	cin >> user_name;

	SafeStatistic(); // сохраняем статистику в файл

	int statictic;
	point2:
	cout << "\n\nВывести всю статистику ?\n1 - Да\n2 - Нет\n";
	cin >> statictic;

	switch (statictic) {
	case 1:
		LoadStatistic();
		cout << "\n\nОбязательно сыграй снова !\n\n";
		break;
	case 2:
		cout << "\n\nОбязательно сыграй снова !\n\n";
		break;
	default:
		cout << "\n\nНеверный ввод!\n";
		goto point2;
		break;
	}
}

// проверка клетки
bool Sudoku::IsEmpty(int user_row, int user_col)
{
	return gameField[user_row][user_col] == 0;
}

// вывод статистики в консоль для текущей игры
void Sudoku::ShowStatistics()
{
	cout << "Сложность игры : " << game_difficult << "\nВремя игры : " << game_time << " секунд\nКоличество неверных ходов : " << mistake_count << "\nИспользовано подсказок : " << hits_count << endl;
}

// сохраняем статистику в файл
void Sudoku::SafeStatistic()
{
	ofstream fout;
	fout.open(path, ios::app);

	if ( !fout.is_open())
		cout << "Ошибка открытия файла\n";
	else {
		fout << "Имя : " << user_name << "\nСложность игры : " << game_difficult << "\nВремя игры : " << game_time << " секунд\nКоличество неверных ходов : " << mistake_count << "\nИспользовано подсказок : " << hits_count << "\n\n";
	}
	fout.close();
}

void Sudoku::LoadStatistic()
{
	cout << "\n\tОбщая статистика\n";

	ifstream fin;
	fin.open(path);

	if ( !fin.is_open())
		cout << "Ошибка открытия файла\n";
	else {

		string str;

		while (!fin.eof()) { // пока файл не закончился

			str = "";			
			getline(fin, str);
			cout << str << endl;
		}
	}

	fin.close();
}


