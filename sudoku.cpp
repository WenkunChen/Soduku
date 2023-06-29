#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include<string.h>

#pragma warning (disable: 4996)
#define BOARD_SIZE 9
using namespace std;


static vector<int> origin_line = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };//�����վֳ�ʼ��

// �������tmp����(row, col)λ���Ƿ�Ϸ�
bool IsLegal(int tmp, vector<vector<int>>& board, int row, int col) {
    // ������Ƿ����ظ�����
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[row][j] == tmp) {
            return false;
        }
    }
    // ������Ƿ����ظ�����
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][col] == tmp) {
            return false;
        }
    }
    // ���3x3�ӿ����Ƿ����ظ�����
    int blockRow = (row / 3) * 3;
    int blockCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[blockRow + i][blockCol + j] == tmp) {
                return false;
            }
        }
    }
    return true;
}

// �ݹ�����һ�������վ�
bool GenerateFinal(vector<vector<int>>& board, int row, int col) {
    //��������
    if (col == BOARD_SIZE) {
        col = 0;
        row++;
        if (row == BOARD_SIZE) {
            return true;  // �����վ��������
        }
    }

    if (board[row][col] != 0) {
        return GenerateFinal(board, row, col + 1);
    }

    random_shuffle(origin_line.begin(), origin_line.end());//�������1~9��˳������

    for (int num : origin_line) {
        if (IsLegal(num, board, row, col)) {
            board[row][col] = num;
            if (GenerateFinal(board, row, col + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

// ��ӡ�����վ�
void PrintBoard(const vector<vector<int>>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0)
                cout << "$" << " "; //�ո���$��ʾ
            else
                cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

//���ݴ���Ĳ���num,����num�������վ�
void GenerateFinals(vector<vector<int>>& board, int num) {
    vector<vector<int>> initial(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    for (int i = 0; i < num; i++) {
        if (GenerateFinal(board, 0, 0)) {
            cout << "[" << i + 1 << "]" << endl;
            PrintBoard(board);
            board = initial;
        }
        else {
            cout << "generate sudoku finals failed!!!" << endl;
        }
    }
}

// ����ڵ�blank_num��������������Ϸ
void DigBlanks(vector<vector<int>>& board, int blank_num) {
    for (int i = 0; i < blank_num; i++) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        while (board[row][col] == 0) {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        }
        board[row][col] = 0;
    }
}

// �ݹ������,�������ж��ٸ���
void CountSolution(vector<vector<int>>& board, int row, int col, int& solution) {
    if (col == BOARD_SIZE) {
        col = 0;
        row++;
        if (row == BOARD_SIZE) {
            solution++; // ��ĸ���
            return;
        }
    }
    if (board[row][col] != 0) {
        CountSolution(board, row, col + 1, solution);
        return;
    }
    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (IsLegal(num, board, row, col)) {
            board[row][col] = num;
            CountSolution(board, row, col + 1, solution);
            board[row][col] = 0;
        }
    }
}

bool SearchUnsolved(vector<vector<int>> board, int& row, int& col) {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    //bool flag = true;//��־λ���жϵ�ǰ���������Ƿ���û���ȥ����
    //for (row = 0; row < BOARD_SIZE && flag ==true; row++) {
    //    for (col = 0; col < BOARD_SIZE && flag == true; col++) {
    //        if (board[row][col] == 0) {
    //            flag = false;
    //        }
    //    }
    //}
    if (!SearchUnsolved(board, row, col)) {
        return true; // �����ѽ��
    }

    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (IsLegal(num, board, row, col)) {
            board[row][col] = num;
          
            if (solveSudoku(board)) {
                return true;
            }
            board[row][col] = 0; // ����
            
        }
    }
    return false; // �޽�
}

//����Ψһ��������Ϸ
void DigBlanksOnly(vector<vector<int>>& board, int blank_num) {
    for (int i = 0; i < blank_num; i++) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        while (board[row][col] == 0) {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        }
        int temp = board[row][col];
        board[row][col] = 0;

        // ���Ψһ��
        int count = 0;
        vector<vector<int>> tempBoard = board;
        GenerateFinal(tempBoard, 0, 0);
        CountSolution(tempBoard, 0, 0, count);
        if (count != 1) {
            board[row][col] = temp;
        }
    }
}

//��ָ���ļ�·���ж�����������⣬��д�ص��洢��������ļ�
void LoadAndSolve(vector<vector<int>>& board,char* input_path, const string& output_path) {
    ifstream in_file(input_path);
    ofstream out_file(output_path);
    if (!in_file) {
        cerr << "Failed to open input file!" << endl;
        return;
    }
    if (!out_file) {
        cerr << "Failed to open output file��" << endl;
        return;
    }
    string str, temp;
    int no = 0;
    while (in_file >> str) {
        str = str.substr(1, str.length() - 2);
        no = stoi(str);
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                in_file >> temp;
                if (temp == "$")board[i][j] = 0;
                else board[i][j] = stoi(temp);
            }
        }
        if (solveSudoku(board)) {
            out_file << "[" << no << "]" << endl;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    out_file << board[i][j] << " ";
                }
                out_file << endl;
            }
        }
        else {
            out_file << "No solution!!!" << endl;
        }
    }
    in_file.close();
    out_file.close();
}

