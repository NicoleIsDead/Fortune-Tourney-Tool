//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#ifndef PLAYER_H
#define PLAYER_H

#include <QImage>
#include <QString>

class Player {
public:
	Player();
	Player(QString _name, QImage _emoteDefault, QImage _emoteHappy, QImage _emoteSad, QImage _emoteRolling);

	typedef enum Emotion {
		Default = 0,
		Happy = 1,
		Sad = 2,
		Rolling = 3
	} Emotion;

	QString Name;

	QImage EmoteDefault;
	QImage EmoteHappy;
	QImage EmoteSad;
	QImage EmoteRolling;
};

#endif // PLAYER_H
