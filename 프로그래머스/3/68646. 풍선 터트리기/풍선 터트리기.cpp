#include <string>
#include <vector>

/*
    N개의 풍선이 존재하고, 서로 다른 숫자가 써있다. 풍선을 하나만 남길때까지 터트릴 것
    
    1. 임의의 두 풍선을 고르고, 하나를 터트린다.
    2. 터진 풍선으로 인해 빈 공간이 생기면, 밀착시킨다.
    
    이 중, 두 풍선 중에 번호가 더 작은 풍선을 터트리는 행위는 1번만 가능하다.
    어떤 풍선을 최후까지 남기는 것이 가능한 풍선들의 개수를 return하자.
    
    어떤 풍선을 마지막까지 남기려면, 왼쪽 혹은 오른쪽에 나보다 큰 값의 풍선이 와야 한다.
    일단 작은 값 터트리는 것이 불가능하다고 생각하자.
    
    왼쪽에 항상 나보다 큰 값만 있고, 오른쪽에도 항상 나보다 큰 값이 있어줘야 한다.
    
    풀이방법
    1. 풍선 개수만큼의 vector<bool>을 만들고, 값을 false로 세팅한다.
    2. 왼쪽에서부터 보면서 최소값이 갱신될때마다 vector의 값을 true로 바꾼다.
    3. 오른쪽에서도 같은 일을 반복한다.
    4. vector의 값이 true인 모든 노드를 센다.
*/

using namespace std;

int solution(vector<int> a) {
    int answer = 0;
    
    vector<bool> check(a.size(), false);
    
    int max_val = 1e9 + 1;
    for (int i = 0; i < a.size(); i++) {
        if (max_val > a[i]) {
            max_val = a[i];
            
            if (!check[i]) {
                check[i] = true;
                answer++;
            }
        }
    }
    
    max_val = 1e9 + 1;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (max_val > a[i]) {
            max_val = a[i];
            
            if (!check[i]) {
                check[i] = true;
                answer++;
            }
        }
    }
    
    return answer;
}