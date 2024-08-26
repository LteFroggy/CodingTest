#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    2N명의 사원이 N명씩 나뉘어서 숫자 게임 한다.
    모든 사원이 무작위 자연수를 하나씩 받는다.
    경기는 한 명당 한 번만 한다
    
    서로의 수를 공개하고, 숫자가 크면 승리한다.
    동일하다면, 하지 않는다.
    
    A팀은 출전 순서를 얼른 정하고 B팀에게 공개했다! B팀은 최종 승점을 가장 높이는 방식으로 매치를 하려 한다.
    가장 높은 점수를 구해보자.
    
    
    ***
    이기려면, 나보다 낮으면서 사용되지 않은 점수가 1개 이상 있어야 한다.
    따라서 낮은 점수 순으로 정렬하고, B를 보면서 A를 보면 된다.
    
    1. A, B의 값을 오름차순 정렬한다
    2. B[0]을 보고, B[0]보다 크거나 같은 값이 나오기 전까지 A를 보며 a_count를 증가시킨다
    3. a_count가 1이상이면, a_count를 1 감소시키고 answer를 1 증가시킨다. B의 점수로 이길 수 있는 사람이 있기 때문
    4. B를 다 볼때까지 위를 반복한다.
*/

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    int a_count = 0;
    int a_cursor = 0;
    
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    for (int i = 0; i < B.size(); i++) {
        // 먼저 B[i]보다 크거나 같은 값이 나올때까지 A를 확인한다.
        while (a_cursor < A.size() && A[a_cursor] < B[i]) {
            a_cursor++;
            a_count++;
        }
        
        // 현재 B[i]의 값으로 이길 수 있는 사람이 있다면, a_count를 감소시키고 answer를 증가시킨다.
        if (a_count > 0) {
            a_count--;
            answer++;
        }
    }
    
    return answer;
}