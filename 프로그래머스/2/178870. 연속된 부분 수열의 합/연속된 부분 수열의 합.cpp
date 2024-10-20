#include <string>
#include <vector>

using namespace std;

/*
    비내림차순(오름차순인데, 같은 값이 있음)으로 정렬된 수열이 있다. 부분 수열을 찾자
    
    1. 기존 수열에서 임의의 두 인덱스와 그 사이의 모든 값을 포함하는 부분 수열이어야 한다
    2. 합이 k이다
    3. 합이 k인 부분수열 중, 제일 짧은 것을 찾는다
    4. 제일 짧은 것도 여러개라면, 제일 앞에 있는 것을 찾는다.
    
    어떻게? window를 사용해서 밀 것인데, window의 사이즈가 가변적인 느낌으로!
    
    예를 들어 1 2 3 4 5가 있고 k = 7이라면?
    
    [1] 2 3 4 5 -> 합이 1이므로 윈도우 사이즈 추가
    [1 2] 3 4 5 -> 합이 3이므로 윈도우 사이즈 추가
    [1 2 3] 4 5 -> 합이 6이므로 윈도우 사이즈 추가
    [1 2 3 4] 5 -> 합이 10이므로, 윈도우 줄이기
    1 [2 3 4] 5 -> 합이 9이므로, 윈도우 줄이기
    1 2 [3 4] 5 -> 합이 7이므로 일단 당첨! 이제 다음 값을 본다(윈도우 사이즈 유지하고, 오른쪽으로 밀기)
    1 2 3 [4 5] -> 합이 9이므로 윈도우 줄이기
    1 2 3 4 [5] -> 합이 5이고, 윈도우를 더 늘릴 수 없으니 종료
*/

vector<int> slice_vector(vector<int> &target, int a, int b) {
    return vector<int>(target.begin() + a, target.begin() + b + 1);
}

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    
    // 일단 첫 사이즈를 1로 해두고 시작한다
    int front_idx(0), back_idx(0);
    int sum = sequence[0];
    while (back_idx < sequence.size()) {
        // 만약 현재 sum이 k보다 작다면, 윈도우를 증가시킨다.
        if (sum < k) {
            // 근데 더 이상 윈도우 확장이 불가능하다면, 그냥 그만하면 된다
            if (back_idx == sequence.size() - 1) break;
            
            sum += sequence[++back_idx];
        }
        
        // sum이 k보다 크다면, 윈도우를 감소시킨다
        // 대신에, 값 하나가 k보다 커버릴 수도 있으므로 이 경우에는 종료시킨다.
        // 종료시키는 이유는, 어차피 비내림차순이라 이것보다 더 가도 이보다 작은 값이 나올 일은 없기 때문
        else if (sum > k && front_idx == back_idx) {
            break;
        }
        
        // 그냥 크기만 하다면, 윈도우 감소
        else if (sum > k) {
            sum -= sequence[front_idx++];
        }
        
        // 만약 같다면???? 길이를 비교하고 answer에 집어넣기
        else if (sum == k) {
            // 만약 answer가 비어있는 상황이라면, 지금 찾은 것을 넣는다.
            if (answer.size() == 0) {
                answer.push_back(front_idx);
                answer.push_back(back_idx);
            }
            
            // 비어있지 않다면, 길이를 비교하고 집어넣는다
            else if (answer[1] - answer[0] > (back_idx - front_idx)) {
                answer[0] = front_idx;
                answer[1] = back_idx;
            }
            
            // 그 후에 윈도우를 뒤로 한 칸 밀어준다
            sum -= sequence[front_idx++];
            sum += sequence[++back_idx];
        }
    }
    return answer;
}