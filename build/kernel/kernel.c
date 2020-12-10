


#include "../drivers/ports.h"
//#include "util.h"
#define ROWS 25
#define COLS 80


void	set_cursor(int x, int y)
{
	unsigned char pos = y * COLS + x;
	pos = x;
	if (y > 0)
	{
		pos += (y * 80);
	}
	port_byte_out(0x3d4, 0x0f);
	port_byte_out(0x3d5, (unsigned short) (pos & 0xff));
//	port_word_out(0x3d5, (pos >> 8));
	port_byte_out(0x3d4, 0x0e);
	
	port_byte_out(0x3d5, (unsigned short) ((pos >> 8) & 0xff));	
//	port_word_out(0x3d5, (pos & 0xff));
}

void	terminal_init()
{

	int size = ROWS * COLS;
	int i;
	char *screen = 0xb8000;
	i = 0;
	while (i < size)
	{
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = 0x0f;
		i++;	
	}
	set_cursor(0, 2);
}


void kprint(char *message)
{
	char *vid_mem = (char *)0xb8000;
	int i;
	int x;
	
//	set_cursor(1, 1);
	i = 0;
	x = 0;
	while (message[i])
	{
		vid_mem[x] = message[i];
		x += 2;
		i++;
	}
}

void main()
{
	char *video_memory = (char *)0xb8000;
//	*video_memory = 'X';	
	
//	kprint("Hello world");
	terminal_init();
	kprint("HEllo world");
//	clear_screen();

	int i;

/*(	i = 0;
	while (i < 3)
	{
		char str[255];
		int_to_ascii(i, str);
		kprint_at(str, 0, i);
		i++;
	}*/
//	kprint_at("THis text forces the kernel to scroll. Row 0 will vanish", 60, 24);
//	kprint("ANd with this text, the kernel will scroll again and now I will diasapepar too.");

	/*
	port_byte_out(0x3d4, 14);
	int position;

	position = port_byte_in(0x3d5);
	position = position << 8;

	port_byte_out(0x3d4, 15);
	position += port_byte_in(0x3d5);

	int offset_from_vga = position * 2;
	char *vga = (char *)0xb8000;
	vga[offset_from_vga] = 'x';
	vga[offset_from_vga+1] = 0x0f;	
	*/
}
