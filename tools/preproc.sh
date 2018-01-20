#!/bin/bash

arm-linux-gnueabi-gcc -Wp,-MD,entry.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/5/include \
        -I$KERNEL_SRC \
        -I$KERNEL_SRC/arch/arm/include \
        -I$KERNEL_SRC/arch/arm/mach-omap2/include \
        -I$KERNEL_SRC/arch/arm/include/generated  \
        -I$KERNEL_SRC/include \
        -I$KERNEL_SRC/arch/arm/include/uapi \
        -I$KERNEL_SRC/arch/arm/include/generated/uapi \
        -I$KERNEL_SRC/include/uapi \
        -I$KERNEL_SRC/include/generated/uapi \
-I$KERNEL_SRC/arch/arm/mach-ebsa110/include        \
-I$KERNEL_SRC/arch/arm/mach-ixp4xx/include        \
-I$KERNEL_SRC/arch/arm/mach-s3c64xx/include        \
-I$KERNEL_SRC/arch/arm/mach-lpc32xx/include        \
-I$KERNEL_SRC/arch/arm/mach-dove/include        \
-I$KERNEL_SRC/arch/arm/mach-pxa/include        \
-I$KERNEL_SRC/arch/arm/plat-samsung/include        \
-I$KERNEL_SRC/arch/arm/mach-w90x900/include        \
-I$KERNEL_SRC/arch/arm/mach-ks8695/include        \
-I$KERNEL_SRC/arch/arm/mach-netx/include        \
-I$KERNEL_SRC/arch/arm/mach-exynos/include        \
-I$KERNEL_SRC/arch/arm/mach-iop33x/include        \
-I$KERNEL_SRC/arch/arm/mach-footbridge/include        \
-I$KERNEL_SRC/arch/arm/mach-iop32x/include        \
-I$KERNEL_SRC/arch/arm/plat-orion/include        \
-I$KERNEL_SRC/arch/arm/mach-sa1100/include        \
-I$KERNEL_SRC/arch/arm/mach-omap2/include        \
-I$KERNEL_SRC/arch/arm/mach-ep93xx/include        \
-I$KERNEL_SRC/arch/arm/mach-omap1/include        \
-I$KERNEL_SRC/arch/arm/plat-pxa/include        \
-I$KERNEL_SRC/arch/arm/plat-versatile/include        \
-I$KERNEL_SRC/arch/arm/include        \
-I$KERNEL_SRC/arch/arm/mach-spear/include        \
-I$KERNEL_SRC/arch/arm/plat-omap/include        \
-I$KERNEL_SRC/arch/arm/mach-rpc/include        \
-I$KERNEL_SRC/arch/arm/mach-davinci/include        \
-I$KERNEL_SRC/arch/arm/mach-s3c24xx/include        \
-I$KERNEL_SRC/arch/arm/mach-iop13xx/include        \
        -include $KERNEL_SRC/include/linux/kconfig.h \
-D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-PIE -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fno-ipa-sra -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -O2 --param=allow-store-data-races=0 -DCC_HAVE_ASM_GOTO -fno-reorder-blocks -fno-ipa-cp-clone -fno-partial-inlining -Wframe-larger-than=1024 -fstack-protector-strong -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -gdwarf-4 -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -fno-function-sections -fno-data-sections    -DKBUILD_BASENAME='"main"'  -DKBUILD_MODNAME='"main"' -E entry.c > entry-preproc.c


