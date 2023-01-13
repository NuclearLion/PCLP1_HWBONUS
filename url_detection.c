// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "url_detection.h"

int read_domain_db(char domains[][DOM_LEN])
{
	//open the domain file
	FILE *domains_db = fopen("data/urls/domains_database", "rt");
	if (!domains_db) {
		fprintf(stderr, "Could not open domains db file\n");
		return FALSE;
	}

	//read the domains and save them in the matrix
	int index_read_db = 0;
	fscanf(domains_db, "%s", domains[index_read_db]);
	while (feof(domains_db) == 0) {
		++index_read_db;
		fscanf(domains_db, "%s", domains[index_read_db]);
	}

	//close the file
	fclose(domains_db);
	//in case the read was succesfull, return TRUE(1) succes status
	return TRUE;
}

void url_detect(void)
{
	//read the domains from database
	char domains[DOMDB_CNT][DOM_LEN];
	if (!read_domain_db(domains)) {
		fprintf(stderr, "Domains could not be read\n");
		return;
	}
	//try to open the input file
	FILE *input = fopen("data/urls/urls.in", "rt");
	if (!input) {
		fprintf(stderr, "Could not open input in url detect\n");
		return;
	}
	//try to open the output file
	FILE *output = fopen("urls-predictions.out", "wt");
	if (!output) {
		fprintf(stderr, "Could not open the open file in url detect\n");
		fclose(input);
		return;
	}

	char url[URL_LEN];
	char separator[] = "/ ";
	//list of malicious extensions
	char extension[EXT_CNT][6] = {
		".exe",
		".doc",
		".dom",
		".cc",
		".sh",
		".bat",
		".i",
		".dat",
		".pl",
		".pdf"
	};

	fscanf(input, "%s", url);
	while (feof(input) == 0) {
		//boolean to check if it is malware
		int malw = FALSE;

		//the domain of the url is the first part (separated by /)
		char *dom_ptr = strtok(url, separator);
		int len_dom = strlen(dom_ptr);
		//count how many digits are in the domain
		int digit_cnt = digit_counter(dom_ptr);

		//if there are more than 10% digits, it's malicious
		if (digit_cnt >= 0.1 * len_dom)
			malw = TRUE;

		//check if the domain is in the database
		if (!malw)
			malw = check_db(dom_ptr, domains);

		//continue separating the url
		while (dom_ptr) {
			char *aux = strtok(NULL, separator);
			//if it's the last part of the url (maybe the file)
			if (!aux && !malw) {
				for (int i = 0; i < EXT_CNT; ++i)
					//check if it's extension is in the list
					if (strstr(dom_ptr, extension[i])) {
						malw = TRUE;
						break;
					}
			}
			dom_ptr = aux;
		}

		//print the result
		print_predict(malw, output);
		//read the next url
		fscanf(input, "%s", url);
	}

	//close the files
	fclose(input);
	fclose(output);
}

//count how many digits are in the domain
int digit_counter(char *ptr)
{
	int digit_cnt = 0;
	for (int i = 0; ptr[i]; ++i) {
		if (isdigit(ptr[i]))
			++digit_cnt;
	}
	return digit_cnt;
}

//check if the domain is in the database
int check_db(char *ptr, char domains[][DOM_LEN])
{
	for (int i = 0; i < DOMDB_CNT; ++i)
		if (strcmp(ptr, domains[i]) == 0)
			return TRUE;
	return FALSE;
}
