#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

/*
    K칸 건너뛸 수 있는 경우, i에서 i+K 로 갈 수 있음.
    
    그럼 가장 먼저 사라질 K개의 이어지는 값을 구하자.
    각 구간별 사라지는 Max값을 구한다.
    
    i ~ i + K중 가장 큰 값을 Rolling하면서 구해가면 됨
    Rolling에는 deque를 사용하자.
    
    왜 ?? 
    구간 내 가장 큰 값을 구하기 쉽기 때문.
    
    앞에서부터 뒤로 내림차순이 되도록 que를 구성한다.
    뒤에 나보다 작은 값이 있다면 빼버리고 내가 들어간다.
    
    예를 들어 3 5 2 4 2, K = 2라면
    3
    5 (3은 5보다 작으니 뺀다)
    5 2
    4 (5는 idx - 2번째 원소여서 빠지고, 2는 4보다 작아서 빠진다)
    4 2 
    매번 제일 앞에 있는 원소가 그 idx 내의 최대값이다.
    
    기본적으로 내림차순이 되도록 구성하니 최대값인건 이해되는데, 어떻게 idx - k이하의 원소가 내부에 남아있지 않음을 장담하는가?
    idx - k번쨰 원소가 가장 큰 값이었다면, 제일 앞에 있기 때문에 잘려나간다.
    그렇다고 제일 큰 값이 아니라면?? 그 다음 큰 값에 의해 잘려나가기 때문에 중간에 남아있을 수는 없다.
    따라서 idx - k번째 원소는 이미 사라졌거나, 제일 앞에 있음을 장담할 수 있다.
    
    index기준으로 저장할 것.
*/

int solution(vector<int> stones, int k) {
    int answer = 1e9;
    
    int idx(0);
    deque<int> dq;
    do {
        // 제일 앞 원소가 idx - k번째 값이라면, 자른다
        if (!dq.empty() && dq.front() == idx - k) {
            dq.pop_front();
        }
        
        // 이번 값을 제일 뒤에 넣을 것이다. 근데, 나보다 작거나 같은 값은 다 뺀다 (내림차순이 되도록)
        while (!dq.empty() && stones[dq.back()] <= stones[idx]) {
            dq.pop_back();
        }
        
        // 그리고, 내가 들어간다
        dq.push_back(idx);
        
        // idx >= K - 1이라면, 필요한 값은 다 들어간 것이다. 여기서부터 앞 값을 통해 answer를 갱신한다
        if (idx >= k - 1) {
            answer = min(answer, stones[dq.front()]);
        }
    } while (++idx < stones.size());
    
    return answer;
}