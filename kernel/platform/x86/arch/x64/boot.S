.intel_syntax noprefix
.section .multiboot
.align 4
.long 0x1BADB002
.long 0x00000003
.long -(0x1BADB002 + 0x00000003)

.section .init.data,"aw"
.align 4096
.global boot_pml4
boot_pml4:
    .quad boot_pdpt + 0x003
    .fill 511, 8, 0

.align 4096
boot_pdpt:
    .quad boot_pd + 0x003
    .quad 0
    .quad boot_pd_high + 0x003
    .fill 509, 8, 0

.align 4096
boot_pd:
    .set page, 0
    .rept 512
        .quad page + 0x083
        .set page, page + 0x200000
    .endr

.align 4096
boot_pd_high:
    .quad boot_pt_high0 + 0x003
    .quad boot_pt_high1 + 0x003
    .quad boot_pt_high2 + 0x003
    .quad boot_pt_high3 + 0x003
    .fill 508, 8, 0

.align 4096
boot_pt_high0:
    .set page, 0x00100000
    .rept 512
        .quad page + 0x003
        .set page, page + 0x1000
    .endr

.align 4096
boot_pt_high1:
    .set page, 0x00300000
    .rept 512
        .quad page + 0x003
        .set page, page + 0x1000
    .endr

.align 4096
boot_pt_high2:
    .set page, 0x00500000
    .rept 512
        .quad page + 0x003
        .set page, page + 0x1000
    .endr

.align 4096
boot_pt_high3:
    .set page, 0x00700000
    .rept 512
        .quad page + 0x003
        .set page, page + 0x1000
    .endr

.align 16
gdt32:
    .quad 0x0000000000000000
    .quad 0x00af9a000000ffff
    .quad 0x00cf92000000ffff
gdt32_ptr:
    .word (3 * 8) - 1
    .quad gdt32

.align 8
.global x86_boot_info_ptr
x86_boot_info_ptr:
    .quad 0

.section .init
.code32
.extern _boot_start
.extern _kernel_entry_c
.extern x86_runtime_init
.extern _svc_start_stack
.extern _svc_stack
.extern _bss_start
.extern _bss_end

.global __entry
__entry:
    cli
    cld
    mov esp, offset _svc_start_stack
    lgdt [gdt32_ptr]

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, offset boot_pml4
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    jmp 0x08:long_mode_entry

.code64
.global __efi_entry
.global __ap_wait_entry
__efi_entry:
    cli
    cld
    mov [rip + x86_boot_info_ptr], rcx
    lea rax, [rip + boot_pml4]
    mov cr3, rax
    lea rsp, [rip + _svc_start_stack]
    lgdt [rip + gdt32_ptr]
    lea rax, [rip + long_mode_entry]
    push 0x08
    push rax
    retfq

__ap_wait_entry:
    mov rbx, rsi
    mov dword ptr [rbx + 12], 0x21
1:
    mov eax, dword ptr [rbx + 0]
    cmp eax, 2
    je 2f
    pause
    jmp 1b
2:
    mov dword ptr [rbx + 12], 0x22
    mov edi, dword ptr [rbx + 4]
    mov rax, qword ptr [rbx + 16]
    mov cr3, rax
    mov rsp, qword ptr [rbx + 32]
    mov rax, qword ptr [rbx + 24]
    jmp rax

long_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor eax, eax
    mov fs, ax
    mov gs, ax
    lea rsp, [rip + _svc_start_stack]
    xor ebp, ebp

    lea rdi, [rip + _bss_start]
    lea rcx, [rip + _bss_end]
    sub rcx, rdi
    xor eax, eax
    shr rcx, 3
    rep stosq

    call x86_runtime_init
    call _boot_start
    lea rsp, [rip + _svc_stack]
    call _kernel_entry_c

halt_forever:
    cli
    hlt
    jmp halt_forever
