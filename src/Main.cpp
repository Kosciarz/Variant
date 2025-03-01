#include "Point.hpp"
#include "Visitor.hpp"
#include "StateMachine.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <variant>



template <typename T>
std::variant<T, std::nullopt_t> ExtractValue(const std::variant<std::optional<T>, T>& var)
{
    using null_variant = std::variant<T, std::nullopt_t>;

    return std::visit(
        [](auto&& value) -> null_variant
        {
            using Type = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<Type, std::optional<T>>)
                return value.has_value() ? null_variant(value.value()) : null_variant(std::nullopt);
            else
                return null_variant(value);
        },
        var);
}

int main()
{
    // std::variant<int, double, Point> var{Point{1.0, 2.0}};
    // std::visit(Visitor{}, var);

    // std::variant<Point> point_pack{Point{3.3, 4.4}};
    // std::visit(VisitorWithParams{100}, point_pack);

    // std::variant<int, bool> package{true};
    // std::visit(
    //     Overload{
    //         [](int val) { std::cout << val; },
    //         [](bool val) { std::cout << std::boolalpha << val; },
    //     },
    //     package);

    // auto v1 = ExtractValue(std::variant<std::optional<int>, int>(1));
    // auto v2 = ExtractValue(std::variant<std::optional<std::string>, std::string>(std::string("abc")));
    // auto v3 = ExtractValue(std::variant<std::optional<double>, double>());
    // auto v4 = ExtractValue(std::variant<std::optional<Point>, Point>(Point{1.0, 2.0}));

    GameStateMachine game;
    game.StartGame(100, 1);

    try
    {
        game.ProcessEvent(event::HitByMonster{30});
        game.ReportCurrentState();
        game.ProcessEvent(event::HitByMonster{30});
        game.ReportCurrentState();
        game.ProcessEvent(event::HitByMonster{30});
        game.ReportCurrentState();
        game.ProcessEvent(event::HitByMonster{30});
        game.ReportCurrentState();
        game.ProcessEvent(event::Restart{100});
        game.ReportCurrentState();
        game.ProcessEvent(event::HitByMonster{60});
        game.ReportCurrentState();
        game.ProcessEvent(event::HitByMonster{50});
        game.ReportCurrentState();
        game.ProcessEvent(event::Restart{});
        game.ReportCurrentState();
    }
    catch (std::exception& ex)
    {
        std::cout << "Exception! " << ex.what() << '\n';
    }
}