#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
    오른쪽에 있는 값 중 가장 큰 값을 찾아내야 한다.
    이런 문제는 자기보다 큰 값을 만날때까지 계속 빼면 된다.
    
    왼쪽 값부터 스택에 넣기
    3 5 2 3 7
    3 넣었다.
    3
    
    5 만났다. 3보다 크므로 3 뺀다
    5
    
    2 넣는다.
    5 2
    
    3 만났다. 2보다 크므로 2 뺀다
    5 3
    
    7 만났다. 3보다 크므로 3 뺀다
    5보다 크므로 5도 뺀다
    7
*/

int main() {
    // 먼저 수열 입력받기
    int N;
    cin >> N;
    
    // 결과 저장용 배열
    vector<int> result(N, 0);
    
    // 왼쪽부터 보자.. 제일 끝부터 보면서 스택을 사용할 것
    stack<pair<int, int>> stk;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        // 스택이 비어있으면 그냥 넣는다.
        if (stk.empty()) {
            stk.push({tmp, i});
        }
        
        // 비어있지 않다면, 오큰수보다 큰 값이 나올때까지 계속 값을 빼줘야 한다.
        else {
            while (!stk.empty() && stk.top().first < tmp) {
                int idx = stk.top().second;
                result[idx] = tmp;
                stk.pop();
            }
            
            stk.push({tmp, i});
        }
    }
    
    // for문이 끝났다면, 스택에 남은 값만큼 -1을 출력한다
    while (!stk.empty()) {
        int idx = stk.top().second;
        result[idx] = -1;
        stk.pop();
    }

    for (auto v : result) cout << v << " ";
    
    return 0;
}