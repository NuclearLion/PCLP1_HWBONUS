// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "utils.h"

void print_predict(int malw, FILE *output)
{
	if (!malw)
		fprintf(output, "%d\n", BEN);
	else
		fprintf(output, "%d\n", MAL);
}
