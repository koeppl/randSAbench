#include <iostream>
#include "benchmark.hpp"
#include "uint40.hpp"

using namespace std;

std::ifstream::pos_type filesize(const char* filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  return in.tellg(); 
}


int main(const int argc, const char *const argv[]) {
  if(argc < 1) {
    fprintf(stderr, "Usage: %s basename\n", argv[0]);
    return 1;
  }
  const string basename = argv[1];

  const std::string raw_filename = basename + ".raw";
  assert_file_exists(raw_filename.c_str());
  const size_t raw_filesize = static_cast<size_t>(filesize(raw_filename.c_str()));

  const std::string sa_filename = basename + ".sa5";
  assert_file_exists(sa_filename.c_str());
  const auto sa = map_file<uint40>(sa_filename.c_str());


  const std::string query_filename = basename + ".query";
  assert_file_exists(query_filename.c_str());
  // {
  //   uint64_t query_index;
  //   std::ifstream queryfile(query_filename);
  //   for(size_t number_queries = 0; ; ++number_queries) {
  //     queryfile.read(reinterpret_cast<char*>(&query_index), 5); // read uint<40> bit integer
  //     CHECK_LT(query_index, raw_filesize);
  //   }
  // }

  const auto query = map_file<uint40>(query_filename.c_str());

  CHECK_EQ(sa.second, raw_filesize);
  CHECK_EQ(query.second, raw_filesize);
  for(size_t i = 0; i < raw_filesize; ++i) {
    CHECK_LT(static_cast<uint64_t>(sa.first[i]), raw_filesize);
    CHECK_LT(static_cast<uint64_t>(query.first[i]), raw_filesize);
  }
  return 0;
}
