#include "stdlib.h"

//  A ---> B ---> C ---> A
struct graph initg()
{
    char verts[] = {'A', 'B', 'C'};

    struct edge edges[] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'A'},
    };

    struct graph graph;

    graph.nverts = 3;
    graph.nedges = 3;

    graph.directed = 1;
    graph.verts = verts;
    graph.edges = edges;

    return graph;
}

int _kernel()
{
    struct graph graph = initg();
    put_flist(&graph);

    return 0;
}
