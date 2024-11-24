#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    보물, 유적이 가득할 것으로 추정되는 문 발견함.
    열쇠에는 홈과 돌기가 있다. 열쇠의 돌기를 자물쇠의 홈에 맞추면 자물쇠가 열림.
    
    자물쇠 영역을 벗어난 열쇠 부분은 상관 없으나, 영억 내에서는 열쇠의 돌기와 자물쇠의 홈이 정확히 일치해야 함.
    
    열쇠의 돌기와 자물쇠의 돌기가 만나서는 안됨.
    
    자물쇠의 구멍을 하나 잡는다. 그리고 열쇠를 4방향으로 돌려가며 각 홈을 맞춰본다.
*/

vector<vector<int>> rotate_clockwise(vector<vector<int>> board) {
    vector<vector<int>> result(board.size(), vector<int>(board.size(), 0));
    // 아래의 순서와 같이 키 뒤집기
    int idx = 0;
    for (int i = board.size() - 1; i >= 0; i--) {
        for (int j = 0; j < board.size(); j++) {
            result[j][i] = board[idx / board.size()][idx % board.size()];
            idx++;
        }
    }
    
    return result;
    
    /*
        1  2  3  4
        5  6  7  8
        9  10 11 12
        13 14 15 16
        
        13 9  5  1
        14 10 6  2
        15 11 7  3
        16 12 8  4
    */
}

void print_board(vector<vector<int>> board) {
    for (auto v_ : board) {
        for (auto v : v_) {
            cout << v << " ";
        }
        cout << endl;
    }
}

inline bool inboard_check(int N, int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < N;
}

// lock과 key, 그리고 그 bias를 보고 가능한지 체크해준다
bool check_lock(int y_bias, int x_bias, const vector<vector<int>> &lock, const vector<vector<int>> &key) {
    int N = lock.size();
    int M = key.size();
    
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            // 지금 보려는 Key의 위치가 key의 범위를 넘어갔다면?
            if (!inboard_check(M, y + y_bias, x + x_bias)) {
                // 자물쇠가 홈이라면 false고, 홈이 아니라면 상관없다
                if (lock[y][x] == 0) return false;
                else continue;
            }
            
            // key가 lock의 범위 내라면, 합이 맞는지 체크한다
            if (lock[y][x] + key[y + y_bias][x + x_bias] != 1) return false;
        }
    }
    
    // 다 문제없이 통과했다면, true를 반환
    return true;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    
    // 자물쇠를 보면서 어떤 홈에다 맞출지 찾는다.
    int lock_idx = 0;
    int lock_std_y = -1;
    int lock_std_x = -1;
    while (lock_std_y == -1 && lock_idx < lock.size() * lock.size()) {
        if (lock[lock_idx / lock.size()][lock_idx % lock.size()] == 0) {
            lock_std_y = lock_idx / lock.size();
            lock_std_x = lock_idx % lock.size();
        }
        lock_idx++;
    }
    
    if (lock_std_y == -1) return true;
    
    // 총 3번 돌리면서 확인할 것
    for (int i = 0; i < 4; i++) {
        // 키를 전부 탐색
        for (int y = 0; y < key.size(); y++) {
            for (int x = 0; x < key.size(); x++) {
                // 만약 이 자리가 홈이라면, 자물쇠의 빈칸에 맞추고 체크한다.
                if (key[y][x] == 1) {
                    int y_bias = y - lock_std_y;
                    int x_bias = x - lock_std_x;
                    
                    // 가능한 상황이었다면, true 반환하고 바로 끝.
                    if (check_lock(y_bias, x_bias, lock, key)) {
                        /// cout << i * 90 << "도 회전한 상황에서 y_bias = " << y_bias << ", x_bias = " << x_bias << "로 발견" << endl;
                        print_board(key);
                        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
                        print_board(lock);
                        return true;
                    }
                        
                }
            }
        }
        
        // 전부 탐색했는데 가능한 것 없었다면, 키 돌리기
        key = rotate_clockwise(key);
    }
    
    return false;
}