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



	fclose(input);
	fclose(output);
}
