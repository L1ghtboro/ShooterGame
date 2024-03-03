#pragma once

#include "GameUIControl.h"

ref class GameInfoOverlay : public ShooterGame::IGameUIControl
{
internal:
    GameInfoOverlay(const std::shared_ptr<DX::DeviceResources>& deviceResources);

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources(D2D_SIZE_F overlaySize);
    void ReleaseDeviceDependentResources();

    bool Visible() { return m_visible; };
    ID2D1Bitmap1* Bitmap();

public:
    // IGameUIControl interface
    virtual void SetGameLoading(uint32 dots);
    virtual void SetGameStats(int maxLevel, int hitCount, int shotCount);
    virtual void SetGameOver(bool win, int maxLevel, int hitCount, int shotCount, int highScore);
    virtual void SetLevelStart(int level, Platform::String^ objective, float timeLimit, float bonusTime);
    virtual void SetPause(int level, int hitCount, int shotCount, float timeRemaining);
    virtual void SetAction(ShooterGame::GameInfoOverlayCommand action);
    virtual void HideGameInfoOverlay() { m_visible = false; };
    virtual void ShowGameInfoOverlay() { m_visible = true; };
    virtual void ShowTooSmall();
    virtual void HideTooSmall();

private:
    // Cached pointer to device resources.
    std::shared_ptr<DX::DeviceResources> m_deviceResources;

    bool m_visible;
    bool m_tooSmallActive;

    D2D1_RECT_F m_titleRectangle;
    D2D1_RECT_F m_bodyRectangle;
    D2D1_RECT_F m_actionRectangle;

    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_levelBitmap;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_tooSmallBitmap;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatTitle;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormatBody;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_textBrush;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_backgroundBrush;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_actionBrush;
    Platform::String^ m_titleString;
    Platform::String^ m_bodyString;
    Platform::String^ m_actionString;
};
