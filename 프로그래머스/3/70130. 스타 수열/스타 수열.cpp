#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    부분수열은, x의 몇몇 원소를 제거하거나 제거하지 않고 원래 순서대로 유지했을 때 얻을 수 있는 새로운 수열이다.
    
    그리고 스타 수열은, x의 길이가 2 이상이고, 두 개씩 묶은 원소들의 교집합의 원소의 개수가 1 이상이어야 한다.
    그리고 두 개씩 묶은 원소는 서로 같은 값이면 안된다.
    
    가장 긴 스타 수열 내놓으시오
    
    길이는 최대 50만이다.
    그리고 스타 수열이 될 조건이 있는지 쭉 확인해야 함
    
    스타 수열은 결국 하나의 공통된 값을 가져야 하는 것이다. 따라서 등장 횟수가 많아야 함.
    그리고 앞 혹은 뒤에 같은 값이 나오지 않아야 한다.
    
    값을 하나씩 잡고 순회하자
    근데 값이 a의 길이까지라, 50만 * 50만이 된다....
    전부 순회는 말이 안 됨
    큰 값부터 순회하자
*/

bool comp_std(vector<int> a, vector<int> b) {
    return a[1] > b[1];
}

int solution(std::vector<int> a) {
    int answer = 0;
    
    vector<vector<int>> val_count;
    
    // 일단 초기값 추가
    for (int i = 0; i < a.size(); i++) val_count.push_back(vector<int>{i, 0});
    
    // 갯수 세기
    for (int i = 0; i < a.size(); i++) val_count[a[i]][1]++;
    
    sort(val_count.begin(), val_count.end(), comp_std);
    
    // 정렬 후 확인
    /// for (auto v : val_count) cout << v[0] << " : " << v[1] << endl;
    
    // 스타 수열이 불가능하다면(모두 같은 값이라면), 0을 돌려보낸다
    if (val_count[0][1] == a.size()) return 0;
    
    // 이제 제일 많이 나온 값부터 확인한다
    for (int i = 0; i < val_count.size(); i++) {
        int val = val_count[i][0];
        int tmp_answer = 0;
        
        // A B A가 있을때, AB가 쌍이 되고, BA가 다시 쌍이 되는 일을 막기 위한 변수
        int last_usedVal = -1;
        
        // 근데, 최대값보다 작은 값들만 남았다면 이제 해볼 필요 없음
        if (val_count[i][1] <= answer) break;
        
        for (int j = 0; j < a.size(); j++) {
            // 일단, 목표값을 찾는다
            if (a[j] == val) {
                // 값을 찾았다면, 먼저 앞의 값을 본다.
                // 앞의 값이 나와 같지 않다면, 스타 수열에 넣는다.
                if (j != 0 && a[j - 1] != val && last_usedVal != j - 1) {
                    tmp_answer++;
                    continue;
                }
                
                // 앞의 값을 못 본다면, 뒤를 본다
                if (j != a.size() - 1 && a[j + 1] != val) {
                    tmp_answer++;
                    last_usedVal = j + 1;
                    continue;
                }
            }
        }
        
        // for문 다 봤다면, 값을 등록한다
        if (answer < tmp_answer) answer = tmp_answer;
    }

    return answer * 2;
}