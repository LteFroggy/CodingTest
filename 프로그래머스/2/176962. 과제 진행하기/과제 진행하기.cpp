#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

/*
    과제를 시작하기로 한 시간이 되면 시작한다.
    
    새로운 과제 시작 시간이 되었을 때, 기존 진행중인 과제가 있다면, 진행 중이던 과제 멈추고 새로운거 한다
    진행중이던 과제가 끝나면, 멈춰뒀던걸 다시 한다.
    멈춰둔 과제가 여러 개면, 가장 최근에 멈춘 것부터 다시 한다.
    
    과제 끝낸 순서대로 이름 담아 return한다.
*/

bool sort_std(vector<string> a, vector<string> b) {
    return stoi(a[1]) < stoi(b[1]);
}

string transformTime(string tmp) {
    int sum = 0;
    
    string hour = tmp.substr(0, 2);
    string min = tmp.substr(3, 2);
    
    sum += 60 * stoi(hour);
    sum += stoi(min);
    
    return to_string(sum);
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    
    // hh:mm 형식의 값을 분값으로 수정
    for (auto& plan : plans) {
        plan[1] = transformTime(plan[1]);
    }
    
    // 시작 시간 기준으로 정렬
    sort(plans.begin(), plans.end(), sort_std);
    
    // 남은 과제 목록
    stack<pair<string, int>> leftReports;
    
    // 이제 하나씩 시작시간 보면서 확인하기
    for (int i = 0; i < plans.size(); i++) {
        string subName = plans[i][0];
        int startTime = stoi(plans[i][1]);
        int neededTime = stoi(plans[i][2]);
        
        /// cout << subName << " 과제 시작" << endl;
        
        // 1. 다음 과제 시작시간 체크하기
        int nextStartTime;
        if (i == plans.size() - 1) nextStartTime = 1440;
        else nextStartTime = stoi(plans[i+1][1]);
        
        // 2. 과제 수행 가능 시간 구하기
        int spareTime = nextStartTime - startTime;
        
        // 3. 지금 과제 끝낼 수 있는가?
        if (neededTime <= spareTime) {
            // 먼저 지금 과제 끝내고 남는 과제 수행한다.
            int timeLeft = spareTime - neededTime;
            
            /// cout << "현재 과제 종료. 남은 시간은 " << timeLeft << endl;
            
            answer.push_back(subName);
            
            // 남는 과제 수행하기
            while (timeLeft && !leftReports.empty()) {
                string leftSubName = leftReports.top().first;
                int leftReportTime = leftReports.top().second;
                leftReports.pop();
                
                /// cout << leftSubName << " 과제 꺼내서 하기. " << leftReportTime << "분 더 해야 함" << endl;
                
                // 남는 시간에 과제 끝낼 수 있나?
                if (leftReportTime <= timeLeft) {
                    timeLeft -= leftReportTime;
                    answer.push_back(leftSubName);
                    
                    
                    /// cout << "완료, 남은 시간은 " << timeLeft << endl;
                }
                
                // 끝내지 못하나?
                else {
                    leftReportTime -= timeLeft;
                    timeLeft = 0;
                    
                    leftReports.push({leftSubName, leftReportTime});
                    
                    /// cout << "완료 못함. " << leftReportTime << "분 남아서 다시 푸시" << endl;
                }
            }
        }
        
        // 과제 끝내지 못했나?
        else {
            neededTime -= spareTime;
            
            /// cout << "완료 못함. " << neededTime << "분 남아서 푸시" << endl;
            
            // Queue에 넣어놓기
            leftReports.push({subName, neededTime});
        }
    }
    
    // 남은 과제 쭉 넣기
    while (!leftReports.empty()) {
        answer.push_back(leftReports.top().first);
        leftReports.pop();
    }
    return answer;
}