//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#ifndef PLAYERLOADER_H
#define PLAYERLOADER_H

#include <QVector>
#include "player.h"

class PlayerLoader {
public:
	PlayerLoader();

	QVector<Player> LoadPlayerList(QString folderPath);
	Player LoadPlayer(QString playerFolderPath, QString playerName);

};

#endif // PLAYERLOADER_H
