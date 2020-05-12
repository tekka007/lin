	.file	"asm-offsets.c"
# GNU C (Ubuntu 4.8.5-4ubuntu8) version 4.8.5 (x86_64-linux-gnu)
#	compiled by GNU C version 4.8.5, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0
# warning: GMP header version 6.1.2 differs from library version 6.2.0.
# warning: MPFR header version 4.0.1 differs from library version 4.0.2.
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -nostdinc
# -I /home/olivier/kernel/linux-test/arch/x86/include -I include
# -imultilib 32 -imultiarch i386-linux-gnu -D __KERNEL__ -D CONFIG_AS_CFI=1
# -D CONFIG_AS_CFI_SIGNAL_FRAME=1 -D CONFIG_AS_CFI_SECTIONS=1
# -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
# -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
# -isystem /usr/lib/gcc/x86_64-linux-gnu/4.8/include
# -include include/generated/autoconf.h
# -MD arch/x86/kernel/.asm-offsets.s.d arch/x86/kernel/asm-offsets.c -m32
# -msoft-float -mregparm=3 -mpreferred-stack-boundary=2 -march=atom
# -mtune=atom -maccumulate-outgoing-args -mno-sse -mno-mmx -mno-sse2
# -mno-3dnow -auxbase-strip arch/x86/kernel/asm-offsets.s -O2 -Wall -Wundef
# -Wstrict-prototypes -Wno-trigraphs -Werror=implicit-function-declaration
# -Wno-format-security -Wno-sign-compare -Wdeclaration-after-statement
# -Wno-pointer-sign -p -fno-strict-aliasing -fno-common
# -fno-delete-null-pointer-checks -freg-struct-return -ffreestanding
# -fstack-protector -fno-asynchronous-unwind-tables -fno-omit-frame-pointer
# -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack
# -fverbose-asm
# options enabled:  -faggressive-loop-optimizations -fauto-inc-dec
# -fbranch-count-reg -fcaller-saves -fcombine-stack-adjustments
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdefer-pop -fdevirtualize -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
# -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
# -fif-conversion -fif-conversion2 -findirect-inlining -finline
# -finline-atomics -finline-functions-called-once -finline-small-functions
# -fipa-cp -fipa-profile -fipa-pure-const -fipa-reference -fipa-sra
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fivopts -fkeep-static-consts -fleading-underscore -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -foptimize-register-move -foptimize-strlen -fpartial-inlining -fpeephole
# -fpeephole2 -fprefetch-loop-arrays -fprofile -free -freg-struct-return
# -fregmove -freorder-blocks -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-insns2 -fshow-column -fshrink-wrap
# -fsigned-zeros -fsplit-ivs-in-unroller -fsplit-wide-types
# -fstack-protector -fstrict-volatile-bitfields -fsync-libcalls
# -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
# -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
# -ftree-copy-prop -ftree-copyrename -ftree-cselim -ftree-dce
# -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink
# -ftree-slp-vectorize -ftree-slsr -ftree-sra -ftree-switch-conversion
# -ftree-tail-merge -ftree-ter -ftree-vect-loop-version -ftree-vrp
# -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss -m32
# -m96bit-long-double -maccumulate-outgoing-args -malign-stringops -mcx16
# -mfxsr -mglibc -mieee-fp -mlong-double-80 -mmovbe -mno-fancy-math-387
# -mno-red-zone -mno-sse4 -mpush-args -msahf -mtls-direct-seg-refs

	.text
	.p2align 4,,15
	.globl	foo
	.type	foo, @function
foo:
	pushl	%ebp	#
	movl	%esp, %ebp	#,
	call	mcount
