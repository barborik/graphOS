#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

struct edge
{
    char vert1;
    char vert2;
};

struct graph
{
    char nverts;
    char nedges;

    char directed;
    char *verts;
    struct edge *edges;
};

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

void puts(char *str)
{
    int off = 0;
    while (*str)
    {
        putc(*str++, off++, 0);
    }
}

void cls()
{
    int i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        putc(0, i, 0);
    }
}

void strcpy(char *dest, char *src, int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        dest[i] = src[i];
    }
}

void put_flist(struct graph *graph)
{
    char flist_str[SCREEN_WIDTH * SCREEN_HEIGHT + 1];

    // clear the buffer
    int i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT + 1; i++)
    {
        flist_str[i] = ' ';
    }
    flist_str[SCREEN_WIDTH * SCREEN_HEIGHT] = 0; // null-terminate it

    if (graph->directed)
    {
        char *arrow = "--->";
        for (i = 0; i < graph->nedges; i++)
        {
            flist_str[SCREEN_WIDTH * i] = graph->edges[i].vert1;
            strcpy(&flist_str[SCREEN_WIDTH * i + 2], arrow, 4);
        }
    }

    puts(flist_str);
}
