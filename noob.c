#include "noob.h"

int main(int argc, const char *argv[]) {
  RebuildYourself(argc, argv);

  if (HasFlag(argc, argv, "web")) {
    BuildAndRunCommand("rm -rf builds/web/* && emcc -o builds/web/yingyang.html src/ying-yang.c -Iraylib/src -Lraylib/src -lraylib "
                       "-s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=16777216 -DPLATFORM_WEB -DSUPPORT_TRACELOG=0 --shell-file src/shell.html");

    if (HasFlag(argc, argv, "serve"))
      BuildAndRunCommand("emrun builds/web/yingyang.html");
  } else {
    BuildAndRunCommand("rm -rf builds/ying-yang && gcc src/ying-yang.c -Iinclude -lraylib "
                       "-lGL -lm -lpthread "
                       "-ldl -lrt -lX11 "
                       "-o builds/ying-yang");

    if (HasFlag(argc, argv, "run"))
      BuildAndRunCommand("./builds/ying-yang");
  }

  return 0;
}
