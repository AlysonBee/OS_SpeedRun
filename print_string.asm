

[org 0x7c00]

mov bx, HELLO
call print

call print_nl

mov bx, GOODBYE
call print
call print_nl

mov dx, 0x12fe
call print_hex

jmp $

%include "print.asm"
%include "hex.asm"

HELLO: db "hello world"
GOODBYE: db "GOODBYTE"

times 510-($-$$) db 0
dw 0xaa55
