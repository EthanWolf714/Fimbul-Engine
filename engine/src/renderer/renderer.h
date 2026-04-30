#pragma once
#include "defines.h"


class renderer {
    public:
        b8 renderer_initialize();
        void renderer_shutdown();
        void initVulkan();

    private:
        VkInstance instance;

};