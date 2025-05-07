// #include <bits/stdc++.h>
// using namespace std;

// class Graph{
//     public:
//     int V;
//     vector<vector<int>>adjmatrix;
//     Graph(int ver){
//         V=ver;
//         adjmatrix.resize(V,vector<int>(V,INT_MAX));
//     }

//     void addEdge(int u,int v){
//         adjmatrix[u][v]=1;
//         adjmatrix[v][u]=1;
//     }

//     void dfsr(int node,vector<bool>&visited){
//         visited[node]=true;
//         cout<<node<<" ";
//         for(int i=0;i<V;i++){
//             if(adjmatrix[node][i]==1 && !visited[i]){
//                 dfsr(i,visited);
//             }
//         }
//     }

//     void dfsi(int start){
//         vector<bool>visited(V,false);
//         stack<int>s;
//         s.push(start);
//         while(!s.empty()){
//             int node=s.top();
//             s.pop();
//             if(!visited[node]){
//                 visited[node]=true;
//                 cout<<node<<" ";
//             }
//             for(int i=V-1;i>=0;i--){
//                 if(adjmatrix[node][i]==1 && !visited[i]){
//                     s.push(i);
//                 }
//             }
//         }
//     }

//     void bfs(int start){
//         vector<int>visited(V,false);
//         queue<int>q;
//         q.push(start);
//         visited[start]=true;
//         while(!q.empty()){
//             int node=q.front();
//             q.pop();
//             cout<<node<<" ";
//             for(int i=0;i<V;i++){
//                 if(adjmatrix[node][i]==1 && !visited[i]){
//                     visited[i]=true;
//                     q.push(i);
//                 }
//             }
//         }
//     }

//     int connectedDFS(){
//         vector<bool>visited(V,false);
//         int count=0;
//         for(int i=0;i<V;i++){
//             if(!visited[i]){
//                 cout<<"component "<<count+1<<": ";
//                 dfsr(i,visited);
//                 count++;
//                 cout<<endl;
//             }
//         }
//         return count;
//     }
// };
// int main() {
//     Graph g(7);

//     g.addEdge(0, 1);
//     g.addEdge(1, 2);
//     g.addEdge(3, 4);
//     g.addEdge(5, 6);

//     cout << "BFS from node 0: ";
//     g.bfs(0);
//     cout << endl;

//     cout << "DFS (Iterative) from node 0: ";
//     g.dfsi(0);
//     cout << endl;

//     cout << "Connected Components:\n";
//     int total = g.connectedDFS();
//     cout << "Total Connected Components: " << total << endl;

//     return 0;
// }
    

#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int V;
    vector<vector<int>>adjmatrix;
    Graph(int ver){
        V=ver;
        adjmatrix.resize(V,vector<int>(V,0));
    }

    void addedge(int u,int v){
        adjmatrix[u][v]=1;
        adjmatrix[v][u]=1;
    }

    void dfsr(int node, vector<bool>&visited){
        visited[node]=true;
        cout<<node<<" ";
        for(int i=0;i<V;i++){
            if(adjmatrix[node][i]&& !visited[i]){
                dfsr(i,visited);
            }
        }
 
    }

    void dfsi(int start){
        vector<bool>visited(V,false);
        stack<int>s;
        s.push(start);
        while(!s.empty()){
            int node= s.top();
            s.pop();
            if(!visited[node]){
                visited[node]=true;
                cout<<node<<" ";
            }

            for(int i=0;i<V;i++){
                if(!visited[i] && adjmatrix[node][i]==1){
                    s.push(i);
                }
            }
        }

    }

    void bfs(int start){
        vector<bool>visited(V,false);
        queue<int>q;
        visited[start]=true;
        q.push(start);
        while(!q.empty()){
            int node=q.front();
            q.pop();
            cout<<node<<" ";
            for(int i=0;i<V;i++){
                if(!visited[i] && adjmatrix[node][i]==1){
                    visited[i]=true;
                    q.push(i);
                }
            }
        }
    }

    int connected(){
        vector<bool>visited(V,false);
        int count=0;
        for(int i=0;i<V;i++){
            if(!visited[i]){
                cout<<"component: "<<count+1<<": ";
                dfsr(i,visited);
                count++;
                cout<<endl;
            }
        }
        return count;
    }
};
int main() {
    Graph g(7);

    g.addedge(0, 1);
    g.addedge(1, 2);
    g.addedge(3, 4);
    g.addedge(5, 6);

    cout << "BFS from node 0: ";
    g.bfs(0);
    cout << endl;

    cout << "DFS (Iterative) from node 0: ";
    g.dfsi(0);
    cout << endl;

    cout << "Connected Components:\n";
    int total = g.connected();
    cout << "Total Connected Components: " << total << endl;

    return 0;
}