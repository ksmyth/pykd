#include "stdafx.h"

#include "win/dbgeng.h"

namespace pykd {

//////////////////////////////////////////////////////////////////////////////

void disasmAssemblay( ULONG64 offset, const std::string &instruction, ULONG64 &nextOffset )
{
    PyThread_StateRestore pyThreadRestore( g_dbgEng->pystate );

    HRESULT     hres;

    hres = g_dbgEng->control->Assemble( offset, instruction.c_str(), &nextOffset );
    if ( FAILED( hres ) )
        throw DbgException( "IDebugControl::Assemble failed" );
}

///////////////////////////////////////////////////////////////////////////////

void disasmDisassembly( ULONG64 offset, std::string &instruction, ULONG64 &nextOffset )
{
    PyThread_StateRestore pyThreadRestore( g_dbgEng->pystate );

    HRESULT     hres;
    char        buffer[0x100];
    ULONG       disasmSize = 0;
    ULONG64     endOffset = 0;
    
    hres = 
        g_dbgEng->control->Disassemble(
            offset,
            DEBUG_DISASM_EFFECTIVE_ADDRESS,
            buffer,
            sizeof(buffer),
            &disasmSize,
            &nextOffset );

    if ( FAILED( hres ) )
        throw DbgException( "IDebugControl::Disassemble failed" );

    instruction = std::string( buffer, disasmSize - 2);
}

///////////////////////////////////////////////////////////////////////////////

} // end pykd namespace
