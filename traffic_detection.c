// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "traffic_detection.h"

void traffic_detect(void)
{
	//open the input file
	FILE *input = fopen("data/traffic/traffic.in", "rt");
	if (!input) {
		fprintf(stderr, "Could not open input in traffic detect\n");
		return;
	}

	//open the output file
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
		int mal = FALSE; //is malware boolean
		int pos = 0; //position
		char sep[] = ",";

		//separate the categories inside the .in file
		char *category = strtok(traffic, sep);
		while (category) {
			//if it is on the flow_duration column
			if (pos == 4)
				if (!strstr(category, ZERO_SECONDS))
					mal = TRUE;

			//if it's on the fwd_pkts_payload.avg column
			int fwd_pkts_payload_avg;
			if (pos == 12)
				fwd_pkts_payload_avg = atoi(category);

			//if it's on the flow_pkts_payload.avg column
			if (pos == 16 && !mal) {
				int flow_pkts_payload_avg = atoi(category);
				if (flow_pkts_payload_avg != 0)
					if (flow_pkts_payload_avg == fwd_pkts_payload_avg)
						mal = TRUE;
			}

			category = strtok(NULL, sep);
			++pos; //count the column index
		}
		print_predict(mal, output);
		fgets(traffic, TRAFFIC_LEN, input);
	}

	//close the files
	fclose(input);
	fclose(output);
}
