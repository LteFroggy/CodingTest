#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    거스름돈 주는 경우의 수 구하기
    돈의 종류는 주어진다
    
    DP로 하자
    
    이건 순서가 상관이 없다. 따라서 각 동전별로 가능한 방법을 만들어준다.
*/

int solution(int n, vector<int> money) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    
    for (auto v : money) {
        for (int i = v; i <= n; i++) {
            // v원이 만들 수 있는 값들을 모두 체크한다
            dp[i] += dp[i - v];
        }
    }
    
    return dp[n];
}