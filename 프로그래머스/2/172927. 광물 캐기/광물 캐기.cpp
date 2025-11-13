#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    다이아몬드, 철, 돌 곡괭이 0 ~5개 있다.
    광물 캐면 피로도 소모한다.
    
    최소한의 피로도로 광물을 캐자!
    한번 사용하기 시작한 곡괭이는 사용할 수 없을 때까지 쭉 써야 함
    광물은 주어진 순서대로만 캘 수 있음
    광산의 모든 광물을 캐거나, 곡괭이를 다 쓸 때까지 광물을 캔다.
    
    광물은 다섯개 캘 수 있음
    일단. 각 구간별로 캐면 얼마가 드는지 본다.
    
    cost[i][j]는, i번째 구간을 j곡괭이로 캤을 때의 피로도이다.
    
    피로도가 높은 구간을 완화하는 게 가장 유효하므로, 가장 피로도가 큰 구간부터 다이아를 쓰면 됨
*/

bool comp_std(vector<int> a, vector<int> b) {
    return a[0] > b[0];
}

vector<int> mineralsToInt(vector<string> minerals) {
    vector<int> result;
    for (auto v : minerals) {
        if (v.substr(0, 2) == "di") result.push_back(2);
        else if (v.substr(0, 2) == "ir") result.push_back(1);
        else if (v.substr(0, 2) == "st") result.push_back(0);
    }
    
    return result;
}

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    
    // 몇 번 가능한가?
    int length = minerals.size() / 5;
    if (minerals.size() % 5 != 0) length++;
    
    // 광물 길이와 곡괭이의 개수 중 더 짧은 쪽으로 한다.
    int pickCount = 0;
    for (auto v : picks) pickCount += v;
    length = pickCount > length ? length : pickCount;
    
    // 광물 일단 숫자로 변환
    vector<int> iMinerals = mineralsToInt(minerals);
    
    // for (auto v : iMinerals) cout << v << " "; cout << endl;
    
    // 각 구간을 특정 곡괭이로 캤을 때의 피로도 정리
    vector<vector<int>> tiredCost(length, vector<int>(3, 0));
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 5; k++) {
                int index = i * 5 + k;
                
                if (index >= iMinerals.size()) break;

                int materialDiff = iMinerals[index] - j > 0 ? iMinerals[index] - j : 0;
                tiredCost[i][j] += static_cast<int>(pow(5, materialDiff));
            }
        }
    }
    
    // 출력
    // for (int i = 0; i < tiredCost.size(); i++) {
    //     cout << i + 1 << "번째 구간" << endl;
    //     for (int j = 0; j < 3; j++) {
    //         cout << j << " : " << tiredCost[i][j] << endl;
    //     }
    //     cout << endl << endl << endl;
    // }
    
    // 돌 곡괭이를 썼을 때 피로도가 큰 순으로 정렬한다.
    sort(tiredCost.begin(), tiredCost.end(), comp_std);
    
    // 이제 곡괭이 사용한다
    for (int i = 0; i < tiredCost.size(); i++) {
        // 다이아 사용 가능한가? 그럼 사용
        if (picks[0]) {
            picks[0]--;
            answer += tiredCost[i][2];
        }
        
        // 철 사용 가능한가? 사용
        else if (picks[1]) {
            picks[1]--;
            answer += tiredCost[i][1];
        }
        
        // 다 안되면, 돌 사용
        else {
            answer += tiredCost[i][0];
        }
    }
    
    return answer;
}