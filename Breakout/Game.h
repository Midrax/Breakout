//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();
    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

    // Audio
    void OnNewAudioDevice() { m_retryAudio = true; }

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Audio
    std::unique_ptr<DirectX::AudioEngine>   m_audEngine;
    bool m_retryAudio;

    std::unique_ptr<DirectX::SoundEffect>   m_paddle;
    std::unique_ptr<DirectX::SoundEffect>   m_wall;
    std::unique_ptr<DirectX::SoundEffect>   m_brick;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
};
