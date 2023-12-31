#include "domain/node.hpp"
#include "domain/artist.hpp"
#include "domain/states/yellow_state.hpp"
#include "domain/states/gray_state.hpp"
#include "presentation/game.hpp"
#include "factories/artist_factory.hpp"
#include <iostream>

void YellowState::handleInteraction(std::shared_ptr<Game> game, std::shared_ptr<Node> node, std::shared_ptr<Artist> artist) {
	
	if (node->interactions == 2) {
		node->tag = 'G';
		node->interactions = 1;
		node->state = std::make_shared<GrayState>();
	}
	else {
		node->interactions++;

		float x = node->x;
		float y = node->y;
		float vx = 0;
		float vy = 0;

		auto newArtist = ArtistFactory::createArtist(x, y, vx, vy);
		game->newArtists.push_back(newArtist);
	}
}
