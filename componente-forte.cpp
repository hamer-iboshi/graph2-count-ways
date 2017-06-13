#include<bits/stdc++.h>
#include <graphviz/cgraph.h>

using namespace std;

typedef vector<int> vi;

typedef pair<string,int> tatributes;

typedef unordered_map<string,int> vatr;

typedef struct {
		string name;
		int	visited;
		vi neighbors;
		int componente;
} tgraph;

typedef vector<tgraph> graph;

unordered_map<string,int> dict;
unordered_map<int,string> rdict;

graph G,GT;

int *visitG, *visitGT;

void printDict(){
		cout << "Print Dictionary" << endl;
		for(auto& p: dict)
				cout << " " << p.first << " => " << p.second << '\n';
}

void printNodes(graph &g){
		cout << "Print Nodes" << endl;
		for(int i=0;i < (int) g.size(); i++){
				cout << g[i].name << " ";
				cout << g[i].visited << " ";
				cout << "NEIGHBORS: ";
				for(int j=0;j< (int) g[i].neighbors.size();j++){
						cout << rdict[g[i].neighbors[j]] << " ";
				}
				cout << endl;
		}
}

void printDot(graph &g){
	int j,i;
	cout << "strict digraph resultado_exemplo {\n\n";
	for(int i=0;i < (int) g.size(); i++){
		cout << "\t\"" << g[i].name << "\"";
		j=0;
		cout << endl;
	}

	for(i=0;i < (int) g.size(); i++){
				for(j=0;j< (int) g[i].neighbors.size();j++){
            cout << "\t\"" << g[i].name << "\" -> \"" << rdict[g[i].neighbors[j]] << "\";\n";
        }
	}
	cout << "}\n";
}

void DFS(int node, int c){
		if(!G[node].componente){
			G[node].visited = c;
			visitG[node] = c;
		} else return;
		for(int i=0;i < (int) G[node].neighbors.size();i++){
				//cout << "ind : " << rdict[G[node].neighbors[i]] << endl;
				if( !G[G[node].neighbors[i]].visited ){
						DFS(G[node].neighbors[i],c);
				}
		}
}

void DFS2(int node,int c){
		if(!G[node].componente){
			GT[node].visited = c;
			visitGT[node] = c;
		} else return;
		vatr *aux;
		for(int i=0;i < (int) GT[node].neighbors.size();i++){
				if(! GT[GT[node].neighbors[i]].visited){
						//cout << "ind : " << rdict[GT[node].neighbors[i]] << endl;
						DFS2(GT[node].neighbors[i],c);
				}
		}
}

int main(){
		//ler GRAFO from .dot
		Agraph_t *g = agread(stdin, NULL);
		tgraph auxtg;
		vi comp;
		char *auxname;
		int i=0;
		/*
			 printf("%s\n", agnameof(g));
			 printf("%d vertices\n", agnnodes(g));
			 printf("%d arestas\n", agnedges(g));
			 printf("%sdirecionado\n", agisdirected(g) ? "" : "não ");
			 printf("%ssimples\n", agissimple(g) ? "" : "não ");

			 printf("vértices e atributos\n");
		 */
		for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)){
				auxtg.name = string(agnameof(v));
				auxtg.visited = 0;
				auxtg.componente = 0;
				dict.insert({auxtg.name,i});
				rdict.insert({i,auxtg.name});
				//printf("\n");
				G.push_back(auxtg);
				GT.push_back(auxtg);
				comp.push_back(0);
				i++;
		}
		visitGT = (int*) malloc(sizeof(int)*(int)G.size());
		visitG = (int*) malloc(sizeof(int)*(int)G.size());
		i=0;
		for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)){
				if(agcountuniqedges(g,v, 0, 1) > 0){
						for (Agedge_t *edge=agfstedge(g,v); edge;   edge = agnxtedge(g,edge,v)){
								Agnode_t *nghb = aghead(edge);
								if(strcmp(agnameof(nghb),agnameof(v))){
										G[i].neighbors.push_back(dict[string(agnameof(nghb))]);
										GT[dict[string(agnameof(nghb))]].neighbors.push_back(i);
								}
						}
				}
				i++;
		}
		//printDict();
		//printNodes(G);
		//printNodes(GT);
		//Start DFS
		graph auxGT = GT;
		int c = 1;
		bool temComp = false;
		for(i=0;i<(int)G.size();i++){
			if(!G[i].visited){
				DFS(i,c);
				DFS2(i,c);
				for(int j=0;j < (int)G.size();j++){
					if((visitG[j] == visitGT[j]) && (!comp[j])){
						comp[j] = c;
						G[j].componente = c;
						temComp=true;
					}else if(!comp[j]){
						GT[j].visited = 0;
						G[j].visited = 0;
					}
				}
				if(temComp){
					temComp=false;
					c++;
				}
				memset(visitGT,0,sizeof(visitGT));
			}
		}
		
		for(int j=0;j < (int)G.size();j++) cout << comp[j] << "\t"<< rdict[j] << endl;
		//printNodes(G);
		//printDot(G);
		return 0;
}
