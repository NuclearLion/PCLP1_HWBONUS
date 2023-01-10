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

void url_detect()
{
	char domains[DOMDB_CNT][DOM_LEN];
	read_domain_db(domains);

	FILE *input = fopen("data/urls/urls.in", "rt");
	FILE *output = fopen("urls-predictions.out", "wt");

	char url[URL_LEN];
	char separator[] = "/ ";

	fscanf(input, "%s", url);
	while (feof(input) == 0) {
		char *dom_ptr = strtok(url, separator);

		int malw = FALSE;

		for (int i = 0; i < DOMDB_CNT; ++i) {
			if (strcmp(dom_ptr, domains[i]) == 0) {
				fprintf(output, "%d\n", MAL);
				malw = TRUE;
				break;
			}
		}
		
		while (dom_ptr) {
			char *aux = strtok(NULL, separator);
			if (!aux) {
				if (strstr(dom_ptr, ".exe")) {
					//printf("%s\n", dom_ptr);
					fprintf(output, "%d\n", MAL);
					malw = TRUE;
				}
			}
			dom_ptr = aux;
			
		}

		if (!malw)
			fprintf(output, "%d\n", BEN);

		fscanf(input, "%s", url);
	}


	fclose(input);
	fclose(output);	
}
