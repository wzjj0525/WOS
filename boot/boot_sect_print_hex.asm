;print dx with HEX
print_hex:
    pusha
    and ax, 0
    and cx, 0
    cmp dx, 0
    je print_hex_0
    jne print_hex_n0
print_hex_0:
    mov al, '0'
    int 0x10
    jmp print_hex_end
print_hex_n0:
    mov ax, dx
    and dx, 0
    mov bx, 0x10
loop1:
    div bx
    push dx
    add cx, 1
    cmp ax, 0
    je print_stack
    and dx, 0
    jmp loop1
print_stack:
    mov ah, 0x0e
    pop bx
    mov al, bl
    add al, 48
    cmp al, 58
    jge great
    jmp print_char
great:
    add al, 7
print_char:
    int 0x10
    loop print_stack
    jmp print_hex_end


print_hex_end:
    mov bx, str_nextline
    call print_str
    popa
    ret

str_nextline:
    db 0x0a, 0x0d, 0
