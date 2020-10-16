load_disk:   ;load dh sectors to es:bx from Drive NO.dl
    push ax
    push dx
    mov ah, 0x02 ;function mode
    mov al, dh
    mov ch, 0x00 ;cylinder 0
    mov dh, 0x00 ;head 0
    mov cl, 0x02 ;load from sector 2(index from 1)

    int 0x13
    jc disk_error
    pop dx
    cmp al, dh
    jne disk_error
    pop ax
    ret
disk_error:
    mov bx, msg_disk_error
    call print_str
    jmp $
msg_disk_error:
    db 'Load disk ERROR!', 0x0a, 0x0d, 0
