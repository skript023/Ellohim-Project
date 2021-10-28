.DATA
    player_scid	dq	0

.CODE
    _set_rid_join PROC
	    mov [rax],player_scid
        lea rdi,[rsi+000000E0]
        mov rcx,rdi
        movups xmm0,[rax]
        mov eax,r12d
        movdqu [rsp+40],xmm0
        xchg [r14],eax
        mov [r14+04],r12d
    _set_rid_join ENDP
END