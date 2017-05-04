#include<stdio.h>
#include<string.h>
#include <graphviz/cgraph.h>

int main(void) {

		Agraph_t *g = agread(stdin, NULL);

		printf("%s\n", agnameof(g));
		printf("%d vertices\n", agnnodes(g));
		printf("%d arestas\n", agnedges(g));
		printf("%sdirecionado\n", agisdirected(g) ? "" : "não ");
		printf("%ssimples\n", agissimple(g) ? "" : "não ");

		printf("vértices e atributos\n");

		for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v)){

				printf("%s:", agnameof(v));

				for (Agsym_t *atributo=agnxtattr(g,AGNODE,NULL); atributo; atributo=agnxtattr(g,AGNODE,atributo))
						printf(" %s=\'%s\'", atributo->name, agxget(v, atributo));
				if(agcountuniqedges(g,v, 0, 1) > 0){
				printf("\n\tEDGES n %d : ",agcountuniqedges(g,v, 0, 1));
						for (Agedge_t *edge=agfstedge(g,v);	edge;		edge = agnxtedge(g,edge,v)){
								Agnode_t *nghb = aghead(edge);
								if(strcmp(agnameof(nghb),agnameof(v)))
										printf("%s ",agnameof(nghb));
						}
				}
				printf("\n");

		}
		return 0;
}