#APP
# 33 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_ax $44 offsetof(struct sigcontext, ax)	#
# 0 "" 2
# 34 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_bx $32 offsetof(struct sigcontext, bx)	#
# 0 "" 2
# 35 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_cx $40 offsetof(struct sigcontext, cx)	#
# 0 "" 2
# 36 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_dx $36 offsetof(struct sigcontext, dx)	#
# 0 "" 2
# 37 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_si $20 offsetof(struct sigcontext, si)	#
# 0 "" 2
# 38 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_di $16 offsetof(struct sigcontext, di)	#
# 0 "" 2
# 39 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_bp $24 offsetof(struct sigcontext, bp)	#
# 0 "" 2
# 40 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_sp $28 offsetof(struct sigcontext, sp)	#
# 0 "" 2
# 41 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_SIGCONTEXT_ip $56 offsetof(struct sigcontext, ip)	#
# 0 "" 2
# 42 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 44 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86 $0 offsetof(struct cpuinfo_x86, x86)	#
# 0 "" 2
# 45 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86_vendor $1 offsetof(struct cpuinfo_x86, x86_vendor)	#
# 0 "" 2
# 46 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86_model $2 offsetof(struct cpuinfo_x86, x86_model)	#
# 0 "" 2
# 47 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86_mask $3 offsetof(struct cpuinfo_x86, x86_mask)	#
# 0 "" 2
# 48 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_hard_math $6 offsetof(struct cpuinfo_x86, hard_math)	#
# 0 "" 2
# 49 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_cpuid_level $20 offsetof(struct cpuinfo_x86, cpuid_level)	#
# 0 "" 2
# 50 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86_capability $24 offsetof(struct cpuinfo_x86, x86_capability)	#
# 0 "" 2
# 51 "arch/x86/kernel/asm-offsets_32.c" 1
	
->CPUINFO_x86_vendor_id $60 offsetof(struct cpuinfo_x86, x86_vendor_id)	#
# 0 "" 2
# 52 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 54 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_task $0 offsetof(struct thread_info, task)	#
# 0 "" 2
# 55 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_exec_domain $4 offsetof(struct thread_info, exec_domain)	#
# 0 "" 2
# 56 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_flags $8 offsetof(struct thread_info, flags)	#
# 0 "" 2
# 57 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_status $12 offsetof(struct thread_info, status)	#
# 0 "" 2
# 58 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_preempt_count $20 offsetof(struct thread_info, preempt_count)	#
# 0 "" 2
# 59 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_addr_limit $24 offsetof(struct thread_info, addr_limit)	#
# 0 "" 2
# 60 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_restart_block $28 offsetof(struct thread_info, restart_block)	#
# 0 "" 2
# 61 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_sysenter_return $60 offsetof(struct thread_info, sysenter_return)	#
# 0 "" 2
# 62 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TI_cpu $16 offsetof(struct thread_info, cpu)	#
# 0 "" 2
# 63 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 65 "arch/x86/kernel/asm-offsets_32.c" 1
	
->GDS_size $0 offsetof(struct desc_ptr, size)	#
# 0 "" 2
# 66 "arch/x86/kernel/asm-offsets_32.c" 1
	
->GDS_address $2 offsetof(struct desc_ptr, address)	#
# 0 "" 2
# 67 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 69 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EBX $0 offsetof(struct pt_regs, bx)	#
# 0 "" 2
# 70 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_ECX $4 offsetof(struct pt_regs, cx)	#
# 0 "" 2
# 71 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EDX $8 offsetof(struct pt_regs, dx)	#
# 0 "" 2
# 72 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_ESI $12 offsetof(struct pt_regs, si)	#
# 0 "" 2
# 73 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EDI $16 offsetof(struct pt_regs, di)	#
# 0 "" 2
# 74 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EBP $20 offsetof(struct pt_regs, bp)	#
# 0 "" 2
# 75 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EAX $24 offsetof(struct pt_regs, ax)	#
# 0 "" 2
# 76 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_DS $28 offsetof(struct pt_regs, ds)	#
# 0 "" 2
# 77 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_ES $32 offsetof(struct pt_regs, es)	#
# 0 "" 2
# 78 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_FS $36 offsetof(struct pt_regs, fs)	#
# 0 "" 2
# 79 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_GS $40 offsetof(struct pt_regs, gs)	#
# 0 "" 2
# 80 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_ORIG_EAX $44 offsetof(struct pt_regs, orig_ax)	#
# 0 "" 2
# 81 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EIP $48 offsetof(struct pt_regs, ip)	#
# 0 "" 2
# 82 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_CS $52 offsetof(struct pt_regs, cs)	#
# 0 "" 2
# 83 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_EFLAGS $56 offsetof(struct pt_regs, flags)	#
# 0 "" 2
# 84 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_OLDESP $60 offsetof(struct pt_regs, sp)	#
# 0 "" 2
# 85 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PT_OLDSS $64 offsetof(struct pt_regs, ss)	#
# 0 "" 2
# 86 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 88 "arch/x86/kernel/asm-offsets_32.c" 1
	
