[ORG 0x7c00]
[BITS 16]

%define NUM_OF_SECTORS 0x01
%define pSMAP 0x0000

; Main entry point where BIOS leaves us.
 
Main:
    jmp 0x0000:.FlushCS               ; Some BIOS' may load us at 0x0000:0x7C00 while other may load us at 0x07C0:0x0000.
                                      ; Do a far jump to fix this issue, and reload CS to 0x0000.
 
.FlushCS:   
    xor ax, ax
 
    ; Set up segment registers.
    mov ss, ax
    ; Set up stack so that it starts below Main.
    mov sp, Main
 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    cld
    
    ; set display mode by bios
    ; characters only
    ; 80*25
    ; 16 bit color
    mov ah,0x00
    mov al,0x03
    int 0x10
    
    mov si,BOOTING
    call Print
    
.Test_a20:
    call Check_a20
    test ax,ax
    jnz .A20_enabled               ; A20 has been enabled, skip enable a20
    
    ; enable a20 using bios
    mov ax, 0x2401
    int 0x15
    
    jmp .Test_a20
    
.A20_enabled:
    ; a20 is enabled
    ; detect memory
    mov si,pSMAP
    call Detect_memory
    
    mov si,BOOTLOADER
    call Print
    
    mov ah,0x02
    mov al,NUM_OF_SECTORS
    mov ch,0x0
    mov cl,0x02
    mov dh,0x0
    mov dl,0x80
    mov bx,0x7e00
    int 0x13
    
    test ah,ah
    jnz Error
    mov bx,[nSMAP]
    jmp 0x7e00
    
Error:    
    mov si,ERROR
    call Print
    jmp $

; messages
BOOTING db "Booting...", 0x0A, 0x0D, 0 
BOOTLOADER db "Loading bootloader...", 0x0A, 0x0D, 0
ERROR db "Error!!!", 0x0A, 0x0D, 0
;=========================================================
Check_a20:
.Check_a20:
    pushf
    push ds
    push es
    push di
    push si
 
    cli
 
    xor ax, ax ; ax = 0
    mov es, ax
 
    not ax ; ax = 0xFFFF
    mov ds, ax
 
    mov di, 0x0500
    mov si, 0x0510
 
    mov al, byte [es:di]
    push ax
 
    mov al, byte [ds:si]
    push ax
 
    mov byte [es:di], 0x00
    mov byte [ds:si], 0xFF
 
    cmp byte [es:di], 0xFF
 
    pop ax
    mov byte [ds:si], al
 
    pop ax
    mov byte [es:di], al
 
    mov ax, 0
    je .Check_a20__exit
 
    mov ax, 1
 
.Check_a20__exit:
    pop si
    pop di
    pop es
    pop ds
    popf
 
    ret
;=========================================================
; use the INT 0x15, eax= 0xE820 BIOS function to get a memory map
; inputs: es:di -> destination buffer for 24 byte entries
; outputs: bp = entry count, trashes all registers except esi
Detect_memory:
	xor ebx, ebx		; ebx must be 0 to start
	xor bp, bp		; keep an entry count in bp
	mov edx, 0x0534D4150	; Place "SMAP" into edx
	mov eax, 0xe820
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes
	int 0x15
	jc short .failed	; carry set on first call means "unsupported function"
	mov edx, 0x0534D4150	; Some BIOSes apparently trash this register?
	cmp eax, edx		; on success, eax must have been reset to "SMAP"
	jne short .failed
	test ebx, ebx		; ebx = 0 implies list is only 1 entry long (worthless)
	je short .failed
	jmp short .jmpin
.e820lp:
	mov eax, 0xe820		; eax, ecx get trashed on every int 0x15 call
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes again
	int 0x15
	jc short .e820f		; carry set means "end of list already reached"
	mov edx, 0x0534D4150	; repair potentially trashed register
.jmpin:
	jcxz .skipent		; skip any 0 length entries
	cmp cl, 20		; got a 24 byte ACPI 3.X response?
	jbe short .notext
	test byte [es:di + 20], 1	; if so: is the "ignore this data" bit clear?
	je short .skipent
.notext:
	mov ecx, [es:di + 8]	; get lower uint32_t of memory region length
	or ecx, [es:di + 12]	; "or" it with upper uint32_t to test for zero
	jz .skipent		; if length uint64_t is 0, skip entry
	inc bp			; got a good entry: ++count, move to next storage spot
	add di, 24
.skipent:
	test ebx, ebx		; if ebx resets to 0, list is complete
	jne short .e820lp
.e820f:
	mov [nSMAP], bp	; store the entry count
	clc			; there is "jc" on end of list to this point, so the carry must be cleared
	ret
.failed:
	stc			; "function unsupported" error exit
	ret
;=========================================================
Print:
    pushad
.PrintLoop:
    lodsb                             ; Load the value at [@es:@si] in @al.
    test al, al                       ; If AL is the terminator character, stop printing.
    je .PrintDone                  	
    mov ah, 0x0E	
    int 0x10
    jmp .PrintLoop                    ; Loop till the null character not found.
 
.PrintDone:
    popad                             ; Pop all general purpose registers to save them.
    ret
;=========================================================
; count of SMAPs
nSMAP dw 0x0