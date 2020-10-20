[org 0x7c00]

mov [BOOT_DEV], dl ;BIOS set boot drive in dl
mov bp, 0x8000
mov sp, bp
mov bx, msg_1
call print_str

mov dl, [BOOT_DEV]
mov dh, 5          ;number of sectors

mov bx, 0x1000
call load_disk
cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 0x1
mov cr0, eax

jmp 8:init_pm

;mov dx, [0x9000]
;call print_hex

;mov dx, [0x9000 + 512]
;call print_hex
%include "boot/boot_sect_print.asm"
%include "boot/boot_sect_print_hex.asm"
%include "boot/boot_sect_load_disk.asm"
%include "boot/GDT.asm"
msg_1:
    db 'Hello,WOS!', 0x0a, 0x0d, 0
msg_2:
    db 'Good bye!', 0x0a, 0x0d, 0
BOOT_DEV:
    db 0


[bits 32]
init_pm:
    mov ax, 16
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    call begin_pm
    jmp 0x1000

begin_pm:
    ;mov ebx, msg_pm
   ; call print_str_pm
    ret




times 510-($-$$) db 0

dw 0xaa55



