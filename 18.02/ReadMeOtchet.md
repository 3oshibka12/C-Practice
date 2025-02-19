## 1) Компиляция прошла успешно;

## 2) Переменная **static** видна в file1.o, да и **global_var** действительно присутствует в двух ".o";

```
[bogdan@trds 18.02]$ nm file1.o
0000000000000000 D global_var
                 U printf
0000000000000000 T print_from_file1
0000000000000004 d static_var


[bogdan@trds 18.02]$ nm file2.o
0000000000000000 D global_var
                 U printf
0000000000000000 T print_from_file2
                 U static_var


[bogdan@trds 18.02]$ nm main.o
                 U global_var
0000000000000000 T main
                 U printf
                 U print_from_file1
                 U print_from_file2
```

## 3) Получил ошибку из-за **повторного определения global_var**;

```
[bogdan@trds 18.02]$ gcc file1.o file2.o main.o -o program
/usr/bin/ld: file2.o:(.data+0x0): повторное определение «global_var»; file1.o:(.data+0x0): здесь первое определение
/usr/bin/ld: file2.o: в функции «print_from_file2»:
file2.c:(.text+0x1d): неопределённая ссылка на «static_var»
```

## 4) Исправил код и вернулся к шагу 1) (А после ОПЯТЬ выполнил первый шаг, соответственно, после удаления вызова static_var)

### Теперь видно, что static_var пропала (ну, как в общем-то и ожидалось), а global_var перестала быть глобальной (и даже это правильно);
```
[bogdan@trds 18.02]$ nm file1.o
0000000000000000 D global_var
                 U printf
0000000000000000 T print_from_file1
0000000000000004 d static_var


[bogdan@trds 18.02]$ nm file2.o
                 U global_var
                 U printf
0000000000000000 T print_from_file2


[bogdan@trds 18.02]$ nm main.o
                 U global_var
0000000000000000 T main
                 U printf
                 U print_from_file1
                 U print_from_file2
```

## 5) Просмотрел нахождение ранее знакомых переменных в памяти: храняться они в *.data* (для **file1.o**, тк там сами объявлены; в остальных - \*UND\*)
```
[bogdan@trds 18.02]$ objdump -t file1.o

file1.o:     формат файла elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 file1.c
0000000000000000 l    d  .text  0000000000000000 .text
0000000000000000 l    d  .data  0000000000000000 .data
0000000000000004 l     O .data  0000000000000004 static_var    <--
0000000000000000 l    d  .rodata        0000000000000000 .rodata
0000000000000000 g     O .data  0000000000000004 global_var    <--
0000000000000000 g     F .text  0000000000000035 print_from_file1
0000000000000000         *UND*  0000000000000000 printf


[bogdan@trds 18.02]$ objdump -t file2.o

file2.o:     формат файла elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 file2.c
0000000000000000 l    d  .text  0000000000000000 .text
0000000000000000 l    d  .rodata        0000000000000000 .rodata
0000000000000000 g     F .text  000000000000001e print_from_file2
0000000000000000         *UND*  0000000000000000 global_var    <--
0000000000000000         *UND*  0000000000000000 printf


[bogdan@trds 18.02]$ objdump -t main.o

main.o:     формат файла elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 main.c
0000000000000000 l    d  .text  0000000000000000 .text
0000000000000000 l    d  .rodata        0000000000000000 .rodata
0000000000000000 g     F .text  0000000000000036 main
0000000000000000         *UND*  0000000000000000 global_var    <--
0000000000000000         *UND*  0000000000000000 printf
0000000000000000         *UND*  0000000000000000 print_from_file1
0000000000000000         *UND*  0000000000000000 print_from_file2
```

