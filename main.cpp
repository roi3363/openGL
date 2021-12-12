#ifdef __APPLE__
#define IS_APPLE 1
#endif

#include "app/app.h"

int main() {
    App app;
    app.setup();
    app.run();
    app.close();
    return 0;
}

