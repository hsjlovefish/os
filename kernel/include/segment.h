#pragma once

#define KERNEL_CS 0x8
#define KERNEL_DS 0x10

#define USER32_CS 0x1b
#define USER_DS   0x23
#define USER_CS   0x2b

// 段描述符表中，第6项作为任务状态段的段描述符
#define GDT_TSS_ENTRY 6
