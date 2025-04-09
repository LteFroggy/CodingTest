#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
    n * m 사이즈의 격자 미로가 생긴다
    미로의 x, y에서 출발해 r, c로 이동해 탈출하자
    
    이동하는 거리가 총 k여야 하고, 출발지와 도착지를 포함해서 같은 격자를 두 번 이상 방문해도 된다.
    미로에서 탈출한 경로를 문자열로 나타냈을 때, 사전순으로 가장 빨라야 한다.
    
    대신, 이 조건대로 미로 탈출이 불가능하다면 impossible을 return하자.
    
    일단 상하좌우로만 움직일 수 있으니 abs(r - x) + abs(c - y)가 k보다 작다면 impossible을 return한다.
    또, 짝수 홀수가 중요하다. k가 홀수인데 두 값의 차가 짝수라면 죽었다 깨도 도착 못함.
*/

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    
    int moveDist = abs(r - x) + abs(c - y);
    // 기본적으로 거리가 안되면 impossible
    if (moveDist > k) return "impossible";
    // 홀수, 짝수가 안맞아도 impossible
    else if (moveDist % 2 != k % 2) return "impossible";
    
    // dlru -> 아래, 왼쪽, 오른쪽, 위 순서로 사전 순으로 빠르다.
    // 따라서 여유가 생긴다면, 아래나 왼쪽부터 가줘야 함
    
    // 먼저, 제일 빠르게 가기 위한 길을 찾는다.
    int up_count = 0;
    int down_count = 0;
    int left_count = 0;
    int right_count = 0;
    
    int height_diff = abs(r - x);
    for (int i = 0; i < height_diff; i++) {
        if (x > r) up_count++;
        else down_count++;
    }
    
    int width_diff = abs(c - y);
    for (int i = 0; i < width_diff; i++) {
        if (y > c) left_count++;
        else right_count++;
    }
    
    // 그리고 여유값을 찾는다.
    int move_left = k - moveDist;
    
    // 만약 여유값이 0개라면, 여유가 없으니 사전순에 맞게 이동을 배치하고 return한다.
    if (move_left == 0) {
        while (down_count-- > 0) answer += 'd';
        while (left_count-- > 0) answer += 'l';
        while (right_count-- > 0) answer += 'r';
        while (up_count-- > 0) answer += 'u';
        
        return answer;
    }
    
    // 여유가 좀 남는다면! 아래부터 한번 체크해본다.
    // 이동 횟수가 무한히 남았다고 가정하면, 일단 제일 아래까지 진행하고, 그 다음에 왼쪽으로 끝까지 진행한 후 구석에서 비비는 것이 제일 사전순 앞에 나온다.
    int x_loc = x;
    int y_loc = y;
    
    while (answer.length() < k) {
        /// cout << "현재 answer의 상태 " << answer << ", 상하좌우 남은 이동 횟수 " << up_count << ", " << down_count << ", " << left_count << ", " << right_count << endl;
        // 먼저, 아래로 갈 수 있는 상황인지 체크한다.
        if (x_loc < n) {
            // 원래 아래로 가야 하는 횟수가 남았는가? 그렇다면 이동시키고 계속하기
            if (down_count > 0) {
                x_loc++;
                down_count--;
                answer += 'd';
                
                continue;
            }
            
            // 여분 이동 횟수가 남았는가? 그럼 이동시키고 올라가야 하는 횟수 1회 추가해두기
            else if (move_left > 0) {
                x_loc++;
                up_count++;
                move_left -= 2;
                answer += 'd';
                
                continue;
            }
        }
        
        // 그 다음에는 왼쪽이다.
        if (y_loc > 1) {
            
            // 원래 왼쪽으로 가야 하는 횟수가 남았는가?
            if (left_count > 0) {
                y_loc--;
                left_count--;
                answer += 'l';
                
                continue;
            }
            
            else if (move_left > 0) {
                y_loc--;
                right_count++;
                move_left -= 2;
                answer += 'l';
                
                continue;
            }
        }
        
        // 그 후 오른쪽
        if (y_loc < n) {
            // 원래 오른쪽으로 가야 하는 횟수가 남았는가?
            if (right_count > 0) {
                y_loc++;
                right_count--;
                answer += 'r';
                
                continue;
            }
            
            else if (move_left > 0) {
                y_loc++;
                left_count++;
                move_left -= 2;
                answer += 'r';
                
                continue;
            }
        }
        
        // 그리고 위
        if (x_loc > 1) {
            // 원래 위로 가야 하는 횟수가 남았는가?
            if (up_count > 0) {
                x_loc--;
                up_count--;
                answer += 'u';
                
                continue;
            }
            
            else if (move_left > 0) {
                x_loc--;
                down_count++;
                move_left -= 2;
                answer += 'u';
                
                continue;
            }
        }
    }
    
    return answer;
}