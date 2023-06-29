//
// Created by 陈文坤 on 2023/6/29.
//

#ifndef MYPROJECT_SUDOKU_H
#define MYPROJECT_SUDOKU_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

#pragma warning (disable: 4996)
#define BOARD_SIZE 9

bool IsLegal(int tmp, vector<vector<int>>& board, int row, int col);

bool GenerateFinal(vector<vector<int>>& board, int row, int col);

void PrintBoard(const vector<vector<int>>& board, const string& output_path);

void GenerateFinals(vector<vector<int>>& board, int num, const string& output_path);

void DigBlanks(vector<vector<int>>& board, int blank_num);

void CountSolution(vector<vector<int>>& board, int row, int col, int& solution);

bool SearchUnsolved(vector<vector<int>> board, int& row, int& col);

bool SolveSudoku(vector<vector<int>>& board);

void DigBlanksOnly(vector<vector<int>>& board, int blank_num);

void LoadAndSolve(vector<vector<int>>& board,char* input_path, const string& output_path);

bool JudgeRange(int lower, int higher,int num);

bool ParameterHandler(char* argv[]);

#endif //MYPROJECT_SUDOKU_H
