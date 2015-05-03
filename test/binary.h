/*
 * binary.h
 *
 *  Created on: Mar 27, 2015
 *      Author: Cody
 */

#ifndef BINARY_H_
#define BINARY_H_


#ifdef __cplusplus
 extern "C" {
#endif

/// n-th Bit
#define BIT_(n) (1 << (n))

/// set n-th bit of x to 1
#define BIT_SET_(x, n) ( (x) | BIT_(n) )

/// clear n-th bit of x
#define BIT_CLR_(x, n) ( (x) & (~BIT_(n)) )

#define BIN8(x)               (0b##x)
#define BIN16(b1, b2)         (0b##b1##b2)
#define BIN32(b1, b2, b3, b4) (0b##b1##b2##b3##b4)

#ifdef __cplusplus
}
#endif


#endif /* BINARY_H_ */
