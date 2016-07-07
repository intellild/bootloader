#include "basicconsole.h"

NAMESPACE_BEGIN
extern "C" void __Start()
{
    BasicConsole console;
    console.clear();
    console.puts("hello\n\0");
    while (1)
        ;
}
NAMESPACE_END