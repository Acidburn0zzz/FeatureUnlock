//
//  kern_start.cpp
//  FeatureUnlock.kext
//
//  Copyright © 2020 osy86, DhinakG, 2021 Mykola Grymalyuk. All rights reserved.
//

#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>
#include <Headers/kern_user.hpp>

#define MODULE_SHORT "sidecar"

#pragma mark - Patches

// SidecarCore.framework
// Replaces Mac with Nac
static const uint8_t kMacModelSidecarOriginal[] = { 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

static const uint8_t kMacModelSidecarPatched[] = { 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

// AirPlayCore.framework
// Replaces Mac with Nac
static const uint8_t kMacModelAirplayOriginal[] = { 0x69, 0x4D, 0x61, 0x63, 0x31, 0x37, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x32, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x33, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x4D, 0x61, 0x63, 0x4D, 0x69, 0x6E, 0x69, 0x38, 0x2C, 0x31
};

static const uint8_t kMacModelAirplayPatched[] = { 0x69, 0x4E, 0x61, 0x63, 0x31, 0x37, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x32, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x38, 0x2C, 0x33, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x4E, 0x61, 0x63, 0x4E, 0x69, 0x6E, 0x69, 0x38, 0x2C, 0x31
};

// SidecarCore.framework
// Replaces iPad with hPad
static const uint8_t kIPadModelOriginal[] = { 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00, 0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32
};

static const uint8_t kIPadModelPatched[] = { 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00, 0x68, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00, 0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00, 0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00, 0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00, 0x68, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00, 0x68, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00, 0x68, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32
};

// UniversalControl.framework
// Replaces Mac with Nac, Pad with Qad
static const uint8_t kUniversalControlModelOriginal[] = { 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00, 0x69, 0x4D, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00, 0x69, 0x50, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00, 0x69, 0x50, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00, 0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00, 0x69, 0x50, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00, 0x4D, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x50, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00, 0x4D, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00, 0x4D, 0x61, 0x63, 0x50, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

static const uint8_t kUniversalControlModelPatched[] = { 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x32, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x33, 0x2C, 0x33, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x31, 0x00, 0x69, 0x4E, 0x61, 0x63, 0x31, 0x36, 0x2C, 0x32, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x31, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x32, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x33, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x34, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x35, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x36, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x37, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x38, 0x00, 0x69, 0x51, 0x61, 0x64, 0x34, 0x2C, 0x39, 0x00, 0x69, 0x51, 0x61, 0x64, 0x35, 0x2C, 0x31, 0x00, 0x69, 0x51, 0x61, 0x64, 0x35, 0x2C, 0x32, 0x00, 0x69, 0x51, 0x61, 0x64, 0x35, 0x2C, 0x33, 0x00, 0x69, 0x51, 0x61, 0x64, 0x35, 0x2C, 0x34, 0x00, 0x69, 0x51, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x31, 0x00, 0x69, 0x51, 0x61, 0x64, 0x36, 0x2C, 0x31, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x38, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x35, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x36, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x41, 0x69, 0x72, 0x37, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x39, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x39, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x30, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x33, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x34, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x31, 0x2C, 0x35, 0x00, 0x4E, 0x61, 0x63, 0x42, 0x6F, 0x6F, 0x6B, 0x51, 0x72, 0x6F, 0x31, 0x32, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x36, 0x2C, 0x32, 0x00, 0x4E, 0x61, 0x63, 0x6D, 0x69, 0x6E, 0x69, 0x37, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x51, 0x72, 0x6F, 0x35, 0x2C, 0x31, 0x00, 0x4E, 0x61, 0x63, 0x51, 0x72, 0x6F, 0x36, 0x2C, 0x31
};

// CoreBrightness.framework
// Lowers NightShift requirement: 10.12 - 10.13.0
static const uint8_t kNightShiftLegacyOriginal[] = { 0x09, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
};
static const uint8_t kNightShiftLegacyPatched[] = { 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
};

// CoreBrightness.framework
// Lowers NightShift requirement: 10.13.1+
static const uint8_t kNightShiftOriginal[] = { 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
};
static const uint8_t kNightShiftPatched[] = { 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
};

static_assert(sizeof(kMacModelSidecarOriginal) == sizeof(kMacModelSidecarPatched), "patch size invalid");
static_assert(sizeof(kMacModelAirplayOriginal) == sizeof(kMacModelAirplayPatched), "patch size invalid");
static_assert(sizeof(kIPadModelOriginal) == sizeof(kIPadModelPatched), "patch size invalid");
static_assert(sizeof(kUniversalControlModelOriginal) == sizeof(kUniversalControlModelPatched), "patch size invalid");
static_assert(sizeof(kNightShiftOriginal) == sizeof(kNightShiftPatched), "patch size invalid");
static_assert(sizeof(kNightShiftLegacyOriginal) == sizeof(kNightShiftLegacyPatched), "patch size invalid");

static mach_vm_address_t orig_cs_validate {};

#pragma mark - Kernel patching code

template <size_t findSize, size_t replaceSize>
static inline void searchAndPatch(const void *haystack, size_t haystackSize, const char *path, const uint8_t (&needle)[findSize], const uint8_t (&patch)[replaceSize]) {
   if (UNLIKELY(KernelPatcher::findAndReplace(const_cast<void *>(haystack), haystackSize, needle, findSize, patch, replaceSize)))
	   DBGLOG(MODULE_SHORT, "found function to patch at %s!", path);
}

#pragma mark - Patched functions

// pre Big Sur
static boolean_t patched_cs_validate_range(vnode_t vp, memory_object_t pager, memory_object_offset_t offset, const void *data, vm_size_t size, unsigned *result) {
    char path[PATH_MAX];
    int pathlen = PATH_MAX;
    boolean_t res = FunctionCast(patched_cs_validate_range, orig_cs_validate)(vp, pager, offset, data, size, result);
    if (res && vn_getpath(vp, path, &pathlen) == 0 && UserPatcher::matchSharedCachePath(path)) {
        searchAndPatch(data, size, path, kMacModelSidecarOriginal, kMacModelSidecarPatched);
        searchAndPatch(data, size, path, kIPadModelOriginal, kIPadModelPatched);
        if ((getKernelVersion() == KernelVersion::HighSierra && getKernelMinorVersion() >= 2) || getKernelVersion() >= KernelVersion::Mojave) {
            searchAndPatch(data, size, path, kNightShiftOriginal, kNightShiftPatched);
        } else {
            searchAndPatch(data, size, path, kNightShiftLegacyOriginal, kNightShiftLegacyPatched);
        }
    }
    return res;
}

// For Big Sur and newer
static void patched_cs_validate_page(vnode_t vp, memory_object_t pager, memory_object_offset_t page_offset, const void *data, int *validated_p, int *tainted_p, int *nx_p) {
    char path[PATH_MAX];
    int pathlen = PATH_MAX;
    FunctionCast(patched_cs_validate_page, orig_cs_validate)(vp, pager, page_offset, data, validated_p, tainted_p, nx_p);
	if (vn_getpath(vp, path, &pathlen) == 0 && UserPatcher::matchSharedCachePath(path)) {
        searchAndPatch(data, PAGE_SIZE, path, kMacModelSidecarOriginal, kMacModelSidecarPatched);
        searchAndPatch(data, PAGE_SIZE, path, kIPadModelOriginal, kIPadModelPatched);
        searchAndPatch(data, PAGE_SIZE, path, kNightShiftOriginal, kNightShiftPatched);
        if (getKernelVersion() >= KernelVersion::Monterey) {
            searchAndPatch(data, PAGE_SIZE, path, kUniversalControlModelOriginal, kUniversalControlModelPatched);
            searchAndPatch(data, PAGE_SIZE, path, kMacModelAirplayOriginal, kMacModelAirplayPatched);
        }
    }
}

#pragma mark - Patches on start/stop

static void pluginStart() {
	DBGLOG(MODULE_SHORT, "start");
	lilu.onPatcherLoadForce([](void *user, KernelPatcher &patcher) {
		KernelPatcher::RouteRequest csRoute =
			getKernelVersion() >= KernelVersion::BigSur ?
			KernelPatcher::RouteRequest("_cs_validate_page", patched_cs_validate_page, orig_cs_validate) :
			KernelPatcher::RouteRequest("_cs_validate_range", patched_cs_validate_range, orig_cs_validate);
		if (!patcher.routeMultipleLong(KernelPatcher::KernelID, &csRoute, 1))
			SYSLOG(MODULE_SHORT, "failed to route cs validation pages");
	});
}

// Boot args.
static const char *bootargOff[] {
    "-caroff"
};
static const char *bootargDebug[] {
    "-cardbg"
};
static const char *bootargBeta[] {
    "-carbeta"
};

// Plugin configuration.
PluginConfiguration ADDPR(config) {
    xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
    LiluAPI::AllowNormal,
    bootargOff,
    arrsize(bootargOff),
    bootargDebug,
    arrsize(bootargDebug),
    bootargBeta,
    arrsize(bootargBeta),
    KernelVersion::Catalina,
    KernelVersion::Monterey,
    pluginStart
};
