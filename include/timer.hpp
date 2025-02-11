/// performance for time
// __TIC__(forward)
//    module.forward(inputs).toTensor();
// __TOC__(forward)
//
// > forward: 8714442 microseconds = 8714 milliseconds

#include <cstdio>
#include <chrono>
using namespace std::chrono;
#define __TIC__(tag) steady_clock::time_point tag##_begin = steady_clock::now();
#define __TOC__(tag) steady_clock::time_point tag##_end = steady_clock::now();\
		fprintf(stderr, "%10s:%6ld ms = %9ld us\n", #tag, duration_cast<milliseconds>(tag##_end - tag##_begin).count(),duration_cast<microseconds>(tag##_end - tag##_begin).count());
