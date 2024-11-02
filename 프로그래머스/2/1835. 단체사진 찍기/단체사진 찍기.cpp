#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <iostream>


using namespace std;

/*
    겨울을 맞은 카카오프렌즈 귀 여 워
    
    마지막에 단체사진을 위해 카메라 앞에 섰다! 근데 네오는 프로도와 같이 서고 싶고, 라이언은 튜브에게서 세 칸 떨어져 찍고 싶다
    각 프렌즈가 원하는 조건을 입력으로 받고, 모든 조건을 만족하도록 하는 경우의 수를 세보자.
    
    그냥 모든 방법으로 세워보고, 다 세운 다음에 조건 100개 다 비교하면 된다
    모든 방법으로 세우는 수 7! = 40,320가지, 그리고 조건 100개씩이면 4,032,000가지이므로 10^6에서 처리된다.
*/

// backTrack을 통해 세우는 모든 방법을 확인하는 함수
/*
    vector<string> data             주어진 입력
    string person_list              사람 리스트, (ACFJMNRT)
    unordered_map<char, int> locs   어떤 사람이 몇 번째 자리에 서있는지 저장
    vector<bool> inLine             어떤 사람이 이미 줄에 섰는지 확인
    int index                       이번에 몇 번째 사람을 세우는건지 확인
    int answer                      가능한 경우의 수를 저장하기 위한 int
*/

bool flag = true;

void backtrack(const vector<string> &data, const string person_list, unordered_map<char, int> &locs, vector<bool> &inLine, int index, int &answer) {
    // index가 8이라면, 여덟 명 다 세운 것이므로 모든 조건을 확인한다.
    if (index == 8) {
        bool possible = true;
        for (auto v : data) {
            // 먼저, 대상이 되는 두 명을 파악한다
            char a = v[0];
            char b = v[2];
            // 그 둘의 거리 차를 파악한다
            int loc_diff = abs(locs[a] - locs[b]) - 1;
            int val_condition = v[4] - '0';

            // 조건을 파악한다. 
            char condition = v[3];
            
            // 거리가 이것 미만이어야 하는 것
            if (condition == '<' && loc_diff >= val_condition) {
                possible = false;
                break;
            }
            
            // 거리가 val_condition 이상이어야 함
            else if (condition == '>' && loc_diff <= val_condition) {
                possible = false;
                break;
            }
            
            // 거리가 val_condition과 같아야 함
            else if (condition == '=' && loc_diff != val_condition) {
                possible = false;
                break;
            }
        }
        
        // 모든 조건 확인했는데 문제 없다면, answer 증가시키기
        if (possible) answer++;        
        return;
    }
    
    // index가 8이 아니라면, 다른 사람을 세워야 하는 것이므로 아직 안 선 사람을 이번 자리에 모두 세워본다.
    for (int i = 0; i < 8; i++) {
        // 이번 사람이 아직 안 섰다면, 요 자리에 세워본다.
        if (!inLine[i]) {
            inLine[i] = true;
            locs.insert({person_list[i], index});
            
            backtrack(data, person_list, locs, inLine, index + 1, answer);
            
            inLine[i] = false;
            locs.erase(person_list[i]);
            
        }
    }
    
    return;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    vector<bool> inLine(8, false);
    string person_list = "ACFJMNRT";
    unordered_map<char, int> locs;
    
    backtrack(data, person_list, locs, inLine, 0, answer);
    
    return answer;
}