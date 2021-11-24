#include "stdlib.h"
#include "graph.h"

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
    char vert1;
    char vert2;

    while (1)
    {
    loop_start:

        cls();
        puts_c("BarboSoft graphOS 2021", 0, 0);
        puts_c("1) successors list", 0, 2);
        puts_c("2) adjacency matrix", 0, 3);
        puts_c("3) find path between 2 vertices", 0, 4);

        switch (getc())
        {
        case '1':
            cls();
            put_slist(graph);
            break;
        case '2':
            cls();
            put_adjmat(graph);
            break;
        case '3':
            cls();
            puts("press key with ascii value of vertex 1");
            vert1 = getc();
            cls();
            puts("press key with ascii value of vertex 2");
            vert2 = getc();

            fill_b(put_path(fpath_2v(graph, vert1, vert2)), 0, MAX_VERTS);
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
