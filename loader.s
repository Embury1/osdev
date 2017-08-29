global loader                                           ; the entry symbol for ELF
global kernel_stack                                     ; the address of the kernel stack

extern kmain

MAGIC_NUMBER    equ 0x1BADB002                          ; define the magic number constant
ALIGN_MODULES   equ 0x00000001                          ; tell GRUB to align modules
FLAGS           equ ALIGN_MODULES
CHECKSUM        equ -(MAGIC_NUMBER + FLAGS)             ; calculate the checksum
                                                        ; (magic number + checksum + flags should equal 0)

KERNEL_STACK_SIZE       equ 4096                        ; size of stack in bytes

section .bss
align 4                                                 ; align at 4 bytes
kernel_stack:                                           ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                              ; reserve stack for the kernel_stack

section .text                                           ; start of the text (code) section
align 4                                                 ; the code must be 4 byte aligned
    dd MAGIC_NUMBER                                     ; write the magic number to the machine code,
    dd ALIGN_MODULES                                    ; align modules,
    dd CHECKSUM                                         ; and the checksum

loader:                                                 ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE           ; point esp to the start of the
                                                        ; stack (end of memory area)

enter_kmain:
    push ebx
    call kmain

hang:
    jmp hang