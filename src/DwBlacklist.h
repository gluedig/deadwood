#ifndef __DWBLACKLIST_DEFINED__
#define __DWBLACKLIST_DEFINED__
/* Malloc */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

struct bl_entry{
	char *str;
	struct bl_entry *next;
};

void read_blacklist(void);
void bl_clear(struct bl_entry **list);
void bl_add(struct bl_entry **list, char *entry);
void bl_dump(struct bl_entry *list);
int is_on_bl(struct bl_entry *list, char *entry);

#endif /* __DWBLACKLIST_DEFINED__ */
