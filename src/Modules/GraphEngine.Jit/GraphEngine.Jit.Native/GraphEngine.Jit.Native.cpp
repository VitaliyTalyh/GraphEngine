// GraphEngine.Jit.Native.cpp : Defines the exported functions for the DLL application.
//

#include <asmjit.h>
#include <TrinityCommon.h>

using namespace asmjit;

JitRuntime g_jitruntime;

typedef int(*Func)(void);

DLL_EXPORT TrinityErrorCode test(OUT Func& fn)
{
    CodeHolder code;                        // Holds code and relocation information.
    code.init(g_jitruntime.getCodeInfo());  // Initialize to the same arch as JIT runtime.

    X86Assembler a(&code);                  // Create and attach X86Assembler to `code`.
    a.mov(x86::eax, 1);                     // Move one to 'eax' register.
    a.ret();                                // Return from function.

    Error err = g_jitruntime.add(&fn, &code);
    return err ? TrinityErrorCode::E_FAILURE
        : TrinityErrorCode::E_SUCCESS;
}

DLL_EXPORT void test2(Func fn)
{
    printf("%d\n", fn());
}