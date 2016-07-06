#include "basicconsole.h"

NAMESPACE_BEGIN
extern "C" void __Start()
{
    BasicConsole console;
    console.puts("hello");
    while (1)
        ;
}
NAMESPACE_END