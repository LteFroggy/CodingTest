#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    일단 A점수 역순으로 정렬한다
    
    그 다음은 B점수 정순으로 정렬!
    
    B점수만 계속 보면서, B점수가 현재 최대값보다 작은 친구들은 다 죽는다.
    예를 들어
    3 2 -> 기준값(2)
    3 2 -> 최대값과 같음
    2 1 -> 최대값(2)보다 작음 -> 인센티브 탈락
    2 2 -> 최대값과 같음
    1 4 -> 최대값 갱신(4)
    
    4 4 -> 기준값(4)
    3 2 -> 탈락
    3 3 -> 탈락
    3 6 -> 기준값 갱신(6)
    2 4 -> 탈락
    2 5 -> 탈락
    1 2 -> 탈락
    1 3 -> 탈락
*/

bool comp_std(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) return a[1] < b[1];
    else return a[0] > b[0];
}

bool sum_based(vector<int> a, vector<int> b) {
    return a[0] + a[1] > b[0] + b[1];
}

int solution(vector<vector<int>> scores) {
    vector<int> myVal = scores[0];
    int answer = 0;
    
    vector<vector<int>> incentive_candidates;
    sort(scores.begin(), scores.end(), comp_std);
    int max_val = scores[0][1];

    for (auto v : scores) {
        // 현재 기준값(max_val)보다 낮은 값이 나온다면, 바로 탈락
        if (v[1] < max_val) {
            // 근데 탈락한게 나라면, -1을 바로 return한다
            if (v == myVal) return -1;
            continue;
        }
        
        // 기준값을 갱신할 여지가 있다면, 갱신
        else if (v[1] > max_val) {
            max_val = v[1];
        }
        
        // 탈락하지 않은 친구들은 인센티브 후보에 넣어주기
        incentive_candidates.push_back(v);
    }
    
    // 남은 후보들 점수합순 정렬
    sort(incentive_candidates.begin(), incentive_candidates.end(), sum_based);
    
    /*
    // 남은 후보들 보기
    for (auto v : incentive_candidates) {
        for (auto v_ : v) cout << v_ << " ";
        cout << endl;
    }
    */
    
    // 내가 나올때까지 탐색한다
    int ranking = 0;
    int tie_count = 0;
    int score = 0;
    int idx = 0;
    
    for (auto person : incentive_candidates) {
        // 첫 사람이면, 1등이다. 기준점수가 됨
        if (score == 0) {
            ranking = 1;
            tie_count = 1;
            score = person[0] + person[1];
        }
        
        // 두 번째 사람부터는 점수 비교한다
        else {
            // 점수가 같다면, tie_count만 늘어난다
            if (score == person[0] + person[1]) {
                tie_count++;
            }
            
            // 점수가 다르면, 순위가 늘어난다
            else {
                score = person[0] + person[1];
                ranking += tie_count;
                tie_count = 1;
            }
        }
        
        // 만약 나라면, 이 값을 리턴하면 된다!
        if (person == myVal) {
            answer = ranking;
            break;
        }
    }
    
    
    return answer;
}