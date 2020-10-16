print_str:
    push ax
    mov ah, 0x0e
loop:
    mov al, [bx]
    cmp al, 0
    je print_end
    int 0x10
    add bx, 1
    jmp loop
print_end:
    pop ax
    ret
