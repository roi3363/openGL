#ifdef __APPLE__
#define PLATFORM "APPLE"
#else
#define PLATFORM "LINUX"
#endif

#include "app/app.h"

int main() {
    App app;
    app.setup();
    app.run();
    return 0;
}

