#include <gtest/gtest.h>
#include "sudoku.h"
#include <fstream>
#include <string>

bool isValidFinal(vector<vector<int>>& board) {
    int checkbox[9] = {0};
    // 按行检查
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int num = board[row][col];
            // 出现空位
            if(num == 0) {
                return false;
            }
            // 同一行内出现重复数字
            if(checkbox[num - 1] == 1) {
                return false;
            }
            checkbox[num - 1] = 1;
        }
        memset(&checkbox, 0, sizeof(checkbox));
    }
    // 按列检查
    for (int col = 0; col < BOARD_SIZE; col++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            int num = board[row][col];
            // 出现空位
            if(num == 0) {
                return false;
            }
            // 同一列内出现重复数字
            if(checkbox[num - 1] == 1) {
                return false;
            }
            checkbox[num - 1] = 1;
        }
        memset(&checkbox, 0, sizeof(checkbox));
    }
    // 按宫格检查
    for (int blockRow = 0; blockRow < 3; blockRow++) {
        for (int blockCol = 0; blockCol < 3; blockCol++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    int num = board[blockRow * 3 + row][blockCol * 3 + col];
                    // 出现空位
                    if(num == 0) {
                        return false;
                    }
                    // 同一宫内出现重复数字
                    if(checkbox[num - 1] == 1) {
                        return false;
                    }
                    checkbox[num - 1] = 1;
                }
            }
            memset(&checkbox, 0, sizeof(checkbox));
        }
    }
    return true;
}

TEST(TestCase, testIsLegal) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board = {{0,2,0,8,0,1,7,9,0},
             {0,0,0,0,0,0,0,0,0},
             {7,0,5,0,0,0,4,0,0},
             {0,3,0,0,0,0,0,0,0},
             {0,0,0,0,0,5,0,6,0},
             {8,0,7,0,0,9,0,0,2},
             {0,0,0,0,2,0,0,5,0},
             {0,0,0,0,0,3,0,8,0},
             {3,0,2,0,0,0,0,0,9}
             };
    ASSERT_EQ(IsLegal(4, board, 0, 0), true);
    ASSERT_EQ(IsLegal(8, board, 0, 0), false);
    ASSERT_EQ(IsLegal(3, board, 0, 0), false);
    ASSERT_EQ(IsLegal(5, board, 0, 0), false);
}

TEST(TestCase, testGenerateFinal) {
    vector<vector<int>> board1(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    GenerateFinal(board1, 0, 0);
    ASSERT_EQ(isValidFinal(board1), true);

    vector<vector<int>> board2(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board2 = {{0,2,3,8,5,1,7,9,6},
              {1,0,8,4,9,7,3,2,5},
              {7,9,0,2,3,6,4,1,8},
              {5,3,6,0,8,2,9,4,7},
              {2,4,9,3,0,5,8,6,1},
              {8,1,7,6,4,0,5,3,2},
              {6,7,4,9,2,8,0,5,3},
              {9,5,1,7,6,3,2,0,4},
              {3,8,2,5,1,4,6,7,0}
    };
    GenerateFinal(board2, 0, 0);
    ASSERT_EQ(isValidFinal(board2), true);


    vector<vector<int>> board3(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board3 = {{0,2,3,9,5,6,7,8,9},
              {1,6,8,4,9,7,3,2,5},
              {7,9,5,2,3,6,4,1,8},
              {5,3,6,1,8,2,9,4,7},
              {2,4,9,3,7,5,8,6,1},
              {8,1,7,6,4,9,5,3,2},
              {6,7,4,9,2,8,1,5,3},
              {9,5,1,7,6,3,2,8,4},
              {3,8,2,5,1,4,6,7,9}
    };
    GenerateFinal(board3, 0, 0);
    ASSERT_EQ(isValidFinal(board3), false);
}

TEST(TestCase, testDigBlanks) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board = {{4,2,3,8,5,1,7,9,6},
             {1,6,8,4,9,7,3,2,5},
             {7,9,5,2,3,6,4,1,8},
             {5,3,6,1,8,2,9,4,7},
             {2,4,9,3,7,5,8,6,1},
             {8,1,7,6,4,9,5,3,2},
             {6,7,4,9,2,8,1,5,3},
             {9,5,1,7,6,3,2,8,4},
             {3,8,2,5,1,4,6,7,9}
    };
    int blank_num = 0;
    DigBlanks(board, 30);
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            if(board[row][col] == 0){
                blank_num++;
            }
        }
    }
    ASSERT_EQ(blank_num, 30);

    blank_num = 0;
    DigBlanks(board, 30);
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            if(board[row][col] == 0){
                blank_num++;
            }
        }
    }
    ASSERT_EQ(blank_num, 60);
}

