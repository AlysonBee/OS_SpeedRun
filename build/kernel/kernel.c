
#include "../drivers/ports.h"
#include "util.h"


void main()
{
//	clear_screen();

	int i;

	i = 0;
	while (i < 24)
	{
		char str[255];
		int_to_ascii(i, str);
		kprint_at(str, 0, i);
		i++;
	}
	kprint_at("THis text forces the kernel to scroll. Row 0 will vanish", 60, 24);
	kprint("ANd with this text, the kernel will scroll again and now I will diasapepar too.");

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
