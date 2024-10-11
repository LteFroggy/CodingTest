#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*
    앞의 감시카메라와 같은 방법으로 수행하면 될 듯.
    종료시간 순으로 정렬하고, 그 친구 끝나는 시점에 요격 설치
    근데 끝에서 딱 맞추면 안사라짐
    그래서 0.5 앞으로 땡겨서 쏴주면 될듯. 어차피 미사일은 정수 값에서만 나오기때문에 별 상관 없음
*/

bool sorting(vector<int> a, vector<int> b) {
    if (a[1] < b[1])
        return true;
    else 
        return false;
}
    
int solution(vector<vector<int>> targets) {
    int answer = 0;
    
    sort(targets.begin(), targets.end(), sorting);
    
    /*
    cout << "after sorting" << endl;
    vector<vector<int>>::iterator iter;
    
    for (iter = targets.begin(); iter != targets.end(); iter++) {
        vector<int> v = *iter;
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    */
    
    // 여기서부터 정렬할 것
    int position_now = -1;
    
    for (int i = 0; i < targets.size(); i++) {
        if (targets[i][0] >= position_now) {
            answer += 1;
            position_now = targets[i][1];
        }
    }
    
    return answer;
}