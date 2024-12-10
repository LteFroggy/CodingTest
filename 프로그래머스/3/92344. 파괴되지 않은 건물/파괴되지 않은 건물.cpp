#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    내구도를 가진 건물 존재, 공격을 받으면 내구도 감소하고 회복도 가능하다.
    
    공격과 회복은 항상 직사각형 모양!
    가로세로 누적합 사용하자.
    
    5 5 5
    5 5 5
    5 5 5
    누적합 표현시,
    
    5 5 5 의 누적합 표현시
    5 0 0 이다.
    그럼 세줄이면??
    5 5 0
    5 5 0
    0 0 0
    
    5 0 -5
    5 0 -5
    0 0  0
    
    5   0 -5
    0   0  0
    -5  0  5
    세로줄부터 풀면 됨
    
    그러니, a,b ~ c,d까지 공격을 했다면
    a,b에는 +1
    a, d+1에는 -1
    c+1, b에도 -1
    c+1, d+1에는 +1을 주면 됨!
*/

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    
    int N = board.size();
    int M = board[0].size();
    
    // board에 누적합을 적용시켜야 한다.
    // 가로 먼저 적용하고, 그 다음에 세로 적용
    for (int i = 0; i < N; i++) {
        int val = 0;
        int old_val = 0;
        for (int j = 0; j < M; j++) {
            // 현재 값과의 차이에 따라 값을 등록한다
            old_val = board[i][j];
            board[i][j] = board[i][j] - val;
            val = old_val;
        }
    }
    
    // 세로에 대해 누적합 적용
    for (int i = 0; i < M; i++) {
        int val = 0;
        int old_val = 0;
        for (int j = 0; j < N; j++) {
            // 현재 값과의 차이에 따라 값을 등록한다
            old_val = board[j][i];
            board[j][i] = board[j][i] - val;
            val = old_val;
        }
    }
    
    
    // 누적합이 적용된 보드 확인
    /*
    for (auto v_ : board) {
        for (auto v : v_) cout << v << " "; cout << endl;
    }
    */
    
    // 이제 들어오는 값에 대해 누적합 사용
    
    for (auto tmp : skill) {
        int y1 = tmp[1];
        int x1 = tmp[2];
        int y2 = tmp[3];
        int x2 = tmp[4];
        // 공격이면 내구도 내리고, 회복이면 올린다.
        int degree = tmp[0] == 2 ? tmp[5] : -tmp[5];
        
        // 누적합 적용
        board[y1][x1] += degree;
        if (x2 + 1 < M) board[y1][x2 + 1] -= degree;
        if (y2 + 1 < N) board[y2 + 1][x1] -= degree;
        if (y2 + 1 < N && x2 + 1 < M) board[y2 + 1][x2 + 1] += degree;
    }
    
    // 마지막으로 누적합을 푼다
    // 세로부터 풀어줘야 함
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // 세로를 풀 때 첫 행은 신경쓰지 않아도 된다.
            if (j == 0) continue;
            board[j][i] += board[j-1][i];
        }
    }
    
    
    // 가로 풀기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 가로를 풀 때 첫 열은 신경쓰지 않는다
            if (j == 0) continue;
            board[i][j] += board[i][j-1];
        }
    }
    
    // 풀린 결과 확인 
    /*
    cout << endl << endl;
    for (auto v_ : board) {
        for (auto v : v_) cout << v << " "; cout << endl;
    }
    */
    
    
    // 다 풀었으면, 이제 값이 음수인지 체크한다
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] > 0) answer++;
        }
    }
    
    return answer;
}