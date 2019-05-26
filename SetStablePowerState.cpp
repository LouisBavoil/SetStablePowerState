#include <wrl/client.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <stdio.h>

using Microsoft::WRL::ComPtr;

void Error(const char *str)
{
    fprintf(stderr, str);
    exit(1);
}

int main(int argc, char *argv[])
{
    ComPtr<IDXGIFactory4> mDxgiFactory;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(mDxgiFactory.ReleaseAndGetAddressOf()))))
    {
        Error("ERROR: CreateDXGIFactory1 failed \n");
    }

    ComPtr<IDXGIAdapter> Adapter;
    if (FAILED(mDxgiFactory->EnumAdapters(0, Adapter.GetAddressOf())))
    {
        Error("ERROR: EnumAdapters failed with Adapter=0\n");
    }

    ID3D12Device* pDevice = nullptr;
    if (FAILED(D3D12CreateDevice(Adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&pDevice))))
    {
        Error("ERROR: D3D12CreateDevice failed\n");
    }

    HRESULT hr = pDevice->SetStablePowerState(TRUE);
    if (FAILED(hr))
    {
        Error("ERROR: SetStablePowerState failed. Do you have the Win10 SDK installed?\n");
    }

    printf("SUCCESS. Close this program to restore default clocks.");
    Sleep(INFINITE);

    pDevice->Release();

    return 0;
}
