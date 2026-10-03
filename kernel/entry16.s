; Real-Mode -> Protected Mode -> Long Mode transitions

BOOTINFO equ 0x500
E820_BUF equ BOOTINFO+0x10
E820_MAX equ 64
PML4 equ 0x1000
PDPT equ 0x2000
PD equ 0x3000
STACK_TOP equ 0x90000
BOOTDRIVE equ BOOTINFO+0x00
BOOTPARTOFF equ BOOTINFO+0x02
BOOTPARTSEG equ BOOTINFO+0x04
E820_COUNT equ BOOTINFO+0x08
CODE32 equ 0x08
DATA32 equ 0x10
CODE64 equ 0x18

section .text.entry progbits alloc exec nowrite align=16
global start
global BOOTDRIVE
global BOOTPARTOFF
global BOOTPARTSEG
extern entry64
extern __bss_start
extern __bss_end

[BITS 16]
start:
	cli
	cld
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x7C00
	mov [BOOTDRIVE],dl
	mov [BOOTPARTOFF],si
	mov [BOOTPARTSEG],di
	sti
	call check_cpu
	call enable_a20
	call get_e820
	cli
	lgdt [gdt_desc]
	mov eax,cr0
	or eax,1
	mov cr0,eax
	jmp CODE32:pm32

check_cpu:
	pushfd
	pop eax
	mov ecx,eax
	xor eax,1<<21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax,ecx
	je .no_cpuid
	mov eax,0x80000000
	cpuid
	cmp eax,0x80000001
	jb .no_ext
	mov eax,0x80000001
	cpuid
	test edx,1<<29
	jz .no_lm
	ret
.no_cpuid:
	mov si,msg_no_cpuid
	jmp fatal
.no_ext:
	mov si,msg_no_ext
	jmp fatal
.no_lm:
	mov si,msg_no_lm
	jmp fatal
	
disk_reset:
	pusha
	mov ah,0
	stc
	int 0x13
	jc kill_motor
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
	
kbc_wait_input_clear:
	in al,0x64
	test al,0x02
	jnz kbc_wait_input_clear
	ret
	
kbc_wait_output_full:
	in al,0x64
	test al,0x01
	jz kbc_wait_output_full
	ret
	
check_a20:
	push ds
	push es
	push si
	push di
	xor ax,ax
	mov ds,ax
	mov ax,0xFFFF
	mov es,ax
	mov si,0x0500
	mov di,0x0510
	mov al,[si]
	push ax
	mov al,es:[di]
	push ax
	mov byte [si],0x00
	mov byte es:[di],0xFF
	mov al,[si]
	cmp al,es:[di]
	jne .enabled
	pop ax
	mov es:[di],al
	pop ax
	mov [si],al
	xor ax,ax
	jmp .exit
.enabled:
	pop ax
	mov es:[di],al
	pop ax
	mov [si],al
	mov ax,1
.exit:
	pop di
	pop si
	pop es
	pop ds
	ret
	
enable_a20:
	call check_a20
	cmp ax,1
	je .done
.bios:
	mov ax,0x2401
	int 0x15
	call check_a20
	test ax,ax
	jnz .done
.fast:
	in al,0x92
	or al,0x02
	out 0x92,al
	call check_a20
	cmp ax,1
	je .done
.kbc:
	call kbc_wait_input_clear
	mov al,0xAD
	out 0x64,al
	call kbc_wait_input_clear
	mov al,0xD0
	out 0x64,al
	call kbc_wait_output_full
	in al,0x60
	push ax
	call kbc_wait_input_clear
	mov al,0xD1
	out 0x64,al
	call kbc_wait_input_clear
	pop ax
	or al,0x02
	out 0x60,al
	call kbc_wait_input_clear
	mov al,0xAE
	out 0x64,al
	call check_a20
	cmp ax,1
	je .done
.fail:
	mov si,msg_no_a20
	jmp fatal
.done:
	ret

get_e820:
	xor ebx,ebx
	xor si,si
	mov di,E820_BUF
