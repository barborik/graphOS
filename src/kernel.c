int main()
{
	volatile char* VIDEO_MEM = (volatile char*)0xB8000;

	*VIDEO_MEM = 'H';
	*VIDEO_MEM++ = 0x0f;

	while(1);
	return 0;
};
