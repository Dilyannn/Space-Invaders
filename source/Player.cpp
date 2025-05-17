#include "../header/Player.hpp"

Player::Player(): Player((GetScreenWidth() - 64) / 2, GetScreenHeight() - 100) {}

Player::Player(int x, int y, int playerLives, int playerScore):
GameObject(x, y), playerLives(playerLives), playerScore(playerScore) {
    image = LoadTexture("../source/images/spaceship.png");
}

Player::~Player() {
    UnloadTexture(image);
}

Player::Player(const Player& rhs):
GameObject(rhs), playerLives(rhs.playerLives), playerScore(rhs.playerScore) {
    image = LoadTexture("../source/images/spaceship.png");
}

Player& Player::operator=(const Player& rhs) {
    if (this != &rhs) {
        GameObject::operator=(rhs);
        playerLives = rhs.playerLives;
        playerScore = rhs.playerScore;

        UnloadTexture(image);
        image = LoadTexture("../source/images/spaceship.png");
    }
    return *this;
}

void Player::draw() {
    DrawTexture(image, getX(), getY(), WHITE);
}

void Player::moveLeft() {
    int newX = getX() - 7;
    if (newX >= 25) setX(newX);
}

void Player::moveRight() {
    int newX = getX() + 7;
    if (newX + image.width <= GetScreenWidth() - 25) setX(newX);
}

void Player::shoot() {
    // TODO add class Bullet logic
}

Player Player::operator+(int points) const {
    Player result = *this;
    result.playerScore += points;
    return result;
}

Player Player::operator-(int points) const {
    Player result = *this;
    result.playerScore -= points;
    return result;
}

int Player::getPlayerLives() const {
    return playerLives;
}

int Player::getPlayerScore() const {
    return playerScore;
}

void Player::setPlayerLives(int lives) {
    playerLives = lives;
}

void Player::setPlayerScore(int score) {
    playerScore = score;
}

std::ostream& Player::ins(std::ostream& out) const {
    out << "Player: Lives=" << playerLives << ", Score=" << playerScore
    << ", Position=(" << getX() << "," << getY() << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Player& rhs) {
    return rhs.ins(out);
}

void Player::reset() { // Reset position, lives, and score
    setX((GetScreenWidth() - image.width) / 2);
    setY(GetScreenHeight() - 100);
    playerLives = 3;
    playerScore = 0;
}
