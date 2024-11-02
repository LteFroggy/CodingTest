#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

/*
    죠르디가 면접 보러 왔다.
    코로나 바이러스 감염 예방을 위해 거리를 둬서 대기해야 하는데, 앉는 규칙이 있다.
    
    1. 대기실은 5개, 대기실은 5x5크기
    응시자들끼리는 맨해튼거리가 2이하가 되면 안된다, 단 자리 사이가 막혀있으면 상관없음
    
    각 자리에서 DFS로 2번까지 탐색하고, 새로운 값을 찾으면 X가 된다.
*/

class block {
    public:
    int y;
    int x;
    int start_y;
    int start_x;
    int move_left;
    
    block(int a, int b, int c, int d, int e) : y(a), x(b), start_y(c), start_x(d), move_left(e) {};
};

inline bool inboard_check(int y, int x) {
    return y >= 0 && y < 5 && x >= 0 && x < 5;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer(5, 1);
    
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, -1, 0, 1};
    
    vector<vector<int>> dist;
    stack<block> stk;
    
    // 각 회의실별로 같은 행동을 반복한다.
    for (int i = 0; i < 5; i++) {
        /*
        for (auto v : places[i]) {
            for (auto v_ : v) cout << v_ << " ";
            cout << endl;
        }
        */
        
        // 0, 0부터 쭉 훑으며 진행한다
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                // 사람을 찾으면, 여기서부터 탐색을 진행하도록 집어넣는다.
                if (places[i][y][x] == 'P') {
                    stk.push(block(y, x, y, x, 2));
                }
            }
        }
        
        // 모두 훑었다면, 탐색을 시작한다.
        while(!stk.empty()) {
            block now = stk.top();
            stk.pop();
            
            
            // 현재 내가 더 이동이 불가능한 상태라면, 아래의 일체는 진행하지 않는다
            if (now.move_left == 0) continue;
            
            // 상하좌우를 보면서 탐색을 진행한다. X로는 가지 않음
            for (int k = 0; k < 4; k++) {
                int y_ = now.y + dy[k];
                int x_ = now.x + dx[k];
                
                // 보드 밖으로 나가면 보지 않는다.
                if (!inboard_check(y_, x_)) continue;
                // 벽은 가보지 않는다.
                if (places[i][y_][x_] == 'X') continue;
                // 내가 시작한 위치는 볼 필요 없다!
                if (y_ == now.start_y && x_ == now.start_x) continue;
                
                // 현재 내가 이동할 칸을 보면서, P라면 거리두기 위반을 찾은 것이다.
                // 스택을 모두 비우고, break한다.
                if (places[i][y_][x_] == 'P') {
                    // cout << i+1 << "번째 회의실" <<  y_ << ", " << x_ << "에서 위반자 발견" << endl;
                    answer[i] = 0;
                    while(!stk.empty()) stk.pop();
                    break;
                }
                
                // P가 아니라면, 다음으로 진행시킨다. 
                // 단, move_left가 현재 0이라면 더 탐색이 불가능한것이므로, 보내지 않는다.
                if (places[i][y_][x_] == 'O') {
                    stk.push(block(y_, x_, now.start_y, now.start_x, now.move_left - 1));
                }
            }
        }
    }
    
    return answer;
}