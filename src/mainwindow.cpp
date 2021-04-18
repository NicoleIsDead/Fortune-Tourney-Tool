//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#include "constants.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerloader.h"
#include "calculation.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>

// ---------------------------------------------------------------------------------
// Initialization
// ---------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

	// Make the reset button inaccessible for now
	this->ui->resetGUIButton->setVisible(untrue);

	// Make an instance of the PlayerLoader class and use it to load the player list
	PlayerLoader loader;
	PlayerList = loader.LoadPlayerList(PLAYER_DATABASE_PATH);

	// Insert the Player data into the Combobox in alphabetical order
	ui->playerSelectorComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
	for (int i = 0; i < PlayerList.count(); i++) {
		ui->playerSelectorComboBox->insertItem(i, QIcon(), PlayerList.at(i).Name);
	}

	// Use the PlayerLoader instance from before to load the FortuneTeller's emotes into the FortuneTeller player object
	FortuneTeller = loader.LoadPlayer(FORTUNE_TELLER_EMOTE_PATH, ".");
	updateFortuneTellerEmote();

	// Set the Max FortunePoints Label according to the constant MAX_FORTUNE_POINTS_VALUE
	this->ui->maxFortunePointsValueLabel->setText(QString("/ ") + QString::number(MAX_FORTUNE_POINTS_VALUE));

	// Set the colors of the chance indicator bar
	this->ui->NegativeSpace->pixmap().fill(CHANCE_INDICATOR_NEGATIVE_COLOR);
	this->ui->vortigauntWaifu->pixmap().fill(CHANCE_INDICATOR_POSITIVE_COLOR);;
	updateChanceBar(0);

	// set the PassFail label text (which you wouldn't want to see because it's reserved for the result image) to empty
	this->ui->passFailLabel->setText("");
}



MainWindow::~MainWindow() {
    delete ui;
}





// ---------------------------------------------------------------------------------
// Image update functions
// ---------------------------------------------------------------------------------
void MainWindow::updateCharacterEmote(Player player, Player::Emotion emote) {
	QPixmap pictureboxImage;

	switch (emote) {
		case Player::Emotion::Default: pictureboxImage.convertFromImage(player.EmoteDefault); break;
		case Player::Emotion::Happy: pictureboxImage.convertFromImage(player.EmoteHappy); break;
		case Player::Emotion::Sad: pictureboxImage.convertFromImage(player.EmoteSad); break;
		case Player::Emotion::Rolling: pictureboxImage.convertFromImage(player.EmoteRolling); break;
		default: return;
	}

	this->ui->favCharacterEmotePicturebox->setPixmap(pictureboxImage);
}

void MainWindow::updateCharacterEmote(Player::Emotion emote) {
	updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), emote);
}

// Pretty much the same as updateCharacterEmote() but for Kaavi instead
void MainWindow::updateFortuneTellerEmote(Player::Emotion emote) {
	QPixmap pictureboxImage;

	switch (emote) {
		default:
		case Player::Emotion::Default: pictureboxImage.convertFromImage(FortuneTeller.EmoteDefault); break;
		case Player::Emotion::Happy: pictureboxImage.convertFromImage(FortuneTeller.EmoteHappy); break;
		case Player::Emotion::Sad: pictureboxImage.convertFromImage(FortuneTeller.EmoteSad); break;
		case Player::Emotion::Rolling: pictureboxImage.convertFromImage(FortuneTeller.EmoteRolling); break;
	}

	this->ui->fortuneTellerEmotePicturebox->setPixmap(pictureboxImage);
}






// ---------------------------------------------------------------------------------
// UI handling
// ---------------------------------------------------------------------------------
void MainWindow::on_startCalculationButton_clicked() {
	//Check if a valid input is given
	if (this->ui->fortunePointsInputBox->value() > MAX_FORTUNE_POINTS_VALUE) {
		this->ui->fortunePointsInputBox->setValue(MAX_FORTUNE_POINTS_VALUE);
	}

	//Disable all UI elements that may not be changed anymore
	this->ui->playerSelectorComboBox->setEnabled(untrue);
	this->ui->fortunePointsInputBox->setEnabled(untrue);
	this->ui->calculatedChanceOutputBox->setEnabled(untrue);
	this->ui->startCalculationButton->setEnabled(untrue);

	//Play the spin animation
	updateFortuneTellerEmote(Player::Emotion::Rolling);
	updateCharacterEmote(Player::Emotion::Rolling);
	rngValue = calculation::calculateRNGVal(MAX_FORTUNE_POINTS_VALUE);
	startAnimation(rngValue);
}

void MainWindow::on_resetGUIButton_clicked() {
	this->ui->playerSelectorComboBox->setEnabled(true);
	this->ui->fortunePointsInputBox->setEnabled(true);
	this->ui->calculatedChanceOutputBox->setEnabled(true);
	this->ui->startCalculationButton->setEnabled(true);
	this->ui->resetGUIButton->setVisible(untrue);
	this->ui->playerSelectorComboBox->setCurrentIndex(0);
	this->ui->fortunePointsInputBox->setValue(0);
	updateCharacterEmote();
	updateFortuneTellerEmote();
	this->ui->Marker->setGeometry(QRect(10, 50, 21, 31));
	this->ui->passFailLabel->setPixmap(QPixmap());
}

