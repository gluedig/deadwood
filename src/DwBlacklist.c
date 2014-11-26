#include "DwBlacklist.h"
#include "DwSys.h"
extern dw_str* key_s[];
extern struct bl_entry *blacklist;

void read_blacklist() {
	char *filename;

        if(key_s[DWM_S_name_whitelist] != 0) {
                filename = dw_to_cstr(key_s[DWM_S_name_whitelist]);
	}
	if (filename) {
		FILE *whitelist;
		char line[512];

		dw_log_3strings("Whitelist file: ", filename, "", 2);
	        whitelist = fopen(filename,"rb");
        	if(whitelist == NULL) {
			dw_log_string("Failed to open whitelist file", 0);
                	goto end; /* File open error */
	        }
		if (blacklist)
			bl_clear(&blacklist);
		while (! feof(whitelist)) {
			if ( fgets (line , 255, whitelist) != NULL ) {
				line[strcspn(line, "\n\r")] = 0;
				if (strcmp(line, "") == 0)
					continue;
		        	bl_add(&blacklist, line);
			}
		}
		fclose(whitelist);

	}

//	bl_dump(blacklist);
end:
	if (filename)
		free(filename);
}

int is_on_bl(struct bl_entry *list, char *entry) {
	struct bl_entry *it = list;
	int found = 0;
	while (it) {
		if (strstr(entry, it->str) != 0 ) {
			found = 1;
			break;
		}
		it = it->next;
	}
	return found;
}

void bl_clear(struct bl_entry **list) {
	struct bl_entry *it = *list;
	dw_log_string("Clearing list",11);

	while (it) {
		struct bl_entry *cur = it;
		it = it->next;
		free(cur->str);
		cur->next = 0;
		free(cur);
	}
	*list = 0;
}


void bl_add(struct bl_entry **list, char *entry) {
	struct bl_entry *it;
	struct bl_entry *new;
	dw_log_3strings("Adding to list: ", entry, "",11);

	if (*list == NULL) {
		*list = malloc(sizeof(struct bl_entry));
		it = *list;
		it->str = malloc(strlen(entry));
		strcpy(it->str, entry);
		it->next = NULL;
	} else {
		it = *list;
		while (it->next) {
			it = it->next;
		}
		new = malloc(sizeof(struct bl_entry));
		new->str = malloc(strlen(entry));
		strcpy(new->str, entry);
		new->next = NULL;
		it->next = new;
	}
}

void bl_dump(struct bl_entry *list) {
	struct bl_entry *it;
	it = list;
	printf("%x\n", list);
	while (it) {
		printf("<%x> %s -> <%x>\n", it, it->str, it->next);
		it = it->next;
	}
}


