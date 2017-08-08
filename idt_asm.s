global idt_load

extern interrupt_handler

section .text

%macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword 0                         ; push 0 as error code
    push    dword %1                        ; push the interrupt number
    jmp     common_interrupt_handler        ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword %1                        ; push the interrupt number
    jmp     common_interrupt_handler        ; jump to the common handler
%endmacro

common_interrupt_handler:                   ; the common parts of the generic interrupt handler
    push    esp
    add     dword [esp], 8
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    ebp
    push    esi
    push    edi
    call interrupt_handler
    pop     edi
    pop     esi
    pop     ebp
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    pop     esp
    iret

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

idt_load:
    mov     eax, [esp+4]
    lidt    eax
    ret