->EXEC_DOMAIN_handler $4 offsetof(struct exec_domain, handler)	#
# 0 "" 2
# 89 "arch/x86/kernel/asm-offsets_32.c" 1
	
->IA32_RT_SIGFRAME_sigcontext $164 offsetof(struct rt_sigframe, uc.uc_mcontext)	#
# 0 "" 2
# 90 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 92 "arch/x86/kernel/asm-offsets_32.c" 1
	
->pbe_address $0 offsetof(struct pbe, address)	#
# 0 "" 2
# 93 "arch/x86/kernel/asm-offsets_32.c" 1
	
->pbe_orig_address $4 offsetof(struct pbe, orig_address)	#
# 0 "" 2
# 94 "arch/x86/kernel/asm-offsets_32.c" 1
	
->pbe_next $8 offsetof(struct pbe, next)	#
# 0 "" 2
# 97 "arch/x86/kernel/asm-offsets_32.c" 1
	
->TSS_sysenter_sp0 $-8572 offsetof(struct tss_struct, x86_tss.sp0) - sizeof(struct tss_struct)	#
# 0 "" 2
# 100 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PAGE_SIZE_asm $4096 PAGE_SIZE	#
# 0 "" 2
# 101 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PAGE_SHIFT_asm $12 PAGE_SHIFT	#
# 0 "" 2
# 102 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PTRS_PER_PTE $512 PTRS_PER_PTE	#
# 0 "" 2
# 103 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PTRS_PER_PMD $512 PTRS_PER_PMD	#
# 0 "" 2
# 104 "arch/x86/kernel/asm-offsets_32.c" 1
	
->PTRS_PER_PGD $4 PTRS_PER_PGD	#
# 0 "" 2
# 106 "arch/x86/kernel/asm-offsets_32.c" 1
	
->crypto_tfm_ctx_offset $48 offsetof(struct crypto_tfm, __crt_ctx)	#
# 0 "" 2
# 145 "arch/x86/kernel/asm-offsets_32.c" 1
	
->
# 0 "" 2
# 146 "arch/x86/kernel/asm-offsets_32.c" 1
	
->BP_scratch $484 offsetof(struct boot_params, scratch)	#
# 0 "" 2
# 147 "arch/x86/kernel/asm-offsets_32.c" 1
	
->BP_loadflags $529 offsetof(struct boot_params, hdr.loadflags)	#
# 0 "" 2
# 148 "arch/x86/kernel/asm-offsets_32.c" 1
	
->BP_hardware_subarch $572 offsetof(struct boot_params, hdr.hardware_subarch)	#
# 0 "" 2
# 149 "arch/x86/kernel/asm-offsets_32.c" 1
	
->BP_version $518 offsetof(struct boot_params, hdr.version)	#
# 0 "" 2
# 150 "arch/x86/kernel/asm-offsets_32.c" 1
	
->BP_kernel_alignment $560 offsetof(struct boot_params, hdr.kernel_alignment)	#
# 0 "" 2
#NO_APP
	popl	%ebp	#
	ret
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
