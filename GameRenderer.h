#pragma once

#include "DeviceResources.h"
#include "GameUIConstants.h"
#include "GameInfoOverlay.h"
#include "GameHud.h"
#include "ShooterGame.h"

ref class Simple3DGame;
ref class GameHud;

ref class GameRenderer
{
internal:
    GameRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
    void ReleaseDeviceDependentResources();
    void Render();

    concurrency::task<void> CreateGameDeviceResourcesAsync(_In_ Simple3DGame^ game);
    void FinalizeCreateGameDeviceResources();
    concurrency::task<void> LoadLevelResourcesAsync();
    void FinalizeLoadLevelResources();

    Simple3DGameDX::IGameUIControl^ GameUIControl() { return m_gameInfoOverlay; };

    DirectX::XMFLOAT2 GameInfoOverlayUpperLeft()
    {
        return DirectX::XMFLOAT2(m_gameInfoOverlayRect.left, m_gameInfoOverlayRect.top);
    };
    DirectX::XMFLOAT2 GameInfoOverlayLowerRight()
    {
        return DirectX::XMFLOAT2(m_gameInfoOverlayRect.right, m_gameInfoOverlayRect.bottom);
    };
    bool GameInfoOverlayVisible() { return m_gameInfoOverlay->Visible(); }

#if defined(_DEBUG)
    void ReportLiveDeviceObjects();
#endif

protected private:
    // Cached pointer to device resources.
    std::shared_ptr<DX::DeviceResources> m_deviceRe
