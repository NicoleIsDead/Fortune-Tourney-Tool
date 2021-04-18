//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#include "calculation.h"
#include <QRandomGenerator>

calculation::calculation() {

}

float calculation::calculateChance(int inputFortunePoints, int maxFortunePoints) {
	return (((float)inputFortunePoints / (float)maxFortunePoints) * 100);
}

bool calculation::calculateWin(int inputFortunePoints, int maxFortunePoints, int& rngResult) {
	rngResult = calculateRNGVal(maxFortunePoints);

	if (rngResult < inputFortunePoints) { return true; }
	else { return false; }
}

int calculation::calculateRNGVal(int maxFortunePoints) {
	int result = QRandomGenerator::system()->bounded(maxFortunePoints);

	return result;
}
