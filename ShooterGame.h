#pragma once

#include "GameConstants.h"
#include "Audio.h"
#include "Camera.h"
#include "Level.h"
#include "GameObject.h"
#include "GameTimer.h"
#include "MoveLookController.h"
#include "PersistentState.h"
#include "Sphere.h"
#include "GameRenderer.h"

enum class GameState
{
    Waiting,
    Active,
    LevelComplete,
    TimeExpired,
    GameComplete,
};

typedef struct
{
    Platform::String^ tag;
    int totalHits;
    int totalShots;
    int levelCompleted;
} HighScoreEntry;

typedef std::vector<HighScoreEntry> HighScoreEntries;

ref class GameRenderer;

ref class ShooterGame
{
internal:
    ShooterGame();

    void Initialize(
        _In_ MoveLookController^ controller,
        _In_ GameRenderer^ renderer
    );

    void LoadGame();
    concurrency::task<void> LoadLevelAsync();
    void FinalizeLoadLevel();
    void StartLevel();
    void PauseGame();
    void ContinueGame();
    GameState RunGame();
    void SetCurrentLevelToSavedState();

    void OnSuspending();
    void OnResuming();

    bool IsActivePlay() { return m_timer->Active(); }
    int LevelCompleted() { return m_currentLevel; };
    int TotalShots() { return m_totalShots; };
    int TotalHits() { return m_totalHits; };
    float BonusTime() { return m_levelBonusTime; };
    bool GameActive() { return m_gameActive; };
    bool LevelActive() { return m_levelActive; };
    HighScoreEntry HighScore() { return m_topScore; };
    Level^ CurrentLevel() { return m_level[m_currentLevel]; };
    float TimeRemaining() { return m_levelTimeRemaining; };
    Camera^ GameCamera() { return m_camera; };
    std::vector<GameObject^> RenderObjects() { return m_renderObjects; };

private:
    void LoadState();
    void SaveState();
    void SaveHighScore();
    void LoadHighScore();
    void InitializeAmmo();
    void UpdateDynamics();

    MoveLookController^ m_controller;
    GameRenderer^ m_renderer;
    Camera^ m_camera;

    Audio^ m_audioController;

    std::vector<Sphere^> m_ammo;
    uint32 m_ammoCount;
    uint32 m_ammoNext;

    HighScoreEntry m_topScore;
    PersistentState^ m_savedState;

    GameTimer^ m_timer;
    bool m_gameActive;
    bool m_levelActive;
    int m_totalHits;
    int m_totalShots;
    float m_levelDuration;
    float m_levelBonusTime;
    float m_levelTimeRemaining;
    std::vector<Level^> m_level;
    uint32 m_levelCount;
    uint32 m_currentLevel;

    Sphere^ m_player;
    std::vector<GameObject^> m_objects;
    std::vector<GameObject^> m_renderObjects;

    DirectX::XMFLOAT3 m_minBound;
    DirectX::XMFLOAT3 m_maxBound;
};
