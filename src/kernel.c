#include "stdlib.h"

struct graph initg()
{
    char verts[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    struct edge edges[] = {
        {'A', 'D'},
        {'B', 'D'},
        {'C', 'D'},
        {'E', 'C'},
        {'C', 'G'},
        {'B', 'G'},
        {'G', 'G'},
        {'E', 'C'},
    };

    struct graph graph;

    graph.directed = 1;

    graph.verts_n = 7;
    graph.edges_n = 8;

    memcpy(graph.verts_b, verts, graph.verts_n);
    memcpy(graph.edges_b, edges, graph.edges_n * sizeof(struct edge));

    return graph;
}

void cmd(struct graph *graph)
{
    while (1)
    {
    loop_start:

        cls();
        puts_c("1) successors list", 0, 0);
        puts_c("2) adjacency matrix", 0, 1);
        puts_c("3) find path between 2 vertices", 0, 2);

        switch (getc())
        {
        case '1':
            cls();
            put_slist(graph, 'C');
            break;
        case '2':
            cls();
            put_adjmat(graph);
            break;
        case '3':
            cls();
            bf_path2v(graph, 'A', 'A');
            break;
        default:
            goto loop_start;
        }

        puts_c("press any key...", 0, SCREEN_HEIGHT - 1);
        getc();
    }
}

int kernel()
{
    struct graph graph = initg();
    cmd(&graph);

    return 0;
}
