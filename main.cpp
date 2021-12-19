#ifdef __APPLE__
#define IS_APPLE 1
#else
#define IS_APPLE 0
#endif

#include "app/app.h"

int main() {
    App app;
    app.setup();
    app.run();
    return 0;
}

