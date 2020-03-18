#include "gpib.h"
#include <algorithm>
#include <QtDebug>
#include <utility>

GPIB::GPIB()
    : ibsta_(nullptr)
    , ibcntl_(nullptr)
    , ibclr_(nullptr)
    , ibdev_(nullptr)
    , ibconfig_(nullptr)
    , ibrd_(nullptr)
    , ibwrt_(nullptr)
{
    init();
}

//public:
void GPIB::openDevice(int deviceAddress)
{
    //open device
    int handle = ibdev_(0, deviceAddress, 0, T3s, 1, 0);
    if (handle >= 0) {
        deviceHandles_.insert(std::make_pair(deviceAddress, handle));
    }
    qDebug()<<statusGpib(*ibsta_).c_str();
}

bool GPIB::isOpen(int deviceAddress) const
{
  return (getHandle(deviceAddress) >= 0);
}

void GPIB::cmd(int deviceAddress, std::string command)
{
    int handle = getHandle(deviceAddress);
    if (handle == -1) {
        return;
    }
    command.append("\n");
    ibwrt_(handle, (LPSTR)command.c_str(), (LONG)(command.size() + 1));
}

std::string GPIB::query(int deviceAddress, std::string queryStr)
{
    int handle = getHandle(deviceAddress);
    if (handle == -1) {
        return std::string();
    }

    queryStr.append("\n");
    ibwrt_(handle, (LPSTR)queryStr.c_str(), (LONG)(queryStr.size() + 1));
    ibrd_(handle, readBuffer_, 512L);
    readBuffer_[(*ibcntl_) - 1] = '\0';
    return std::string(readBuffer_);
}

//private:
void GPIB::init()
{
    //library handle
    static HINSTANCE Gpib32Lib = NULL;

    //load library and check if loading failed
    Gpib32Lib = LoadLibraryA("gpib-32.dll");
    if (!Gpib32Lib) {
        return;
    }

    //library successfully loaded, get function addresses
    ibsta_ = (int *)GetProcAddress(Gpib32Lib, (LPCSTR)"user_ibsta");
    ibcntl_ = (long *)GetProcAddress(Gpib32Lib, (LPCSTR)"user_ibcnt");
    iberr_ = (int *)GetProcAddress(Gpib32Lib, (LPCSTR)"user_iberr");

    ibclr_ = (int(__stdcall *)(int))GetProcAddress(Gpib32Lib, (LPCSTR)"ibclr");
    ibdev_ = (int(__stdcall *)(int, int, int, int, int, int))GetProcAddress(Gpib32Lib, (LPCSTR)"ibdev");
    ibconfig_ = (int(__stdcall*)(int, int, int))GetProcAddress(Gpib32Lib, (LPCSTR)"ibconfig");
    ibrd_ = (int(__stdcall *)(int, PVOID, LONG))GetProcAddress(Gpib32Lib, (LPCSTR)"ibrd");
    ibwrt_ = (int(__stdcall *)(int, PVOID, LONG))GetProcAddress(Gpib32Lib, (LPCSTR)"ibwrt");
}

int GPIB::getHandle(int address) const
{
    auto it = std::find_if(deviceHandles_.begin(), deviceHandles_.end(),
                           [&address] (const auto& el) { return el.first == address; });
    int handle = -1;
    if (it != deviceHandles_.end()) {
        handle = deviceHandles_.at(address);
    }

    return handle;
}

void GPIB::checkstatus()
{
    statusGpib(*ibsta_);
}

std::string GPIB::statusGpib(int ibsta)
{
    if(ibsta & ERR)
    {
        return errorCode(*iberr_);
    }
    else if(ibsta & TIMO)
    {
        return "TIMO";
    }
    else if(ibsta & END)
    {
        return "END";
    }
    else if(ibsta & SRQI)
    {
        return "SRQI";
    }
    else if(ibsta & RQS)
    {
        return "RQS";
    }
    else if(ibsta & CMPL)
    {
        return "CMPL";
    }
    else if(ibsta & LOK)
    {
        return "LOK";
    }
    else if(ibsta & REM)
    {
        return "REM";
    }
    else if(ibsta & CIC)
    {
        return "CIC";
    }
    else if(ibsta & ATN)
    {
        return "ATN";
    }
    else if(ibsta & TACS)
    {
        return "TACS";
    }
    else if(ibsta & LACS)
    {
        return "LACS";
    }
    else if(ibsta & DTAS)
    {
        return "DTCS";
    }
    else if(ibsta & DCAS)
    {
        return "DCAS";
    }
    else
    {
        return "Kein Status";
    }   
}

std::string GPIB::errorCode(int iberr)
{
    if(iberr & EDVR)
    {
        return "System error";
    }
    else if(iberr & ECIC)
    {
        return "Function requires GPIB interface to be CIC";
    }
    else if(iberr & ENOL)
    {
        return "No Listeners on the GPIB";
    }
    else if(iberr & EADR)
    {
        return "GPIB interface not addressed correctly";
    }
    else if(iberr & EARG)
    {
        return "Invalid argument to function call";
    }
    else if(iberr & ESAC)
    {
        return "GPIB interface not System Controller as required";
    }
    else if(iberr & EABO)
    {
        return "I/O operation aborted (timeout)";
    }
    else if(iberr & ENEB)
    {
        return "Nonexistent GPIB interface";
    }
    else if(iberr & EDMA)
    {
        return "DMA error";
    }
    else if(iberr & EOIP)
    {
        return "Asynchronous I/O in progress";
    }
    else if(iberr & ECAP)
    {
        return "No capability for operation";
    }
    else if(iberr & EFSO)
    {
        return "File system error";
    }
    else if(iberr & EBUS)
    {
        return "GPIB bus error";
    }
    else if(iberr & ESRQ)
    {
        return "SRQ stuck in ON position";
    }
    else if(iberr & ETAB)
    {
        return "Table problem";
    }
    else if(iberr & ELCK)
    {
        return "Interface is locked";
    }
    else if(iberr & EARM)
    {
        return "ibnotify callback failed to rearm";
    }
    else if(iberr & EHDL)
    {
        return "Input handle is invalid";
    }
    else if(iberr & EWIP)
    {
        return "Wait in progress on specified input handle";
    }
    else if(iberr & ERST)
    {
        return "The event notification was cancelled due to a reset of the interface";
    }
    else if(iberr & EPWR)
    {
        return "The interface lost power";
    }
    else
    {
        return "no known error";
    }
}
