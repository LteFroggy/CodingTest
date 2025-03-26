#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/*    
    프렌즈를 두 팀으로 나누고, 팀이 같은 곳을 다른 순서로 방문하게 해서 먼저 순회를 마치면 승리한다.
    방문시에는 방문할 곳의 2차원 좌표를 구하고, 각 장소를 이진트리의 노드가 되게 만든 후에 순회 방법을 힌트로 준다.
    
    방문할 2차원 좌표값을 구하고, 각 장소는 이진트리의 노드이다.
    순회 방법은 알려준다.
    
    전위순회, 후위순회를 한 결과가 각 팀이 방문해야 할 순서이다.
    
    y값 기준으로 탐색해 내려가자
    대신, 값이 좀 많으니 압축 필요하다.
    같은 y축 친구들은 같은 층?이다.
    set으로 정렬하다. search는 logN이니, NlogN으로 좌표 압축 가능하다.
    
    이후에는 max_left, max_right를 이용해 누구의 자식인지 찾아가는 과정을 반복한다.
*/

struct node {
    int value = 0;
    int x;
    int y;
    node* left = nullptr;
    node* right = nullptr;
    
    // 트리에는 최대 좌우범위가 있다. 누군가의 왼쪽 서브트리일 경우, max_right가 제한되고, 누군가의 오른쪽 서브트리일 경우 max_left가 제한된다.
    int max_left = -1e9;
    int max_right = 1e9;
    
    node(vector<int> a) : x(a[0]), y(a[1]), value(a[2]) {}
};

void preorder(node* now, vector<int>& result) {
    // 전위는 나 - 왼 - 오 순으로 본다
    result.push_back(now->value);
    
    if (now->left != nullptr) preorder(now->left, result);
    if (now->right != nullptr) preorder(now->right, result);
}

void postorder(node* now, vector<int>& result) {
    // 후위는 왼, 오, 나 순으로 본다
    if (now->left != nullptr) postorder(now->left, result);
    if (now->right != nullptr) postorder(now->right, result);
    result.push_back(now->value);
}

bool comp_std(vector<int> a, vector<int> b) {
    if (a[1] == b[1]) return a[0] < b[0];
    return a[1] > b[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    set<int> x_list;
    set<int> y_list;
    
    // 먼저 좌표 압축해준다. set에 넣어서 x좌표, y좌표 정렬할 것
    for (auto v : nodeinfo) {
        x_list.insert(v[0]);
        y_list.insert(v[1]);
    }
    
    // 이제, 이걸 unordered_map에 저장해둔다!
    int val = 0;
    unordered_map<int, int> x_mapping;
    for (auto v : x_list) x_mapping.insert({v, val++});
    
    val = 0;
    unordered_map<int, int> y_mapping;
    for (auto v : y_list) y_mapping.insert({v, val++});
    
    // 매핑 적용한 새 배열 만들기. 노드값까지 포함한다
    vector<vector<int>> nodeinfo_new;
    for (int i = 0; i < nodeinfo.size(); i++) {
        int new_x = x_mapping[nodeinfo[i][0]];
        int new_y = y_mapping[nodeinfo[i][1]];
        nodeinfo_new.push_back({new_x, new_y, i + 1});
    }
    
    // 트리 만들기! 일단 y좌표 순으로, 그리고 x좌표 순으로 정렬한다.
    sort(nodeinfo_new.begin(), nodeinfo_new.end(), comp_std);
    
    // 새 좌표 확인
    /// for (auto v : nodeinfo_new) cout << v[0] << ", " << v[1] << endl;
    
    // 이제 왼쪽자식과 오른쪽자식을 따지면 된다!
    // 일단 0번이 무조건 루트이다.
    node *root = new node(nodeinfo_new[0]);
    
    // 현재 말단에 존재하는 리프노드들과 새로 저장된 리프노드들을 기록하기 위함
    vector<node*> leafs;
    vector<node*> new_leafs;
    
    new_leafs.push_back(root);
    
    // 이제 값을 보면서 한 줄(같은 y값을 가지는 라인업)을 찾는다
    for (int i = 1; i < nodeinfo_new.size(); i++) {
        /// cout << "현재 i 값 : " << i << endl;
        
        // 현재 노드의 y값이 이전의 y값이 다르다면, 새 depth로 넘어온 것이다. leaf와 new_leaf를 교환한다
        if (nodeinfo_new[i][1] != nodeinfo_new[i - 1][1]) {
            leafs = new_leafs;
            new_leafs = vector<node*>();
        }
        
        
        // 나는 지금 존재하는 말단 중 누구의 자식인지 확인한다.
        for (auto v : leafs) {
            // leaf노드의 x좌표보다 내 x좌표가 작고, 이 노드의 max_left보다 내가 크다면 나는 이 사람의 자식이 될 수 있다.
            if (nodeinfo_new[i][0] < v->x && v->max_left < nodeinfo_new[i][0]) {
                node* me = new node(nodeinfo_new[i]);
                // 이 경우, 나의 max_left는 상속받고, max_right는 이 노드가 된다.
                me->max_left = v->max_left;
                me->max_right = v->x;
                v->left = me;

                new_leafs.push_back(me);

                /// cout << nodeinfo_new[i][0] << "," << nodeinfo_new[i][1] << "은 " << v->x << "," << v->y << "의 왼쪽 자식이다" << endl;

                break;
            }

            // leaf노드의 x좌표보다 내 x좌표가 크고, 이 노드의 max_right보다 내가 작다면 자식이 될 수 있다.
            else if (nodeinfo_new[i][0] > v->x && v->max_right > nodeinfo_new[i][0]) {
                node* me = new node(nodeinfo_new[i]);
                // 이 경우, 나의 max_right는 상속받고, max_left는 이 노드가 된다.
                me->max_right = v->max_right;
                me->max_left = v->x;
                v->right = me;

                new_leafs.push_back(me);

                /// cout << nodeinfo_new[i][0] << "," << nodeinfo_new[i][1] << "은 " << v->x << "," << v->y << "의 오른쪽 자식이다" << endl;

                break;
            }
        } // for
    } // for

    // 이제 모든 일이 끝났다. 순회를 수행해본다.
    answer = vector<vector<int>>(2);
    preorder(root, answer[0]);
    postorder(root, answer[1]);
    
    return answer;
}




// 필요 구조체 및 함수 정의

