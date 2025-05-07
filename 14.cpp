#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int V;
    vector<vector<int>>adjmatrix;
    Graph(int ver){
        V=ver;
        adjmatrix.resize(V,vector<int>(V,INT_MAX));
    }

    void addedge(int u,int v,int weight){
        adjmatrix[u][v]=weight;
        adjmatrix[v][u]=weight;
    }

    void prims(int start){
        vector<bool>inMst(V,false);
        inMst[start]=true;
        int edgecount=0;int mincost=0;
        while(edgecount<V-1){
            int min=INT_MAX,a=-1,b=-1;
            for(int i=0;i<V;i++){
                if(inMst[i]){
                    for(int j=0;j<V;j++){
                        if(!inMst[j] && adjmatrix[i][j]<min){
                            min=adjmatrix[i][j];
                            a=i;
                            b=j;
                        }
                    }
                }
            }
            if(a!=-1 && b!=-1){
                cout<<"a: "<<a<<" b: "<<b<<" cost: "<<min<<endl;
                inMst[b]=true;
                mincost+=min;
                edgecount++;
            }
        }
        cout<<"mincost: "<<mincost<<endl;
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

    g.prims(0);
    return 0;
}