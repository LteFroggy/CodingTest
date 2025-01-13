#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/*
    야근을 하면 피로도가 쌓인다. 피로도는 시작한 시점에서 남은 일의 양을 제곱해 더한 값이다.
    
    N시간 동안 야근 피로도를 최소화하여 일할 것이다!
    1시간 동안 1의 작업을 처리할 수 있다면, 퇴근까지 남은 N시간을 바탕으로 야근 피로도의 최소값을 리턴하자.
    
    각 남은 일의 양의 제곱이 합산된다. 그런데 제곱은 밑이 커질수록 기하급수적으로 커지니, 밑을 최소화해야 한다
    밑을 가능한 비슷한 양으로 맞추는 것에 집중하자.
    
    모든 값을 하나의 Set에 넣는다. 그리고 제일 큰 값부터 하나씩 깎는다.
    나머지 값을 모두 합산하면 된다.
*/

long long solution(int n, vector<int> works) {
    long long answer(0);
    
    multiset<int> mySet;
    
    for (auto v : works) mySet.insert(v);
    for (auto iter = mySet.begin(); iter != mySet.end(); iter++) 
        cout << *iter << " "; 
    cout << endl;
    
    // 이제 제일 큰 값을 1씩 N번 깎을 것이다.
    for (int i = 0; i < n; i++) {
        // 위치를 잡아 1을 줄인다.
        auto iter = mySet.end(); iter--;
        int value = *iter - 1;
        // 만약 음수로 내려가면, 더 안 줄여도 된다,
        if (value == -1) continue;
        
        // 음수가 아니라면, 값을 삭제하고 다시 넣는다.
        mySet.erase(iter);
        mySet.insert(value);
    }
    
    
    // 남은 값을 모두 제곱해 더한다
    for (auto iter = mySet.begin(); iter != mySet.end(); iter++) {
        answer += (*iter) * (*iter);
    }
    
    return answer;
}
