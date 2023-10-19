#include "presentation/quadtree/quadtree_node.hpp"
#include "iostream"

QuadtreeNode::QuadtreeNode(int pLevel, float pX, float pY, float pWidth, float pHeight, float scaleX, float scaleY) : level(pLevel), x(pX), y(pY), width(pWidth), height(pHeight), scaleX(scaleX), scaleY(scaleY) {
    points = std::vector<std::shared_ptr<Artist>>();
    children = std::vector<std::shared_ptr<QuadtreeNode>>();
}

void QuadtreeNode::insert(std::shared_ptr<Artist> artist) {
    if (children.empty()) {
        if (points.size() <= MAX_CAPACITY) {
            points.push_back(artist);
        }
        else {
            split();
            for (const auto& a : points) {
                insert(a);
            }
            points.clear();
        }
    }
    else {
        for (const auto& child : children) {
            if (child->contains(artist)) {
                child->insert(artist);
                break;
            }
        }
    }
}

void QuadtreeNode::removePoint(std::shared_ptr<Artist> artist) {
    auto it = std::find(points.begin(), points.end(), artist);
    if (it != points.end()) {
        points.erase(it);
    }
    else {
        for (const auto& child : children) {
            child->removePoint(artist);
        }
    }
}

bool QuadtreeNode::contains(const std::shared_ptr<Artist>& point) const {
    if (point == nullptr) {
        return true;
    }
    return (point->x * scaleX >= x && point->x * scaleX <= (x + width) && point->y * scaleY >= y && point->y * scaleY <= (y + height));
}

void QuadtreeNode::split() {
    float subWidth = width / 2;
    float subHeight = height / 2;
    float x = this->x;
    float y = this->y;

    children.emplace_back(std::make_shared<QuadtreeNode>(level + 1, x, y, subWidth, subHeight, scaleX, scaleY));
    children.emplace_back(std::make_shared<QuadtreeNode>(level + 1, x + subWidth, y, subWidth, subHeight, scaleX, scaleY));
    children.emplace_back(std::make_shared<QuadtreeNode>(level + 1, x, y + subHeight, subWidth, subHeight, scaleX, scaleY));
    children.emplace_back(std::make_shared<QuadtreeNode>(level + 1, x + subWidth, y + subHeight, subWidth, subHeight, scaleX, scaleY));

    for (const auto& point : points) {
        for (const auto& child : children) {
            if (child->contains(point)) {
                child->points.push_back(point);
            }
        }
    }
    points.clear();
}

void QuadtreeNode::update() {
    for (const auto& child : children) {
        child->update();
    }

    if (points.size() > MAX_CAPACITY) {
        split();
        for (const auto& a : points) {
            insert(a);
        }
        points.clear();
    }

    std::vector<std::shared_ptr<Artist>> pointsToRemove;
    for (const auto& point : points) {
        if (!contains(point)) {
            pointsToRemove.push_back(point);
        }
    }

    for (const auto& point : pointsToRemove) {
        auto it = std::find(points.begin(), points.end(), point);
        if (it != points.end()) {
            points.erase(it);
        }        
        insert(point);
    }
}