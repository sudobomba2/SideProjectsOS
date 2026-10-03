[BITS 16]
[ORG 0x7C00]

	jmp short start
	nop
g_BPBOEM: db 'MSDOS5.0'
g_BPBBytesPerSector: dw 512
g_BPBSectorsPerCluster: db 1
g_BPBReservedSectors: dw 1
g_BPBFatCount: db 2
g_BPBDirectoryEntryCount: dw 0xE0
g_BPBTotalSectors: dw 2880
g_BPBMediaDescriptorType: db 0xF0
g_BPBSectorsPerFAT: dw 9
g_BPBSectorsPerTrack: dw 18
g_BPBNumberOfHeads: dw 2
g_BPBHiddenSectors: dd 0
g_BPBLargeSectorCount: dd 0
g_BootDriveNumber: db 0
		   db 0
g_BootSignature: db 0x29
g_BootVolumeID: dd 0x12345678
g_BootVolumeLabel: db 'NO NAME    '
g_BootFileSystemID: db 'FAT12   '

start:
	cli
	cld
.main:
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x7C00
	sti
.next:
	push es
	push word .after
	retf
.after:
	mov [g_BootDriveNumber],dl
	push es
	mov ah,0x08
	int 0x13
	jc floppy_error
	pop es
	and cl,0x3F
	xor ch,ch
	mov [g_BPBSectorsPerTrack],cx
	inc dh
	mov [g_BPBNumberOfHeads],dh
	mov ax,[g_BPBSectorsPerFAT]
	mov bl,[g_BPBFatCount]
	xor bh,bh
	mul bx
	add ax,[g_BPBReservedSectors]
	push ax
	mov ax,[g_BPBDirectoryEntryCount]
	shl ax,5
	xor dx,dx
	div word[g_BPBBytesPerSector]
	test dx,dx
	jz .root_dir_after
	inc ax
.root_dir_after:
	mov cl,al
	pop ax
	mov dl,[g_BootDriveNumber]
	mov bx,g_BootBuffer
	call disk_read
	xor bx,bx
	mov di,g_BootBuffer
.search_kernel:
	mov si,g_BootFileNameLoader
	mov cx,11
	push di
	repe cmpsb
	pop di
	je .found_kernel
	add di,32
	inc bx
	cmp bx,[g_BPBDirectoryEntryCount]
	jl .search_kernel
	jmp kernel_not_found_error
.found_kernel:
	mov ax,[di+26]
	mov [g_BootLoaderCluster],ax
	mov ax,[g_BPBReservedSectors]
	mov bx,g_BootBuffer
	mov cl,[g_BPBSectorsPerFAT]
	mov dl,[g_BootDriveNumber]
	call disk_read
	mov bx,CLOADSEG
	mov es,bx
	mov bx,CLOADOFF
.load_kernel_loop:
	mov ax,[g_BootLoaderCluster]
	add ax,31
	mov cl,1
	mov dl,[g_BootDriveNumber]
	call disk_read
	mov ax,[g_BPBBytesPerSector]
	shr ax,4
	mov cx,es
	add ax,cx
	mov es,ax
	mov ax,[g_BootLoaderCluster]
	mov cx,3
	mul cx
	mov cx,2
	div cx
	mov si,g_BootBuffer
	add si,ax
	mov ax,[ds:si]
	or dx,dx
	jz .even
.odd:
	shr ax,4
	jmp .next_cluster_after
.even:
	and ax,0x0FFF
.next_cluster_after:
	cmp ax,0x0FF8
	jae .read_finish
	mov [g_BootLoaderCluster],ax
	jmp .load_kernel_loop
.read_finish:
	mov dl,[g_BootDriveNumber]
	xor si,si
	xor di,di
	mov ax,CSTARTSEG
	mov ds,ax
	mov es,ax
	call kill_motor
	jmp CSTARTSEG:CSTARTOFF
.hanghalt:
	cli
	hlt
	jmp .hanghalt
	
floppy_error:
	jmp wait_key_and_reboot

kernel_not_found_error:
	jmp wait_key_and_reboot

wait_key_and_reboot:
	xor ah,ah
	int 0x16
	call disk_reset
	jmp 0xFFFF:0x0000
.halt:
	cli
	hlt

lba_to_chs:
	push ax
	push dx
	xor dx,dx
	div word[g_BPBSectorsPerTrack]
	inc dx
	mov cx,dx
	xor dx,dx
	div word[g_BPBNumberOfHeads]
	mov dh,dl
	mov ch,al
	shl ah,6
	or cl,ah
	pop ax
	mov dl,al
	pop ax
	ret

disk_read:
	push ax
	push bx
	push cx
	push dx
	push di
	push cx
	call lba_to_chs
	pop ax
	mov ah,0x02
	mov di,5
.retry:
	pusha
	stc
	int 0x13
	jnc .done
	popa
	call disk_reset
	dec di
	test di,di
	jnz .retry
.fail:
	jmp floppy_error
.done:
	popa
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	ret

disk_reset:
	pusha
	mov ah,0
	stc
	int 0x13
	jc floppy_error
	popa
	ret
	
kill_motor:
	push ax
	push dx
	mov dx,0x3F2
	mov al,0x0C
	out dx,al
	pop dx
	pop ax
	ret

g_BootFileNameLoader: db 'KERNEL64   '
g_BootLoaderCluster: dw 0
CLOADSEG equ 0x0800
CLOADOFF equ 0x0000
CSTARTSEG equ 0x0000
CSTARTOFF equ 0x8000
g_BootBuffer equ 0x1000

times 510-($-$$) db 0
dw 0xAA55
	
