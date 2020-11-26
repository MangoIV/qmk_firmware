#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
    L01, L02, L03, L04, L05,                  R05, R04, R03, R02, R01, \
    L11, L12, L13, L14, L15,                  R15, R14, R13, R12, R11, \
    L21, L22, L23, L24, L25,                  R25, R24, R23, R22, R21, \
                    L31, L32, L33, L34, R34, R33, R32, R31 \
                    ) \
                    { \
                        { L01, L02, L03, L04, L05 }, \
                        {L11, L12, L13, L14, L15 }, \
                        {L21, L22, L23, L24, L25}, \
                        {___, L31, L32, L33, L34}, \
                        {R01, R02, R03, R04, R05 }, \
                        {R15, R14, R13, R12, R11}, \
                        {R25, R24, R23, R22, R21}, \
                        {R34, R33, R32, R31, ___} \
                    } 
