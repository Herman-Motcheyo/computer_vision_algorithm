/**
 * @file image.h
 * @brief Core image type (Image_TCVF) and lifecycle functions.
 *
 * Greyscale 2D image .
 * Pixel access: img->M[row][col], values in [0, max_val].

 */
#ifndef TCVF_IMAGE_H
#define TCVF_IMAGE_H

#include "common.h"



/* ── Core image type ──────────────────────────────────────────────────────── */

typedef struct Image_TCVF {
    int   width;      /**< Number of columns                                 */
    int   height;     /**< Number of rows                                    */
    int   max_val;    /**< Maximum pixel value (typically 255)               */
    int **M;          /**< Pixel matrix — access: M[row][col]                */
} Image_TCVF;

/* ── Lifecycle ────────────────────────────────────────────────────────────── */

/**
 * @brief Allocate a new image with the same dimensions as @p src.
 * @param src   Source image to copy dimensions from.
 * @param dst   Output image (uninitialised).
 * @return TCVF_OK on success, TCVF_ERR_ALLOC on allocation failure.
 */
TCVFStatus tcvf_image_create(const Image_TCVF *src, Image_TCVF *dst);

/**
 * @brief Allocate a new image with explicit dimensions.
 * @param width   Number of columns.
 * @param height  Number of rows.
 * @param max_val Maximum pixel value.
 * @param dst     Output image (uninitialised).
 * @return TCVF_OK on success, TCVF_ERR_ALLOC on allocation failure.
 */
TCVFStatus tcvf_image_create_empty(int width, int height, int max_val, Image_TCVF *dst);

/**
 * @brief Deep-copy @p src into @p dst (allocates new M).
 * @return TCVF_OK on success.
 */
TCVFStatus tcvf_image_copy(const Image_TCVF *src, Image_TCVF *dst);

/**
 * @brief Free all memory owned by @p img and zero its fields.
 * @param img Image to free (may be NULL — no-op).
 */
void tcvf_image_free(Image_TCVF *img);

/* ── Pixel access ─────────────────────────────────────────────────────────── */

/**
 * @brief Read a pixel value.
 * @note  No bounds check — caller is responsible.
 *        Pedagogical shorthand: equivalent to img->M[row][col].
 */
static inline int tcvf_get_pixel(const Image_TCVF *img, int row, int col) {
    return img->M[row][col];
}

/**
 * @brief Write a pixel value, clamped to [0, max_val].
 */
static inline void tcvf_set_pixel(Image_TCVF *img, int row, int col, int val) {
    img->M[row][col] = TCVF_CLAMP(val, 0, img->max_val);
}

/* ── Statistics (used across multiple modules) ────────────────────────────── */

float tcvf_luminance(const Image_TCVF *img);   /**< Mean pixel value          */
float tcvf_contrast (const Image_TCVF *img);   /**< Std deviation of pixels   */
int   tcvf_min_pixel(const Image_TCVF *img);
int   tcvf_max_pixel(const Image_TCVF *img);



#endif /* TCVF_IMAGE_H */