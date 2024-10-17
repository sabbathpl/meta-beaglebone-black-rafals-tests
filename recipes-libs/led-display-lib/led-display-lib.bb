DESCRIPTION = "Testing lib compilation for OLED display"
SUMMARY = "Lib for OLED display"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Where to find source files (can be local, GitHub, etc.)
SRC_URI = "file://src"

# Where to keep downloaded source files (in tmp/work/...)
S = "${WORKDIR}/src"

inherit autotools
inherit logging

do_compile:append() {
    bbwarn "Hello this is a debug message from ${USER}"
}

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
# PARALLEL_MAKE = ""