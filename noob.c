#include "noob.h"

int main(int argc, const char *argv[]) {
  RebuildYourself(argc, argv);

  int run = HasFlag(argc, argv, "run");

  BuildCommand *bc = CreateBuildCommand(128);
  AddCommand(
      bc, "rm -rf builds/ying-yang && gcc src/ying-yang.c -Iinclude -lraylib "
          "-lGL -lm -lpthread "
          "-ldl -lrt -lX11 "
          "-o builds/ying-yang");

  RunCommand(bc);
  FreeCommand(bc);

  if (run)
    BuildAndRunCommand("./builds/ying-yang");

  return 0;
}
