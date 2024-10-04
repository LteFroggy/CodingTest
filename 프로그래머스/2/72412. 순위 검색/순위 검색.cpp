#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
    지원서에는 4가지 선택 항목이 있다
    1. cpp, java, python
    2. frontend, backend
    3. junior, senior
    4. chicken, pizza
    
    결과를 분석하여 지원 조건을 선택하면, 명수를 세야 한다.
    항상 조건을 만족하는 사람 중, X점 이상 받은 사람을 원한다.
    
    개발자는 50,000명 이하
    
    query는 1이상 100,000 이하이다!
    
    각 조건에 맞는 것을 제공해야 한다.
    미리 조건별로 점수만 정렬해두기?
    
    조건은 어떻게 편하게 할까?
    2진수 or로 처리하면 편할지도?
    
    cpp -> 0 (+0)
    java -> 1 (+8)
    python -> 10 (+16)
    
    backend -> 0 (+0)
    frontend -> 1 (+4)
    
    junior -> 0 (+0)
    senior -> 1 (+2)
    
    chicken -> 0 (+0)
    pizza -> 1 (+1)
    
    이렇게 처리하자. 다 붙일 것이다
    예를 들어 java + backend + senior + chicken = 8 + 2 = 1010 = 10이 된다.
    
    그리고 list[10]은 정렬된 점수들이 들어간다.
    
    결국 10111(23) ~ 0000까지의 값이 나올 수 있다는 것.
    그리고 뭔가 들어오면 이진탐색 한다
*/

// 10진수를 2진수로 변환해주는 함수
string int_conversion(int N) {
    string result = "";
    
    for (int i = 4; i >= 0; i--) {
        result += ((N >> i) & 1) + '0';
    }
    
    return result;
}

vector<string> split(string target, char delimeter) {
    stringstream ss(target);
    string tmp;
    vector<string> result;
    
    while (getline(ss, tmp, delimeter)) {
        result.push_back(tmp);
    }
    
    return result;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    
    // 기본값을 저장하기 위한 맵 생성
    unordered_map<string, int> setting;
    setting.insert({"cpp", 16});    // 10XXX
    setting.insert({"java", 8});    // 01XXX
    setting.insert({"python", 0});  // 00XXX
    setting.insert({"backend", 4}); // XX1XX
    setting.insert({"frontend", 0});// XX0XX
    setting.insert({"junior", 2});  // XXX1X
    setting.insert({"senior", 0});  // XXX0X
    setting.insert({"chicken", 1}); // XXXX1
    setting.insert({"pizza", 0});   // XXXX0
    
    vector<vector<int>> values(24, vector<int>());
    
    // 조건별로 일종의 버킷 만들기
    for (auto v : info) {
        vector<string> choices = split(v, ' ');
        int val_int = 0;
        
        
        // 총 5개의 요소, 그 중 4개는 선택지이므로 선택지를 바탕으로 val_int(들어갈 버킷 위치)를 결정한다.
        for (int i = 0; i < 4; i++) {
            /// cout << choices[i] << " "; 
            val_int += setting[choices[i]];
        } /// cout << endl;
        
        // 버킷에 값 집어넣기
        values[val_int].push_back(stoi(choices[4]));
    }
    
    // 이제 버킷들 정렬하기
    for (auto &v : values) sort(v.begin(), v.end());
    
    // 정렬 완료했으면, 조건을 하나씩 본다.
    // 조건을 보는 방법도 들어갈 Bucket을 보는 과정과 비슷하다.
    
    for (auto v : query) {
        int min = 0;
        int max = 0;
        int count = 0;
        
        /*
            1xx1만 만족하면 된다면?
            
            max = 1111    
            min = 1001
            & min은 만족해야 하고,
            | max도 만족해야 한다?
            
            와 max |는 같아야 한다?
            1001 -> min& = 1001, max| = 1111
            
            0XX1 min = 0001, max = 0111
            0011 -> min& = 0001, max| = 0111
            0001 -> min& = 0001, max| = 0111
            1001 -> min& = 0001, max| = 1111 (X)
            
            10XX1 min = 10001, max = 10111
            10111 min = 10001, max = 10111
            10101 min = 10001, max = 10111
            
            XX111 min = 00111, max = 11111
            10111 min = 00111, max = 11111
            01111 min = 00111, max = 11111
            00111 min = 00111, max = 11111
        */
        
        vector<string> choices = split(v, ' ');
        
        // -를 잘 고려해야 한다.
        for (int i = 0; i < choices.size(); i++) {
            // and가 포함되어있는데, 이건 그냥 넘기기
            if (choices[i] == "and") continue;
            
            // '-'인 경우에는, 몇 번째 자리인지 확인해서 max에 더해줘야 한다.
            else if (choices[i] == "-") {
                if (i == 0) max += 24;
                else if (i == 2) max += 4;
                else if (i == 4) max += 2;
                else if (i == 6) max += 1;
            }
            
            // 어떤 특정 값이 나왔다면, 이걸 min과 max에 다 더한다
            else {
                max += setting[choices[i]];
                min += setting[choices[i]];
            }
            
        }
        
        int target_score = stoi(choices[choices.size() - 1]);
        
        /// cout << "min = " << int_conversion(min) << ", max = " << int_conversion(max) << endl;
        /// cout << "조건을 만족하는 " << target_score << " 이상 점수 탐색" << endl;        
        
        // 이제 버킷 조건을 찾았다면, 0 ~ 23 사이의 값 중 해당 조건에 부합하는 값들 모두 뽑아와야 한다.
        for (int i = 0; i < 24; i++) {
            if ((min & i) == min && (max | i) == max) {
                /// cout << int_conversion(i) << "가 만족함" << endl;
                /// cout << "내부 상황 : ";
                // 먼저, 해당 bucket 내에서 lower_bound(같거나 큰 값의 최초 출현 위치)를 찾아낸다.
                int bound = int(lower_bound(values[i].begin(), values[i].end(), target_score) - values[i].begin());
                /// cout << "low_bound는 " << bound << endl;
                // 이제 이 값을 바탕으로, 몇 개가 조건을 만족하는지 탐색한다
                count += values[i].size() - bound;
            }
        }
        
        // 완료했다면, answer에 추가한다
        answer.push_back(count);
    }
    
    
    return answer;
}