#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace __memhooks {

static class hook {
public:
  hook( void ) {
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF |
                   _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
  }
} __HookSingleton;

}

#endif /* _DEBUG */
