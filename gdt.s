global load_gdt

SEGSEL_KERNEL_CS equ 0x08
SEGSEL_KERNEL_DS equ 0x10

section .text

load_gdt:
    mov     eax, [esp+4]
    lgdt    [eax]
    jmp     SEGSEL_KERNEL_CS:.reload_segments

.reload_segments:
    mov     ax, SEGSEL_KERNEL_DS
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     gs, ax
    mov     fs, ax
    ret