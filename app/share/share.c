/*
 * share.c
 */

#include "share.h"

// extern const unsigned int isharedata = 0;

__attribute__ ((section(".share_data"))) share_data_t const_share_data = {
    .SystemCoreClock = 16000000,
    .appVersion = 1
};

__attribute__ ((section(".share_header"))) const osShareHeaderT share_header = \
    {(uint32_t)&const_share_data, sizeof(share_data_t), sizeof(share_bss_t)};

