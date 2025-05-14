#include <string>
#include <vector>

using namespace std;

/*
    다트게임이다. 점수를 무작위로 정해주고, 다트를 던지면서 점수를 깎아 정확히 0점으로 만들면 된다
    
    싱글, 더블, 트리플 똑같이 있고, 불은 모두 50점이다.
    최소한의 다트로 0점을 만들고자 하고, 그러한 방법이 여러개라면 싱글이나 불을 최대한 많이 던지고자 한다
    
    target이 주어졌을 때, 최선의 다트 수와 싱글 혹은 불을 맞춘 횟수의 합을 담아보자.
    
    전에 풀었던 DP와 비슷하다.    

    각 점수별로 낼 수 있는 다트 수와 그때의 싱글, 불 수를 100,000까지 모두 기록한다.
    그리고 값을 내면 된다
    100,000 * 61 = 6,100,000이므로 충분하다
*/

vector<int> solution(int target) {    
    vector<pair<int, int>> dp(target + 1, {1e9, 0});
    
    dp[0] = {0, 0};
    
    for (int i = 0; i < target; i++) {
        // 점수 맞췄을때를 계산
        for (int score = 1; score <= 20; score++) {
            // 싱글, 더블, 트리플이 있다
            for (int mul = 1; mul <= 3; mul++) {
                int newScore = i + (score * mul);
                // 범위 넘어가면 끝내기
                if (newScore > target) break;
                
                int throwCount = dp[i].first + 1;
                int singleCount = dp[i].second + (mul == 1 ? 1 : 0);
                
                // 이게 던진 횟수가 더 적다면 갱신 필요
                if (dp[newScore].first > throwCount) {}
                
                // 던진 횟수가 같아도, 싱글 횟수가 적다면 갱신 필요
                else if (dp[newScore].first == throwCount && dp[newScore].second < singleCount) {}
                
                // 아무것도 걸리지 않으면, 갱신 불필요
                else continue;
                
                // 갱신
                dp[newScore] = {throwCount, singleCount};
            }
        }
        
        // 불 맞췄을때를 계산
        int newScore = i + 50;
        // 범위 넘어가면 끝내기
        if (newScore > target) continue;
        int throwCount = dp[i].first + 1;
        int singleCount = dp[i].second + 1;
        // 던진 횟수가 적거나, 같더라도 싱글 횟수가 적으면 갱신한다
        if (dp[newScore].first > throwCount ||
           (dp[newScore].first == throwCount && dp[newScore].second < singleCount)) {
            dp[newScore] = {throwCount, singleCount};
        } 
    }
    
    return vector<int>{dp[target].first, dp[target].second};
}