.next:
    mov eax,0xE820
	mov edx,0x534D4150
	mov ecx,24
	mov dword[di+20],1
	int 0x15
	jc .done
	cmp eax,0x534D4150
	jne .done
	mov eax,[di+8]
	or eax,[di+12]
	jz .skip
	inc si
	add di,24
	cmp si,E820_MAX
	jae .done
.skip:
	test ebx,ebx
	jnz .next
.done:
	movzx esi,si
	mov [E820_COUNT],esi
	ret

puts:
	pusha
.next:
	lodsb
	test al,al
	jz .done
	mov ah,0x0E
	mov bh,0
	mov bl,0x07
	int 0x10
	jmp .next
.done:
	popa
	ret
	
fatal:
	call puts
	mov si,msg_press_key
	call puts
	xor ax,ax
	int 0x16
	call kill_motor
	call apm_poweroff
	ret
	
apm_poweroff:
	mov ax,0x5300
	xor bx,bx
	int 0x15
	jc .vmfallback
	cmp bx,0x504D
	jne .vmfallback
	mov ax,0x5301
	xor bx,bx
	int 0x15
	jnc .connected
	cmp ah,0x02
	jne .vmfallback
.connected:
	mov si,apm_available
	call puts
	mov ax,0x530E
	xor bx,bx
	mov cx,0x0102
	int 0x15
	mov ax,0x5308
	mov bx,0x0001
	mov cx,0x0001
	int 0x15
	mov ax,0x5307
	mov bx,0x0001
	mov cx,0x0003
	int 0x15
.vmfallback:
	mov si,no_apm_msg
	call puts
	mov dx,0x604
	mov ax,0x2000
	out dx,ax
	mov dx,0xB004
	mov ax,0x2000
	out dx,ax
	mov dx,0x4004
	mov ax,0x3400
	out dx,ax
	stc
.hanghalt_apm:
	mov si,hang_halt_msg
	call puts
	cli
	call kill_motor
	call disk_reset
	hlt
	jmp .hanghalt_apm
	ret

msg_no_cpuid: db "CPU has no CPUID instruction",13,10,0
msg_no_ext: db "CPU has no extended CPUID leaves",13,10,0
msg_no_lm: db "CPU does not support long mode (x86-64)",13,10,0
msg_no_a20: db "Could not enable the A20 line",13,10,0
msg_press_key: db "Press any key to power off...",13,10,0
apm_available: db "APM is Available, Shutting down...",13,10,0
no_apm_msg: db "No APM Detected",13,10,"Using VM Shutdown...",13,10,0
hang_halt_msg: db "No APM Detected",13,10,"It is now safe to turn off your computer",13,10,0

align 8
gdt:
	dq 0
	dq 0x00CF9A000000FFFF
	dq 0x00CF92000000FFFF
	dq 0x00AF9A000000FFFF
gdt_end:

gdt_desc:
	dw gdt_end-gdt-1
	dd gdt

[BITS 32]
pm32:
	mov ax,DATA32
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov esp,STACK_TOP
	mov edi,__bss_start
	mov ecx,__bss_end
	sub ecx,edi
	xor eax,eax
	rep stosb
	mov edi,PML4
	mov ecx,0x3000/4
	xor eax,eax
	rep stosd
	mov dword[PML4],PDPT|3
	mov dword[PDPT],PD|3
	mov edi,PD
	mov eax,0x83
	mov ecx,512
.pd:
    mov [edi],eax
	add eax,0x200000
	add edi,8
	loop .pd
	mov eax,cr4
	or eax,1<<5
	mov cr4,eax
	mov eax,PML4
	mov cr3,eax
	mov ecx,0xC0000080
	rdmsr
	or eax,1<<8
	wrmsr
	mov eax,cr0
	or eax,1<<31
	mov cr0,eax
	jmp CODE64:lm64

[BITS 64]
lm64:
	xor eax,eax
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov dword[0xB8000],0x0F4B0F4F
	mov rsp,STACK_TOP
	mov edi,BOOTINFO
	call entry64
.hang:
	cli
	hlt
	jmp .hang
	ret
