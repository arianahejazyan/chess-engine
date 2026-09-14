#include "uci.h"

int main(int argc, char* argv[]) {
    athena::UCIEngine engine;
    engine.run(argc, argv);
    return 0;
}