#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
    4g를 5g로 바꾸려 한다.
    그런데, 이게 좀 좁아서 바꾸면 전파가 도달하지 않는 아파트가 생긴다.
    
    몇 개의 전파탑을 더 세워야 모든 아파트에 5g가 터질까?
    그냥 안 터지는 곳 최대한 세우면 된다.
    근데 하나하나 체크하기는 값이 너무 많다.
    
    그래서 stations값을 기준으로 나아가야 한다.
    한 전파탑의 위치가 A라면, A - W부터 A + W까지 공급이 가능하다.
    그리고 하나의 전파탑은 최대 2W + 1개의 아파트에 전력 공급이 가능하다.
    
    따라서 idx = 0에서 시작하고, 각 전파탑을 보면서 그 차가 얼마나 되나 보면 된다
    
    예를 들어 W = 1, stations = [4, 11]이라면
    하나의 전파탑은 2W + 1 = 3개의 아파트에 전파 공급 가능
    
    idx = 0 station = 4
    따라서 3 ~ 5까지는 전파가 들어온다
    3 - 0 = 3이므로, 3개의 아파트에 전파를 공급해줘야 한다.
    하나의 전파탑으로 가능
    idx를 전파가 들어오는지 확인하지 못한 첫 아파트로 바꾼다(idx = 6)
    
    idx = 6, station = 11
    10 ~ 12까지는 전파가 들어온다
    10 - 6 = 4이므로 이 사이에는 2개의 전파탑 세워줘야 함
    idx = 13
    
    끝!
*/

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int idx = 1;
    int cover_range = (w * 2) + 1;
    
    for (int i = 0; i < stations.size(); i++) {
        // 일단, 지금 이미 존재하는 전파탑들을 기준으로 거기까지 몇 개를 세워야 할지 확인한다.
        int loc = stations[i];
        int min = stations[i] - w;
        int max = stations[i] + w;
        
        // 이 전파탑의 범위가 idx의 위치를 포함해준다면, 여기는 전파탑을 세울 필요 없음
        if (idx <= max && idx >= min) {}
        
        // 포함하지 않는다면, 전파탑을 몇 개 세워야 할지 구한다
        else {
            int range = min - idx;
            answer += ceil(float(range) / float(cover_range));
        }
        
        idx = max + 1;
    }
    
    // 전파탑을 다 봤다면, 이제 아파트 끝(n)과 현재 위치의 차를 구하고, 그 사이에 몇 개를 세워야 할지 구한다
    // 이미 전파 범위가 아파트 최대값을 넘어갔다면, 볼 필요 없음
    if (idx > n) {}
    // 그렇지 않다면, 좀 더 세워줘야 한다.
    else {
        int range = n - idx + 1;
        answer += ceil(float(range) / float(cover_range));
    }

    return answer;
}