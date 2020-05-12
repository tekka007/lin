	.file	"bounds.c"
# GNU C (Ubuntu 4.8.5-4ubuntu8) version 4.8.5 (x86_64-linux-gnu)
#	compiled by GNU C version 4.8.5, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0
# warning: GMP header version 6.1.2 differs from library version 6.2.0.
# warning: MPFR header version 4.0.1 differs from library version 4.0.2.
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -nostdinc
# -I /home/olivier/kernel/linux-test/arch/x86/include -I include
# -imultilib 32 -imultiarch i386-linux-gnu -D __KERNEL__ -D CONFIG_AS_CFI=1
# -D CONFIG_AS_CFI_SIGNAL_FRAME=1 -D CONFIG_AS_CFI_SECTIONS=1
# -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(bounds)
# -D KBUILD_MODNAME=KBUILD_STR(bounds)
# -isystem /usr/lib/gcc/x86_64-linux-gnu/4.8/include
# -include include/generated/autoconf.h -MD kernel/.bounds.s.d
# kernel/bounds.c -m32 -msoft-float -mregparm=3
# -mpreferred-stack-boundary=2 -march=atom -mtune=atom
# -maccumulate-outgoing-args -mno-sse -mno-mmx -mno-sse2 -mno-3dnow
# -auxbase-strip kernel/bounds.s -O2 -Wall -Wundef -Wstrict-prototypes
# -Wno-trigraphs -Werror=implicit-function-declaration -Wno-format-security
# -Wno-sign-compare -Wdeclaration-after-statement -Wno-pointer-sign -p
# -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks
# -freg-struct-return -ffreestanding -fstack-protector
# -fno-asynchronous-unwind-tables -fno-omit-frame-pointer
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
# 16 "kernel/bounds.c" 1
	
->NR_PAGEFLAGS $23 __NR_PAGEFLAGS	#
# 0 "" 2
# 17 "kernel/bounds.c" 1
	
->MAX_NR_ZONES $3 __MAX_NR_ZONES	#
# 0 "" 2
#NO_APP
	popl	%ebp	#
	ret
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
