/*
 *      multimon.h -- Monitor for many different modulation formats
 *
 *      Copyright (C) 1996
 *          Thomas Sailer (sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu)
 *
 *      Added eas parts - A. Maitland Bottoms 27 June 2000
 *
 *      Copyright (C) 2012-2014
 *          Elias Oenal    (multimon-ng@eliasoenal.com)
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* ---------------------------------------------------------------------- */

#ifndef _MULTIMON_H
#define _MULTIMON_H

#include <stdint.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------- */

extern const float costabf[0x400];
#define COS(x) costabf[(((x)>>6)&0x3ffu)]
#define SIN(x) COS((x)+0xc000)

/* ---------------------------------------------------------------------- */

enum EAS_L2_State
{
    EAS_L2_IDLE = 0,
    EAS_L2_HEADER_SEARCH = 1,
    EAS_L2_READING_MESSAGE = 2,
    EAS_L2_READING_EOM = 3,
};

enum EAS_L1_State
{
    EAS_L1_IDLE = 0,
    EAS_L1_SYNC = 1,
};

struct demod_state {
    const struct demod_param *dem_par;
    union {
        
        struct l2_state_eas {
            char last_message[269];
            char msg_buf[4][269];
            char head_buf[4];
            uint32_t headlen;
            uint32_t msglen;
            uint32_t msgno;
            uint32_t state;
        } eas;

    } l2;
    union {
        
        struct l1_state_eas {
            unsigned int dcd_shreg;
            unsigned int sphase;
            unsigned char lasts;
            unsigned int subsamp;
            unsigned char byte_counter;
            int dcd_integrator;
            uint32_t state;
        } eas;
        
        struct l1_state_afsk12 {
            uint32_t dcd_shreg;
            uint32_t sphase;
            uint32_t lasts;
            uint32_t subsamp;
        } afsk12;
        
        struct l1_state_afsk24 {
            unsigned int dcd_shreg;
            unsigned int sphase;
            unsigned int lasts;
        } afsk24;
        
    } l1;
};

typedef struct buffer
{
    const short* sbuffer;
    const float* fbuffer;
} buffer_t;

struct demod_param {
    const char *name;
    bool float_samples; // if false samples are short instead
    unsigned int samplerate;
    unsigned int overlap;
    void (*init)(struct demod_state *s);
    void (*demod)(struct demod_state *s, buffer_t buffer, int length);
    void (*deinit)(struct demod_state *s);
};

/* ---------------------------------------------------------------------- */

extern const struct demod_param demod_eas;

#define ALL_DEMOD &demod_eas


/* ---------------------------------------------------------------------- */

void _verbprintf(int verb_level, const char *fmt, ...);
#if !defined(MAX_VERBOSE_LEVEL)
#   define MAX_VERBOSE_LEVEL 0
#endif
#define verbprintf(level, ...) \
    do { if (level <= MAX_VERBOSE_LEVEL) _verbprintf(level, __VA_ARGS__); } while (0)


/* ---------------------------------------------------------------------- */
#endif /* _MULTIMON_H */
