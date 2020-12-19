//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Ball.h"
#include "Paddle.h"
#include "Edges.h"
#include "Bricks.h"

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

    // Input
    std::unique_ptr<DirectX::Keyboard>      m_keyboard;

    std::unique_ptr<DirectX::SoundEffect>   m_paddle_sound;
    std::unique_ptr<DirectX::SoundEffect>   m_wall_sound;
    std::unique_ptr<DirectX::SoundEffect>   m_brick_sound;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // Projection
    DirectX::SimpleMath::Matrix m_proj;

    // Ball
    Ball                                    m_ball;
    //Paddle
    Paddle                                  m_paddle;
    // Edges
    Edges                                   m_edges;
    // Bricks
    Bricks                                  m_bricks;

    // Camera
    DirectX::SimpleMath::Vector3 m_cameraPos = Vector3(0.f, 0.f, 6.5f);
    float m_pitch = 0;
    float m_yaw = 0;
};
