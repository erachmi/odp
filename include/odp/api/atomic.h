/* Copyright (c) 2013, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */


/**
 * @file
 *
 * ODP atomic operations
 */

#ifndef ODP_ATOMIC_H_
#define ODP_ATOMIC_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup odp_synchronizers
 *  Atomic types and relaxed operations. These operations cannot be used for
 *  synchronization.
 *  @{
 */


/**
 * Initialize atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[out] atom Pointer to an atomic uint32 variable
 * @param val Value to initialize the variable with
 */
void odp_atomic_init_u32(odp_atomic_u32_t *atom, uint32_t val);


/**
 * Load value of atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param atom Pointer to an atomic uint32 variable
 *
 * @return Value of the variable
 */
uint32_t odp_atomic_load_u32(odp_atomic_u32_t *atom);

/**
 * Store value to atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[out] atom Pointer to an atomic uint32 variable
 * @param val Value to store in the variable
 */
void odp_atomic_store_u32(odp_atomic_u32_t *atom, uint32_t val);

/**
 * Fetch and add to atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 * @param val Value to be added to the variable
 *
 * @return Value of the variable before the addition
 */
uint32_t odp_atomic_fetch_add_u32(odp_atomic_u32_t *atom, uint32_t val);

/**
 * Add to atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 * @param val A value to be added to the variable
 */
void odp_atomic_add_u32(odp_atomic_u32_t *atom, uint32_t val);

/**
 * Fetch and subtract from atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 * @param val A value to be subracted from the variable
 *
 * @return Value of the variable before the subtraction
 */
uint32_t odp_atomic_fetch_sub_u32(odp_atomic_u32_t *atom, uint32_t val);

/**
 * Subtract from atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 * @param val Value to be subtracted from the variable
 */
void odp_atomic_sub_u32(odp_atomic_u32_t *atom, uint32_t val);

/**
 * Fetch and increment atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 *
 * @return Value of the variable before the increment
 */

uint32_t odp_atomic_fetch_inc_u32(odp_atomic_u32_t *atom);

/**
 * Increment atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 */
void odp_atomic_inc_u32(odp_atomic_u32_t *atom);

/**
 * Fetch and decrement atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 *
 * @return Value of the variable before the subtraction
 */
uint32_t odp_atomic_fetch_dec_u32(odp_atomic_u32_t *atom);

/**
 * Decrement atomic uint32 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint32 variable
 */
void odp_atomic_dec_u32(odp_atomic_u32_t *atom);

/**
 * Initialize atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[out] atom Pointer to an atomic uint64 variable
 * @param val Value to initialize the variable with
 */
void odp_atomic_init_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Load value of atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param atom Pointer to an atomic uint64 variable
 *
 * @return Value of the variable
 */
uint64_t odp_atomic_load_u64(odp_atomic_u64_t *atom);

/**
 * Store value to atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[out] atom Pointer to an atomic uint64 variable
 * @param val Value to store in the variable
 */
void odp_atomic_store_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Fetch and add to atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 * @param val Value to be added to the variable
 *
 * @return Value of the variable before the addition
 */

uint64_t odp_atomic_fetch_add_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Add to atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 * @param val Value to be added to the variable
 *
 */
void odp_atomic_add_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Fetch and subtract from atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 * @param val Value to be subtracted from the variable
 *
 * @return Value of the variable before the subtraction
 */
uint64_t odp_atomic_fetch_sub_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Subtract from atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 * @param val Value to be subtracted from the variable
 */
void odp_atomic_sub_u64(odp_atomic_u64_t *atom, uint64_t val);

/**
 * Fetch and increment atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 *
 * @return Value of the variable before the increment
 */
uint64_t odp_atomic_fetch_inc_u64(odp_atomic_u64_t *atom);

/**
 * Increment atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 */
void odp_atomic_inc_u64(odp_atomic_u64_t *atom);

/**
 * Fetch and decrement atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 *
 * @return Value of the variable before the decrement
 */
uint64_t odp_atomic_fetch_dec_u64(odp_atomic_u64_t *atom);

/**
 * Decrement atomic uint64 variable
 * @note Relaxed memory order, cannot be used for synchronization
 *
 * @param[in,out] atom Pointer to an atomic uint64 variable
 */
void odp_atomic_dec_u64(odp_atomic_u64_t *atom);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif