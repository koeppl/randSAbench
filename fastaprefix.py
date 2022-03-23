#!/usr/bin/env python3
from Bio import SeqIO
import sys

if len(sys.argv) < 2:
	print("usage: {} length < infile > outfile".format(sys.argv[0]))
	sys.exit(1)
length = int(sys.argv[1])

seqs = SeqIO.parse(sys.stdin, "fasta")
for i in range(length):
	seq=next(seqs)
	SeqIO.write(seq, sys.stdout, "fasta")
