#include "../header/Player.hpp"
#include "../header/Bullet.hpp"


Player::Player(): Player((GetScreenWidth() - 64) / 2, GetScreenHeight() - 50) {}

Player::Player(int x, int y, int playerLives, int playerScore):
GameObject(x, y), playerLives(playerLives), playerScore(playerScore) {
    image = LoadTexture("../source/images/spaceship.png");
    lastFireTime = 0.;
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
    if (newX >= 7) setX(newX);
}

void Player::moveRight() {
    int newX = getX() + 7;
    if (newX + image.width <= GetScreenWidth() - 7) setX(newX);
}

void Player::shoot() {
    // TODO add class Bullet logic
    //bullets.push_back(Bullet({direction.x + image.width/2 - 2, direction.y},-6));
    if (GetTime() - lastFireTime > 0.35) {
        Vector2 startPos;
        startPos.x = getX() + image.width / 2 - 2;
        startPos.y = getY();

        bullets.push_back(Bullet(startPos, -6));
        lastFireTime = GetTime();
    }
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
    setY(GetScreenHeight() - 50);;
    playerLives = 3;
    playerScore = 0;
}
