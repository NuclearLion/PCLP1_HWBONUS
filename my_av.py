#!/usr/bin/env python3
#Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>

import re

domains_db = open("data/urls/domains_database", "rt")

domains = []
index_read_db = 0
for line in domains_db:
    domains.append(line.strip())
    index_read_db += 1

# for i in range(index_read_db):
# 	print (domains[i])

domains_db.close()

input_f = open("data/urls/urls.in", "rt")
output_f = open("urls-predictions.out", "wt")

extensions = [
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
]
separator = "/"

#url = input.readline().strip()

while True:
	url = input_f.readline()
	if not url:
		break
	#print(url.strip())
	malw = False

	dom_ptr = url.split(separator)
	len_dom = len(dom_ptr)
	#print(dom_ptr[0])

	digits = 0
	if any(c.isdigit() for c in dom_ptr[0]):
		digits += 1

	if digits >= 0.1 * len_dom:
		malw = True
	
	if not malw:
		for i in range(41): #40
			if domains[i] == dom_ptr[0]:
				malw = True

	if not malw:
		for i in range(10): #10
			#if dom_ptr[-1].find(extensions[i]) == :
			if extensions[i] in dom_ptr[-1]:
				malw = True

	if not malw:
		output_f.write("0\n")
	else:
		output_f.write("1\n")

input_f.close()
output_f.close()

input_f1 = open("data/traffic/traffic.in", "rt")
output_f1 = open("traffic-predictions.out", "wt")

traffic = input_f1.readline()

while True:
	traffic = input_f1.readline()
	if not traffic:
		break
	mal = False
	#sep = ",\n"

	category = re.split("[,\n]", traffic)
	#print(category)

	if "0 days 00:00:00" in category[4]:
		mal = True

	# fwd_pkts_payload_avg = float(category[12])
	# flow_pkts_payload_avg = float(category[16])
	# if flow_pkts_payload_avg != 0:
	# 	if 


	#print(fwd_pkts_payload_avg)
	# if not mal:
	# fwd_pkts_payload_avg = float(category[12])
	# flow_pkts_payload_avg = float(category[16])
	# print("flow:", flow_pkts_payload_avg)
	# print("fwd:", fwd_pkts_payload_avg)
	# if flow_pkts_payload_avg != 0:
	# 	if flow_pkts_payload_avg == fwd_pkts_payload_avg:# < 0.000001:
	# 		mal = True
			
	if not mal:
		output_f1.write("1\n")
	else:
		output_f1.write("0\n")

input_f1.close()
output_f1.close()
