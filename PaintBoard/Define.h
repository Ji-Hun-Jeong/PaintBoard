#pragma once
#define CHECKRESULT(result) if(FAILED(result)) assert(0);

#define GETDEVICE() D3DUtils::GetInst().GetDevice()
#define GETCONTEXT() D3DUtils::GetInst().GetContext()