void MainWindow::on_playerSelectorComboBox_currentIndexChanged(int index) {
	if (index >= PlayerList.count()) {
		ui->favCharacterEmotePicturebox->setText("Not available");
		return;
	}

	updateCharacterEmote(PlayerList.at(index));
}

void MainWindow::on_fortunePointsInputBox_valueChanged(int arg1) {
	int newValue = std::clamp(arg1, 0, MAX_FORTUNE_POINTS_VALUE);
	this->ui->fortunePointsInputBox->setValue(newValue);

	float fortuneChance = calculation::calculateChance(newValue, MAX_FORTUNE_POINTS_VALUE);
	this->ui->calculatedChanceOutputBox->setValue(fortuneChance);

	updateChanceBar(fortuneChance);
}


void MainWindow::on_animationCompleted() {
	QObject::disconnect(myAnimation, &QPropertyAnimation::finished, this, &MainWindow::on_animationCompleted);

	if (rngValue < this->ui->fortunePointsInputBox->value()) {
		//this->ui->lineEdit->setText("Pass");
		this->ui->passFailLabel->setPixmap(QPixmap(":/Generic/Resources/Promotion.png"));
		updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Happy);
		updateFortuneTellerEmote(Player::Emotion::Happy);
	}
	else {
		//this->ui->lineEdit->setText("Fail");
		this->ui->passFailLabel->setPixmap(QPixmap(":/Generic/Resources/RankDown.png"));
		updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Sad);
		updateFortuneTellerEmote(Player::Emotion::Sad);
	}

	this->ui->resetGUIButton->setVisible(true);

}

void MainWindow::startAnimation(int rngVal) {
	const int minXVal = 10;
	const int maxXVal = 550;

	int targetPosition = (((float)rngVal/MAX_FORTUNE_POINTS_VALUE)*(maxXVal-minXVal))+minXVal;

	myAnimation = new QPropertyAnimation(ui->Marker, "geometry");
	myAnimation->setDuration(4000);
	myAnimation->setStartValue(QRect(minXVal, 50, 21, 31));
	myAnimation->setKeyValueAt(0.1,QRect(maxXVal,50,10,31));
	myAnimation->setKeyValueAt(0.2,QRect(minXVal,50,10,31));
	myAnimation->setKeyValueAt(0.3,QRect(maxXVal,50,10,31));
	myAnimation->setKeyValueAt(0.4,QRect(minXVal,50,10,31));
	myAnimation->setKeyValueAt(0.6,QRect(maxXVal,50,10,31));
	myAnimation->setKeyValueAt(0.8,QRect(minXVal,50,10,31));
	myAnimation->setKeyValueAt(1.0,QRect(maxXVal,50,10,31));
	myAnimation->setEndValue(QRect(targetPosition, 50, 21, 31));
	//myAnimation->setEndValue(QRect(380, 70, 21, 31));

	QObject::connect(myAnimation, &QPropertyAnimation::finished, this, &MainWindow::on_animationCompleted);

	myAnimation->start();
}


void MainWindow::updateChanceBar(float fortuneChance) {
	int targetMaxWidth = this->ui->NegativeSpace->width();
	int targetHeight = this->ui->NegativeSpace->height();
	int targetWidth = ((fortuneChance/100)*targetMaxWidth);
	int targetXPosition = this->ui->NegativeSpace->x();
	int targetYPosition = this->ui->NegativeSpace->y();
	this->ui->vortigauntWaifu->setGeometry(QRect(targetXPosition,targetYPosition,targetWidth,targetHeight));
}



// ---------------------------------------------------------------------------------
// Debug functions
// ---------------------------------------------------------------------------------
//#define ALLOW_DEBUG_FUNCTIONS
#ifdef ALLOW_DEBUG_FUNCTIONS
void MainWindow::on_pushButtonDefault_clicked() {
	updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Default);
	updateFortuneTellerEmote(0);
}

void MainWindow::on_pushButtonHappy_clicked() {
	updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Happy);
	updateFortuneTellerEmote(1);
}

void MainWindow::on_pushButtonSad_clicked() {
	updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Sad);
	updateFortuneTellerEmote(2);
}

void MainWindow::on_pushButton_clicked() {
	int rngVal = calculation::calculateRNGVal(MAX_FORTUNE_POINTS_VALUE);

	if (rngVal < this->ui->fortunePointsInputBox->value()) {
		this->ui->lineEdit->setText("Pass");
		updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Happy);
		updateFortuneTellerEmote(1);
	}
	else {
		this->ui->lineEdit->setText("Fail");
		updateCharacterEmote(PlayerList.at(this->ui->playerSelectorComboBox->currentIndex()), Player::Emotion::Sad);
		updateFortuneTellerEmote(2);
	}

	startAnimation(rngVal);
/
#endif
