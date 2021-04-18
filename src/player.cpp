//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#include "player.h"

Player::Player() {
	Name = "";

	EmoteDefault = QImage();
	EmoteHappy = QImage();
	EmoteSad = QImage();
	EmoteRolling = QImage();
}

Player::Player(QString _name, QImage _emoteDefault, QImage _emoteHappy, QImage _emoteSad, QImage _emoteRolling) {
	Name = _name;

	EmoteDefault = _emoteDefault;
	EmoteHappy = _emoteHappy;
	EmoteSad = _emoteSad;
	EmoteRolling = _emoteRolling;
}
