#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <cinttypes>
#include <iostream>
#include <variant>

namespace state
{
struct PlayerAlive
{
    uint16_t health{0};
    uint16_t remaining_lives{0};
};

struct PlayerDead
{
    uint16_t remaining_lives{0};
};

struct GameOver
{
};

} // namespace state

namespace event
{
struct HitByMonster
{
    uint16_t force_points{0};
};
struct Heal
{
    uint16_t points{0};
};
struct Restart
{
    uint16_t start_health{0};
};
} // namespace event

using HealthState = std::variant<state::PlayerAlive, state::PlayerDead, state::GameOver>;
using PossibleEvent = std::variant<event::HitByMonster, event::Heal, event::Restart>;

class GameStateMachine
{
public:
    void StartGame(const uint16_t health, const uint16_t lives);

    void ProcessEvent(const PossibleEvent& event);

    void ReportCurrentState();

    HealthState OnEvent(const state::PlayerAlive& alive, const event::HitByMonster& monster);

    HealthState OnEvent(const state::PlayerAlive& alive, const event::Heal& heal);

    HealthState OnEvent(const state::PlayerDead& dead, const event::Restart& restart);

    HealthState OnEvent(const state::GameOver& over, const event::Restart& restart);

    HealthState OnEvent(const auto&, const auto&);

private:
    HealthState m_current_state;
    uint16_t m_current_health;
    uint16_t m_remaining_lives;
};

#endif // STATE_MACHINE_HPP