#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
*/

int dy[3] = {1, 0, 1};
int dx[3] = {0, 1, 1};

inline bool inboard_check(int m, int n, int y, int x) {
    return y >= 0 && y < m && x >= 0 && x < n;
}
             
int solution(int m, int n, vector<string> board) {
    int answer = 0;
    
    vector<vector<bool>> board_bool;
    
    // 더 이상 사라지는 값이 없을때까지 while문 반복
    bool endFlag = false;
    while (!endFlag) {
        
        /*
        // 확인용 출력
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        */
        
        board_bool = vector<vector<bool>>(m, vector<bool>(n, false));
        endFlag = true;
        
        // 모든 칸에 대해 사라짐 체크
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == ' ') continue;
                
                char shape = board[i][j];
                bool pop = true;
                for (int k = 0; k < 3; k++) {
                    int y = i + dy[k];
                    int x = j + dx[k];
                    
                    // 4개가 모두 보드 안에 존재하고, shape가 같아야만 한다.
                    if (inboard_check(m, n, y, x) && shape == board[y][x]) {
                        continue;
                    }
                    
                    // 하나라도 조건이 다르다면 break
                    pop = false;
                    break;
                }
                
                // 터지는 칸이면, bool 배열을 수정한다.
                // 그리고 종료도 하지 않는다
                if (pop) {
                    board_bool[i][j] = true;
                    for (int k = 0; k < 3; k++) {
                        board_bool[i + dy[k]][j + dx[k]] = true;
                    }
                    endFlag = false;
                }
            }
        }
        
        // 한 바퀴 모두 체크했다면, 사라지는 값을 먼저 없앤다.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 값이 사라지는지 체크
                if (board_bool[i][j]) {
                    board[i][j] = ' ';
                    answer++;
                }
            }
        }
        
        // 그리고 값을 다시 채운다
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == ' ') {
                    int new_i = i;
                    // 위의 값을 하나씩 보면서 0이 아닌 값이 있는지 찾는다
                    while (--new_i >= 0 && board[new_i][j] == ' ') {};

                    // 만약 new_i 가 -1까지 갔다면, 바꿀 값을 찾지 못한 것이다.
                    // 위에서 떨어질 값이 있었다면, 그 값을 사용한다.
                    if (new_i != -1) {
                        board[i][j] = board[new_i][j];
                        board[new_i][j] = ' ';
                    }
                }
            }
        }
    }
    
    return answer;
}