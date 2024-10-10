#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    직사각형 모양의 범위를 선택하고, 테두리의 숫자를 한 칸씩 시계방향으로 회전한다
    
    1 2 3       4 1 2
    4 5 6   ->  7 5 3
    7 8 9       8 9 6
    
    회전에 의해 위치가 바뀐 숫자들 중, 가장 작은 숫자들을 순서대로 배열에 담아 return하자.
    회전시키려면, 나보다 시계방향으로 한 칸 앞에 있는 숫자를 집어오면 된다.
    한 칸 앞에 있는 숫자를 집어오는 방법은?? 일단 나는 회전 대상의 첫 열 혹은 마지막 열이거나, 첫 행 혹은 마지막 행이어야 한다.
    내가 첫 열의 마지막 행이나 첫 행도 아니라면
*/

int rotate_board(vector<vector<int>> &board, int row_start, int row_end, int column_start, int column_end) {
    int N = board.size();
    int M = board[0].size();
    int min_val = 1e9;
    
    vector<vector<int>> new_board(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 내가 내 아래 값을 가져와야 하는 경우
            if (i < row_end && i >= row_start && j == column_start) {
                new_board[i][j] = board[i + 1][j];
                min_val = min(min_val, new_board[i][j]);
            }
            // 내가 왼쪽 값을 가져와야 하는 경우
            else if (i == row_start && j > column_start && j <= column_end) {
                new_board[i][j] = board[i][j-1];
                min_val = min(min_val, new_board[i][j]);
            }
            
            // 내가 오른쪽 값을 가져와야 하는 경우
            else if (i == row_end && j < column_end && j >= column_start) {
                new_board[i][j] = board[i][j+1];
                min_val = min(min_val, new_board[i][j]);
            }
            
            // 내가 위쪽 값을 가져와야 하는 경우
            else if (j == column_end && i > row_start && i <= row_end) {
                new_board[i][j] = board[i-1][j];
                min_val = min(min_val, new_board[i][j]);
            }
                
            // 포함 안되면, 그냥 자기 값 쓰기
            else {
                new_board[i][j] = board[i][j];
            }
        }
    }
    
    board = new_board;
    
    return min_val;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    
    vector<vector<int>> board(rows, vector<int>(columns));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = i * columns + j + 1;
        }
    }
    
    for (auto v : queries) {
        answer.push_back(rotate_board(board, v[0] - 1, v[2] - 1, v[1] - 1, v[3] - 1));
    }
    
    return answer;
}