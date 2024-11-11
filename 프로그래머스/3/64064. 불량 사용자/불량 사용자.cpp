#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    무지가 비정상적인 행위를 이용해 당첨을 시도한 응모자들을 발견했다. 이들을 불량 사용자라 한다.
    이들은 당첨 처리 시 제외하도록 프로도에게 전달한다.
    그런데, 개인정보 보호를 위해 아이디 중 일부를 *로 가렸다.
    
    무지는 블량 사용자 목록애 매핑된 아이디를 제재 아이디라고 부른다.
    제재 아이디 목록의 경우의 수를 Return하자.
    
    경우의 수라고 하면, 각 banned_id별로 가능한 user_id를 모두 찾은 후에
    가능한 경우의 수를 곱하면 된다! 단 같은 아이디가 여러 군데에 들어갈 수 있으니 이건 조심해야 함
    순서는 상관없다.
    
    유저아이디 최대 8개
    banned_id도 최대 8개
    각 배열의 크기는 1이상 8이하
    
    모두 비교하면 될 듯
    각 Banned_id별로 가능한 유저의 경우의 수를 모두 저장하는 vector<int>를 만들 것
    vector<vector<int>>를 만들자.
    
    그런데, 아이디의 나열 순서와 관계없이 목록이 동일하다면 하나로 세야 한다.
*/

/*
    각 마스킹 결과별 가능한 리스트들을 확인하며 경우의 수를 answer에 ++해주는 함수
    
    N               -> banned_id의 갯수
    possible_users  -> 각 마스킹 결과별 가능한 리스트
    used            -> 각 유저별로 이미 리스트에 포함되었는지의 여부
    answer          -> 모든 경우 저장(중복방지용 set)
    idx             -> 몇 번째 banned_id를 보고 있는지
    result          -> 지금까지 사용된 유저들의 목록
*/
void backTrack(const int N, const vector<vector<int>> &possible_users, vector<bool> &used, set<string> &answer, int idx, string result) {
    // 만약 idx가 N까지 도달했다면, 모든 banned_id에 해당되는 아이디를 배정해준 것이니 answer에 해당 값을 추가한다.
    if (idx == N) {
        // 넣기 전에는 중복 방지를 위해 sort수행
        sort(result.begin(), result.end());
        answer.insert(result);
        return;
    }
    
    // 아직 도달하지 못했다면, 이번 banned_id에 체크되는 모든 유저들을 체크한다
    for (auto user : possible_users[idx]) {
        // 만약 이번 유저가 이미 앞에서 사용되었다면, 다음 유저를 본다.
        if (used[user]) continue;
        
        // 사용되지 않았다면, 여기서 사용처리하고 다음으로 넘겨본다
        used[user] = true;
        string result_tmp = result;
        result_tmp += user + '0';
        backTrack(N, possible_users, used, answer, idx + 1, result_tmp);
        used[user] = false;
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    
    // banned_id별로 가능한 유저의 번호를 모두 저장하기 위한 배열
    vector<vector<int>> possible_users(banned_id.size());
    
    // banned_id별로 user_id를 체크하면서 이게 가능한 문자열인지 파악한다
    for (int i = 0; i < user_id.size(); i++) {
        string user = user_id[i];
        for (int j = 0; j < banned_id.size(); j++) {
            string banned = banned_id[j];
            // 일단, 글자수가 안 맞으면 체크할 필요가 없다
            if (user.length() != banned.length()) continue;
            
            // 글자수가 맞다면, 한 글자씩 보면서 틀린 부분이 없는지 체크한다.
            bool flag = true;
            for (int k = 0; k < user.length(); k++) {
                // 마스킹된 부분이라면, 이 부분은 비교할 필요 없음
                if (banned[k] == '*') continue;
                // 값이 다르다면, 그만 본다
                else if (banned[k] != user[k]) {
                    flag = false;
                    break;
                }
            }
            
            // 다 보고 나왔을 때, flag가 true라면 가능한 것
            if (flag) {
                possible_users[j].push_back(i);
            }
        }
    }
    // 모든 후보 목록 및 가능 후보 목록 출력
    /*
    for (auto iter = user_id.begin(); iter != user_id.end(); iter++) cout << *iter << " "; cout << endl;
    
    for (int i = 0; i < banned_id.size(); i++) {
        cout << banned_id[i] << " : ";
        for (auto v : possible_users[i]) cout << user_id[v] << " "; cout << endl;
    }
    */
    
    // 이제 가능한 모든 후보들을 봤다. 다음으로는 backtracking을 수행하면서 경우의 수를 따질 것
    int N = banned_id.size();
    vector<bool> used(N);
    set<string> answer;
    
    // void backTrack(const int N, const vector<vector<int>> &possible_users, vector<bool> &used, int &answer, int idx)
    backTrack(N, possible_users, used, answer, 0, "");
    
    return answer.size();
}