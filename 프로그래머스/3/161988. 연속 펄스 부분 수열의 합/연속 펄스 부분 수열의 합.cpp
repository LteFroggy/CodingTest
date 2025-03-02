#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    값을 번갈아서 뒤집어가면서 최대 합이 나오는 구간 찾기
    
    DP로 하자. 값을 쭉 보면서, 각 자리에서 나올 수 있는 최대 부분합들을 저장할 것
    앞의 값이 음수이면 나 자신이 다시 값이 되고, 앞의 값이 양수이면 "앞 값 + 나"가 값이 된다.
*/

long long solution(vector<int> sequence) {
    long long answer = 0;
    vector<int> order;
    vector<int> reverse;
    
    vector<long long> order_dp;
    vector<long long> reverse_dp;
    
    for (int i = 0; i < sequence.size(); i++) {
        if (i % 2 == 0) {
            order.push_back(sequence[i]);
            reverse.push_back(-(sequence[i]));
        }

        else {
            order.push_back(-(sequence[i]));
            reverse.push_back(sequence[i]);
        }
    }
    
    
    /*
    cout << "정순 배열 : "; for (auto v : order) cout << v << " "; cout << endl;
    cout << "역순 배열 : "; for (auto v : reverse) cout << v << " "; cout << endl;
    */
    
    // 정순배열 순회하기
    for (int i = 0; i < sequence.size(); i++) {
        // 0번째일땐 앞 값이 없으므로 그냥 나 자신이 값이 된다.
        if (i == 0) order_dp.push_back(order[i]);
        // 앞 값을 보면서 양수이면 "앞 값 + 나"가 최대 부분합이 되고, 아니라면 나 자신이 최대 부분합이 된다
        else {
            if (order_dp[i - 1] > 0) order_dp.push_back(order_dp[i - 1] + order[i]);
            else order_dp.push_back(order[i]);
        }
        
        // 매 순회마다 answer는 최대값을 향해 간다
        if (answer < order_dp[i]) answer = order_dp[i];
    }
    
    // 역순배열 순회하기
    for (int i = 0; i < sequence.size(); i++) {
        // 0번째일땐 앞 값이 없으므로 그냥 나 자신이 값이 된다.
        if (i == 0) reverse_dp.push_back(reverse[i]);
        // 앞 값을 보면서 양수이면 "앞 값 + 나"가 최대 부분합이 되고, 아니라면 나 자신이 최대 부분합이 된다
        else {
            if (reverse_dp[i - 1] > 0) reverse_dp.push_back(reverse_dp[i - 1] + reverse[i]);
            else reverse_dp.push_back(reverse[i]);
        }
        
        // 매 순회마다 answer는 최대값을 향해 간다
        if (answer < reverse_dp[i]) answer = reverse_dp[i];
    }
    
    return answer;
}