/**
 * @file common.h
 * @brief Shared types, error codes, macros, and version constants for TCVF.
 *
 * Every TCVF header includes this file first.
 *
 * Version history: see CHANGELOG.md
 */
#ifndef TCVF_COMMON_H
#define TCVF_COMMON_H



/* ── Version ──────────────────────────────────────────────────────────────── */

#define TCVF_VERSION_MAJOR  1
#define TCVF_VERSION_MINOR  0
#define TCVF_VERSION_PATCH  0
#define TCVF_VERSION_STRING "1.0.0"

/* ── Status codes ─────────────────────────────────────────────────────────── */

/**
 * @brief Return type for all TCVF functions that can fail.
 *
 * Usage pattern:
 * @code
 *   TCVFStatus s = tcvf_image_create(&src, &dst);
 *   if (s != TCVF_OK) { ... handle error ... }
 * @endcode
 */
typedef enum TCVFStatus {
    TCVF_OK          =  0,  /**< Success                                     */
    TCVF_ERR_NULL    = -1,  /**< NULL pointer passed where forbidden         */
    TCVF_ERR_ALLOC   = -2,  /**< Memory allocation failure (malloc returned NULL) */
    TCVF_ERR_IO      = -3,  /**< File could not be opened, read, or written  */
    TCVF_ERR_FORMAT  = -4,  /**< Unsupported or malformed image format       */
    TCVF_ERR_PARAM   = -5,  /**< Invalid parameter value (e.g. radius <= 0)  */
    TCVF_ERR_DIM     = -6,  /**< Incompatible image dimensions               */
    TCVF_ERR_NOT_IMPL= -7   /**< Feature not yet implemented                 */
} TCVFStatus;

/* ── Utility macros ───────────────────────────────────────────────────────── */

/** Clamp @p v to the closed interval [@p lo, @p hi]. */
#define TCVF_CLAMP(v, lo, hi)  ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

/** Return the larger of two values. */
#define TCVF_MAX(a, b)  ((a) > (b) ? (a) : (b))

/** Return the smaller of two values. */
#define TCVF_MIN(a, b)  ((a) < (b) ? (a) : (b))

/** Absolute value (integer). */
#define TCVF_ABS(x)     ((x) < 0 ? -(x) : (x))

/**
 * @brief Free a pointer and set it to NULL.
 *
 * Prevents double-free bugs.
 * @code
 *   TCVF_FREE(img->M);   // frees and nulls in one step
 * @endcode
 */
#define TCVF_FREE(p)    do { if ((p)) { free(p); (p) = NULL; } } while (0)

/* ── Pixel bounds ─────────────────────────────────────────────────────────── */

#define TCVF_PIXEL_MIN  0
#define TCVF_PIXEL_MAX  255


#endif /* TCVF_COMMON_H */