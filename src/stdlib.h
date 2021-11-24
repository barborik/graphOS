#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

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

    char verts_b[20];
    struct edge edges_b[256];

    char adjmat[20 * 20];
};

// get character from keyboard
char getc()
{
    char c;
    __asm
    {
        mov ah, 0
        int 0x16
        mov byte ptr [c], al
    }
    return c;
}

// put character at coords
void putc(char c, int x, int y)
{
    int off = (y * SCREEN_WIDTH + x) * 2;

    __asm
    {
        mov ax, 0xb800
        mov es, ax
        mov al, byte ptr [c]
        mov bx, word ptr [off]
        mov [es:bx], al
    }
}

// print null-terminated string
void puts(char *str)
{
    int ofs = 0;
    while (*str)
    {
        putc(*str++, ofs++, 0);
    }
}

// print null-terminated string at coords
void puts_c(char *str, int x, int y)
{
    int ofs = SCREEN_WIDTH * y + x;
    while (*str)
    {
        putc(*str++, ofs++, 0);
    }
}

// print string with specified length
void puts_l(char *str, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        putc(*str++, i, 0);
    }
}

// clear screen
void cls()
{
    int i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        putc(0, i, 0);
    }
}

// fill buffer with specified character
void fill_b(char *buff, char c, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        buff[i] = c;
    }
}

// memory copy
void memcpy(void *dst, void *src, int num)
{
    int i;
    char *d = dst;
    char *s = src;
    for (i = 0; i < num; i++)
    {
        d[i] = s[i];
    }
}

void put_slist(struct graph *graph, char vert)
{
    if (graph->directed)
    {
        char cvert = vert;
        int traversed_n = 0;
        struct edge *traversed_b[256];

        int i;
        int j;
        for (i = 0; i < graph->edges_n; i++)
        {
            // check if exists
            if (graph->edges_b[i].vert1 == cvert)
            {
                // check if not already traversed
                for (j = 0; j < graph->edges_n; j++)
                    if (&graph->edges_b[i] == traversed_b[j])
                        goto next_edge;
                // continue if not
                putc(graph->edges_b[i].vert1, 6 * traversed_n, 0);
                puts_c("--->", 6 * traversed_n + 2, 0);
                putc(graph->edges_b[i].vert2, 6 * traversed_n + 7, 0);

                traversed_n++;
                cvert = graph->edges_b[i].vert2;
            }
        next_edge:;
        }
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

int bf_path2v(struct graph *graph, char vert1, char vert2)
{
    if (graph->directed)
    {
    }
}
