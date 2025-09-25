#include <iostream>
#include <string> 
#include <vector>
#include <queue>

using namespace std;

/*
    1 ~ n개의 좌표 포인트 존재, 
    
    로봇마다 운송 경로가 있다. m개의 포인트, 첫 포인트에서 시작해 할당된 포인트 순서대로 방문
    
    사용되는 로봇은 총 x대이고, 0초에 동시 출발
    1초마다 x혹은 y로 한 칸씩 움직인다
    
    다음 포인트로 갈 때는 최단 경로로만 이동, y축 먼저 맞추고 c좌표 움직인다
    
    마지막 포인트에 도달하면 그냥 거기서 사라진다.
    
    같은 좌표에 로봇이 2대 이상 모이면 충돌가능. 총 몇 번의 충돌이 발생하는지 구해보자.
    
    *** 좌표는 1부터 시작하는 체계를 사용하고 있으므로 좌표는 1부터 시작
    로봇번호는 0번부터
    포인트는 0번부터로 다 수정
*/

typedef pair<int, int> point;

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    int answer = 0;
    
    // r의 최대값, c의 최대값 확인
    int maxR = 0, maxC = 0;
    
    for (auto v : points) {
        maxR = maxR < v[0] ? v[0] : maxR;
        maxC = maxC < v[1] ? v[1] : maxC;
    }
    
    // 각 포인트별 로봇 갯수
    vector<vector<int>> pointCount(maxR + 1, vector<int>(maxC + 1));
    
    // 각 로봇의 현재 위치를 저장할 vector
    vector<point> robotLoc(routes.size());
    
    // 각 로봇이 몇 번째 위치에 가야 하는지 저장하기 위한 vector
    vector<int> targetLoc(routes.size(), 1);
    
    // 몇 개의 루트를 방문하면 끝인가??
    int routeCount = routes[0].size();
    
    // 움직일 로봇들이 저장되는 큐
    queue<int> moveQueue;
    queue<int> nextMoveQueue;
    
    // 현재 위치 초기화
    for (int i = 0; i < routes.size(); i++) {
        // 시작 위치를 본다
        int startLoc = routes[i][0] - 1;
        
        // 시작 위치 지정
        int startR = points[startLoc][0];
        int startC = points[startLoc][1];
        
        robotLoc[i].first = startR;
        robotLoc[i].second = startC;
        
        // 위치 처리
        if (pointCount[startR][startC]++ == 1) {
            answer++;
        }
    }
    
    // 처음엔 모든 로봇이 움직여야 한다. moveQueue에 삽입
    for (int i = 0; i < routes.size(); i++) moveQueue.push(i);
    
    // 모든 로봇이 행동 완료할때까지 시간 단위로 시뮬레이션 처리
    while (!moveQueue.empty()) {
        /// cout << "이동 진행" << endl;
        
        // 모든 칸이 비어있다고 처리
        for (auto &v: pointCount) fill(v.begin(), v.end(), 0);
        
        while (!moveQueue.empty()) {
            // 큐에서 로봇 꺼낸다
            int robotNum = moveQueue.front();
            moveQueue.pop();
            
            // 현재 위치와 다음 위치 확인
            int nowR = robotLoc[robotNum].first;
            int nowC = robotLoc[robotNum].second;
            
            int targetNum = routes[robotNum][targetLoc[robotNum]] - 1;
            int targetR = points[targetNum][0];
            int targetC = points[targetNum][1];
            
            /// cout << robotNum + 1 << "번 로봇의 현 위치 : " << nowR << ", " << nowC << endl;
            /// cout << robotNum + 1 << "번 로봇의 목표 위치 : " << targetR << ", " << targetC << endl;
            
            // R이 맞지 않으면 R부터 이동
            if (targetR != nowR) {
                nowR += targetR > nowR ? 1 : -1;
            }
            // 아니면 L 이동
            else {
                nowC += targetC > nowC ? 1 : -1;
            }
            
            /// cout << robotNum + 1 << "번 로봇의 이동 후 위치 : " << nowR << ", " << nowC << endl;
            
            // nowR, nowC 갱신
            robotLoc[robotNum].first = nowR;
            robotLoc[robotNum].second = nowC;
            
            // 충돌 확인, 2대 이상 충돌한건 신경 안쓴다.
            if (pointCount[nowR][nowC]++ == 1) {
                answer++;       
            }
            
            // 이동 후에 목표 지점에 도달했다면, targetLoc 1증가
            if (targetR == nowR && targetC == nowC) targetLoc[robotNum]++;
            
            // 아직 종료 조건에 도달하지 못했다면, nextMoveQueue에 추가
            if (targetLoc[robotNum] != routeCount) nextMoveQueue.push(robotNum);
        }
        
        // 보드판 현황
        /*
        cout << "보드판 현황" << endl;
        for (int r = 1; r <= maxR; r++) {
            for (int c = 1; c <= maxC; c++) 
                cout << pointCount[r][c] << " "; cout << endl;
        }
        cout << endl << endl;
        */
            
        
        // 다 돌았다면, moveQueue랑 nextMoveQueue 교체
        swap(moveQueue, nextMoveQueue);
        nextMoveQueue = {};
    }
    
    return answer;
}