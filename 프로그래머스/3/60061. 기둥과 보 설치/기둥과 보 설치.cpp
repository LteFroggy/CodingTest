#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    주택 건축한다.
    죠르디는 기둥과 보를 통해 벽면 구조물을 자동으로 세울 것
    이 프로그램은 2차원 가상 벽면에 기둥, 보를 이용해 구조물을 설치할 수 있다.
    
    기둥 및 보는 길이가 1인 선분으로 표시된다.
    
    기둥은 기준 좌표에서 위로, 보는 기준 좌표에서 오른쪽으로 설치된다.
    
    기둥은 바닥 위나 보의 한쪽 끝 부분 위, 혹은 다른 기둥 위에 있어야 한다
    
    이제, 우리가 할 작업이 순서대로 담긴 2차원 배열이 주어진다.
    
    모든 명령어를 수행한 후 구조물의 상태를 return하자
    만약, 결과가 조건을 만족하지 못하면 그 작업은 무시한다
    
    값은 x, y, a, b형태로 주어진다
    x, y는 교차점의 좌표
    a는 구조물 종류
    b는 설치, 삭제 여부
    
    보는 교차점 기준으로 오른쪽, 기둥은 위로 설치한다
    구조물이 겹치거나 없는 구조물을 삭제하는 경우는 없다.
*/

// 특정 지점에 기둥이 지어질 수 있는지 확인 
bool isVerticalPossible(int x, int y, const vector<vector<vector<bool>>> &board) {
    int n = board.size();
    
    // 1. 바닥 위인가?
    if (y == 0) return true;
            
    // 2. 다른 기둥 위에 있는가?
    else if (y > 0 && board[x][y-1][0]) return true;

    // 3. 보의 한쪽 끝인가?
    else if (board[x][y][1]) return true;
    else if (x > 0 && board[x-1][y][1]) return true;
    
    return false;
}

// 특정 지점에 보가 지어질 수 있는가?
bool isHorizentalPossible(int x, int y, const vector<vector<vector<bool>>> &board) {
    int n = board.size();
    
    // 1. 한쪽 끝이 기둥 위에 있는가?
    if (y > 0 && board[x][y-1][0]) return true;
    else if (y > 0 && x < n && board[x+1][y-1][0]) return true;
            
    // 2. 양쪽 끝에 보가 있는가??
    else if ((x > 0 && board[x-1][y][1]) && (x < n && board[x+1][y][1]))return true;
    
    return false;
}

bool comp_std(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) {
        if (a[1] == b[1]) {
            return a[2] < b[2];
        }
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    // 3차원 벡터로 보드판을 만든다. board[x][y][z]에서 x, y는 좌표를 의미하고, z = 0은 기둥, 1은 보이다.
    // true면 존재, false면 미존재이다.
    vector<vector<vector<bool>>> board(n + 1, vector<vector<bool>>(n + 1, {false, false}));
    
    for (auto build : build_frame) {
        // 값 추출하기
        int x = build[0];
        int y = build[1];
        int target = build[2];
        bool destroy = build[3] == 0 ? true : false;

        // 설치하는 경우
        if (!destroy) {
            // 겹치도록 설치하거나, 없는 것을 삭제하는 일은 없으니 설치 가능한지 조건만 보면 된다
            // 기둥 설치하는 경우
            if (target == 0) 
                board[x][y][0] = isVerticalPossible(x, y, board);
            // 보 설치하는 경우
            else 
                board[x][y][1] = isHorizentalPossible(x, y, board);
        }

        // 철거하는 경우
        else {
            // 기둥을 철거하는 경우
            if (target == 0) {
                // 일단, 보드에서 나를 삭제하고 나와 이어진 모든 값들이 문제가 없는지 보면 된다. 문제가 있다면, 내 값을 원상복구하고 없던 일로
                board[x][y][0] = false;
                
                // 기둥 위에 기둥이 있었는가?
                if (y < n && board[x][y+1][0]) {
                    // 그렇다면 그 기둥이 유지될 수 있는가?
                    if (!isVerticalPossible(x, y+1, board)) {
                        // 불가능하다면 초기화
                        board[x][y][0] = true;
                        continue;
                    }
                }

                // 기둥의 윗면으로부터 오른쪽으로 뻗는 보가 있었는가
                if (board[x][y+1][1]) {
                    // 그럼 그 보가 유지될 수 있나?
                    if (!isHorizentalPossible(x, y+1, board)) {
                        board[x][y][0] = true;
                        continue;
                    }
                }

                // 기둥의 윗면에서부터 왼쪽으로 뻗은 보가 있었는가?
                if (x > 0 && y < n && board[x-1][y+1][1]) {
                    // 그럼 그 보가 유지될 수 잇나?
                    if (!isHorizentalPossible(x-1, y+1, board)) {
                        board[x][y][0] = true;
                        continue;
                    }
                }
            }

            // 보를 철거하는 경우
            else {
                // 일단 보를 철거해보고 확인
                board[x][y][1] = false;
                
                // 내 왼쪽에 이어진 보가 있었는가?
                if (x > 0 && board[x-1][y][1]) {
                    // 유지가능?
                    if (!isHorizentalPossible(x-1, y, board)) {
                        board[x][y][1] = true;
                        continue;
                    }
                }

                // 내 오른쪽에 이어진 보가 있었는가?
                if (x < n && board[x+1][y][1]) {
                    if (!isHorizentalPossible(x+1, y, board)) {
                        board[x][y][1] = true;
                        continue;
                    }
                }

                // 보의 왼쪽 끝에서 올라간 기둥이 있었는가?
                if (board[x][y][0]) {
                    if (!isVerticalPossible(x, y, board)) {
                        board[x][y][1] = true;
                        continue;
                    }
                }

                // 보의 오른쪽 끝에서 올라간 기둥이 있었는가?
                if (x < n && board[x+1][y][0]) {
                    if (!isVerticalPossible(x+1, y, board)) {
                        board[x][y][1] = true;
                        continue;
                    }
                }
            }
        }
    }
    
    // 다 마무리했으면, answer에 다 집어넣는다
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (board[i][j][0]) answer.push_back({i, j, 0});
            if (board[i][j][1]) answer.push_back({i, j, 1});
        }
    }
    
    // 이후 정렬한다.
    sort(answer.begin(), answer.end(), comp_std);
    return answer;
}