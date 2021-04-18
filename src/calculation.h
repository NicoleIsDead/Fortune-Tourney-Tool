//MIT License
//Copyright (c) 2021 NicoleIsDead
//https://github.com/NicoleIsDead

#ifndef CALCULATION_H
#define CALCULATION_H

#include <QRandomGenerator>

class calculation {
public:
	calculation();

	/// \brief Returns the chance in percent (0.0f to 100.0f) calculated from the input fortune points and maximum fortune points to keep the code readable
	/// \param The player's ammount of fortune points
	/// \param The maximum ammount of fortune points
	/// \return Chance percentage
	static float calculateChance(int inputFortunePoints, int maxFortunePoints);



	/// \brief Call this function to do a full rng routine. Returns the win result. The rngResult output parameter can be used for animation, debug or something else
	/// \param inputFortunePoints
	/// \param maxFortunePoints
	/// \param rngResult
	/// \return
	static bool calculateWin(int inputFortunePoints, int maxFortunePoints, int& rngResult);



	/// \brief Get a number from the RNG
	/// \param maxFortunePoints
	/// \return
	static int calculateRNGVal(int maxFortunePoints);



private:
};

#endif // CALCULATION_H
