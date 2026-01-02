#include <string>
#include <vector>

using namespace std;

/*
    3x3 빈칸에서 빙고놀이.
    9칸이 다 차면 무승부
    
    혼자 선후공 다 하기.
    
    혼자 막 놀았다. 그런데 규칙을 어겼다
    1. 순서를 헷갈려서 같은걸 두 번 했다.
    2. 게임이 종료됐음에도 게임을 진행했다.
    
    게임판만 보고 문제 없는 상황인지 판단해보자.
    
    1번 실수. 같은 걸 두 번 체크했을 경우
    1-1. O가 X보다 두 개 많은가?
    1-2. X가 O보다 하나라도 많은가?
    
    2번 실수. 게임이 종료됐음에도 진행하는 경우
    2-1. 3개가 이어진 것이 2개 이상인지 체크한다.
    2-2. 가능한 경우의 수를 모두 확인
*/

int solution(vector<string> board) {
    // 일단 O, X의 수를 센다.
    int oCount(0);
    int xCount(0);
    
    for (auto row : board) {
        for (auto val : row) {
            if (val == 'O') oCount++;
            else if (val == 'X') xCount++;
        }
    }
    
    // 1번 종료 조건
    if (oCount > xCount + 1) return 0;
    else if (xCount > oCount) return 0;
    
    /// 2번 종료 조건
    int oWinCount(0), xWinCount(0);
    
    for (int i = 0; i < 3; i++) {
        // 가로줄 체크
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == 'O') oWinCount++;
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == 'X') xWinCount++;
        
        // 세로줄 체크
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == 'O') oWinCount++;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == 'X') xWinCount++;
    }
    
    // 대각선 체크
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'O') oWinCount++;
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'X') xWinCount++;
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] == 'O') oWinCount++;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] == 'X') xWinCount++;
    
    // 둘 다 이겼을수는 없음
    if (oWinCount > 0 && xWinCount > 0) return 0;
    
    // O가 이겼다면, O가 하나 많아야 함
    if (oWinCount > 0 && oCount != xCount + 1) return 0;
    
    // X가 이겼다면, 갯수가 동일해야 함
    if (xWinCount > 0 && xCount != oCount) return 0;
    return 1;
}