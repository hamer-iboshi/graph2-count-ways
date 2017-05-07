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
		vatr atributes;
} tgraph;

typedef vector<tgraph> graph;

unordered_map<string,int> dict;
unordered_map<int,string> rdict;

graph G; //Global 

void printDict(){
		cout << "Print Dictionary" << endl;
		for(auto& p: dict)
				cout << " " << p.first << " => " << p.second << '\n';
}

void printNodes(graph g){
		cout << "Print Nodes" << endl;
		for(int i=0;i < (int) g.size(); i++){
				cout << g[i].name << " ";
				cout << g[i].visited << " ";
				cout << "ATTRIBUTES: ";
				for(auto& p: g[i].atributes){
						cout << " " << p.first << " => " << p.second << " ";
				}
				cout << "NEIGHBORS: ";
				for(int j=0;j< (int) g[i].neighbors.size();j++){
						cout << g[i].neighbors[j] << " ";
				}
				cout << endl;
		}
}

void printDot(graph g){
	int j;
	cout << "strict digraph resultado_exemplo {\n\n";
	for(int i=0;i < (int) g.size(); i++){
		cout << "\t\"" << g[i].name << "\"";
		j=0;
		for(auto& p: g[i].atributes){
			if(!j) cout << " [" << p.first << "=" << p.second;
			else cout << ", " << p.first << "=" << p.second;
			j++;
    }
		cout << "];\n";
	}

	for(int i=0;i < (int) g.size(); i++){
				for(int j=0;j< (int) g[i].neighbors.size();j++){
            cout << "\t\"" << g[i].name << "\" -> \"" << rdict[g[i].neighbors[j]] << "\";\n";
        }
	}
	cout << "}\n";
}

vatr* DFS(int node){
		vatr *aux;
		
		for(int i=0;i < (int) G[node].neighbors.size();i++){
				if( G[G[node].neighbors[i]].visited ){
						aux =  &G[G[node].neighbors[i]].atributes;
				}else{
						aux = DFS(G[node].neighbors[i]);
				}
				//cout << "ind : " << G[node].neighbors[i] << endl;
				for(auto iter = aux->begin(); iter != aux->end(); ++iter){
					//	cout << " " << iter->first << " => " << iter->second << '\n';
						auto search = G[node].atributes.find(iter->first);
						if(search != G[node].atributes.end()) {
							search->second++;
						}else{
							G[node].atributes.insert({ iter->first,iter->second });
						}
				}
		}
		G[node].visited = 1;
		return &G[node].atributes;
}


int main(){
		//ler GRAFO from .dot
		Agraph_t *g = agread(stdin, NULL);
		int root;
		tgraph auxtg;
		tatributes auxta;
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
				dict.insert({auxtg.name,i});
				rdict.insert({i,auxtg.name});
				if(agcountuniqedges(g,v, 1, 0) == 0)
						root = dict[auxtg.name];
				for (Agsym_t *atributo=agnxtattr(g,AGNODE,NULL); atributo; atributo=agnxtattr(g,AGNODE,atributo)){
						auxname = agxget(v, atributo);
						if(atoi(auxname)){
								auxtg.atributes.insert({string(atributo->name), atoi(auxname)});
								//printf(" %s=\'%d\'", auxta.first.c_str(),auxta.second);
						}
				}
				//printf("\n");
				G.push_back(auxtg);
				auxtg.atributes.clear();
				i++;
		}
		i=0;
		for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)){
				if(agcountuniqedges(g,v, 0, 1) > 0){
						//printf("\n\tEDGES n %d : ",agcountuniqedges(g,v, 0, 1));
						for (Agedge_t *edge=agfstedge(g,v); edge;   edge = agnxtedge(g,edge,v)){
								Agnode_t *nghb = aghead(edge);
								if(strcmp(agnameof(nghb),agnameof(v))){
										G[i].neighbors.push_back(dict[string(agnameof(nghb))]);
								}
						}
				}
				i++;
		}
		//cout << "root is: " << root << endl;
		//printDict();
		//printNodes(G);
		//Start DFS
		DFS(root);
		//printNodes(G);
		printDot(G);
		return 0;
}
