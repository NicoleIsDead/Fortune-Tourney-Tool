//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define untrue false

#include <QString>
#include <QColor>

const int MAX_FORTUNE_POINTS_VALUE = 4000;
const QString PLAYER_DATA_PATH = "PlayerData";
const QString DEFAULT_EMOTE_PATH = PLAYER_DATA_PATH + "\\default";
const QString FORTUNE_TELLER_EMOTE_PATH = PLAYER_DATA_PATH + "\\kaavi";
const QString PLAYER_DATABASE_PATH = PLAYER_DATA_PATH + "\\playerDatabase";

const QColor CHANCE_INDICATOR_NEGATIVE_COLOR = QColor(224,24,24);
const QColor CHANCE_INDICATOR_POSITIVE_COLOR = QColor(56,216,29);

#endif // CONSTANTS_H
