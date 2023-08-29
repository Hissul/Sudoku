#pragma once

using namespace std;

class Sudoku
{
	enum{EASY = 1 , NORMAL = 2 , HARD = 3 ,SIZE = 9};
	string path = "SudokuStatistic.txt";

	int field[SIZE][SIZE]; // ������� ����
	int frist_number_in_row; // ������ ����� � ������
	int gameField[SIZE][SIZE]; // ������� ����

	char user_name[15];
	char game_difficult[8];
	int mistake_count; // ����������� ������
	int game_time; // ����� � ����
	int hits_count; // ���������� �������������� ���������

	int number_open; // ����������� �������� �����

public:
	Sudoku(); // �����������

	void CreateFild(); // ����� �������� ����
	void RotateField(); // ����� ��� �������� ����
	void SwapRows(); // ����� ������ ���� ����� � �������� ������ ������
	void SwapColumns(); // ����� ������ ���� ������� � �������� ������ ������


	void CreateGameFild(); // �������� �������� ���� � ����� ���������	

	void Check(int frist_number_in_row); // �������� ����� � ���� �� ����� �� ������

	void ShowField(); // ����� ������ �������� ���� � �������
	void ShowGameField(); // ����� ������ �������� ���� � �������

	void BodyGame(); // ����
	bool IsEmpty(int user_row ,int user_col); // �������� ������

	void ShowStatistics(); // ����� ���������� � ������� ��� ������� ����

	void SafeStatistic(); // ��������� ���������� � ����
	void LoadStatistic(); // ������ ���������� �� �����

};