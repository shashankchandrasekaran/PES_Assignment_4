/*
 *  Filename: log.h
 *  Created on: Oct 11, 2022
 *  Author: Shashank Chandrasekaran
 *	Description: This file defines timeout values for various states in debug
 *	and production mode as well as abstraction of printf in debug mode
 */

#ifndef LOG_H_
#define LOG_H_

#ifdef DEBUG
#define LOG PRINTF 	//Consider LOG as printf in debug mode
#define TIMEOUT 80	//Timeout of 5 sec for STOP and GO state
#define WAR_TIMEOUT 48	//Timeout of 3 sec for WARNING state
#else //In production mode
#define LOG(...)
#define TIMEOUT 320		//Timeout of 20 sec for STOP and GO state
#define WAR_TIMEOUT 80	//Timeout of 5 sec for WARNING state
#endif

#endif /* LOG_H_ */
