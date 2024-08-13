#include <string>
#include <vector>

using namespace std;

/*
    상하좌우로 움직인다.
    0,0에서 시작
    
    10 x 10사이즈 보드판이다.
    
    처음 걸어본 길을 세어볼 것이다! 좌표평면의 경계를 넘어서는 명령은 그냥 무시한다.
    가로 길, 세로 길이 있다. 가로 길 저장용으로 2차원 벡터 하나, 세로 길 저장용으로 2차원 벡터 하나 사용하자
*/

// 보드판 범위를 벗어나지 않는지 체크하기
bool inboard_check(int y, int x) {
    return y < 11 && y >= 0 && x < 11 && x >= 0; 
}


// x, y모두 0 ~ 10까지라고 생각하고 시작을 5,5라고 하자.
int solution(string dirs) {
    // 10 x 10사이즈 벡터를 가로선, 세로선에 대해 만든다.
    // horizen[i][j] y = i, x = j에서 뻗어나간 세로줄을 의미한다.
    vector<vector<bool>> horizen(11, vector<bool>(11));
    vector<vector<bool>> vertical(11, vector<bool>(11));
    int answer = 0;
    
    int y(5), x(5);
    for (int i = 0; i < dirs.length(); i++) {
        
        // 왼쪽으로 가는 경우, y, x에서 y, x-1로 이어지는 가로선을 타는 것이므로 이를 처리한다.
        if (dirs[i] == 'L' && inboard_check(y, x - 1)) {
            // 안 가본 선인 경우에만 answer 증가시키기
            if (!horizen[y][x-1]) {
                answer++;
                horizen[y][x-1] = true;
            }
            x--;
        }
        
        else if (dirs[i] == 'R' && inboard_check(y, x + 1)) {
            if (!horizen[y][x]) {
                answer++;
                horizen[y][x] = true;
            }
            x++;
        }
        
        else if (dirs[i] == 'U' && inboard_check(y + 1, x)) {
            if (!vertical[y][x]) {
                answer++;
                vertical[y][x] = true;
            }
            y++;
        }
        
        else if (dirs[i] == 'D' && inboard_check(y - 1, x)) {
            if (!vertical[y-1][x]) {
                answer++;
                vertical[y-1][x] = true;
            }
            y--;
        }
    }
    
    return answer;
}