## 6) Просмотрел "бинарник"
```
[bogdan@trds 18.02]$ strings program
/lib64/ld-linux-x86-64.so.2
__libc_start_main
printf
libc.so.6
GLIBC_2.2.5
GLIBC_2.34
__gmon_start__
PTE1
H= @@
file1.c -> global_var = %d
file1.c -> static_var = %d
file2.c -> global_var = %d
main.c -> global_var = %d
;*3$"
GCC: (GNU) 12.2.1 20221121 (RED SOFT 12.2.1-3)
GCC: (GNU) 12.4.1 20240730 (RED SOFT 12.4.0-1)
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
3p1094
running gcc 12.2.1 20221121
annobin gcc 12.2.1 20221121
plugin name: annobin
GA*GOW
GA+stack_clash
GA*cf_protection
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
GA+omit_frame_pointer
GA!stack_realign
GA*FORTIFY
GA+GLIBCXX_ASSERTIONS
crt1.o
.annobin_abi_note.c
.annobin_abi_note.c_end
.annobin_abi_note.c.hot
.annobin_abi_note.c_end.hot
.annobin_abi_note.c.unlikely
.annobin_abi_note.c_end.unlikely
.annobin_abi_note.c.startup
.annobin_abi_note.c_end.startup
.annobin_abi_note.c.exit
.annobin_abi_note.c_end.exit
__abi_tag
.annobin_init.c
.annobin_init.c_end
.annobin_init.c.hot
.annobin_init.c_end.hot
.annobin_init.c.unlikely
.annobin_init.c_end.unlikely
.annobin_init.c.startup
.annobin_init.c_end.startup
.annobin_init.c.exit
.annobin_init.c_end.exit
.annobin_static_reloc.c
.annobin_static_reloc.c_end
.annobin_static_reloc.c.hot
.annobin_static_reloc.c_end.hot
.annobin_static_reloc.c.unlikely
.annobin_static_reloc.c_end.unlikely
.annobin_static_reloc.c.startup
.annobin_static_reloc.c_end.startup
.annobin_static_reloc.c.exit
.annobin_static_reloc.c_end.exit
.annobin__dl_relocate_static_pie.start
.annobin__dl_relocate_static_pie.end
crtbegin.o
deregister_tm_clones
__do_global_dtors_aux
completed.0
__do_global_dtors_aux_fini_array_entry
frame_dummy
__frame_dummy_init_array_entry
file1.c
static_var
file2.c
main.c
crtend.o
__FRAME_END__
_DYNAMIC
__GNU_EH_FRAME_HDR
_GLOBAL_OFFSET_TABLE_
__libc_start_main@GLIBC_2.34
print_from_file2
_edata
_fini
printf@GLIBC_2.2.5
global_var
__data_start
__gmon_start__
__dso_handle
_IO_stdin_used
_dl_relocate_static_pie
print_from_file1
__bss_start
main
__TMC_END__
_init
```



### Дополнительные задания

