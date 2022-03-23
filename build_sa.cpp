#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>

#include <utility>
#include <typeinfo>

#include <divsufsort64.h>

#include "mmap.hpp"
#include "dcheck.hpp"


int main(const int argc, char *const argv[]) {
    if(argc < 1) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return 1;
    }
    const auto text = map_file<unsigned char>(argv[1]);
    const size_t length = text.second;
    int64_t* sa = new int64_t[length];
    divsufsort64(text.first, sa, length);
    for(size_t i = 0; i < length; ++i) {
	DCHECK_LT(static_cast<uint64_t>(sa[i]), 1UL<<40);
	fwrite(sa+i, 5, 1, stdout);
    }
    // fwrite(sa, sizeof(tdc::uint_t<40>), length, stdout);
    delete [] sa;

    // tdc::uint_t<40>* sa = new tdc::uint_t<40>[length];
    // saisxx<unsigned char*, tdc::uint_t<40>*, tdc::uint_t<40>>(text.first, sa, length);
    // saisxx<unsigned char*, tdc::uint_t<40>*, int64_t>(text.first, sa, length);

    return 0;
}

