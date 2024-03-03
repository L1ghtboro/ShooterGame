#pragma once

#include "DeviceResources.h"
#include "MoveLookController.h"
#include "GameRenderer.h"
#include "ShooterGame.h"
#include "GameUIControl.h"


namespace GameControl
{
    private enum class UpdateEngineState
    {
        WaitingForResources,
        ResourcesLoaded,
        WaitingForPress,
        Dynamics,
        TooSmall,
        Suspended,
        Deactivated,
    };

    private enum class PressResultState
    {
        LoadGame,
        PlayLevel,
        ContinueLevel,
    };

    private enum class GameInfoOverlayState
    {
        Loading,
        GameStats,
        GameOverExpired,
        GameOverCompleted,
        LevelStart,
        Pause,
    };
};

class GameMain : public DX::IDeviceNotify
{
public:
    GameMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
    ~GameMain();
    void CreateWindowSizeDependentResources();
    void Run();
    void Suspend();
    void Resume();
    void Visibility(bool visible);
    void Close() { m_windowClosed = true; }

    // IDeviceNotify
    virtual void OnDeviceLost();
    virtual void OnDeviceRestored();

    void PauseRequested() { if (m_updateState == GameControl::UpdateEngineState::Dynamics) m_pauseRequested = true; };
    void PressComplete() { if (m_updateState == GameControl::UpdateEngineState::WaitingForPress) m_pressComplete = true; };
    void ResetGame();

    void WindowActivationChanged(Windows::UI::Core::CoreWindowActivationState activationState);

private:
    void SetGameInfoOverlay(GameControl::GameInfoOverlayState state);
    void InitializeGameState();
    void UpdateLayoutState();
    void Update();
    void WaitingForResourceLoading();

private:
    bool m_windowClosed;
    bool m_pauseRequested;
    bool m_pressComplete;
    bool m_renderNeeded;
    bool m_haveFocus;
    bool m_visible;

    std::shared_ptr<DX::DeviceResources> m_deviceResources;
    ShooterGame::IGameUIControl^ m_uiControl;

    MoveLookController^ m_controller;
    GameRenderer^ m_renderer;
    Simple3DGame^ m_game;

    GameControl::UpdateEngineState m_updateState;
    GameControl::UpdateEngineState m_updateStateNext;
    GameControl::PressResultState m_pressResult;
    GameControl::GameInfoOverlayState m_gameInfoOverlayState;
    ShooterGame::GameInfoOverlayCommand m_gameInfoOverlayCommand;
    uint32 m_loadingCount;
};
