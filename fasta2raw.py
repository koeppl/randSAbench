#!/usr/bin/env python3
from Bio import SeqIO
import sys

for seq_record in SeqIO.parse(sys.stdin, "fasta"):
	print(str(seq_record.seq), end='')
