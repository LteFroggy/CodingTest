#include <string>
#include <vector>
#include <iostream>

/*
    n x m사이즈 격자
    
    빨간수레 파란수레 하나씩 있음.
    시작부터 도착까지 이동해야 한다.
    
    꼭 상하좌우중 하나로 움직여야 함. 대신 규칙이 있다
    
    1. 수레는 벽 밖으로 갈 수 없음
    2. 이미 방문했던 칸으로 움직일 수 없음
    3. 도착한 칸의 수레는 움직이지 않음
    4. 두 수레는 동시에 같은 칸에 있을 수 없음
    5. 수레끼리 자리 바꾸기 불가능
    
    필요한 턴의 최소값 전달하기
    
    최대 4x4이다. 따라서 존재할수있는 빨강, 파랑의 총 상태는 16 x 16 = 256가지
    이동 가능은 상하좌우 4x4 = 16가지. 따라서 총 256 x 16 가지이다.
*/

using namespace std;

struct Point {
    int y;
    int x;
    
    bool operator==(const Point& other) const {
        return y == other.y && x == other.x;
    }
    
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.y << " " << p.x << ")";
        return os;
    }
    
    Point& operator=(const Point& other) {
        if (this == &other) return *this;
        
        y = other.y;
        x = other.x;
        return *this;
    }
};

bool inboardCheck(int n, int m, Point loc) {
    return n > loc.y && loc.y >= 0 && loc.x >= 0 && loc.x < m;
}

