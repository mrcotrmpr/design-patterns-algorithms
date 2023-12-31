#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "domain/museum.hpp"
#include "domain/artist.hpp"
#include "domain/node.hpp"
#include "memento/game_state_memento.hpp"
#include "quadtree/quadtree.hpp"
#include "memory"

class SDLFacade;

class Game : public std::enable_shared_from_this<Game> {
public:
	void start();
	void addArtist(std::shared_ptr<Artist> artist);
	void removeArtist(std::shared_ptr<Artist> artist);
	std::shared_ptr<Node> getNode(float x, float y, bool scaled);
	std::shared_ptr<Artist> getArtist(float x, float y, bool scaled);
	std::vector<std::shared_ptr<Artist>> getArtists();
	std::shared_ptr<Artist> getArtist(std::shared_ptr<Artist> artist);
	std::shared_ptr<GameStateMemento> createMemento();
	void restoreMemento(std::shared_ptr<GameStateMemento> memento);
	std::vector<std::shared_ptr<Artist>> newArtists;
	std::shared_ptr<Museum> museum;
	std::shared_ptr<SDLFacade> sdl;
	std::shared_ptr<Node> pathFindingStart;
	std::shared_ptr<Node> pathFindingEnd;
	std::shared_ptr<Node> currentPathfindingStart;
	std::shared_ptr<Node> currentPathfindingEnd;
	bool artistsMoving = false;
	bool renderArtists = true;
	bool renderPath = true;
	bool renderVisited = true;
	bool renderQuadtree = true;
	bool pathCollision = true;
	bool menuVisible = false;
	bool atPresent = true;
	bool breadthFirstSearch = true;
	bool currentBreadthFirstSearch = true;
	bool checkCollisionsNaive = true;
	int windowWidth = 800;
	int windowHeight = 800;
	int currentMementoIndex = -1;
	float scaleX = static_cast<float>(windowWidth) / 53.0f;
	float scaleY = static_cast<float>(windowHeight) / 53.0f;
	std::shared_ptr<Quadtree> quadtree;
private:
	std::vector<std::shared_ptr<Artist>> artists;
};

#endif // GAME_HPP
