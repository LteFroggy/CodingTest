#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

/*
    우선순위 큐
    큐가 비어있으면 0,0 
    비어있지 않으면 최대, 최소를 return
    
    두 개의 우선순위 큐 쓰기 (큰순위, 작은순위)
    근데, 하나에서 삭제된 걸 반대편에선 어떻게 인식할까??
    인식까진 아니어도, 유효한 값인지 확인하기 위해 별도 Map을 사용한다.
*/

vector<string> split(string target, char deli = ' ') {
    stringstream ss(target);
    vector<string> result;
    string tmp;
    
    while (getline(ss, tmp, deli)) {
        result.push_back(tmp);
    }
    
    return result;
}

class double_heap {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<>> minHeap;
    unordered_map<int, int> map_count;
    int size = 0;

public:
    int getSize() {
        return size;
    }
    
    void insert(int v) {
        maxHeap.push(v);
        minHeap.push(v);
        size++;
        
        if (map_count.find(v) == map_count.end()) map_count.insert({v, 1});
        else map_count[v]++;
    }
    
    int getMax() {
        // maxHeap에서 제일 큰 값을 찾는다.
        int result = 0;
        while (!maxHeap.empty()) {
            // 아직 남아있는 값이면, 이걸 반환하고 map_count를 하나 줄인다.
            if (map_count[maxHeap.top()] != 0) {
                result = maxHeap.top();
                map_count[result]--;
                
                size--;
                return result;
            }
            // 이제 없는 값이라면, 삭제하고 다음 값을 본다
            else {
                maxHeap.pop();
            }
        }
        
        return result;
    }
    
    int getMin() {
        // minHeap에서 제일 작은 값을 찾는다.
        int result = 0;
        while (!maxHeap.empty()) {
            // 아직 남아있는 값이면, 이걸 반환하고 map_count를 하나 줄인다.
            if (map_count[minHeap.top()] != 0) {
                result = minHeap.top();
                map_count[result]--;
                
                size--;
                return result;
            }
            // 이제 없는 값이라면, 삭제하고 다음 값을 본다
            else {
                minHeap.pop();
            }
        }
        
        return result;
    }
};

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    double_heap myDouble;
    
    // 각 값에 대해서 동작을 수행한다
    for (auto v : operations) {
        vector<string> tmp = split(v);
        
        // 삽입하기
        if (tmp[0] == "I") {
            myDouble.insert(stoi(tmp[1]));
        }
        
        else if (tmp[0] == "D") {
            // 값이 하나도 없으면, 아무 동작도 하지 않음
            if (myDouble.getSize() == 0) continue;
            
            // 값이 하나라도 있다면, 큰거나 작은것 중 할 일 함
            if (tmp[1] == "1") myDouble.getMax();
            else myDouble.getMin();
        }
    }
    
    // 값이 하나도 안 남았으면, 둘다 0 넣어주기
    if (myDouble.getSize() == 0) {
        answer.push_back(0);
        answer.push_back(0);
    }
    // 값이 하나만 남았으면, 그걸로 둘 다 넣어주기
    else if (myDouble.getSize() == 1) {
        int tmp = myDouble.getMax();
        
        answer.push_back(tmp);
        answer.push_back(tmp);
    }
    
    // 값이 두 개 이상 남았다면, 큰값 작은값 각각 넣어주기
    else {
        answer.push_back(myDouble.getMax());
        answer.push_back(myDouble.getMin());
    }
    return answer;
}