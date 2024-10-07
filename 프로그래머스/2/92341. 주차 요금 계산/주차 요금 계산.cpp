#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iostream>

using namespace std;

/*
    주차요금 계산하기!
    주차요금은 5000 + (주차시간 - 180) / 10 * 600이다.
    
    기본시간, 요금, 단위시간, 요금 줄 것이다
    
    24시 단위이니, 앞 숫자에는 60을 곱하고 뒤의 값을 더하자.
    
    입차, 출차만 구분하면 된다. 출차가 없으면 2359로 하자
    낮은 순으로 구해야 하니, map을 쓰자.
*/

// delimeter 기준으로 split
vector<string> split(string target, char delimeter);

// 입차시간, 출차시간을 기준으로 비용을 계산해준다.
int calculate_fee(vector<int> fees, int time);

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    
    // 입차시간 기록하고 이를 바탕으로 금액 계산할 것
    unordered_map<string, int> in_time;
    
    // 각 차량별로 누적 시간 저장
    map<string, int> cumulative_time;
    
    for (int i = 0; i < records.size(); i++) {
        // 한 줄에 들어온 정보를 띄어쓰기 기준으로 분리
        vector<string> record_single = split(records[i], ' ');
        // 시간 정보는 HH:MM처럼 생겼으니 HH과 MM을 분리
        vector<string> time_info = split(record_single[0], ':');
    
        // HH * 60 + MM = 시간 이다
        int time = stoi(time_info[0]) * 60 + stoi(time_info[1]);
        string car_num = record_single[1];
        string type = record_single[2];
        
        // 입차면, 이걸 map에 넣는다.
        if (type == "IN") {
            in_time[car_num] = {time};
        }
        
        // 출차면, 입차 시간을 보고 금액을 계산해서 cumulate_time에 추가한다.
        else {
            // 시간 계산하기
            int parking_time = time - in_time[car_num];
            
            // 그리고 in_time에서 해당 열을 삭제한다
            in_time.erase(car_num);
            
            // 아직 전에 입차한 적이 없는 차량인 경우, 값을 생성해 넣는다.
            if (cumulative_time.find(car_num) == cumulative_time.end()) {
                cumulative_time.insert({car_num, parking_time});
            }
            
            // 전에 이미 입차했던 차량이라면, 그 비용에 값을 더한다
            else {
                cumulative_time[car_num] += parking_time;
            }
            
            /*
            cout << car_num << "출차함" << endl;
            cout << "현재까지 총 주차 시간은 " << cumulative_time[car_num] << endl;
            cout << "현재 in_time 배열 내부 : ";
            for (auto v : in_time) {
                cout << v.first << ", " << v.second << endl;
            }
            cout << endl;
            */
            
        }
    }
    
    // 출차시간이 없는 차량들의 경우, 23:59로 일괄적으로 처리해야 한다
    for (auto iter = in_time.begin(); iter != in_time.end(); iter++) {
        string car_num = iter->first;
        int in_time = iter->second;
        int out_time = (23 * 60) + 59;
        
        int time = out_time - in_time;
        
        // 아직 전에 입차한 적이 없는 차량인 경우, 값을 생성해 넣는다.
        if (cumulative_time.find(car_num) == cumulative_time.end()) 
            cumulative_time.insert({car_num, time});   
        // 입차한 적이 있다면, 그 값에 더해준다
        else 
            cumulative_time[car_num] += time;
    }
    
    // 이제, 순차적으로 출력한다.
    for (auto iter = cumulative_time.begin(); iter != cumulative_time.end(); iter++) {
        answer.push_back(calculate_fee(fees, iter->second));
        // cout << iter->first << " : " << calculate_fee(fees, iter->second) << endl;
    }
    
    return answer;
}


// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 함수 구현부 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

vector<string> split(string target, char delimeter) {
    stringstream ss(target);
    string tmp;
    vector<string> result;
    
    while (getline(ss, tmp, delimeter)) {
        result.push_back(tmp);
    }
    
    return result;
}

// 주차 비용을 계산해주는 함수
int calculate_fee(vector<int> fees, int time) {
    // 기본요금으로 시작한다.
    int fee(fees[1]);
    
    // 기본 시간 초과했다면, 추가 요금 부과
    if (time > fees[0]) {
        int exceed_time = time - fees[0];
        // 단위시간으로 나누고 거기다 요금을 곱해서 부과한다.
        fee += (exceed_time / fees[2]) * fees[3];
        // 나머지가 0이 아니라면, 올림에 의해 1 단위시간분의 요금을 더 부과한다.
        if (exceed_time % fees[2] != 0) fee += fees[3];
    }
    
    return fee;
}