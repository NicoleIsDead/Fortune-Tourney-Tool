//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------
#include "playerloader.h"
#include "player.h"
#include "constants.h"
#include <QDir>
#include <QStringList>
#include <QMessageBox>
#include <QString>

// ---------------------------------------------------------------------------
// Constructors / Deconstructors
// ---------------------------------------------------------------------------
PlayerLoader::PlayerLoader() {

}

// ---------------------------------------------------------------------------
// LoadPlayerList
// Loads and returns a QVector of Players based on subdirectories of the input path
// ---------------------------------------------------------------------------
QVector<Player> PlayerLoader::LoadPlayerList(QString folderPath) {

	//The path string of the player database folder
	QString playerDatabaseFolderPath = folderPath;
	//An object for scanning the player database folder
	QDir playerDatabaseDirectory(playerDatabaseFolderPath);
	//The output QVector of the player data
	QVector<Player> returnVector;

	//Check if the PlayerDatabase folder is missing
	if (!playerDatabaseDirectory.isReadable()) {
		QMessageBox message;
		message.setText("PlayerDatabase folder missing at: " + playerDatabaseDirectory.absolutePath());
		message.exec();
	}

	QStringList stringList = playerDatabaseDirectory.entryList();

	for (int i = 0; i < stringList.count(); i++){
		QString characterName = stringList[i];

		if (characterName == "." || characterName == "..") { continue; }

		returnVector.append(LoadPlayer(playerDatabaseFolderPath, characterName));
	}

	return returnVector;
}

// ---------------------------------------------------------------------------
// LoadPlayer
// Loads and returns a Players object based on the input path
// Checks if an emote is missing and if so, replaces it with freed jyanshi
// ---------------------------------------------------------------------------
Player PlayerLoader::LoadPlayer(QString playerFolderPath, QString playerName) {

	//Load the player's information
	QString inputPlayerName = playerName;
	QImage inputCharacterEmoteDefault(playerFolderPath+"\\"+playerName+"\\default");
	QImage inputCharacterEmoteHappy(playerFolderPath+"\\"+playerName+"\\happy");
	QImage inputCharacterEmoteSad(playerFolderPath+"\\"+playerName+"\\sad");
	QImage inputCharacterEmoteRolling(playerFolderPath+"\\"+playerName+"\\rolling");

	//check for missing images and replace these with freed jyanshi
	if (inputCharacterEmoteDefault.isNull()) { inputCharacterEmoteDefault.load(DEFAULT_EMOTE_PATH + "\\default.png"); }
	if (inputCharacterEmoteHappy.isNull()) { inputCharacterEmoteHappy.load(DEFAULT_EMOTE_PATH + "\\happy.png"); }
	if (inputCharacterEmoteSad.isNull()) { inputCharacterEmoteSad.load(DEFAULT_EMOTE_PATH + "\\sad.png"); }
	if (inputCharacterEmoteRolling.isNull()) { inputCharacterEmoteRolling.load(DEFAULT_EMOTE_PATH + "\\rolling.png"); }

	//if one of the images is still missing, the software will asume that the default player is not available
	if (inputCharacterEmoteDefault.isNull()
			|| inputCharacterEmoteHappy.isNull()
			|| inputCharacterEmoteSad.isNull()
			|| inputCharacterEmoteRolling.isNull()) {

		QMessageBox message;
		message.setText("Default player emote not loaded");
		message.exec();
	}

	return Player(inputPlayerName, inputCharacterEmoteDefault, inputCharacterEmoteHappy, inputCharacterEmoteSad, inputCharacterEmoteRolling);
}
