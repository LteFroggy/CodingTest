#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    디스크 컨트롤러는 대기 큐가 있다.
    작업 없으면 대기 큐에서 소요시간, 요청시간, 번호 작은것 순으로 우선순위 본다
    
    nonpreemtive함
    
    컨텍스트 스위칭 오버헤드는 아예 없다
    
    어떤 시점에 어떤 작업을 할지 고르는 게 제일 중요하다.
    그렇다고 맘대로 정렬 하는것도 애매함, 작업 번호를 기억해놔야 하기 때문
    작업 번호 기억이 중요한가? 어차피 turnaround time이 메인인데, 상관없다.
    
    힙으로 하는거구나.. priority_queue 사용한다.
*/

// jobs를 시간순으로 정렬한다
bool comp_jobs(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

// 대기 큐 내부 정렬 방법 작성
struct comp_std {
    bool operator()(vector<int> a, vector<int> b) {
        if (a[1] == b[1]) return a[0] > b[0];
        else return a[1] > b[1];
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    priority_queue<vector<int>, vector<vector<int>>, comp_std> waiting_queue;
    
    // 작업 큐 소팅
    sort(jobs.begin(), jobs.end(), comp_jobs);
    // 소팅 결과 확인
    for (auto v : jobs) cout << v[0] << ", " << v[1] << endl;
    cout << endl;
    
    int time_now = 0;
    int idx = 0;
    
    do {
        // cout << "시간 " << time_now << "반복" << endl;
        // 현재 시간에 대기 큐에 들어올 수 있는 모든 작업 삽입
        while (idx < jobs.size() && time_now >= jobs[idx][0]) {
            waiting_queue.push(jobs[idx]);
            idx++;
            
            // cout << "시간 : " << time_now << endl;
            // cout << "큐 사이즈 : " << waiting_queue.size() << endl;
        }
        
        // 대기 큐 제일 앞 작업 수행
        if (!waiting_queue.empty()) {
            int job_requested = waiting_queue.top()[0];
            int job_required = waiting_queue.top()[1];
            waiting_queue.pop();

            time_now += job_required;
            answer += time_now - job_requested;   
        }
        
        // 할 작업이 없다면, 그냥 시간 보낸다
        else time_now++;
    } while (!waiting_queue.empty() || idx < jobs.size());
    
    // 마지막에 평균값을 구한다
    answer /= jobs.size();
    return answer;
}