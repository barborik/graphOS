#include "stdlib.h"

//  A ---> B ---> C ---> A
struct graph initg()
{
    char verts[] = {'A', 'B', 'C', 'D'};

    struct edge edges[] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'A'},
        {'D', 'A'},
        {'B', 'D'},
    };

    struct graph graph;

    graph.directed = 1;

    graph.verts_n = 4;
    graph.edges_n = 5;

    memcpy(graph.verts_b, verts, graph.verts_n);
    memcpy(graph.edges_b, edges, graph.edges_n * sizeof(struct edge));

    return graph;
}

void cmd(struct graph *graph)
{
    while (1)
    {
        cls();
        puts_c("1) neighbor list", 0, 0);
        puts_c("2) adjacency matrix", 0, 1);

        switch (getc())
        {
        case '1':
            cls();
            put_flist(graph);
            break;
        case '2':
            cls();
            put_adjmat(graph);
            break;
        }

        puts_c("press any key...", 0, SCREEN_HEIGHT - 1);
        getc();
    }
}

int _kernel()
{
    struct graph graph = initg();
    cmd(&graph);

    return 0;
}
