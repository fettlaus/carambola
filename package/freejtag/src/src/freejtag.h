/*
 * freejtag.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef FREEJTAG_H_
#define FREEJTAG_H_
#ifdef DEBUG
#define ERROR(...) fprintf(stderr, __VA_ARGS__)
#define PRINT(...) fprintf(stdout, __VA_ARGS__)
#else
#define ERROR(...)
#define PRINT(...)
#endif

#endif /* FREEJTAG_H_ */
