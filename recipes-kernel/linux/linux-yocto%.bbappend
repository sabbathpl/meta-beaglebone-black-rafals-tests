PR = "r0"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://enable_i2c1.dtsi \
    file://enable_analog_inputs.dtsi \
    file://config_misc.cfg \
    file://config_gpio_support.cfg \
    file://config_analog_inputs.cfg \
"

do_configure:append() {
    cp ${WORKDIR}/*.dtsi ${B}/source/arch/${ARCH}/boot/dts
    echo '#include "enable_i2c1.dtsi"' >> ${B}/source/arch/${ARCH}/boot/dts/am335x-boneblack.dts
    echo '#include "enable_analog_inputs.dtsi"' >> ${B}/source/arch/${ARCH}/boot/dts/am335x-boneblack.dts
}

do_compile:append() {
    # Ensure the custom .config file is used
    yes '' | make oldconfig
}