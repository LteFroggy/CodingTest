#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    삼각달팽이 한국다람쥐 한국다람쥐 한한한국다람쥐
    
    n이 주어지면, 밑변의 길이와 높이가 n인 삼각형을 만든다.
    첫 행부터 마지막 행까지 순서대로 합친 배열을 돌려주면 됨
    
    일단, n = 1일 땐 블럭 개수 1개
    n = 2면 3개
     1
    2 3
    
    n = 3이면 6개
      1
     2 6
    3 4 5 
    
    n = 4일 때 10개
    n = 5일 때 15개.
    
    n(n + 1) / 2 -> 1부터 n까지의 합 만큼의 블록이 있음을 알 수 있다
    
    숫자 규칙을 생각해보자.
    1. 왼쪽 아래로 내려간다(i + j)(층 값)
    2. 왼쪽 끝이라면, 다시 오른쪽으로 간다 (i + 1);
    3. 오른쪽 끝에서부터 올라온다 (i / 2 - j(층 값))
    4. 1로 돌아간다.
    
    위의 규칙을 반복한다!
    이걸 알고리즘화 해보자.
*/

vector<int> solution(int n) {
    int block_size = n * (n + 1) / 2;
    // 처음엔 값을 모두 0으로 초기화시킨다! 헷갈리지 않게
    vector<int> answer(block_size, 0);
    
    
    // 첫 지점에서 시작하기
    int now = 0;
    int val = 1;
    int row = 1;
    
    // 첫 지점 값은 미리 세팅해준다
    answer[now] = val++;
    // 세 가지 행동을 반복해야 한다.
    while (val <= block_size) {
        // 1. 왼쪽 아래로 내려가기
        while (now + row < block_size && answer[now + row] == 0) {
            // 아래로 내려가는 것이므로 row도 증가시킨다
            now += row;
            row++;
            
            answer[now] = val++;
        }
        
        // 2. 오른쪽으로 가기
        while (now + 1 < block_size && answer[now + 1] == 0) {
            now++;
            
            answer[now] = val++;
        }
        
        // 3. 왼쪽 위로 올라가기
        while (now - row >= 0 && answer[now - row] == 0) {
            // 위로 올라가는 것이므로, row도 감소시킨다
            now -= row;
            row--;
            
            answer[now] = val++;
        }
     }
    
    /*
    n = 4일 때, block_size = 10
     
    now = 0, row = 1에서 시작해서 왼쪽 아래로
    now[0] = 1; row = 1
    now[1] = 2; row = 2
    now[3] = 3; row = 3
    now[6] = 4; row = 4
    6 + 4 == 10이므로 왼쪽아래 끝
    
    오른쪽으로
    now[7] = 5; row = 4
    now[8] = 6; row = 4
    now[9] = 7; row = 4
    9 + 1 == 10이므로 오른쪽 끝
    
    다시 위로
    now[5] = 8; row = 3;
    now[2] = 9; row = 2;
    now[2-2] != 0 이므로 위 끝
    
    다시 왼쪽아래로
    now[4] = 10; row = 3
    val = 11이므로 block_size보다 커져서 종료.
    */
    
    return answer;
}