### 1. 
```
[bogdan@trds 18.02]$ objdump -x program

program:     формат файла elf64-x86-64
program
архитектура: i386:x86-64, флаги 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
начальный адрес 0x0000000000401040

Заголовок программы:
    PHDR off    0x0000000000000040 vaddr 0x0000000000400040 paddr 0x0000000000400040 align 2**3
         filesz 0x00000000000002d8 memsz 0x00000000000002d8 flags r--
  INTERP off    0x0000000000000318 vaddr 0x0000000000400318 paddr 0x0000000000400318 align 2**0
         filesz 0x000000000000001c memsz 0x000000000000001c flags r--
    LOAD off    0x0000000000000000 vaddr 0x0000000000400000 paddr 0x0000000000400000 align 2**12
         filesz 0x0000000000000510 memsz 0x0000000000000510 flags r--
    LOAD off    0x0000000000001000 vaddr 0x0000000000401000 paddr 0x0000000000401000 align 2**12
         filesz 0x00000000000001bd memsz 0x00000000000001bd flags r-x
    LOAD off    0x0000000000002000 vaddr 0x0000000000402000 paddr 0x0000000000402000 align 2**12
         filesz 0x000000000000017c memsz 0x000000000000017c flags r--
    LOAD off    0x0000000000002df8 vaddr 0x0000000000403df8 paddr 0x0000000000403df8 align 2**12
         filesz 0x0000000000000228 memsz 0x0000000000000230 flags rw-
 DYNAMIC off    0x0000000000002e08 vaddr 0x0000000000403e08 paddr 0x0000000000403e08 align 2**3
         filesz 0x00000000000001d0 memsz 0x00000000000001d0 flags rw-
    NOTE off    0x0000000000000338 vaddr 0x0000000000400338 paddr 0x0000000000400338 align 2**3
         filesz 0x0000000000000040 memsz 0x0000000000000040 flags r--
    NOTE off    0x0000000000000378 vaddr 0x0000000000400378 paddr 0x0000000000400378 align 2**2
         filesz 0x0000000000000044 memsz 0x0000000000000044 flags r--
0x6474e553 off    0x0000000000000338 vaddr 0x0000000000400338 paddr 0x0000000000400338 align 2**3
         filesz 0x0000000000000040 memsz 0x0000000000000040 flags r--
EH_FRAME off    0x0000000000002074 vaddr 0x0000000000402074 paddr 0x0000000000402074 align 2**2
         filesz 0x000000000000003c memsz 0x000000000000003c flags r--
   STACK off    0x0000000000000000 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**4
         filesz 0x0000000000000000 memsz 0x0000000000000000 flags rw-
   RELRO off    0x0000000000002df8 vaddr 0x0000000000403df8 paddr 0x0000000000403df8 align 2**0
         filesz 0x0000000000000208 memsz 0x0000000000000208 flags r--

Динамический раздел:
  NEEDED               libc.so.6
  INIT                 0x0000000000401000
  FINI                 0x00000000004011b0
  INIT_ARRAY           0x0000000000403df8
  INIT_ARRAYSZ         0x0000000000000008
  FINI_ARRAY           0x0000000000403e00
  FINI_ARRAYSZ         0x0000000000000008
  GNU_HASH             0x00000000004003c0
  STRTAB               0x0000000000400440
  SYMTAB               0x00000000004003e0
  STRSZ                0x000000000000004a
  SYMENT               0x0000000000000018
  DEBUG                0x0000000000000000
  PLTGOT               0x0000000000403fe8
  PLTRELSZ             0x0000000000000018
  PLTREL               0x0000000000000007
  JMPREL               0x00000000004004f8
  RELA                 0x00000000004004c8
  RELASZ               0x0000000000000030
  RELAENT              0x0000000000000018
  VERNEED              0x0000000000400498
  VERNEEDNUM           0x0000000000000001
  VERSYM               0x000000000040048a

Версии ссылок:
  требуется из libc.so.6:
    0x09691a75 0x00 03 GLIBC_2.2.5
    0x069691b4 0x00 02 GLIBC_2.34

Разделы:
Idx Name          Разм      VMA               LMA               Фа  смещ.  Выр.
  0 .interp       0000001c  0000000000400318  0000000000400318  00000318  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.gnu.property 00000040  0000000000400338  0000000000400338  00000338  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  0000000000400378  0000000000400378  00000378  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .note.ABI-tag 00000020  000000000040039c  000000000040039c  0000039c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .gnu.hash     0000001c  00000000004003c0  00000000004003c0  000003c0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynsym       00000060  00000000004003e0  00000000004003e0  000003e0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .dynstr       0000004a  0000000000400440  0000000000400440  00000440  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version  00000008  000000000040048a  000000000040048a  0000048a  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .gnu.version_r 00000030  0000000000400498  0000000000400498  00000498  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rela.dyn     00000030  00000000004004c8  00000000004004c8  000004c8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .rela.plt     00000018  00000000004004f8  00000000004004f8  000004f8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 .init         0000001b  0000000000401000  0000000000401000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt          00000020  0000000000401020  0000000000401020  00001020  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .text         0000016f  0000000000401040  0000000000401040  00001040  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .fini         0000000d  00000000004011b0  00000000004011b0  000011b0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .rodata       00000073  0000000000402000  0000000000402000  00002000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame_hdr 0000003c  0000000000402074  0000000000402074  00002074  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .eh_frame     000000cc  00000000004020b0  00000000004020b0  000020b0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .init_array   00000008  0000000000403df8  0000000000403df8  00002df8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 19 .fini_array   00000008  0000000000403e00  0000000000403e00  00002e00  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 20 .dynamic      000001d0  0000000000403e08  0000000000403e08  00002e08  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .got          00000010  0000000000403fd8  0000000000403fd8  00002fd8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got.plt      00000020  0000000000403fe8  0000000000403fe8  00002fe8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .data         00000018  0000000000404008  0000000000404008  00003008  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .bss          00000008  0000000000404020  0000000000404020  00003020  2**0
                  ALLOC
 25 .comment      0000005e  0000000000000000  0000000000000000  00003020  2**0
                  CONTENTS, READONLY
 26 .gnu.build.attributes 00001cd4  0000000000406028  0000000000406028  00003080  2**2
                  CONTENTS, READONLY, OCTETS
SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000              crt1.o
0000000000401066 l       .text  0000000000000000              .hidden .annobin_abi_note.c
0000000000401066 l       .text  0000000000000000              .hidden .annobin_abi_note.c_end
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c_end.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c_end.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c_end.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c.exit
0000000000401040 l       .text  0000000000000000              .hidden .annobin_abi_note.c_end.exit
000000000040039c l     O .note.ABI-tag  0000000000000020              __abi_tag
0000000000401066 l       .text  0000000000000000              .hidden .annobin_init.c
0000000000401066 l       .text  0000000000000000              .hidden .annobin_init.c_end
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c_end.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c_end.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c_end.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c.exit
0000000000401040 l       .text  0000000000000000              .hidden .annobin_init.c_end.exit
0000000000401070 l       .text  0000000000000000              .hidden .annobin_static_reloc.c
0000000000401075 l       .text  0000000000000000              .hidden .annobin_static_reloc.c_end
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c_end.hot
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c_end.unlikely
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c_end.startup
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c.exit
0000000000401040 l       .text  0000000000000000              .hidden .annobin_static_reloc.c_end.exit
0000000000401070 l       .text  0000000000000000              .hidden .annobin__dl_relocate_static_pie.start
0000000000401075 l       .text  0000000000000000              .hidden .annobin__dl_relocate_static_pie.end
0000000000000000 l    df *ABS*  0000000000000000              crtbegin.o
0000000000401080 l     F .text  0000000000000000              deregister_tm_clones
00000000004010b0 l     F .text  0000000000000000              register_tm_clones
00000000004010f0 l     F .text  0000000000000000              __do_global_dtors_aux
0000000000404020 l     O .bss   0000000000000001              completed.0
0000000000403e00 l     O .fini_array    0000000000000000              __do_global_dtors_aux_fini_array_entry
0000000000401120 l     F .text  0000000000000000              frame_dummy
0000000000403df8 l     O .init_array    0000000000000000              __frame_dummy_init_array_entry
0000000000000000 l    df *ABS*  0000000000000000              file1.c
000000000040401c l     O .data  0000000000000004              static_var
0000000000000000 l    df *ABS*  0000000000000000              file2.c
0000000000000000 l    df *ABS*  0000000000000000              main.c
0000000000000000 l    df *ABS*  0000000000000000              crtend.o
0000000000402178 l     O .eh_frame      0000000000000000              __FRAME_END__
0000000000000000 l    df *ABS*  0000000000000000              
0000000000403e08 l     O .dynamic       0000000000000000              _DYNAMIC
0000000000402074 l       .eh_frame_hdr  0000000000000000              __GNU_EH_FRAME_HDR
0000000000403fe8 l     O .got.plt       0000000000000000              _GLOBAL_OFFSET_TABLE_
0000000000000000       F *UND*  0000000000000000              __libc_start_main@GLIBC_2.34
0000000000404008  w      .data  0000000000000000              data_start
000000000040115b g     F .text  000000000000001e              print_from_file2
0000000000404020 g       .data  0000000000000000              _edata
00000000004011b0 g     F .fini  0000000000000000              .hidden _fini
0000000000000000       F *UND*  0000000000000000              printf@GLIBC_2.2.5
0000000000404018 g     O .data  0000000000000004              global_var
0000000000404008 g       .data  0000000000000000              __data_start
0000000000000000  w      *UND*  0000000000000000              __gmon_start__
0000000000404010 g     O .data  0000000000000000              .hidden __dso_handle
0000000000402000 g     O .rodata        0000000000000004              _IO_stdin_used
0000000000404028 g       .bss   0000000000000000              _end
0000000000401070 g     F .text  0000000000000005              .hidden _dl_relocate_static_pie
0000000000401040 g     F .text  0000000000000026              _start
0000000000401126 g     F .text  0000000000000035              print_from_file1
0000000000404020 g       .bss   0000000000000000              __bss_start
0000000000401179 g     F .text  0000000000000036              main
0000000000404020 g     O .data  0000000000000000              .hidden __TMC_END__
0000000000401000 g     F .init  0000000000000000              .hidden _init
```


### 2. Статическая компиляция приказала долго жить...