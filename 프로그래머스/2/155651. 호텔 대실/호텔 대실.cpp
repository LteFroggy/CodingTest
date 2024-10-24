#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    최소한의 객실만 쓰자!
    최소 객실의 수를 return 해주세요
    
    ### 틀린 풀이 ####
    종료 시간 기준 정렬한다.
    종료 시간에 안 맞으면, 방 하나 더 써야 한다.
    
    ### 시작 시간 기준 정렬해야 한다 ####
    
    
    시작 시간 기준 정렬과 종료 시각 기준 정렬의 차이
    
    - 시작 시간 기준 정렬
    시작 시간 기준 정렬은 회의실 배정 문제에서 가능한 한 오래 회의실을 사용하는 상황을 풀기에 적합하다.
    시작 시간 기준으로 정렬했기 때문에 시작을 앞당길 수 있기 때문. 또한 다음 회의도 시작 시간을 기준으로 들어가기 때문에 남는 시간을 최소화할 수 있다.
    ex, 이전 회의가 8시에 끝나는데, 9~13인 회의와 10~12인 회의가 있다면 종료 시간 기준으로는 10~12가 들어간다. 이러면 가동률이 떨어짐
        대신, 시작 시간 기준을 쓰면 9 ~ 13이 들어갈 수 있다.
    
    또한 시작 시간을 기준으로 확인하기 때문에, 이전 회의와 겹치는지의 여부를 쉽게 판단할 수 있다.
    따라서 충돌 방지에 적합함. 이 문제는 최대한 방을 적게 써야(충돌을 줄여야)하므로 이것을 사용해야 한다.
    
    
    
    - 종료 시각 기준 정렬
    Greedy한 접근으로, 회의를 최대한 많이 배정하는 데에 유리하다.
    하나의 @@로 최대한 많은 @@를 처리하는 문제에서 사용하기 적합함
    끝나는 시간 기준으로 정렬을 수행하면, 가장 빨리 끝나는(뒤쪽에 공간을 가장 많이 남기는)친구를 먼저 선택하여 적용할 수 있기 때문
    빨리 끝날수록 뒤에 회의가 많이 배치될 확률 역시 올라간다. 그때그때 가장 공간을 많이 남기는 선택을 하기 때문에 greedy임
*/

// HH:MM의 string을 [hh, mm]의 vector<string>으로 쪼개준다.
vector<string> split(string a, char deli);

// HH:MM값을 split을 통해 나누고, h * 60 + m을 수행해 반환한다.
int time_to_int(string time);

// 시작 시간 기준으로 정렬할 수 있도록 하는 정렬 기준
bool comp(vector<string> a, vector<string> b);


int solution(vector<vector<string>> book_time) {
    
    // 일단, 들어오는 시간 기준으로 정렬하기
    sort(book_time.begin(), book_time.end(), comp);
    
    // 출력부
    /*
    for (auto v : book_time) {
        for (auto v_ : v) {
            cout << v_ << " ";
        }
        cout << endl;
    }
    */
    
    // priority_queue를 이용해 방을 관리할 것!
    // 제일 먼저 사용이 종료되는 방을 직관적으로 관리하기 편하기 때문.
    // 대신, 값이 작은 순으로 정렬되어야 하므로 greater<>를 기준으로 사용
    priority_queue<int, vector<int>, greater<>> rooms;
    
    // 이제 방을 하나씩 넣으면서 필요한 방 개수를 관리한다
    for (auto book : book_time) {
        // 일단 이번 예약 들어온 손님의 시작 시간과 끝나는 시간을 본다
        // 끝나는 시간에 10을 더하는 이유는 퇴실 청소에 10분이 걸리기 때문
        int start_time = time_to_int(book[0]);
        int end_time = time_to_int(book[1]) + 10;
        
        // cout << "사용 시작 시간 : " << start_time / 60 << ":" << start_time % 60 << endl;
        // cout << "사용 종료 시간 : " << end_time / 60 << ":" << end_time % 60 << endl;
        
        // 아직 객실을 하나도 안 쓴 상황이라면, 새 객실을 사용한다.
        if (rooms.empty()) {
            rooms.push(end_time);
            // cout << "방이 없으므로 방 추가" << endl << endl;
            continue;
        }
        
        // 객실이 하나 이상 있다면, 이미 사용한 방 중에 가장 빨리 끝나는 방에 이번 손님을 넣을 수 있는지 확인한다
        // 넣을 수 있다면, 거기다 집어 넣는다!
        if (start_time >= rooms.top()) {
            // cout << "현재 " << rooms.top() / 60 << ":" << rooms.top() % 60 << "에 끝나는 방이 있어 거기 넣음" << endl;
            rooms.pop();
            rooms.push(end_time);
        }

        // 아직 그 방 사용이 끝나지 않아서 넣을 수 없다면, 새 방을 만들어 넣는다.
        else {
            // cout << "방이 끝나지 않아 방 추가" << endl;
            rooms.push(end_time);
        }
        cout << endl;
    }
    
    // 마지막에 사용된 방 수를 보면 된다!
    return rooms.size();
}


/* ㅡㅡㅡㅡㅡ 함수 구현부 ㅡㅡㅡㅡㅡ */

// HH:MM의 string을 [hh, mm]의 vector<string>으로 쪼개준다.
vector<string> split(string a, char deli) {
    stringstream ss(a);
    string tmp;
    vector<string> result;
    
    while (getline(ss, tmp, deli)) {
        result.push_back(tmp);
    }
    
    return result;
}

// HH:MM값을 split을 통해 나누고, h * 60 + m을 수행해 반환한다.
int time_to_int(string time) {
    vector<string> h_m = split(time, ':');
    
    return 60 * stoi(h_m[0]) + stoi(h_m[1]);
}


// 시작 시간 기준으로 정렬할 수 있도록 하는 정렬 기준
bool comp(vector<string> a, vector<string> b) {
    return time_to_int(a[0]) < time_to_int(b[0]);
}