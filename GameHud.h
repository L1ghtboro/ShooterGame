#pragma once

#include "ShooterGame.h"
#include "DirectXSample.h"

ref class Simple3DGame;

ref class GameHud
{
internal:
    GameHud(
        _In_ const std::shared_ptr<DX::DeviceResources>& deviceResources,
        _In_ Platform::String^ titleHeader,
        _In_ Platform::String^ titleBody
    );

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
    void ReleaseDeviceDependentResources();
    void Render(_In_ Simple3DGame^ game);

private:
    // Cached pointer to device resources.
    std::shared_ptr<DX::DeviceResources> m_deviceResources;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_textBrush;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatBody;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatBodySymbol;

    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatTitleHeader;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatTitleBody;
    Microsoft::WRL::ComPtr<ID2D1Bitmap> m_logoBitmap;
    Microsoft::WRL::ComPtr<IDWriteTextLayout> m_titleHeaderLayout;
    Microsoft::WRL::ComPtr<IDWriteTextLayout> m_titleBodyLayout;

    bool m_showTitle;
    Platform::String^ m_titleHeader;
    Platform::String^ m_titleBody;

    float m_titleBodyVerticalOffset;
    D2D1_SIZE_F m_logoSize;
    D2D1_SIZE_F m_maxTitleSize;
};
