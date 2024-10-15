#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

/*
    N개의 정점과 M개의 간선을 가진 무향 그래프가 주어진다.
    T = 1일 때, G에서 정해진 K개의 정점을 지운다.
    T = t일 때는, T = t-1에서 지워진 정점과 이웃했던 정점들을 지운다.
    G에 사이클이 존재하지 않는 최초의 시간 C를 구하는 프로그램을 써보자.


    처음 주어지는 그래프 G는 모든 정점이 연결된 그래프이고, 사이클이 있다.
    자기 자신과 연결된 간선 주어지지 않으나, 중복은 가능하다.

    사이클 탐색이 union_find로 가능하다고 한다!

    1. 사라지는 정점을 보고, 각 정점이 사라질 시간을 예측해서 predict에 넣는다.
    2. 각 간선들을 보고, 이 간선이 사라지기 직전 시간을 기록해서 (정점1, 정점2, 생기는 시간) 배열을 edges_time에 넣는다
    3. 시간을 역으로 돌려가면서 간선을 하나씩 생성하고, 사이클이 생기는 최초의 시점을 찾는다!
    3-1. 사이클이 생기는지의 여부는 Union-Find를 활용할 것
*/

using namespace std;

// 간선 정보와 사라지는 시간을 포함해서 기록할 struct
struct edge_time {
    edge_time(int a, int b, int c) : nodeA(a), nodeB(b), time(c) {};
    int nodeA;
    int nodeB;
    int time;
};

// 더 오래 남아있는 노드를 앞쪽으로 배치하도록 정렬한다.
bool compare(edge_time a, edge_time b) {
    if (a.time == b.time) return a.nodeA < b.nodeA;
    return a.time > b.time;
}

int find(vector<int> &parents, int target) {
    if (parents[target] == target) return parents[target];
    else parents[target] = find(parents, parents[target]);
    return parents[target];
}

// 두 가족을 합친다. 작은 값이 부모가 되도록 함
void union_parents(vector<int> &parents, int a, int b) {
    int a_parents = find(parents, a);
    int b_parents = find(parents, b);

    // cout << "수정 전 " << a << "의 부모 : " << a_parents << endl;
    // cout << "수정 전 " << b << "의 부모 : " << b_parents << endl;

    if (a_parents < b_parents) parents[b_parents] = a_parents;
    else parents[a_parents] = b_parents; 

    // cout << "수정 후 " << a_parents << "의 부모 : " << parents[a_parents] << endl;
    // cout << "수정 후 " << b_parents << "의 부모 : " << parents[b_parents] << endl;
 }

int main(int argc, char** argv) {
    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int, int>> edges(M);
    vector<int> predicted(N, 1000000);

    // 간선 입력받기
    for (int i = 0; i < M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        edges[i] = {node1 - 1, node2 - 1};
    }

    queue<int> que;

    // 사라지는 간선 입력받고, 사라지는 시간 적용을 위해 queue에 넣기
    for (int i = 0; i < K; i++) {
        int tmp;
        cin >> tmp;

        predicted[tmp - 1] = 1;
        que.push(tmp - 1);
    }

    int time_max = 1;
    // 사라지는 시간 predicted에 적용하기
    while (!que.empty()) {
        int now = que.front();
        // 혹시 0번 노드가 사라진 후에 N번 노드가 사라지나?.. 아니다!
        /*
        int before = now - 1 < 0 ? N - 1 : now - 1;
        int next = now + 1 >= N ? 0 : now + 1;
        */

        int before = now - 1;
        int next = now + 1;
        que.pop();

        // 앞 노드 사라지는 시간 적용하기.
        if (before >= 0 && predicted[before] == 1000000) {
            predicted[before] = predicted[now] + 1;
            que.push(before);
            time_max = predicted[now] + 1;
        }

        /*
        
        1 2
        1 3
        1 4 
        1 5
        1 6

        1 2 3 4 5 6
        1 2 3 4 5 6
        1 1 3 4 5 6
        1 1 1 4 5 6
        1 1 1 1 5 6
        1 1 1 1 1 6
        1 1 1 1 1 1

        5 6
        
        */

        // 뒷 노드 사라지는 시간 적용하기
        if (next < N && predicted[next] == 1000000) {
            predicted[next] = predicted[now] + 1;
            que.push(next);
            time_max = predicted[now] + 1;
        }
    }

    // 적용 확인
    /*
    for (auto v : predicted) cout << v << " ";
    cout << endl;
    */

    // 이제 사라지는 시간을 적용한 배열 만들기
    vector<edge_time> new_edges;

    for (auto v : edges) {
        int nodeA = v.first;
        int nodeB = v.second;
        // 시간은 nodeA와 수명과 nodeB의 수명 중 더 짧은 것으로 책정
        int time = min(predicted[nodeA], predicted[nodeB]);
        
        new_edges.push_back(edge_time(nodeA, nodeB, time));
    }

    // 배열 정렬 후 확인
    sort(new_edges.begin(), new_edges.end(), compare);
    /*
    for (auto v : new_edges) {
        cout << v.nodeA << ", " << v.nodeB << " : " << v.time << endl;
    }
    */
    
    
    // 이제 union_find 할 것
    vector<int> parents(N);
    // 처음에 자신의 부모는 자신이다.
    for (int i = 0; i < N; i++) {
        parents[i] = i;
    }

    int edge_idx = 0;
    bool loop_flag = false;
    // 역으로 최대 시간에서부터 간선을 생성해 올 것이다.
    for (int i = time_max; i > 0; i--) {
        // cout << "time : " << i << endl;
        // 이번 시간에 생성 가능한 간선을 모두 만든다.
        while (new_edges[edge_idx].time >= i) {
            int nodeA = new_edges[edge_idx].nodeA;
            int nodeB = new_edges[edge_idx].nodeB;
            edge_idx++;

            cout << "A : " << nodeA << ", B : " << nodeB << endl;

            // 두 노드를 연결한다!(부모를 같게 만든다)
            if (find(parents, nodeA) != find(parents, nodeB)) {
                union_parents(parents, nodeA, nodeB);
                

                cout << "수정 후 parents : ";
                for (auto v : parents) cout << v << " "; cout << endl;
            }
                
            // 만약, 두 노드의 부모가 같다면, 이번 시간에 루프가 사라진 것이다!
            else if (find(parents, nodeA) == find(parents, nodeB)) {
                cout << i << endl;
                loop_flag = true;
                break;
            }
        }

        // 이미 루프를 찾았다면 더 탐색할 필요 없음
        if (loop_flag) break;
    }
    
    return 0;
}
