#include <string>
#include <vector>

using namespace std;

/*
    
*/

int solution(vector<vector<string>> board, int h, int w) {
    int answer(0);
    
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, -1, 0 ,1};
    
    // 현재 색깔 저장
    string colorNow = board[h][w];
    
    // 상하좌우 관찰
    for (int k = 0; k < 4; k++) {
        int a_ = h + dy[k];
        int b_ = w + dx[k];
        
        if (a_ >= 0 && a_ < board.size() && b_ >= 0 && b_ < board.size()) {
            
            if (board[a_][b_] == colorNow) 
                answer++;
        }
        
        else continue;
    }
    
    return answer;
}