//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "player.h"
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
	void on_playerSelectorComboBox_currentIndexChanged(int index);
	void on_startCalculationButton_clicked();
	void on_fortunePointsInputBox_valueChanged(int arg1);
	void on_resetGUIButton_clicked();

#ifdef ALLOW_DEBUG_FUNCTIONS

	void on_pushButtonDefault_clicked();
	void on_pushButtonHappy_clicked();
	void on_pushButtonSad_clicked();
	void on_pushButton_clicked();

#endif

	void on_animationCompleted();


private:
	Ui::MainWindow* ui;
	QVector<Player> PlayerList;
	QPropertyAnimation* myAnimation;
	int rngValue;

	// The fortuneteller emotes are stored in an instance of the Player class
	Player FortuneTeller;

	void updateCharacterEmote(Player player, Player::Emotion emote = Player::Emotion::Default);
	void updateCharacterEmote(Player::Emotion emote = Player::Emotion::Default);
	void updateFortuneTellerEmote(Player::Emotion emote = Player::Emotion::Default);
	void updateChanceBar(float fortuneChance);
	void startAnimation(int rngVal);

};
#endif // MAINWINDOW_H
