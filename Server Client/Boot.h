#ifndef AP_SECONDMS_BOOT_H
#define AP_SECONDMS_BOOT_H

#include "../Solver And Cacher/StringReverser.h"
#include "../Solver And Cacher/FileCacheManager.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

namespace server_side {
    namespace boot {

        class Main {

        public:
            int main(int argc, char **argv);
        };
    }
}

#endif
