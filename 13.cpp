// // #include <bits/stdc++.h>
// // using namespace std;

// // class Graph {
// //     int V;
// //     vector<vector<int>> adj;

// // public:
// //     Graph(int ver) {
// //         V=ver;
// //         adj.resize(V);
// //     }

// //     void addEdge(int u, int v) {
// //         adj[u].push_back(v);
// //     }

// //     void dfs(int node, vector<int>& vis, stack<int>& st) {
// //         vis[node] = 1;
// //         for (auto it : adj[node]) {
// //             if (!vis[it]) dfs(it, vis, st);
// //         }
// //         st.push(node);
// //     }

// //     vector<int> topoSortDFS() {
// //         vector<int> vis(V, 0);
// //         stack<int> st;
// //         for (int i = 0; i < V; i++) {
// //             if (!vis[i]) dfs(i, vis, st);
// //         }

// //         vector<int> topo;
// //         while (!st.empty()) {
// //             topo.push_back(st.top());
// //             st.pop();
// //         }
// //         return topo;
// //     }
// // };

// // int main() {
// //     Graph g(6);
// //     g.addEdge(5, 2);
// //     g.addEdge(5, 0);
// //     g.addEdge(4, 0);
// //     g.addEdge(4, 1);
// //     g.addEdge(2, 3);
// //     g.addEdge(3, 1);

// //     vector<int> topo = g.topoSortDFS();
// //     cout << "Topological Sort using DFS:\n";
// //     for (int node : topo) cout << node << " ";
// //     cout << endl;
// // }



// // #include <bits/stdc++.h>
// // using namespace std;

// // class Graph{
// //     public:
// //     int V;
// //     vector<vector<int>>adjmatrix;

// //     Graph(int ver){
// //         V=ver;
// //         adjmatrix.resize(V);
// //     }

// //     void addEdge(int u,int v){
// //         adjmatrix[u].push_back(v);
// //     }

// //     void dfs(int node, vector<int>&visi,stack<int>&s){
// //         visi[node]=1;
// //         for(auto it: adjmatrix[node]){
// //             if(!visi[it]){
// //                 dfs(it,visi,s);
// //             }
// //         }
// //         s.push(node);
// //     }

// //     vector<int> topodfs(){
// //         vector<int>visi(V,0);
// //         stack<int>s;

// //         for(int i=0;i<V;i++){
// //             if(!visi[i]){
// //                 dfs(i,visi,s);
// //             }
// //         }

// //         vector<int>topo;
// //         while(!s.empty()){
// //             topo.push_back(s.top());
// //             s.pop();
// //         }

// //         return topo;

// //     }

// // };
// // int main(){
// //     Graph g(6);
// //     g.addEdge(5,2);
// //     g.addEdge(5,0);
// //     g.addEdge(4,0);
// //     g.addEdge(4,1);
// //     g.addEdge(2,3);
// //     g.addEdge(3,1);

// //     vector<int>ans=g.topodfs();
// //     for(int as: ans){
// //         cout<<as<<" ";
// //     }
// //     return 0;

// // }


// #include <bits/stdc++.h>
// using namespace std;

// class Graph{
//     public:
//     int V;
//     vector<vector<int>>adjmatrix;

//     Graph(int ver){
//         V=ver;
//         adjmatrix.resize(V);
//     }

//     void addEdge(int u,int v){
//         adjmatrix[u].push_back(v);
//     }

//     void dfs(int node, vector<int>&visi,stack<int>&s){
//         visi[node]=1;
//         for(auto it: adjmatrix[node]){
//             if(!visi[it]){
//                 dfs(it,visi,s);
//             }
//         }
//         s.push(node);
//     }

//     vector<int> topodfs(){
//         vector<int>visi(V,0);
//         stack<int>s;

//         for(int i=0;i<V;i++){
//             if(!visi[i]){
//                 dfs(i,visi,s);
//             }
//         }

//         vector<int>topo;
//         while(!s.empty()){
//             topo.push_back(s.top());
//             s.pop();
//         }
//         return topo;
//     }

// };

// int main(){
//     Graph g(6);
//     g.addEdge(5,2);
//     g.addEdge(5,0);
//     g.addEdge(4,0);
//     g.addEdge(4,1);
//     g.addEdge(2,3);
//     g.addEdge(3,1);

//     vector<int>ans=g.topodfs();
//     for(int as: ans){
//         cout<<as<<" ";
//     }
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
        adjmatrix.resize(V);
    }

    void addEdge(int u,int v){
        adjmatrix[u].push_back(v);
    }

    void dfs(int node,vector<int>&visi,stack<int>&s){
        visi[node]=1;
        for(auto it: adjmatrix[node]){
            if(!visi[it]){
                dfs(it,visi,s);
            }
        }
        s.push(node);
    }

    vector<int> topodfs(){
        vector<int>visi(V,0);
        stack<int>s;

        for(int i=0;i<V;i++){
            if(!visi[i]){
                dfs(i,visi,s);
            }
        }

        vector<int>topo;
        while(!s.empty()){
            topo.push_back(s.top());
            s.pop();
        }
        return topo;
    }
};

int main(){
    Graph g(6);
    g.addEdge(5,2);
    g.addEdge(5,0);
    g.addEdge(4,0);
    g.addEdge(4,1);
    g.addEdge(2,3);
    g.addEdge(3,1);

    vector<int>ans=g.topodfs();
    for(int as: ans){
        cout<<as<<" ";
    }
    return 0;

}