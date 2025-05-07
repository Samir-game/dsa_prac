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

//     void addEdge(int u,int v,int weight){
//         adjmatrix[u][v]=weight;
//         adjmatrix[v][u]=weight;
//         for(int i=0;i<V;i++) adjmatrix[i][i]=0;
//     }

//     void dijkstra(int start,int end){
//         vector<int>dist(V,INT_MAX);
//         vector<int>parent(V,-1);
//         priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

//         dist[start]=0;
//         pq.push({0,start});
//         while(!pq.empty()){
//             int u=pq.top().second;
//             int d=pq.top().first;
//             pq.pop();
//             if(d>dist[u]) continue;

//             for(int v=0;v<V;v++){
//                 if(adjmatrix[u][v]!=INT_MAX && adjmatrix[u][v]+dist[u]<dist[v]){
//                     dist[v]=adjmatrix[u][v]+dist[u];
//                     pq.push({dist[v],v});
//                     parent[v]=u;
//                 }
//             }
//         }
//         if(dist[end]==INT_MAX) {
//             cout<<"no path"<<endl;
//             return;
//         }

//         cout<<"total cost: "<<dist[end]<<endl;

//         vector<int>path;
//         for(int v=end;v!=-1;v=parent[v]){
//             path.push_back(v);
//         }
//         reverse(path.begin(),path.end());
//         for(int v:path){
//             cout<<v<<" ";
//         }cout<<endl;
//     }
// };

// int main(){
//     int V,E;
//     cout<<"V E: ";
//     cin>>V>>E;

//     Graph g(V);
//     for(int i=0;i<E;i++){
//         int u,v,weight;
//         cout<<"u v weight: ";
//         cin>>u>>v>>weight;
//         g.addEdge(u,v,weight);
//     }

//     g.dijkstra(0,4);
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
        adjmatrix.resize(V,vector<int>(V,INT_MAX));
        for(int i=0;i<V;i++) adjmatrix[i][i]=0;
    }

    void addedge(int u,int v,int weight){
        adjmatrix[u][v]=weight;
        adjmatrix[v][u]=weight;
    }

    void dijkstra(int start,int end){
        vector<int>dist(V,INT_MAX);
        vector<int>parent(V,-1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

        dist[start]=0;
        pq.push({0,start});

        while(!pq.empty()){
            int u=pq.top().second;
            int d=pq.top().first;
            pq.pop();

            if(d>dist[u]) continue;

            for(int v=0;v<V;v++){
                if(adjmatrix[u][v]!=INT_MAX && dist[u]+adjmatrix[u][v]<dist[v]){
                    dist[v]=adjmatrix[u][v]+dist[u];
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        if(dist[end]==INT_MAX){
            cout<<"no path\n";
            return;
        }

        cout<<"shortest path: "<<dist[end]<<endl;
        
        vector<int>path;
        for(int v=end;v!=-1;v=parent[v]){
            path.push_back(v);
        }
        reverse(path.begin(),path.end());
        for(int x:path){
            cout<<x<<" ";
        }cout<<endl;
    }
};

int main(){
        int V,E;
        cout<<"V E: ";
        cin>>V>>E;
    
        Graph g(V);
        for(int i=0;i<E;i++){
            int u,v,weight;
            cout<<"u v weight: ";
            cin>>u>>v>>weight;
            g.addedge(u,v,weight);
        }
    
        g.dijkstra(0,4);
        return 0;
}