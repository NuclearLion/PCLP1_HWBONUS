// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "traffic_detection.h"

void traffic_detect(void)
{
	FILE *input = fopen("data/traffic/traffic.in", "rt");
	if (!input) {
		fprintf(stderr, "Could not open input in traffic detect\n");
		return;
	}

	FILE *output = fopen("traffic-predictions.out", "wt");
	if (!output) {
		fprintf(stderr, "Could not open the open file in traffic detect\n");
		fclose(input);
		return;
	}

	//read the header
	char header[HEADER_LEN];
	fgets(header, HEADER_LEN, input);

	char traffic[TRAFFIC_LEN];
	fgets(traffic, TRAFFIC_LEN, input);

	while (feof(input) == 0) {
		int mal = 0; //is malware boolean
		int pos = 0; //position

		char sep[] = ",";

		char *category = strtok(traffic, sep);
		while (category) {
			//if it is on the flow_duration column
			if (pos == 4)
				if (!strstr(category, ZERO_SECONDS))
					mal = 1;

			// if (pos == 16 && !mal)
			//	if (!strstr(category, "0.0"))
			//		mal = 1;

			category = strtok(NULL, sep);
			++pos;
		}

		print_predict(mal, output);

		fgets(traffic, TRAFFIC_LEN, input);
	}

	//close the files
	fclose(input);
	fclose(output);
}
