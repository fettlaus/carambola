/*
 * freejtag.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef FREEJTAG_H_
#define FREEJTAG_H_
#ifdef DEBUG
#define PRINT(...) g_message(__VA_ARGS__)
#define WARNING(...) g_warning(__VA_ARGS__)
#define CRITICAL(...) g_critical(__VA_ARGS__)
#else
#define PRINT(...)
#define WARNING(...)
#define CRITICAL(...)
#endif
#define ERROR(...) g_error(__VA_ARGS__)

#endif /* FREEJTAG_H_ */
