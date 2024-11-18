#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
    무료 셔틀버스 있다! 크루들이 이걸 운전한다.
    
    09:00부터 n회, t분 간격으로 도착하고, 한 셔틀에는 최대 m명이 탈 수 있다.
    
    도착했을 때 대기 순서대로 태우고 바로 출발. 09:00출발 셔틀에는 09:00대기자도 탈 수 있다.
    콘이 너무 너무 귀찮아서 모든 크루의 도착시간을 알아냈다. 콘이 사무실로 가는 시간 중 제일 늦은 시간을 구하자.
    대신, 콘은 게을러서 같은 시간에 도착한 크루 중 제일 뒤에 선다. 그리고 시간은 23:59를 넘어가지 않는다.
    
    시간별로 사람들이 정렬되도록 pq에 사람들을 정렬하고, 버스가 올때마다 가능한 인원만큼 pq에서 빼본다.
    만약 자리가 남았다? 그럼 거기가 출근 가능한 제일 늦은 시간이다.
*/

// string인 time을 int로 바꿔준다.
int time_to_int(string time) {
    // string에서 시, 분을 추출 (HH:MM)
    string sHour = time.substr(0, 2);
    string sMin = time.substr(3, 2);

    // 값을 int로 변경
    int nHour = stoi(sHour);
    int nMin = stoi(sMin);
    
    // 이걸 더해서 반환
    return nHour * 60 + nMin;
}

string time_to_str(int time) {
    string sResult = "";
    // 먼저 시를 넣는다. 근데 10이하의 값이면 0을 먼저 넣고 넣어줘야 함
    if (time / 60 < 10) sResult += '0';
    sResult += to_string(time / 60);
    
    sResult += ':';
    
    // 그리고 분을 넣는다. 역시 10이하 값이면 0 넣어줘야 함
    if (time % 60 < 10) sResult += '0';
    sResult += to_string(time % 60);
    
    return sResult;
}

string solution(int n, int t, int m, vector<string> timetable) {
    int answer(0);
    
    // 사람들의 출근시간을 내림차순(빠른 순)으로 정렬해 줄 것이다.
    priority_queue<int, vector<int>, greater<>> pq;
    
    // 모든 사람들을 pq에 넣는다
    for (auto time : timetable) {
        pq.push(time_to_int(time));
    }
    
    // 버스 첫 출발시간은 09:00 -> 540
    int bus_time = 540;
    
    for (int i = 0; i < n; i++) {
        // 이번 버스에 탈 수 있는 사람 수 세기
        int left_seat = m;
        
        // 이번 버스에 콘이 타기 위한 최대 시간을 구할 것이다. 이를 위해 딱 한자리 남았을때까지만 사람을 태워본다.
        while (!pq.empty() && pq.top() <= bus_time && left_seat > 1) {
            pq.pop();
            left_seat--;
        }
        
        // 이제 다음으로 온 사람을 봤을 때, 이 버스를 탈 수 없는 사람이라면 버스 시간에 맞춰서만 온다면 이걸 탈 수 있음
        if (pq.empty() || pq.top() > bus_time) answer = bus_time;
        
        // 근데, 한 자리 남았는데 다음 사람이 이 버스를 탈 수 있는 사람이라면. 이 사람보다는 1분 빨리 와야 함.
        else answer = pq.top() - 1;
        
        // 이제 다음 버스를 보기 위해 다음 사람을 태웠다 치고, 넘긴다
        if (pq.top() <= bus_time) pq.pop();
        
        // 다음 버스가 오는 시간을 본다.
        bus_time += t;
    }
    
    // 결과를 string으로 바꿔 반환해야 한다.
    string sAnswer = time_to_str(answer);
    return sAnswer;
}