#define MAX_VERTS 20
#define MAX_EDGES 256

#define NULL 0

struct edge
{
    char vert1;
    char vert2;
};

struct graph
{
    char directed;

    char verts_n;
    char edges_n;

    char verts_b[MAX_VERTS];
    struct edge edges_b[MAX_EDGES];

    char adjmat[MAX_VERTS * MAX_VERTS];
};

// checks if the edge has been traversed
// traversed = 1
// untraversed = 0
int check_t(struct graph *graph, struct edge *traversed[], int *traversed_c, struct edge *edge)
{
    int i = 0;
    for (i = 0; i < *traversed_c; i++)
        if (traversed[i] == edge)
            return 1;
    return 0;
}

// returns next vert linked through an untraversed edge to the specified vert
// returns NULL if none
char next_vert(struct graph *graph, struct edge *traversed[], int *traversed_c, char vert)
{
    int i;
    int j;

    for (i = 0; i < graph->edges_n; i++)
    {
        if (graph->edges_b[i].vert1 == vert)
        {
            if (check_t(graph, traversed, traversed_c, &graph->edges_b[i]))
                goto loop_end;

            traversed[*traversed_c] = &graph->edges_b[i];
            *traversed_c += 1;

            return graph->edges_b[i].vert2;
        }
    loop_end:;
    }

    return NULL;
}

// returns the number of untraversed edges from the specified vert
int utraversed_v(struct graph *graph, struct edge *traversed[], int *traversed_c, char vert)
{
    int i;
    int utraversed_c = 0;

    for (i = 0; i < graph->edges_n; i++)
    {
        if (graph->edges_b[i].vert1 == vert)
        {
            if (!check_t(graph, traversed, traversed_c, &graph->edges_b[i]))
                utraversed_c++;
        }
    }

    return utraversed_c;
}

// slist (successors list) rows are separated by null characters, end of list is marked as 2 null characters
// the function assumes slist length is equal to MAX_EDGES
void get_slist_v(struct graph *graph, char *slist, char vert)
{
    int i = 0;

    int traversed_c = 0;
    struct edge *traversed[MAX_EDGES];

    int edge_count_b[MAX_EDGES];

    // first pass
    do
    {
        slist[i] = vert;
        edge_count_b[i] = utraversed_v(graph, traversed, &traversed_c, vert);
        i++;
    } while (vert = next_vert(graph, traversed, &traversed_c, vert));
    //slist[i] = 0;
}

void put_slist_v(struct graph *graph, char vert, int ofs)
{
    int i;

    char slist[MAX_EDGES];
    fill_b(slist, 0, MAX_EDGES);
    get_slist_v(graph, slist, vert);

    for (i = 0; i < MAX_EDGES; i++)
    {
        if (slist[i] == 0)
        {
            i++;
            if (slist[i] == 0)
                break;
        }

        putc(slist[i], i * 6, ofs);
        if (slist[i + 1] != 0)
            puts_c("-->", i * 6 + 2, ofs);
    }
}

void put_slist(struct graph *graph)
{
    int i;

    for (i = 0; i < graph->verts_n; i++)
    {
        put_slist_v(graph, graph->verts_b[i], i);
    }
}

void gen_adjmat(struct graph *graph)
{
    int i;
    int j;
    int k;

    for (i = 0; i < graph->verts_n; i++)
    {
        for (j = 0; j < graph->verts_n; j++)
        {
            int adj_c = 0;
            for (k = 0; k < graph->edges_n; k++)
            {
                if (graph->edges_b[k].vert1 == graph->verts_b[i] && graph->edges_b[k].vert2 == graph->verts_b[j])
                    adj_c++;
                else if (graph->edges_b[k].vert1 == graph->verts_b[j] && graph->edges_b[k].vert2 == graph->verts_b[i])
                    adj_c++;
            }
            graph->adjmat[graph->verts_n * i + j] = adj_c;
        }
    }
}

void put_adjmat(struct graph *graph)
{
    int i;
    int j;

    gen_adjmat(graph);

    for (i = 0; i < graph->verts_n; i++)
    {
        putc(graph->verts_b[i], 0, i + 2);
        putc('|', 1, i + 2);
        putc(graph->verts_b[i], i + 2, 0);
        putc('-', i + 2, 1);

        for (j = 0; j < graph->verts_n; j++)
            putc(graph->adjmat[graph->verts_n * i + j] + 48, j + 2, i + 2);
    }
}

char *put_path(char *visited)
{
    int i = 0;

    if (visited == NULL)
    {
        puts("error: path not found");
        return NULL;
    }
    else
        puts("success: path found");

    while (visited[i] != 0)
    {
        putc(visited[i], i * 6, 1);
        if (visited[i + 1])
            puts_c("-->", i * 6 + 2, 1);
        i++;
    }

    return visited;
}

int check_v(struct graph *graph, char vert1, char vert2)
{
    int i;
    int check = 0;
    for (i = 0; i < graph->verts_n; i++)
    {
        if (graph->verts_b[i] == vert1)
            check++;
        if (graph->verts_b[i] == vert2)
            check++;
    }

    if (check == 2)
        return 1;
    return 0;
}

// running out of time, bruteforce has to do
char *fpath_2v(struct graph *graph, char vert1, char vert2)
{
    int visited_c = 0;
    static char visited[MAX_VERTS];
    int traversed_c = 0;
    struct edge *traversed[MAX_EDGES];

    char cvert = vert1;
    cls();

    if (!check_v(graph, vert1, vert2))
        return NULL;
    do
    {
        do
        {
            visited[visited_c] = cvert;
            visited_c++;

            // check if found
            if (visited[visited_c - 1] == vert2)
                return visited;
        } while (cvert = next_vert(graph, traversed, &traversed_c, cvert));

        cvert = visited[visited_c - 2];
        visited_c -= 2;
    } while (visited[0] == vert1);

    return NULL;
}
