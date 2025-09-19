#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    퍼즐게임 한다. n개의 퍼즐을 시간 내에 풀어야 함
    퍼즐은 난이도, 소요시간이 정해져있음
    
    퍼즐의 난이도 diff, 소요시간 time_cur, 이전 버즐 소요시간 time_prev, 숙련도 level
    
    diff <= level이면 틀리지 않고 time_cur만에 해결한다
    
    dif > level이면 퍼즐을 diff - level번 틀린다. 틀릴때마다 time_cur 만큼 시간 사용. 추가로 time_prev만큼의 시간을 써서 풀고 와야 한다.
    다시 풀 때는 틀리지 않음
    diff - level번 틀린 이후에 다시 퍼즐을 풀면 time_cur만에 풀고 온다
    
    시간 제한 내에 해결하기 위한 숙련도 최솟값 구하기
    이분탐색으로 하자. diffs의 최고값 기반으로 구하면 됨
*/

int solution(vector<int> diffs, vector<int> times, long long limit) {
    int answer = 0;
    
    // diff의 최댓값 찾기
    int left = 1;
    int right = 0;
    
    for (auto v : diffs) {
        if (right < v) right = v;
    }

    while (left < right) {
        int level = (left + right) / 2;
        long long time = 0;
        
        // mid값으로 진행해보기
        for (int i = 0; i < diffs.size(); i++) {
            // 이번 문제를 푸는데 걸리는 시간은, (diff - level) * (time_prev + time_now)
            if (i != 0 && diffs[i] > level) time += (diffs[i] - level) * (times[i - 1] + times[i]) + times[i];
            else time += times[i];
            
            if (time > limit) break;
        }
        
        // 끝났을 경우, 조건 만족 시 레벨 줄이기, 불만족 시 레벨 늘리기
        if (time <= limit) right = level;
        else left = level + 1;
    }
    
    return left;
}