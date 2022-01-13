#include "coreengine.h"

int main(int argc, char** argv) {

   CoreEngine* core = new CoreEngine(argc,argv);

    delete core;
    return 0;
}