void backTracking(const vector<vector<int>> &maze, int& answer, int turnCount, Point redNow, Point blueNow, vector<vector<bool>> &redVisited, vector<vector<bool>> &blueVisited) {
    
    int n = maze.size();
    int m = maze[0].size();
    
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};
    
    /// cout << "빨강 : " << redNow << ", 파랑 : " << blueNow << endl;
    
    Point redNew = redNow;
    Point blueNew = blueNow;
    
    // 현재 red, blue의 위치가 목적지에 모두 도달했다면 answer와 비교하고 갱신한다
    if (maze[redNow.y][redNow.x] == 3 && maze[blueNow.y][blueNow.x] == 4) {
        answer = answer > turnCount ? turnCount : answer;
        
        /// cout << "answer = " << answer << "로 종료 =========================================" << endl;
        return;
    }
    
    // 만약 이동 횟수가 이미 정답보다 커져버렸다면, 가지치기
    else if (answer <= turnCount) {
        /// cout << "가지치기로 종료 =========================================" << endl;
        return;
    }
    
    // 빨강만 목적지에 도달했다면, 파랑만 움직이기
    else if (maze[redNow.y][redNow.x] == 3) {
        for (int k = 0; k < 4; k++) {
            blueNew.y = blueNow.y + dy[k];
            blueNew.x = blueNow.x + dx[k];
            
            // 이미 가보거나 보드 밖이면 체크하지 않음
            if (!inboardCheck(n, m, blueNew) || blueVisited[blueNew.y][blueNew.x]) continue;
            
            // 이동 목표 위치가 벽이어도 가보지 않음
            if (maze[blueNew.y][blueNew.x] == 5) continue;
            
            // 파랑의 새 위치가 빨강 현재위치와 동일해진다면, 이동 불가능
            if (redNow == blueNew) continue;
            
            // 모두 만족한다면, 새 위치로 이동시켜보기
            /// cout << "파랑만 (" << blueNow.y << " " << blueNow.x << ") 에서 (" << blueNew.y << " " << blueNew.x << ") 으로 이동" << endl;      
            blueVisited[blueNew.y][blueNew.x] = true;
            backTracking(maze, answer, turnCount + 1, redNow, blueNew, redVisited, blueVisited);
            blueVisited[blueNew.y][blueNew.x] = false;
        }
    }

    // 빨강만 움직이기
    else if (maze[blueNow.y][blueNow.x] == 4) {
        for (int k = 0; k < 4; k++) {
            redNew.y = redNow.y + dy[k];
            redNew.x = redNow.x + dx[k];
            
            // 이미 가보거나 보드 밖이면 체크하지 않음
            if (!inboardCheck(n, m, redNew) || redVisited[redNew.y][redNew.x]) continue;
            
            // 이동 목표 위치가 벽이어도 가보지 않음
            if (maze[redNew.y][redNew.x] == 5) continue;
            
            // 빨강의 새 위치가 파랑 현재위치와 동일해진다면, 이동 불가능
            if (redNew == blueNow) continue;
            
            // 모두 만족한다면, 새 위치로 이동시켜보기
            /// cout << "빨강만 (" << redNow.y << " " << redNow.x << ") 에서 (" << redNew.y << " " << redNew.x << ") 으로 이동" << endl;
            redVisited[redNew.y][redNew.x] = true;
            backTracking(maze, answer, turnCount + 1, redNew, blueNow, redVisited, blueVisited);
            redVisited[redNew.y][redNew.x] = false;
        }
    }
    
    // 둘 다 움직이기
    else {
        for (int k = 0; k < 4; k++) {
            for (int k_ = 0; k_ < 4; k_++) {
                redNew.y = redNow.y + dy[k];
                redNew.x = redNow.x + dx[k];
                blueNew.y = blueNow.y + dy[k_];
                blueNew.x = blueNow.x + dx[k_];
                
                // 둘 다 보드판 안쪽인지 확인
                if (!inboardCheck(n, m, redNew) || !inboardCheck(n, m, blueNew)) continue;
                
                // 둘 다 안가본곳인지 확인
                if (redVisited[redNew.y][redNew.x] || blueVisited[blueNew.y][blueNew.x]) continue;
                
                // 둘다 벽은 아닌지 확인
                if (maze[redNew.y][redNew.x] == 5 || maze[blueNew.y][blueNew.x] == 5) continue;
                
                // 새 이동 위치가 둘이 겹치지는 않는지 확인
                if (redNew == blueNew) continue;
                
                // 서로 위치 교차된건 아닌지 확인
                if (redNew == blueNow && blueNew == redNow) continue;
                
                // 전부 문제없다면, 이동시키기
                /// cout << "빨강 (" << redNow.y << " " << redNow.x << ") 에서 (" << redNew.y << " " << redNew.x << ") 으로 이동" << endl;
                /// cout << "파랑 (" << blueNow.y << " " << blueNow.x << ") 에서 (" << blueNew.y << " " << blueNew.x << ") 으로 이동" << endl;      
                blueVisited[blueNew.y][blueNew.x] = true;
                redVisited[redNew.y][redNew.x] = true;
                backTracking(maze, answer, turnCount + 1, redNew, blueNew, redVisited, blueVisited);
                blueVisited[blueNew.y][blueNew.x] = false;
                redVisited[redNew.y][redNew.x] = false;
            }   
        }   
    }    
}

int solution(vector<vector<int>> maze) {
    int answer = 0;
    
    Point redGoal;
    Point blueGoal;
    Point redNow;
    Point blueNow;
    
    // 보드판 보면서 필요한 값 꺼내기
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == 1) {
                redNow.y = i;
                redNow.x = j;
            }
            
            else if (maze[i][j] == 2) {
                blueNow.y = i;
                blueNow.x = j;
            }
            
            else if (maze[i][j] == 3) {
                redGoal.y = i;
                redGoal.x = j;
            }
            
            else if (maze[i][j] == 4) {
                blueGoal.y = i;
                blueGoal.x = j;
            }
        }
    }
    
    
    vector<vector<bool>> redVisited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<vector<bool>> blueVisited(maze.size(), vector<bool>(maze[0].size(), false));
    
    // 초기 위치 visited 갱신
    redVisited[redNow.y][redNow.x] = true;
    blueVisited[blueNow.y][blueNow.x] = true;
    
    answer = 999;
    
    backTracking(maze, answer, 0, redNow, blueNow, redVisited, blueVisited);
    
    return answer == 999 ? 0 : answer;
}