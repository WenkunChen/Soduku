#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>

#pragma warning (disable: 4996)
#define BOARD_SIZE 9
using namespace std;


static vector<int> origin_line = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };//生成终局初始行
random_device rd;
default_random_engine e(rd());

// 检查数字tmp放在(row, col)位置是否合法
bool IsLegal(int tmp, vector<vector<int>>& board, int row, int col) {
    // 检查行是否有重复数字
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[row][j] == tmp) {
            return false;
        }
    }
    // 检查列是否有重复数字
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][col] == tmp) {
            return false;
        }
    }
    // 检查3x3子块内是否有重复数字
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

// 递归生成一轮数独终局
bool GenerateFinal(vector<vector<int>>& board, int row, int col) {
    //按行生成
    if (col == BOARD_SIZE) {
        col = 0;
        row++;
        if (row == BOARD_SIZE) {
            return true;  // 数独终局生成完成
        }
    }

    if (board[row][col] != 0) {
        return GenerateFinal(board, row, col + 1);
    }

    shuffle(origin_line.begin(), origin_line.end(), std::mt19937(std::random_device()()));//随机打乱1~9的顺序排列

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

// 打印数独终局
void PrintBoard(const vector<vector<int>>& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0)
                cout << "$" << " "; //空格用$表示
            else
                cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

//根据传入的参数num,生成num轮数独终局
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

// 随机挖掉blank_num个空生成数独游戏
void DigBlanks(vector<vector<int>>& board, int blank_num) {
    for (int i = 0; i < blank_num; i++) {
        int row = (int)e() % BOARD_SIZE;
        int col = (int)e() % BOARD_SIZE;
        while (board[row][col] == 0) {
            row = (int)e() % BOARD_SIZE;
            col = (int)e() % BOARD_SIZE;
        }
        board[row][col] = 0;
    }
}

// 递归解数独,计算它有多少个解
void CountSolution(vector<vector<int>>& board, int row, int col, int& solution) {
    if (col == BOARD_SIZE) {
        col = 0;
        row++;
        if (row == BOARD_SIZE) {
            solution++; // 解的个数
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
    //bool flag = true;//标志位，判断当前数独盘面是否还有没填进去的数
    //for (row = 0; row < BOARD_SIZE && flag ==true; row++) {
    //    for (col = 0; col < BOARD_SIZE && flag == true; col++) {
    //        if (board[row][col] == 0) {
    //            flag = false;
    //        }
    //    }
    //}
    if (!SearchUnsolved(board, row, col)) {
        return true; // 数独已解决
    }

    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (IsLegal(num, board, row, col)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }
            board[row][col] = 0; // 回溯

        }
    }
    return false; // 无解
}

//生成唯一解数独游戏
void DigBlanksOnly(vector<vector<int>>& board, int blank_num) {
    for (int i = 0; i < blank_num; i++) {
        int row = (int)e() % BOARD_SIZE;
        int col = (int)e() % BOARD_SIZE;
        while (board[row][col] == 0) {
            row = (int)e() % BOARD_SIZE;
            col = (int)e() % BOARD_SIZE;
        }
        int temp = board[row][col];
        board[row][col] = 0;

        // 检查唯一解
        int count = 0;
        vector<vector<int>> tempBoard = board;
        GenerateFinal(tempBoard, 0, 0);
        CountSolution(tempBoard, 0, 0, count);
        if (count != 1) {
            board[row][col] = temp;
        }
    }
}

//从指定文件路径中读入数独，求解，再写回到存储求解结果的文件
void LoadAndSolve(vector<vector<int>>& board,char* input_path, const string& output_path) {
    ifstream in_file(input_path);
    ofstream out_file(output_path);
    if (!in_file) {
        cerr << "Failed to open input file!" << endl;
        return;
    }
    if (!out_file) {
        cerr << "Failed to open output file！" << endl;
        return;
    }
    string str, temp;
    int no;
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

//判断范围是否在[lower，higher]
bool JudgeRange(int lower, int higher,int num) {
    if (num < lower || num > higher || lower > higher) {
        return true;
    }
    return false;
}

// 检查输入参数
void ParameterHandler(char* argv[]) {
    const char* finalFile = "./finals.txt";//存终局的文件
    const char* puzzle_file = "./puzzle.txt";//存游戏的文件
    const char* answer = "./sudoku.txt";//存解答的文件

    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    vector<vector<int>> zero(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    FILE* stream;
    if (argv[1] == nullptr) {
        cout << "Please enter parameters......" << endl;
    }
    else if (strcmp(argv[1], "-c") == 0){
        if (argv[2] == nullptr) {
            cout << "Please enter the final rounds after parameter <-c> " << endl;
            return;
        }
        int final_round = strtol(argv[2], nullptr, 10);
        if (JudgeRange(1,1000000,final_round)) {
            cout << "Parameter <-c> out of boundary!!! Recommended boundary:1~1000000" << endl;
            return;
        }
        freopen_s(&stream, finalFile, "w", stdout);
        GenerateFinals(board, final_round);
        fclose(stdout);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        if (argv[2] == nullptr) {
            cout << "Please enter the file path after parameter <-s>" << endl;
            return;
        }
        char* input_path = argv[2];
        LoadAndSolve(board, input_path, answer);

    }
    else if (strcmp(argv[1], "-n") == 0) {
        if (argv[2] == nullptr) {
            cout << "Please enter the game rounds you want to generate after parameter <-n>" << endl;
            return;
        }
        int game_round = strtol(argv[2], nullptr, 10);
        if (JudgeRange(1,10000,game_round)) {
            cout << "Parameter <-n> out of boundary!!! Recommended boundary:1~10000" << endl;
            return;
        }
        if (argv[3] == nullptr) {//命令中只包含-n和轮数，没用到其他参数
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    int rand_blank = 20 + (int)e() % 36;
                    DigBlanks(board, rand_blank); //随机挖去20-55个空格
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
            if (argv[4] == nullptr) {
                cout << "Please enter the difficulty level after parameter <-m>" << endl;
                return;
            }
            int level = strtol(argv[4], nullptr, 10);
            if (JudgeRange(1,3,level)) {
                cout << "Parameter <-m> out of boundary!!! Recommended boundary:1~3" << endl;
                return;
            }
            //数独难度这里用挖空数量的多少来简单区分，我们简单认为挖空越多难度就越高
            //比如这里我们认为挖[10,29]是简单，[30,49]是中等，[50,59]是困难
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                int rand_num = 0;
                switch (level) {
                    case 1:
                        rand_num = 10 + (int)e() % 20;
                        break;
                    case 2:
                        rand_num = 30 + (int)e() % 20;
                        break;
                    case 3:
                        rand_num = 50 + (int)e() % 10;
                        break;
                    default:;
                }
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    DigBlanks(board, rand_num); //随机挖去seed个空格
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
            if (argv[4] == nullptr) {
                cout << "Please enter a boundary after parameter <-r>" << endl;
                return;
            }
            const char* split = "~";
            // 拆分字符串
            char* p = strtok(argv[4], split);
            int min_num = 0, max_num = 0;
            sscanf_s(p, "%d", &min_num);
            p = strtok(nullptr, split);
            sscanf_s(p, "%d", &max_num);
            if (min_num < 20 || max_num > 55 || max_num < min_num) {
                cout << "Parameter <-r> out of boundary!!! Recommended boundary:20~55" << endl;
                return;
            }
            freopen_s(&stream, puzzle_file, "w", stdout);
            for (int i = 0; i < game_round; i++) {
                int seed = min_num + (int)e() % (max_num - min_num + 1);
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
                int random_num = 1 + (int)e() % 20;
                if (GenerateFinal(board, 0, 0)) {
                    cout << "[" << i + 1 << "]" << endl;
                    DigBlanksOnly(board, random_num); //这里少挖一点空，挖的少唯一解概率高，随机挖去1~20个空格, 若没有唯一解则回填
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

int main([[maybe_unused]] int argc, char* argv[]) {
    ParameterHandler(argv);
    return 0;
}
