#include "StateMachine.hpp"
#include "Visitor.hpp"

#include <cinttypes>
#include <variant>

void GameStateMachine::StartGame(const uint16_t health, const uint16_t lives)
{
    m_current_state = state::PlayerAlive();
}

void GameStateMachine::ProcessEvent(const PossibleEvent& event)
{
    m_current_state = std::visit(Overload{[this](const auto& state, const auto& evt)
                                          {
                                              return OnEvent(state, evt);
                                          }},
                                 m_current_state,
                                 event);
}

void GameStateMachine::ReportCurrentState()
{
    std::visit(Overload{[](const state::PlayerAlive& alive)
                        {
                            std::cout << "PlayerAlive " << alive.health << ", remaining lives: " + alive.remaining_lives
                                      << '\n';
                        },
                        [](const state::PlayerDead& dead)
                        {
                            std::cout << "PlayerDead, remaining lives: " << dead.remaining_lives << '\n';
                        },
                        [](const state::GameOver& over)
                        {
                            std::cout << "GameOver" << '\n';
                        }},
               m_current_state);
}

HealthState GameStateMachine::OnEvent(const state::PlayerAlive& alive, const event::HitByMonster& monster)
{
    std::cout << "PlayerAlive -> HitByMonster force: " << monster.force_points << '\n';

    if (alive.health > monster.force_points)
        return state::PlayerAlive(alive.health - monster.force_points, alive.remaining_lives);

    if (alive.remaining_lives > 0) return state::PlayerDead(alive.remaining_lives - 1);

    return state::GameOver{};
}

HealthState GameStateMachine::OnEvent(const state::PlayerAlive& alive, const event::Heal& heal)
{
    std::cout << "PlayerAlive -> Heal amount: " << heal.points << '\n';

    return state::PlayerAlive(alive.health + heal.points, alive.remaining_lives);
}

HealthState GameStateMachine::OnEvent(const state::PlayerDead& dead, const event::Restart& restart)
{
    std::cout << "PlayerDead -> Restart" << '\n';

    return state::PlayerAlive(restart.start_health, dead.remaining_lives);
}

HealthState GameStateMachine::OnEvent(const state::GameOver& over, const event::Restart& restart)
{
    std::cout << "GameOver -> Restart" << '\n';

    std::cout << "Game Over, please restart the whole game!" << '\n';

    return over;
}

HealthState GameStateMachine::OnEvent(const auto&, const auto&)
{
    throw std::logic_error{"Unsupported state transition"};
}