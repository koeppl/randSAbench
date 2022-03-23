#include <iostream>
#include <fstream>
#include "benchmark.hpp"
#include <functional>
#include "uint40.hpp"

using namespace std;


int main(int argc, char** argv) {
  if(argc < 2){
    fprintf(stderr, "Usage: %s basename\n", argv[0]);
    return 1;
  }
  const string basename = argv[1];
  const string sa_filename = basename + ".sa5";
  assert_file_exists(sa_filename.c_str());
  const auto sa = map_file<uint40>(sa_filename.c_str());
  batch_query("plain-sa", basename, [&](uint64_t query_index) { return sa.first[query_index]; }, true );
}
