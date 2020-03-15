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
    if (handle != 0) {
        deviceHandles_.insert(std::make_pair(deviceAddress, handle));
    }
}

bool GPIB::isOpen(int deviceAddress) const
{
  return (getHandle(deviceAddress) != 0);
}

void GPIB::cmd(int deviceAddress, std::string command)
{
    int handle = getHandle(deviceAddress);
    if (handle == 0) {
        return;
    }

    command.append("\n");
    ibwrt_(handle, (LPSTR)command.c_str(), (LONG)(command.size() + 1));
}

std::string GPIB::query(int deviceAddress, std::string queryStr)
{
    int handle = getHandle(deviceAddress);
    if (handle == 0) {
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
    int handle = 0;
    if (it != deviceHandles_.end()) {
        handle = deviceHandles_.at(address);
    }

    return handle;
}
