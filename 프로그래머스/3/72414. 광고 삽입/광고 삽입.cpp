#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    시청시간을 누적합 하면 된다.
    슬라이딩 윈도우로 밀어가면서..
*/

// 광고 시작 시간의 오름차순으로 값 정렬하기.
bool comp_std(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

// 시간을 int값으로 바꿔주는 함수
int time_to_val(string a) {
    string time = a.substr(0, 2);
    string minute = a.substr(3, 2);
    string second = a.substr(6, 2);
    
    return stoi(time) * 3600 + stoi(minute) * 60 + stoi(second);
}

// int값을 시간으로 바꿔주는 함수
string val_to_time(int a) {
    string result = "";
    
    // 시간 처리
    int time = a / 3600;
    a %= 3600;
    if (time < 10) result += '0';
    result += to_string(time);
    result += ':';
    
    // 분 처리
    int minute = a / 60;
    a %= 60;
    if (minute < 10) result += '0';
    result += to_string(minute);
    result += ':';
    
    if (a < 10) result += '0';
    result += to_string(a);
    
    return result;
}

string solution(string play_time, string adv_time, vector<string> logs) {    
    int iPlaytime = time_to_val(play_time);
    int iAdvtime = time_to_val(adv_time);
    
    vector<vector<int>> iLogs(logs.size(), vector<int>(2, 0));
    
    // logs를 먼저 int값으로 변경해둔다
    for (int i = 0; i < logs.size(); i++) {
        iLogs[i][0] = time_to_val(logs[i].substr(0, 8));
        iLogs[i][1] = time_to_val(logs[i].substr(9, 8));
    }
    
    // 정렬한다
    sort(iLogs.begin(), iLogs.end(), comp_std);
    
    /*
    // 확인하기
    for (int i = 0; i < logs.size(); i++) {
        cout << val_to_time(iLogs[i][0]) << " ~ " << val_to_time(iLogs[i][1]) << " : ";
        cout << iLogs[i][0] << " ~ " << iLogs[i][1] << endl;
    }
    */
    
    // 누적합을 위한 배열 만들기
    vector<int> prefix_sum(iPlaytime + 1, 0);
    
    // 각 사용자들의 시청 기록 기반으로 누적합 적용하기
    for (auto v : iLogs) {
        prefix_sum[v[0]]++;
        prefix_sum[v[1]]--;
    }
    
    // 누적합 풀기
    for (int i = 1; i <= iPlaytime; i++) {
        prefix_sum[i] += prefix_sum[i - 1];
    }
    
    // 이제 광고 시작 시간을 00:00:00으로 설정하고 초기값 구하기
    int iAnswer = 0;
    
    int adv_startTime = 0;
    int adv_endTime = iAdvtime;
    long long maxVal = 0;
    for (int i = 0; i < iAdvtime; i++) {
        maxVal += prefix_sum[i];
    }
    
    long long valNow = maxVal;
    // 이제 광고 시간을 1초씩 밀어가면서 maxVal이 갱신되는 지점을 찾으면 된다.
    while (adv_endTime < iPlaytime) {
        // 시작시간, 끝나는시간을 1초씩 민다
        adv_startTime++;
        adv_endTime++;
        
        // 값을 수정한다
        valNow -= prefix_sum[adv_startTime - 1];
        valNow += prefix_sum[adv_endTime - 1];
        
        // 최대값이 갱신되었는지 확인한다
        if (valNow > maxVal) {
            maxVal = valNow;
            iAnswer = adv_startTime;
        }
    }
    
    // 다 봤다면, 결과를 반환한다
    return val_to_time(iAnswer);
}