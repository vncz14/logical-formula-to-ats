```sh
# in {ANTLR_RUNTIME_DIR}/src/runtime should be "antlr4-runtime.h"
# in {ANTLR_RUNTIME_DIR}/.. should be "libantlr4-runtime.a"
# change the CMakeLists.txt if you don't want those exact locations
export ANTLR_RUNTIME_DIR=""

cmake .
make
```
