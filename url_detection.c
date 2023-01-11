// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "url_detection.h"

void read_domain_db(char domains[][DOM_LEN])
{
	FILE *domains_db = fopen("data/urls/domains_database", "rt");

	int index_read_db = 0;
	fscanf(domains_db, "%s", domains[index_read_db]);
	while (feof(domains_db) == 0) {
		++index_read_db;
		fscanf(domains_db, "%s", domains[index_read_db]);
	}

	fclose(domains_db);
}

void url_detect(void)
{
	char domains[DOMDB_CNT][DOM_LEN];
	read_domain_db(domains);

	FILE *input = fopen("data/urls/urls.in", "rt");
	FILE *output = fopen("urls-predictions.out", "wt");

	char url[URL_LEN];
	char separator[] = "/ ";

	char extension[EXT_CNT][6] = {
		".exe",
		".doc",
		".dom",
		".cc",
		".sh",
		".bat",
		".i",
		".dat",
		".pl"
	};

	fscanf(input, "%s", url);

	while (feof(input) == 0) {
		int malw = FALSE;

		char *dom_ptr = strtok(url, separator);
		int len_dom = strlen(dom_ptr);

		int digit_cnt = 0;
		for (int i = 0; dom_ptr[i]; ++i) {
			if (isdigit(dom_ptr[i]))
				++digit_cnt;
		}

		if (digit_cnt >= 0.1 * len_dom)
			malw = TRUE;

		if (!malw)
			for (int i = 0; i < DOMDB_CNT; ++i) {
				if (strcmp(dom_ptr, domains[i]) == 0) {
					malw = TRUE;
					break;
				}
			}

		while (dom_ptr) {
			char *aux = strtok(NULL, separator);
			if (!aux && !malw) {
				for (int i = 0; i < EXT_CNT; ++i)
					if (strstr(dom_ptr, extension[i])) {
						malw = TRUE;
						break;
					}
			}
			dom_ptr = aux;
		}

		if (!malw)
			fprintf(output, "%d\n", BEN);
		else
			fprintf(output, "%d\n", MAL);

		fscanf(input, "%s", url);
	}

	fclose(input);
	fclose(output);
}
