#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    DP로 가자. 어떤 칸에 올 수 있는 방법은 그 전칸 + 그 전전칸임
*/

long long solution(int n) {
    long long answer = 0;
    vector<int> howMuchWays(n + 1, 0);
    
    // 첫 칸, 두번째 칸은 한 방법으로밖에 못간다
    howMuchWays[0] = 1;
    howMuchWays[1] = 1;
    for (int i = 2; i <= n; i++) {
        // 한 칸에 도달하는 방법은 그 전전칸에서 두칸 뛰거나, 그 전칸에서 한칸 뛰거나.
        // 그러니 두개를 더하면 됨
        howMuchWays[i] = howMuchWays[i - 1] + howMuchWays[i - 2];
        howMuchWays[i] %= 1234567;
    }
    
    return howMuchWays[n];
}