cmd_arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o := arm-eabi-gcc -Wp,-MD,arch/arm/mach-nxp5430/prototype/module/.nx_displaytop.o.d  -nostdinc -isystem /home/bok/devel/nxp4330/jb-mr1.1/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/bok/devel/tmp/stest/kernel-3.4.39/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-nxp5430/include -Iarch/arm/plat-nxp5430/include -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/plat-nxp5430/common -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/plat-nxp5430/drone/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/mach-nxp5430/prototype/base -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/mach-nxp5430/prototype/module -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/mach-nxp5430/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mfpu=vfp -mfloat-abi=softfp -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/plat-nxp5430/common -I/home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/plat-nxp5430/drone/include -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -I/home/bok/devel/tmp/stest/kernel-3.4.39/prototype/base -I/home/bok/devel/tmp/stest/kernel-3.4.39/prototype/module -I/home/bok/devel/tmp/stest/kernel-3.4.39/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mfpu=vfp -mfloat-abi=softfp    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nx_displaytop)"  -D"KBUILD_MODNAME=KBUILD_STR(nx_displaytop)" -c -o arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o arch/arm/mach-nxp5430/prototype/module/nx_displaytop.c

source_arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o := arch/arm/mach-nxp5430/prototype/module/nx_displaytop.c

deps_arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o := \
  arch/arm/mach-nxp5430/prototype/module/nx_displaytop.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_prototype.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_type.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_debug.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_chip.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_clockcontrol.h \
  arch/arm/mach-nxp5430/prototype/module/../base/nx_bit_accessor.h \
  /home/bok/devel/tmp/stest/kernel-3.4.39/arch/arm/mach-nxp5430/prototype/base/nx_type.h \

arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o: $(deps_arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o)

$(deps_arch/arm/mach-nxp5430/prototype/module/nx_displaytop.o):
