#include "domain/node.hpp"
#include "domain/artist.hpp"
#include "domain/states/gray_state.hpp"
#include "domain/states/red_state.hpp"
#include "presentation/game.hpp"
#include <iostream>

void GrayState::handleInteraction(std::shared_ptr<Game> game, std::shared_ptr<Node> node, std::shared_ptr<Artist> artist) {
    if (node->interactions == 2) {
        node->tag = 'R';
        node->interactions = 1;
        node->state = std::make_shared<RedState>();
    }
    else {
        node->interactions++;
    }
}
