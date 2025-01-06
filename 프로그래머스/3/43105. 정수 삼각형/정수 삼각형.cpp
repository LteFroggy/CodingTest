#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 값 찾자
    각 값마다 가장 큰 값만 기록하면 된다.
*/


int solution(vector<vector<int>> triangle) {
    vector<vector<int>> dp(triangle.size());
    
    dp[0].push_back(triangle[0][0]);
    
    int answer = 0;
    for (int i = 1; i < triangle.size(); i++) {
        for (int j = 0; j < triangle[i].size(); j++) {
            // 나의 왼쪽 위 혹은 오른쪽 위의 값만 만날 수 있다.
            // 다시 말해, 나, 나-1만 만날 수 있음
            int LeftUpVal, RightUpVal;
            
            // 내가 0번 값이라면, RightUpVal이 없다.
            if (j == 0) {
                LeftUpVal = 0;
                RightUpVal = dp[i - 1][j];
            }
            
            // 내가 마지막 값이라면, RightUpVal이 없다.
            else if (j == triangle[i].size() - 1) {
                LeftUpVal = dp[i - 1][j - 1];
                RightUpVal = 0;
            }
            
            // 그게 아니라면, 알아서 본다
            else {
                LeftUpVal = dp[i - 1][j - 1];
                RightUpVal = dp[i - 1][j];
            }
            
            // 이제, 둘중 더 큰 값을 dp에 넣는다
            dp[i].push_back(max(LeftUpVal, RightUpVal) + triangle[i][j]);
        }
    }
    
    // 확인용 출력
    /*
    for (auto v : dp) {
        for (auto v_ : v) {
            cout << v_ << " ";
        }
        cout << endl;
    }
    */
    
    // 마지막 줄의 값을 쭉 보면서 제일 큰 값을 넘긴다
    vector<int> results = dp[dp.size() - 1];
    for (int i = 0; i < results.size(); i++) {
        if (answer < results[i])
            answer = results[i];
    }
    
    return answer;
}