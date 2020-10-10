BOOTSEG = 0x07c0
INITSEG = 0x9000
SYSSEG = 0x1000
SYSSIZE = 0x3000
SETUPSEG = 0X9020
ENDSEG = SYSSEG + SYSSIZE  
SETUP_SIZE = 2
ROOT_DEV = 0x306

.text
entry _start
_start:
    mov ax,#BOOTSEG
    mov ds,ax
    mov ax,#INITSEG
    mov es,ax
    mov cx,#256
    xor si,si
    xor di,di

    rep
    movw
    jmpf go,#INITSEG
go:
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov sp,#0xff00

load_setup:
    mov ax,#0x0200
    add ax,#SETUP_SIZE
    mov bx,#0x0200
    mov cx,#0x0002
    mov dx,#0x0000
    int 0x13
    jnc ok_load_setup
    mov dx,#0x0000
    mov ax,#0x0000
    j load_setup

ok_load_setup:
    mov	dl,#0x00
	mov	ax,#0x0800		
	int	0x13
    mov ch,#00

    mov sectors,cx
    mov ax,#INITSEG
    mov es,ax

print_sth:
    mov ah,#0x03
    xor bh,bh
    int 0x10

    mov cx,#msg_end-msg1
    mov	bx,#0x000A		
	mov	bp,#msg1
	mov	ax,#0x1301	
	int	0x10
load_sys:
	mov	ax,#SYSSEG
	mov	es,ax		! segment of 0x010000
	call	read_it
	call	kill_motor

seg cs
	mov	ax,root_dev
	cmp	ax,#0
	jne	root_defined
	seg cs
	mov	bx,sectors
	mov	ax,#0x0208		! /dev/ps0 - 1.2Mb
	cmp	bx,#15
	je	root_defined
	mov	ax,#0x021c		! /dev/PS0 - 1.44Mb
	cmp	bx,#18
	je	root_defined
undef_root:
	jmp undef_root
root_defined:
	seg cs
	mov	root_dev,ax

! after that (everyting loaded), we jump to
! the setup-routine loaded directly after
! the bootblock:

	jmpi	0,SETUPSEG

! This routine loads the system at address 0x10000, making sure
! no 64kB boundaries are crossed. We try to load it as fast as
! possible, loading whole tracks whenever we can.
!
! in:	es - starting address segment (normally 0x1000)
!
sread:	.word 1+SETUP_SIZE	! sectors read of current track
head:	.word 0			
track:	.word 0			

read_it:
	mov ax,es
	test ax,#0x0fff
die:	jne die			
	xor bx,bx		
rp_read:
	mov ax,es
	cmp ax,#ENDSEG		
	jb ok1_read
	ret
ok1_read:
	seg cs
	mov ax,sectors
	sub ax,sread
	mov cx,ax
	shl cx,#9
	add cx,bx
	jnc ok2_read
	je ok2_read
	xor ax,ax
	sub ax,bx
	shr ax,#9
ok2_read:
	call read_track
	mov cx,ax
	add ax,sread
	seg cs
	cmp ax,sectors
	jne ok3_read
	mov ax,#1
	sub ax,head
	jne ok4_read
	inc track
ok4_read:
	mov head,ax
	xor ax,ax
ok3_read:
	mov sread,ax
	shl cx,#9
	add bx,cx
	jnc rp_read
	mov ax,es
	add ax,#0x1000
	mov es,ax
	xor bx,bx
	jmp rp_read

read_track:
	push ax
	push bx
	push cx
	push dx
	mov dx,track
	mov cx,sread
	inc cx
	mov ch,dl
	mov dx,head
	mov dh,dl
	mov dl,#0
	and dx,#0x0100
	mov ah,#2
	int 0x13
	jc bad_rt
	pop dx
	pop cx
	pop bx
	pop ax
	ret
bad_rt:	mov ax,#0
	mov dx,#0
	int 0x13
	pop dx
	pop cx
	pop bx
	pop ax
	jmp read_track

kill_motor:
	push dx
	mov dx,#0x3f2
	mov al,#0
	outb
	pop dx
	ret   
msg1:
    .byte 13,10
    .ascii "Loading WOS.."
    .byte 13,10,13,10
msg_end:
sectors:
    .word 0
.org 508
root_dev:
    .word ROOT_DEV
.org 510
boot_flag:
    .word 0xAA55



