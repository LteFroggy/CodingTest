#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    무지 먹방한다.
    
    N개의 먹어야 할 음식이 있고, 각 음식을 섭취하는 데에 일정 시간이 소요된다.
    무지는 1번부터 먹고, 회전판은 번호 증가 순서대로 무지 앞으로 음식을 가져다 둠
    마지막 번호를 먹으면 회전판에 의해 1번이 다시 온다.
    
    무지는 1초동안 음식 하나를 먹고, 남은건 그대로 두고 다음 음식을 먹는다.
    다음 음식은 남은 음식 가장 가까운 번호의 음식을 말함!
    회전판이 다음 음식을 무지 앞으로 가져오는 데에 걸리는 시간은 없다고 치자.
    
    헉! 먹방 시작했다가 K초 후에 방송 멈췄다
    네트워크 정상화하고 다시 방송을 이어갈 때, 몇 번 음식부터 먹어야 할까??
    
    당연히 하나하나 체크는 불가능하다. 가장 먼저 사라질 음식을 찾는 것이 중요
    priority_queue로 체크하자.
*/

int solution(vector<int> food_times, long long k) {
    int answer = -1;
    priority_queue<int, vector<int>, greater<>> que;
    
    for (auto v : food_times) que.push(v);
    
    cout << que.top() << endl;
    cout << que.size() << endl;
    
    long long time_passed = 0;
    int loop_passed = 0;
    
    // 계속 반복 순회할 것
    while (!que.empty()) {
        // 먼저, 제일 조금 남은 음식과 남은 음식 갯수를 구한다.
        int min_val = que.top();
        int food_count = que.size();
        
        // 그 음식 다 먹을때까지 타이머 체크하면서 돈다.
        while (loop_passed < min_val) {
            // 그래도 중간에 돌 때는 넘어가지 않는지 확인해야 함
            if (time_passed + food_count > k) {
                // 만약에 넘어가게 된다면 그만 보기
                break;
            }
            
            // 아직 종료 시간에 도달하지 못했다면, 한 바퀴 돌린다
            else {
                time_passed += food_count;
                loop_passed++;
            }
        }
        
        // 현재 가장 적게 남은 음식을 다 먹어서 나온거라면, 음식 갯수를 수정한다.
        if (loop_passed >= que.top()) {
            while (!que.empty() && loop_passed >= que.top()) {
                que.pop();
            }
        }
        
        // 이번 바퀴에 답이 나오는 상황이라면, 한 바퀴 돌면서 수를 센다.
        else {
            for (int i = 0; i < food_times.size(); i++) {
                // 이 음식이 아직 남았는가? 확인
                if (food_times[i] > loop_passed) {
                    // 만약 지금이 방송 끊어진 시점이라면, 이거 먹을 차례라고 리턴하면 된다.
                    if (time_passed == k) {
                        answer = i + 1;
                        break;
                    }
                    
                    // 음식 남았다면, 1초 추가한다.
                    else time_passed++;
                }
            }
            break;
        }
    }
    
    
    return answer;
}