#! /bin/bash

set -eo pipefail

cmake --build .
lcov --directory . --zerocounters
lcov --capture --initial --directory . --output-file coverage_base.info
lcov --capture --directory . --output-file coverage_test.info
ctest
lcov --add-tracefile coverage_base.info --add-tracefile coverage_test.info --output-file coverage_total.info
lcov --extract coverage_total.info '*/src/*' '*/include/*' --output-file coverage_filtered.info
lcov --remove coverage_filtered.info '/usr/*' '*googletest*' '*nlohmann*' '*bs_thread_pool*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_html
firefox coverage_html/index.html