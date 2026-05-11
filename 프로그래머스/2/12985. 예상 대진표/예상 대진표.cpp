#include <iostream>
#include <cmath>

using namespace std;

/*
    N명 토너먼트, 1 ~ N명 배정
    
    A번 참가자는 B번과 몇 라운드에서 만나는가?
    
    i번째 라운드에서 n / 2^i가 같은 모든 참가자가 함께 경기한다
    
    ex) 1번째 라운드
    0 / 2 = 0
    1 / 2 = 0 -> 0, 1번이 함께
    
    2번째
    0 / 4 = 0
    1 / 4 = 0
    ... -> 0 ~ 3번 함께
    
    
    그러므로 우리는 A번호와 B번호가 같은 몫을 가지게 되는 i값을 찾으면 된다.
*/

int solution(int n, int a, int b) {
    int idx = 1;
    a--;
    b--;
    
    while (true) {
        if (a / (1 << idx) == b / (1 << idx)) { break; }
        idx++;
    }

    return idx;
}