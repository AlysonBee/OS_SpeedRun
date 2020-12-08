

#include "screen.h"
#include "ports.h"
#include "../kernel/util.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char addr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint_at(char *message, int col, int row)
{
	int offset;
	if (col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else
	{
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
	int i =0;
	while (message[i] != 0)
	{
		offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void kprint(char *message)
{
	kprint_at(message, -1, -1);
}

int print_char(char c, int col, int row, char attr)
{
	unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
	if (!attr) attr = WHITE_ON_BLACK;

	if (col >= MAX_COLS || row >= MAX_ROWS)
	{
		vidmem[2 * (MAX_COLS) * (MAX_ROWS) -2] = 'E';
		vidmem[2 * (MAX_COLS) * (MAX_ROWS) -1] = RED_ON_WHITE;
		return get_offset(col, row);
	}
	int offset;
	if (col >= 0 && row >= 0) offset = get_offset(col, row);
	
	if (c == '\n')
	{
		row = get_offset_row(offset);
		offset = get_offset(0, row+1);
	}
	else
	{
		vidmem[offset] = c;
		vidmem[offset + 1] = attr;
		offset += 2;
	}

	if (offset >= MAX_ROWS * MAX_COLS * 2)
	{
		int i;
		i = 1;
		while (i < MAX_ROWS)
		{
			memory_copy(get_offset(0, i) + VIDEO_ADDRESS,
				get_offset(0, i-1) + VIDEO_ADDRESS,
				MAX_COLS * 2);
			i++;
		}
		char *last_line = get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
		i = 0;
		while (i < MAX_COLS * 2)
		{
			last_line[i] = 0;
			i++;
		}
		offset -= 2 * MAX_COLS;
	}
	set_cursor_offset(offset);
	return offset;
}

int get_cursor_offset()
{
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset * 2;	
}

void set_cursor_offset(int offset)
{
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}


void clear_screen()
{
	int screen_size;
	int i;
	char *screen = (char *)VIDEO_ADDRESS;

	screen_size = MAX_COLS * MAX_ROWS;
	i = 0;
	while (i < screen_size)
	{
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = WHITE_ON_BLACK;
		i++;
	}
	set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row)
{
	return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset)
{
	return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
	return (offset - (get_offset_row(offset) * 2* MAX_COLS)) / 2;
}













































