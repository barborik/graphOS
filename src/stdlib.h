#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

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
