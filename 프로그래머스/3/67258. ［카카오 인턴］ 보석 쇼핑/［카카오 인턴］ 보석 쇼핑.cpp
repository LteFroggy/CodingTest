#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
    쇼핑하면 어피치는 진열대의 물건을 싹쓸이한다.
    진열된 모든 보석의 종류를 1개 이상 포함하는 가장 짧은 구간을 찾아 구매하고싶어한다.
    
    시작 진열대 번호와 끝 진열대 번호를 return하자.
    
    
    1. 일단 모든 진열대를 한번 싹 보며 보석 리스트를 확인한다.
    2. 리스트를 unordered_map에 넣는다.
    
    보석을 볼때마다 +1, 없앨때마다 -1하면서 진행한다
    
    보석의 배치가 이와 같다 하자.
    D R R D D E S D
    일단, 모든 보석이 등장할때까지 진행한다
    
    D R E S
D    1 0 0 0 
R    1 1 0 0
R    1 2 0 0
D    2 2 0 0
D    3 2 0 0
E    3 2 1 0
S    3 2 1 1 -> 모든 보석 등장!
    이제 앞에서부터 빼본다(모든 값이 1 이상이라는 가정 하에)
-D   2 2 1 1
-R   2 1 1 1 -> 여기서 더 빼면 불가능하다. R이 0이 되기 때문. 따라서 현재 Left Pointer인 2와 Right Pointer인 6을 사용, 2 ~ 6까지의 구간을 answer에 저장한다.
-R   2 0 1 1
    또 R이 1이상이 되는 시점까지 쭉 보면 됨. 이러면서 answer의 길이가 짧은 것으로 계속 갱신한다.
*/

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    
    // 먼저 값을 쭉 보면서 unordered_map을 갱신해야 함.
    unordered_map<string, int> gem_count;
    
    for (auto v : gems) {
        if (gem_count.find(v) == gem_count.end()) {
            gem_count.insert({v, 0});
        }
    }
    
    // 만들어진 map 확인
    // for (auto iter = gem_count.begin(); iter != gem_count.end(); iter++) cout << iter->first << endl;
    
    // 이제 보석을 순회하면서 answer를 찾아낸다.
    int type_count(0);
    int left_ptr(0);
    
    
    for (int right_ptr = 0; right_ptr < gems.size(); right_ptr++) {
        // 만약, 더해서 1개가 된다면 type_count를 1증가시킨다
        if (gem_count[gems[right_ptr]] == 0) type_count++;
        gem_count[gems[right_ptr]]++;
        
        // 지금 type_count가 보석 종류 갯수와 같다면, 모든 보석을 1개 이상씩 모은 것이다.
        if (type_count == gem_count.size()) {
            // 최소 길이를 찾아내기 위해, left_count를 증가시켜가며 보석을 빼본다
            while (gem_count[gems[left_ptr]] > 1 && left_ptr <= right_ptr) {
                gem_count[gems[left_ptr]]--;
                left_ptr++;
            }
            
            // 이제 while문이 끝나면, 이거까지 뺐을 때 조건을 만족하지 못하게 되는 것이다.
            // answer과 비교하여 저장한다
            if (answer.size() == 0) {
                answer.push_back(left_ptr);
                answer.push_back(right_ptr);
            }
            
            else if (answer[1] - answer[0] > right_ptr - left_ptr) {
                answer[0] = left_ptr;
                answer[1] = right_ptr;
            }
            
            // answer에 적용해줬으니, 다시 값을 뺸다
            gem_count[gems[left_ptr]]--;
            type_count--;
            left_ptr++;
        }
    }
    
    // 결과에 +1씩 해준다.
    answer[0]++;
    answer[1]++;
    return answer;
}