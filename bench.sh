#!/usr/bin/env zsh
function die {
	echo "$1" >&2
	exit 1
}
set -e
set -x

# git submodule init
# git submodule update
make

mkdir -p external/rasarindex/build
cmake -B external/rasarindex/build external/rasarindex
make -C external/rasarindex/build

local -r kFullFasta=/yotta/fasta/SARS-CoV2.400k.fa
# local -r kFullFasta=/yotta/fasta/test.fa
# local -r kNumSequences=$(grep '^>' "$kFullFasta" | wc -l)
# [[ $kNumSequences -gt 0 ]] || die "no sequences found in $kFullFasta"

# sequences="$kNumSequences"
# steps=$(expr $kNumSequences / 5)
# steps=40
# for sequences in $(seq 10 $steps $kNumSequences); do
# sequences='10'
sequences="400000"
# sequences="50"
	mkdir -p "$kFullFasta.$sequences"
	input="$kFullFasta.$sequences/$(basename $kFullFasta .fa).$sequences.fa"
	[[ ! -e "$input" ]] && ./fastaprefix.py "$sequences" < "$kFullFasta" > "$input"
	[[ $(grep '^>' "$input" | wc -l) -eq "$sequences" ]] || die "number of sequences in $input does not match with $sequences"
	[[ ! -e "$input.raw" ]] && ./fasta2raw.py < "$input" > "$input.raw" && echo -n '\0' >> "$input.raw"
	grep -v "[ACGTN\0]" "$input.raw" && die "raw file contains a non ACGTN character!"
	[[ ! -e "$input.sa5" ]] && ./build_sa.x  "$input.raw" > "$input.sa5"
	[[ ! -e "$input.query" ]] && ./random_shuffle.x $(stat --format="%s" "$input.raw")  0 > "$input.query"
	./sanitycheck.x "$input"
	[[ ! -e "$input.answer" ]] && ./query.x "$input"

	oldpwd=$(pwd)
	cd external/rasarindex/build
	./ri-buildfasta "$input"
	# ./rasa-query "$input" 
	./ri-query "$input" 
	cd "$oldpwd"
# done


