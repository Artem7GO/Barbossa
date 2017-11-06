#include "main.h"

int __attribute__((constructor)) Init()
{
    
    InitializeInterfaces();
    
    InitializeVMTs();
    
    InitializeHooks();
    
    NetVarManager::DumpNetvars();
    
    Offsets::getOffsets();
    
    UpdateResolver();
    
    PrintInfo();
    
    return 0;
}

void __attribute__((constructor)) DeInit()
{

}
