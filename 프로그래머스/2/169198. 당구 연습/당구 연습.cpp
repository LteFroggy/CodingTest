#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
    가로 m
    세로 n
    놓인 좌표 startX startY
    목표 좌표 balls
    벽에 한 번은 맞추고 목표에 맞춘다.
    
    친 공이 굴리간 거리의 최소값
    
    벽에 부딫히면 입사각 반사각 동일 -> 기울기 반전
    꼭짓점에 부딫히면 진행의 반대 -> 기울기 동일, 방향만 반대
    두 공의 좌표가 정확히 일치해야만 맞았음
    공이 목표에 맞기 전에 멈추는 경우는 없음, 맞으면 바로 멈춤
    
    1. 벽 맞추기
    항상 벽 맞추는 것이 유리
*/

vector<int> solution(int m, int n, int startX, int startY, vector<vector<int>> balls) {
    vector<int> answer;
    
    for (auto pos : balls) {
        int xPos = pos[0];
        int yPos = pos[1];
        
        int minDist = 1e9;
        
        // 윗벽, 아랫벽, 왼쪽벽, 오른쪽벽 튀겨보면서 최소값 구하기
        // 윗벽
        int distX = abs(xPos - startX);
        int distY = yPos + startY;
        int distUp = static_cast<int>(pow(distX, 2)) + static_cast<int>(pow(distY, 2));
        // 가는 길에 맞으면, 위로 치면 안됨
        if (xPos == startX && startY > yPos) {}
        else minDist = minDist > distUp ? distUp : minDist;
        
        // 아랫벽
        distX = abs(xPos - startX);
        distY = (n - yPos) + (n - startY);
        int distDown = static_cast<int>(pow(distX, 2)) + static_cast<int>(pow(distY, 2));
        // 가는 길에 맞으면, 아래로 치면 안됨
        if (xPos == startX && startY < yPos) {}
        else minDist = minDist > distDown ? distDown : minDist;
        
        // 왼벽
        distX = xPos + startX;
        distY = abs(yPos - startY);
        int distLeft = static_cast<int>(pow(distX, 2)) + static_cast<int>(pow(distY, 2));
        // 가는 길에 맞으면, 왼쪽으로 치면 안됨
        if (yPos == startY && startX > xPos) {}
        else minDist = minDist > distLeft ? distLeft : minDist;
        
        // 오른벽
        distX = (m - xPos) + (m - startX);
        distY = abs(yPos - startY);
        int distRight = static_cast<int>(pow(distX, 2)) + static_cast<int>(pow(distY, 2));
        // 가는 길에 맞으면, 오른쪽으로 치면 안됨
        if (yPos == startY && startX < xPos) {}
        else minDist = minDist > distRight ? distRight : minDist;
        
        // 최소값 넣기
        answer.push_back(minDist);
    }
    
    return answer;
}