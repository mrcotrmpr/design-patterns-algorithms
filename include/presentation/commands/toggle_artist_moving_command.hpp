#ifndef TOGGLE_ARTISTS_MOVING_COMMAND_HPP
#define TOGGLE_ARTISTS_MOVING_COMMAND_HPP

#include "presentation/commands/command.hpp"

class ToggleArtistsMovingCommand : public Command {
public:
    void execute(std::shared_ptr<Game> game) override;
};

#endif // TOGGLE_ARTISTS_MOVING_COMMAND_HPP
