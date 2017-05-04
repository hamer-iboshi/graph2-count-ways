#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

#define INF 0x3f3f3f3f

typedef pair<int, int> neighbor; //first = id of edges, second = weight of vertice

typedef vector<neighbor> vi;

vi list[150];
int distances[150];
int visited[150];

int main(){
		int N,M,i,j,k,weight,begin,end,current,smaller;
		scanf("%d%d",&N,&M);
		while(N || M){
				for(i=0;i<=N;i++) distances[i] = INF;
				memset(visited,0,sizeof(visited));
				for(i=0;i<M;i++){
						scanf("%d%d%d",&j,&k,&weight);
						list[j].push_back(neighbor(k,weight));
				}
				scanf("%d%d",&begin,&end);
				distances[begin] = 0;
				current = begin;
				while(current != -1){
						visited[current] = 1;
						//printf("Current %d\n",current);
						for(i=0;i<(int)list[current].size();i++){
								if( (distances[current] + list[current][i].second) < distances[list[current][i].first] ){
										distances[list[current][i].first] = distances[current] + list[current][i].second;
										//printf("\t%d\t%d\n",list[current][i].first,distances[current] + list[current][i].second);
								}
						}
						current=-1;
						smaller=INF;
						for(i=1;i<=N;i++){
								if((!visited[i]) && (distances[i] < smaller)){
										current = i;
										smaller = distances[i];
								}
						}
				}
				if(distances[end] >= INF)
						printf("%d\n",-1);
				else
						printf("%d\n",distances[end]);
				for(i=1;i<=N;i++) list[i].clear();
				scanf("%d%d",&N,&M);
		}
		return 0;
}