TEST(TestCase, testCountSolution) {
    vector<vector<int>> board1(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board1 = {{5,1,0,2,0,0,3,0,9},
              {4,2,7,0,9,3,8,0,1},
              {9,3,6,7,0,8,0,4,2},
              {0,4,2,3,5,1,9,8,0},
              {6,9,0,8,7,2,4,5,3},
              {3,8,5,6,4,9,1,2,7},
              {1,6,4,9,8,7,2,3,0},
              {8,7,3,1,2,5,6,9,4},
              {2,5,9,4,3,0,7,1,0}
    };
    int count = 0;
    CountSolution(board1, 0, 0, count);
    ASSERT_EQ(count, 1);

    vector<vector<int>> board2(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board2 = {{7,8,9,1,2,3,4,6,5},
              {6,1,2,4,0,0,3,7,8},
              {3,4,5,8,7,6,1,9,2},
              {8,5,6,9,4,2,7,1,3},
              {2,3,1,5,6,7,8,4,9},
              {9,7,4,3,8,1,5,2,6},
              {1,6,3,7,0,0,2,8,4},
              {5,2,8,6,1,4,9,3,7},
              {4,9,7,2,3,8,6,5,1}
    };
    count = 0;
    CountSolution(board2, 0, 0, count);
    ASSERT_EQ(count, 2);
}

TEST(TestCase, testSearchUnsolved) {
    vector<vector<int>> board1(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board1 = {{4,2,3,8,5,1,7,9,6},
              {1,6,8,4,9,7,3,2,5},
              {7,9,5,2,3,6,4,1,8},
              {5,3,6,1,8,2,9,4,7},
              {2,4,9,3,7,5,8,6,1},
              {8,1,7,6,4,9,5,3,2},
              {6,7,4,9,2,8,1,5,3},
              {9,5,1,7,6,3,2,8,4},
              {3,8,2,5,1,4,6,7,9}
    };
    int row, col;
    ASSERT_EQ(SearchUnsolved(board1, row, col), false);
    ASSERT_EQ(row, 9);
    ASSERT_EQ(col, 9);

    vector<vector<int>> board2(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board2 = {{4,2,3,8,5,1,7,9,6},
              {1,6,8,4,9,7,3,2,5},
              {7,9,5,2,3,6,4,1,8},
              {5,3,6,1,8,2,9,4,7},
              {2,4,9,3,0,5,8,6,1},
              {8,1,7,6,4,9,5,3,2},
              {6,7,4,9,2,8,1,5,3},
              {9,5,1,7,6,3,2,8,4},
              {3,8,2,5,1,4,6,7,9}
    };
    row = col = 0;
    ASSERT_EQ(SearchUnsolved(board2, row, col), true);
    ASSERT_EQ(row, 4);
    ASSERT_EQ(col, 4);
}

TEST(TestCase, testSolveSoduku) {
    vector<vector<int>> board1(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board1 = {{5,1,0,2,0,0,3,0,9},
              {4,2,7,0,9,3,8,0,1},
              {9,3,6,7,0,8,0,4,2},
              {0,4,2,3,5,1,9,8,0},
              {6,9,0,8,7,2,4,5,3},
              {3,8,5,6,4,9,1,2,7},
              {1,6,4,9,8,7,2,3,0},
              {8,7,3,1,2,5,6,9,4},
              {2,5,9,4,3,0,7,1,0}
    };
    ASSERT_EQ(SolveSudoku(board1), true);

    vector<vector<int>> board2(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board2 = {{0,2,0,8,0,1,7,9,0},
              {0,0,0,0,0,0,0,0,0},
              {7,0,5,0,0,0,4,0,0},
              {0,3,0,0,0,0,0,0,0},
              {0,0,0,0,0,5,0,6,0},
              {8,0,7,0,0,9,0,0,2},
              {0,0,0,0,2,0,0,5,0},
              {0,0,0,0,0,3,0,8,0},
              {3,0,2,0,0,0,0,0,9}
    };
    ASSERT_EQ(SolveSudoku(board2), true);
}

TEST(TestCase, testDigBlanksOnly) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    board = {{4,2,3,8,5,1,7,9,6},
             {1,6,8,4,9,7,3,2,5},
             {7,9,5,2,3,6,4,1,8},
             {5,3,6,1,8,2,9,4,7},
             {2,4,9,3,7,5,8,6,1},
             {8,1,7,6,4,9,5,3,2},
             {6,7,4,9,2,8,1,5,3},
             {9,5,1,7,6,3,2,8,4},
             {3,8,2,5,1,4,6,7,9}
    };
    DigBlanksOnly(board, 20);
    int solution_count = 0;
    CountSolution(board, 0, 0, solution_count);
    ASSERT_EQ(solution_count, 1);

    DigBlanksOnly(board, 5);
    solution_count = 0;
    CountSolution(board, 0, 0, solution_count);
    ASSERT_EQ(solution_count, 1);
}

TEST(TestCase, testJudgeRange) {
    ASSERT_EQ(JudgeRange(3, 7, 5), false);
    ASSERT_EQ(JudgeRange(3, 7, 1), true);
    ASSERT_EQ(JudgeRange(3, 7, 9), true);
    ASSERT_EQ(JudgeRange(7, 3, 5), true);
}

TEST(TestCase, testParameterHandler) {
    bool result;

    char* argv_null[] = {nullptr, nullptr};
    result = ParameterHandler(argv_null);
    ASSERT_EQ(result, false);

    char* argv_c_1[] = {nullptr, "-c"};
    result = ParameterHandler(argv_c_1);
    ASSERT_EQ(result, false);
    char* argv_c_2[] = {nullptr, "-c", "1000001"};
    result = ParameterHandler(argv_c_2);
    ASSERT_EQ(result, false);
    char* argv_c_3[] = {nullptr, "-c", "10"};
    result = ParameterHandler(argv_c_3);
    ASSERT_EQ(result, true);

    char* argv_s_1[] = {nullptr, "-s"};
    ASSERT_EQ(ParameterHandler(argv_s_1), false);
    char* argv_s_2[] = {nullptr, "-s", "wrong.path"};
    ASSERT_EQ(ParameterHandler(argv_s_2), true);
    char* argv_s_3[] = {nullptr, "-s", "./puzzle.txt"};
    ASSERT_EQ(ParameterHandler(argv_s_3), true);

    char* argv_n_1[] = {nullptr, "-n"};
    result = ParameterHandler(argv_n_1);
    ASSERT_EQ(result, false);
    char* argv_n_2[] = {nullptr, "-n", "10001"};
    result = ParameterHandler(argv_n_2);
    ASSERT_EQ(result, false);
//    char* argv_n_3[] = {nullptr, "-n", "10", nullptr};
//    result = ParameterHandler(argv_n_3);
//    ASSERT_EQ(result, true);
    char* argv_n_4[] = {nullptr, "-n", "10001", "wrong parameter"};
    result = ParameterHandler(argv_n_4);
    ASSERT_EQ(result, false);

    char* argv_n_m_1[] = {nullptr, "-n", "10", "-m"};
    result = ParameterHandler(argv_n_m_1);
    ASSERT_EQ(result, false);
    char* argv_n_m_2[] = {nullptr, "-n", "10", "-m", "4"};
    result = ParameterHandler(argv_n_m_2);
    ASSERT_EQ(result, false);
    char* argv_n_m_3[] = {nullptr, "-n", "10", "-m", "2"};
    result = ParameterHandler(argv_n_m_3);
    ASSERT_EQ(result, true);

    char* argv_n_r_1[] = {nullptr, "-n", "10", "-r"};
    result = ParameterHandler(argv_n_r_1);
    ASSERT_EQ(result, false);
    char* argv_n_r_2[] = {nullptr, "-n", "10", "-r", "15~35"};
    result = ParameterHandler(argv_n_r_2);
    ASSERT_EQ(result, false);
    char* argv_n_r_3[] = {nullptr, "-n", "10", "-r", "25~65"};
    result = ParameterHandler(argv_n_r_3);
    ASSERT_EQ(result, false);
    char* argv_n_r_4[] = {nullptr, "-n", "10", "-r", "25~35"};
    result = ParameterHandler(argv_n_r_4);
    ASSERT_EQ(result, true);

    char* argv_random[] = {nullptr, "Hello World!"};
    result = ParameterHandler(argv_random);
    ASSERT_EQ(result, false);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}