//�жϷ�Χ�Ƿ���[lower��higher]
bool JudgeRange(int lower, int higher,int num) {
    if (num < lower || num > higher || lower > higher) {
        return true;
    }
    return false;
}

// ����������
void ParameterHandler(char* argv[]) {
    const char* finalFile = "./finals.txt";//���վֵ��ļ�
    const char* puzzle_file = "./puzzle.txt";//����Ϸ���ļ�
    const char* answer = "./sudoku.txt";//������ļ�

    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    vector<vector<int>> zero(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    FILE* stream;
    if (argv[1] == NULL) {
        cout << "Please enter parameters......" << endl;
    }
     else if (strcmp(argv[1], "-c") == 0){
        if (argv[2] == NULL) {
            cout << "Please enter the final rounds after parameter <-c> " << endl;
            return;
        }
        int final_round = atoi(argv[2]);
        if (JudgeRange(1,1000000,final_round)) {
            cout << "Parameter <-c> out of boundary!!! Recommended boundary:1~1000000" << endl;
            return;
        }
        freopen_s(&stream, finalFile, "w", stdout);
        GenerateFinals(board, final_round);
        fclose(stdout);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        if (argv[2] == NULL) {
            cout << "Please enter the file path after parameter <-s>" << endl;
            return;
        }
        char* input_path = argv[2];
        LoadAndSolve(board, input_path, answer);
        
    }
    else if (strcmp(argv[1], "-n") == 0) {
        if (argv[2] == NULL) {
            cout << "Please enter the game rounds you want to generate after parameter <-n>" << endl;
            return;
        }
        int game_round = atoi(argv[2]);
        if (JudgeRange(1,10000,game_round)) {
            cout << "Parameter <-n> out of boundary!!! Recommended boundary:1~10000" << endl;
            return;
        }
        if (argv[3] == NULL) {//������ֻ����-n��������û�õ���������
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    int rand_blank = 20 + rand() % 36;
                    DigBlanks(board, rand_blank); //�����ȥ20-55���ո�
                    PrintBoard(board);
                    board = zero;
                }
                else {
                    cout << "Failed to generate" << endl;
                }
            }
            fclose(stdout);
        }
        else if (strcmp(argv[3], "-m") == 0) {
            if (argv[4] == NULL) {
                cout << "Please enter the difficulty level after parameter <-m>" << endl;
                return;
            }
            int level = atoi(argv[4]);
            if (JudgeRange(1,3,level)) {
                cout << "Parameter <-m> out of boundary!!! Recommended boundary:1~3" << endl;
                return;
            }
            //�����Ѷ��������ڿ������Ķ����������֣����Ǽ���Ϊ�ڿ�Խ���ѶȾ�Խ��
            //��������������Ϊ��[10,29]�Ǽ򵥣�[30,49]���еȣ�[50,59]������
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                int rand_num = 0;
                switch (level) {
                case 1:
                    rand_num = 10 + rand() % 20;
                    break;
                case 2:
                    rand_num = 30 + rand() % 20;
                    break;
                case 3:
                    rand_num = 50 + rand() % 10;
                    break;
                }
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    DigBlanks(board, rand_num); //�����ȥseed���ո�
                    PrintBoard(board);
                    board = zero;
                }
                else {
                    cout << "Generate failed!" << endl;
                }
            }
            fclose(stdout);
        }
        else if (strcmp(argv[3], "-r") == 0) {
            if (argv[4] == NULL) {
                cout << "Please enter a boundary after parameter <-r>" << endl;
                return;
            }
            const char* split = "~";
            // ����ַ���
            char* p = strtok(argv[4], split);
            int min_num = 0, max_num = 0;
            sscanf_s(p, "%d", &min_num);
            p = strtok(NULL, split);
            sscanf_s(p, "%d", &max_num);
            if (min_num < 20 || max_num > 55 || max_num < min_num) {
                cout << "Parameter <-r> out of boundary!!! Recommended boundary:20~55" << endl;
                return;
            }
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                int seed = min_num + rand() % (max_num - min_num + 1);
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    DigBlanks(board, seed); 
                    PrintBoard(board);
                    board = zero;
                }
                else {
                    cout << "Generate failed!" << endl;
                }
            }
            fclose(stdout);
        }
        else if (strcmp(argv[3], "-u") == 0) {
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                int random_num = 1 + rand() % 20;
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    DigBlanksOnly(board, random_num); //��������һ��գ��ڵ���Ψһ����ʸߣ������ȥ1~20���ո�, ��û��Ψһ�������
                    PrintBoard(board);
                    board = zero;
                }
                else {
                    cout << "Generate failed!" << endl;
                }
            }
            fclose(stdout);
        }
    }
    else {
        cout << "Invalid command!!! Please follow the guidelines to input!!!" << endl;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    ParameterHandler(argv);
    return 0;
}

