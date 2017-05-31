#ifndef _ASM_GENERIC_BITOPS_ATOMIC_FLAG_H_
#define _ASM_GENERIC_BITOPS_ATOMIC_FLAG_H_
#include <asm/types.h>

/*
 * NMI events can occur at any time, including when interrupts have been
 * disabled by *_irqsave().  So you can get NMI events occurring while a
 * *_bit function is holding a spin lock.  If the NMI handler also wants
 * to do bit manipulation (and they do) then you can get a deadlock
 * between the original caller of *_bit() and the NMI handler.
 *
 * by Keith Owens
 */

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so if you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
#if 0
static inline void set_flag(unsigned long mask, volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	*p |= mask;
	_atomic_spin_unlock_irqrestore(p, flags);
}

/**
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static inline void clear_flag(unsigned long mask, volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	*p &= ~mask;
	_atomic_spin_unlock_irqrestore(p, flags);
}
#endif

/*#define set_and_clr_flag(fg, s, c) ((fg) &= ~(c),(fg) |= (s))*/
/*#define get_flag(fg, m) ((fg) & (m))*/
static inline unsigned long test_flag_8bit(unsigned long mask,
					   const volatile unsigned char *addr)
{
	return ((*addr) & mask) != 0;
}

static inline unsigned long test_flag(unsigned long mask,
				      const volatile unsigned long *addr)
{
	return ((*addr) & mask) != 0;
}

#if 0
static inline void set_and_clr_flag(unsigned long mask_s, unsigned long mask_c,
				    volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	*p &= ~mask_c;
	*p |= mask_s;
	_atomic_spin_unlock_irqrestore(p, flags);
}

/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered. It may be
 * reordered on other architectures than x86.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void change_flag(unsigned long mask, volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	*p ^= mask;
	_atomic_spin_unlock_irqrestore(p, flags);
}

/**
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It may be reordered on other architectures than x86.
 * It also implies a memory barrier.
 */
static inline unsigned long test_and_set_flag(unsigned long mask,
					      volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long old;
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	old = *p;
	*p = old | mask;
	_atomic_spin_unlock_irqrestore(p, flags);

	return (old & mask) != 0;
}

/**
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It can be reorderdered on other architectures other than x86.
 * It also implies a memory barrier.
 */
static inline unsigned long test_and_clear_flag(unsigned long mask,
						volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long old;
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	old = *p;
	*p = old & ~mask;
	_atomic_spin_unlock_irqrestore(p, flags);

	return (old & mask) != 0;
}

static inline unsigned long test_flag_set_and_clear(unsigned long mask_s,
						    unsigned long mask,
						    volatile unsigned long
						    *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long old;
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	old = *p;
	*p = (old & ~mask) | mask_s;
	_atomic_spin_unlock_irqrestore(p, flags);

	return (old & mask) != 0;
}

/**
 * test_and_change_bit - Change a bit and return its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline unsigned long test_and_change_flag(unsigned long mask,
						 volatile unsigned long *addr)
{
	unsigned long *p = ((unsigned long *)addr);
	unsigned long old;
	unsigned long flags;

	_atomic_spin_lock_irqsave(p, flags);
	old = *p;
	*p = old ^ mask;
	_atomic_spin_unlock_irqrestore(p, flags);

	return (old & mask) != 0;
}
#endif
#endif /* _ASM_GENERIC_BITOPS_ATOMIC_FLAG_H */
