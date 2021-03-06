/*
   Copyright (c) 2015, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

#define BASEBAND "androidboot.baseband"
#define BOOTDEVICE "androidboot.bootdevice"
#define HWVER "android.letv.hardware_version"
#define PANEL "mdss_mdp.panel"
#define PRODUCT "android.letv.product"
#define SERIALNO "androidboot.serialno"

static void import_cmdline(char *name, int for_emulator)
{
    char *value = strchr(name, '=');
    int name_len = strlen(name);

    if (value == 0) return;
    *value++ = 0;
    if (name_len == 0) return;

    if (!strcmp(name, BASEBAND)) {
        property_set("ro.boot.baseband", value);
        property_set("ro.baseband", value);
    } else if (!strcmp(name, BOOTDEVICE))
        property_set("ro.boot.bootdevice", value);
    else if (!strcmp(name, HWVER))
        property_set("ro.config.hardware_version", value);
    else if (!strcmp(name, PANEL))
        return; /* not sure what to do here */
    else if (!strcmp(name, PRODUCT)) {
        property_set("ro.config.product", value);
        property_set("ro.product.model", value);
        property_set("ro.product.device", value);
    } else if (!strcmp(name, SERIALNO)) {
        property_set("ro.boot.serialno", value);
        property_set("ro.serialno", value);
    }
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type) {
    char device[PROP_VALUE_MAX];
    char rf_version[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    import_kernel_cmdline(0, import_cmdline);
    /* America */
    /* TODO: Parse these from kernel command line */
    property_set("ro.board.platform", "msm8994");
    property_set("ro.hardware", "qcom");
    property_set("ro.boot.hardware", "qcom");
    property_set("ro.bootloader", "unknown");
    property_set("ro.bootmode", "unknown");
    property_set("ro.rf_version", "TDD_FDD_Am"); //Sure, why not
    property_set("ro.sf.lcd_density", "480");
    property_set("ro.boot.console", "ttyHSL0");
    property_set("ro.product.board", "MSM8994");
}

