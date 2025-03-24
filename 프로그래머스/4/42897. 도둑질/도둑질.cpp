#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    마을 털자. 각 집은 서로 인접한 집과 방법장치가 연결되어있다! 도둑이 훔칠 수 있는 돈의 최대값을 return하자.
    
    A집을 털려면, A-1과 A+1을 모두 털지 않았어야 한다.
    그 관점에서 가장 큰 값을 생각해보자
    
    첫 집은 마지막 집과 이어진다! 따라서 첫 집을 털지 않아야만 마지막 집을 털 수 있고, 첫 집을 털었다면 마지막 집을 털 수 없다!
    
    두 가지 경우로 나누어 푼다. 첫 집을 털었을 경우와 털지 않았을 경우
    첫 집을 털었을 경우는, 1 ~ n-1까지 DP를
    털지 않았을 때는 2 ~ n까지 DP를 수행한다.
    
    DP는 이 집을 털었을 때와 털지 않았을 때, 둘 중 더 큰 값을 저장하면 된다.
*/

int solution(vector<int> money) {
    int answer = 0;
    int n = money.size();
    
    // 첫 집을 털지 않았을 경우
    int dp_1 = 0;
    int dp_2 = 0;
    int max_money;
    
    for (int i = 1; i < n; i++) {
        max_money = max(dp_1 + money[i], dp_2);
        
        dp_1 = dp_2;
        dp_2 = max_money;
    }
    
    answer = max_money;
    
    // 첫 집을 털었을 경우
    dp_1 = 0;
    dp_2 = 0;
    max_money = 0;
    
    for (int i = 0; i < n-1; i++) {
        max_money = max(dp_1 + money[i], dp_2);
        
        dp_1 = dp_2;
        dp_2 = max_money;
    }
    
    answer = max(answer, max_money);
    
    return answer;
}