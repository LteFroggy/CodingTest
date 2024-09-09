#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    신청 순서대로 방을 배정한다
    원하는 방 번호를 제출
    원하는 방이 비어있다면, 배정
    이미 방이 차있다면, 번호가 크면서 가장 번호가 작은 방을 배정
    
    방은 아주 많고, 봐야 하는 개수는 최대 20만개
    어떤 방을 원할 때, 그 사람이 받을 수 있는 방을 저장하는 배열을 만든다.
    
    Union-Find이다.
*/

// A번 방을 원한 사람이 받을 수 있는 방을 찾아주는 함수
long long find(unordered_map<long long, long long>  &room_find, long long target) {
    // 먼저, 방 주인이 있는지 확인하고, 없다면 방을 배정해준 후 다음 방의 번호로 매칭해둔다.
    if (room_find.find(target) == room_find.end()) {
        room_find.insert({target, target + 1});
        return target;
    }
    
    // 방 주인이 이미 있다면, 찾으러 가야 한다.
    // 경로 압축까지 사용한다.
    return room_find[target] = find(room_find, room_find[target]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    int N = room_number.size();
    unordered_map<long long, long long> room_find;
    
    // 방 찾아준다
    for (auto room : room_number) answer.push_back(find(room_find, room));
    
    return answer;
}