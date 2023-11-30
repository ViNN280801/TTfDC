# "НПО Колибри" test task

## Description

1. After startup, the user configures:<br>
   a. the mask of the input files, for example .txt, testFile.bin;<br>
   b. setting whether to delete input files or not;<br>
   c. the path to save the resulting files;<br>
   d. actions when repeating the output file name: overwriting or
   modification, for example, a counter to the file name;<br>
   e. timer operation or one-time start;<br>
   f. the frequency of polling for the presence of an input file (timer);<br>
   g. the value of 8 bytes for a binary file modification operation.<br>

2. Functionality: modifies input files, for example, an XOR operation with an 8-byte variable entered from the form (Point 1,g).
3. Protection from "fool": if the input file is not closed, do not touch it.

As you can see, program initially absolutely could be configurable by user with the setting which he/she prefer. After setting up, program prints all found files by mask (using [regex](https://en.cppreference.com/w/cpp/regex)). Files modified by simple [XOR](https://en.wikipedia.org/wiki/Exclusive_or) operation which applies to each byte of the file.

## Examples

In this example we can see the interface of the program that is [CLI](https://en.wikipedia.org/wiki/Command-line_interface). With many of information within: hint message, explanations, default values, etc.
Also, this program handles incorrect input and prints error messages if something is wrong. Each error message contains current datetime, function that returns this message and description of the error.

<img src=img/1.png>

Modifying some text files with overwriting mode.

<img src=img/2.png>

## Memory check

Using [valgrind](https://valgrind.org) tool for check of any memory leaks or errors in a program:

```bash
valgrind ./<Your executive file>
```

If you want to use valgrind with full check and with lists of errors, run following command:

```bash
valgrind --leak-check=full --show-leak-kinds=all -s ./<Your executive file>
```

Output:

```console
<loveit@fedora build-NPO_Colibri-Desktop-Release>$ valgrind --leak-check=full --show-leak-kinds=all -s ./NPO_Colibri
==145249== Memcheck, a memory error detector
==145249== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==145249== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==145249== Command: ./NPO_Colibri
==145249== 
Configuration:
a) Mask of the input files
b) Necessary of the removing input files
c) Path to save result files
d) Actions when repeating the output file name: overwriting or modification, for example, a counter to the file name
e) Work with a timer or starting program once
f) Polling frequency (only if at the step (e) your choice is a "Timer")
g) Value of 8 bytes to the binary modification

All blank fields will be filled automatically with the default values:
a) ".*\.txt"
b) All input files will not be removed
c) Path to save output files is current directory
d) Overwrite
e) Start program with the timer
f) 1 sec
g) 1234567890
Enter symbol from (a) to (g) or type "end" word to end your choice
If you want to exit from the program, type "exit"
Type "hint" or "help" to call this message again
Your choice: e
Type "false" or "true": false
Your choice: end
The following files were found: text3.txt; text2.txt; text.txt; CMakeCache.txt
Once start mode selected
Type name of the output file 1: out_1.txt
File text3.txt was successfully modified and put all content to the file /home/vladislavsemykin/Documents/prog/Others/НПО Колибри/build-NPO_Colibri-Desktop-Releaseout_1.txt
Type name of the output file 2: out_2.txt
File text2.txt was successfully modified and put all content to the file /home/vladislavsemykin/Documents/prog/Others/НПО Колибри/build-NPO_Colibri-Desktop-Releaseout_2.txt
Type name of the output file 3: out_3.txt
File text.txt was successfully modified and put all content to the file /home/vladislavsemykin/Documents/prog/Others/НПО Колибри/build-NPO_Colibri-Desktop-Releaseout_3.txt
Type name of the output file 4: out_4.txt
File CMakeCache.txt was successfully modified and put all content to the file /home/vladislavsemykin/Documents/prog/Others/НПО Колибри/build-NPO_Colibri-Desktop-Releaseout_4.txt
==145249== 
==145249== HEAP SUMMARY:
==145249==     in use at exit: 16,768 bytes in 7 blocks
==145249==   total heap usage: 303 allocs, 296 frees, 295,343 bytes allocated
==145249== 
==145249== 32 bytes in 1 blocks are still reachable in loss record 1 of 7
==145249==    at 0x484682C: calloc (vg_replace_malloc.c:1554)
==145249==    by 0x5B2B101: g_malloc0 (gmem.c:163)
==145249==    by 0x5B0DD78: g_hash_table_setup_storage (ghash.c:594)
==145249==    by 0x5B11252: g_hash_table_new_full (ghash.c:1086)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (gquark.c:63)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:375)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FC2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 32 bytes in 1 blocks are still reachable in loss record 2 of 7
==145249==    at 0x484682C: calloc (vg_replace_malloc.c:1554)
==145249==    by 0x5B2B101: g_malloc0 (gmem.c:163)
==145249==    by 0x5B0DD78: g_hash_table_setup_storage (ghash.c:594)
==145249==    by 0x5B11252: g_hash_table_new_full (ghash.c:1086)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (gerror.c:525)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:376)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FF2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 64 bytes in 1 blocks are still reachable in loss record 3 of 7
==145249==    at 0x4846A40: realloc (vg_replace_malloc.c:1649)
==145249==    by 0x5B2B22A: g_realloc (gmem.c:201)
==145249==    by 0x5B0DD63: UnknownInlinedFun (ghash.c:382)
==145249==    by 0x5B0DD63: g_hash_table_setup_storage (ghash.c:592)
==145249==    by 0x5B11252: g_hash_table_new_full (ghash.c:1086)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (gquark.c:63)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:375)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FC2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 64 bytes in 1 blocks are still reachable in loss record 4 of 7
==145249==    at 0x4846A40: realloc (vg_replace_malloc.c:1649)
==145249==    by 0x5B2B22A: g_realloc (gmem.c:201)
==145249==    by 0x5B0DD63: UnknownInlinedFun (ghash.c:382)
==145249==    by 0x5B0DD63: g_hash_table_setup_storage (ghash.c:592)
==145249==    by 0x5B11252: g_hash_table_new_full (ghash.c:1086)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (gerror.c:525)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:376)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FF2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 96 bytes in 1 blocks are still reachable in loss record 5 of 7
==145249==    at 0x484182F: malloc (vg_replace_malloc.c:431)
==145249==    by 0x5B2A439: g_malloc (gmem.c:130)
==145249==    by 0x5B41774: g_slice_alloc (gslice.c:252)
==145249==    by 0x5B1121A: g_hash_table_new_full (ghash.c:1074)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (gquark.c:63)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:375)
==145249==    by 0x5AE7FC2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FC2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 96 bytes in 1 blocks are still reachable in loss record 6 of 7
==145249==    at 0x484182F: malloc (vg_replace_malloc.c:431)
==145249==    by 0x5B2A439: g_malloc (gmem.c:130)
==145249==    by 0x5B41774: g_slice_alloc (gslice.c:252)
==145249==    by 0x5B1121A: g_hash_table_new_full (ghash.c:1074)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (gerror.c:525)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:376)
==145249==    by 0x5AE7FF2: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FF2: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== 16,384 bytes in 1 blocks are still reachable in loss record 7 of 7
==145249==    at 0x484182F: malloc (vg_replace_malloc.c:431)
==145249==    by 0x5B2A439: g_malloc (gmem.c:130)
==145249==    by 0x5AE7FD3: UnknownInlinedFun (gquark.c:64)
==145249==    by 0x5AE7FD3: UnknownInlinedFun (glib-init.c:375)
==145249==    by 0x5AE7FD3: UnknownInlinedFun (glib-init.c:364)
==145249==    by 0x5AE7FD3: glib_init_ctor (glib-init.c:489)
==145249==    by 0x400517E: call_init (dl-init.c:70)
==145249==    by 0x400517E: call_init (dl-init.c:26)
==145249==    by 0x400527C: _dl_init (dl-init.c:117)
==145249==    by 0x401B3DF: ??? (in /usr/lib64/ld-linux-x86-64.so.2)
==145249== 
==145249== LEAK SUMMARY:
==145249==    definitely lost: 0 bytes in 0 blocks
==145249==    indirectly lost: 0 bytes in 0 blocks
==145249==      possibly lost: 0 bytes in 0 blocks
==145249==    still reachable: 16,768 bytes in 7 blocks
==145249==         suppressed: 0 bytes in 0 blocks
==145249== 
==145249== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

How you can see, I have still reachable bytes (16,768 bytes in 7 blocks), it is not the issue of the program. These blocks seems to be related to GLib library, which is commonly used in C/C++ programs. Valgrind didn't report about any memory leaks, so, it's no problems in a functionality.It's a normal behavior of many C/C++ programs that use libraries like GLib.

If you want to redirect valgrind checking to a file, use command below:

```bash
valgrind --leak-check=yes -s --log-file="memory.log" ./<Your executive file>
```
