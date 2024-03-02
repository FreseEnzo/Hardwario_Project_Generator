# Shell features dictionary
DICT_FEATURES: dict[str, str] = {
    "shell": "CONFIG_ADC_SHELL=y\n",
    "accel": "CONFIG_CTR_ACCEL=y\n",
    "adc": "CONFIG_CTR_ADC=y\n",
    "batt": "CONFIG_CTR_BATT=y\n",
    "bluetooth": "CONFIG_CTR_BLE=y\n",
    "buf": "CONFIG_CTR_BUF=y\n",
    "button": "CONFIG_CTR_BUTTON=y\n",
    "defaults": "CONFIG_CTR_DEFAULTS=y\n",
    "edge": "CONFIG_CTR_EDGE=y\n",
    "info": "CONFIG_CTR_INFO=y\n",
    "led": "CONFIG_CTR_LED=y\n",
    "log": "CONFIG_CTR_LOG=y\n",
    "lte": "CONFIG_CTR_LTE_CLKSYNC=y\n",
    "lorawan": "CONFIG_CTR_LRW=y\n",
    "rtc": "CONFIG_CTR_RTC=y\n",
    "shell": "CONFIG_CTR_SHELL=y\n",
    "therm": "CONFIG_CTR_THERM=y\n",
    "wdog": "CONFIG_CTR_WDOG=y\n",
    "entropy_generator": "CONFIG_ENTROPY_GENERATOR=y\n",
    "tinycrypt_sha256": "CONFIG_TINYCRYPT_SHA256=y\n",
    "tinycrypt": "CONFIG_TINYCRYPT=y\n",
    "zcbor_stop_on_error": "CONFIG_ZCBOR_STOP_ON_ERROR=y\n",
    "zcbor": "CONFIG_ZCBOR=y\n",
}

# User save markers
USER_CODE_MARKERS: list[dict[str, str]] = [
    {"begin": "/* USER CODE BEGIN Includes */", "end": "/* USER CODE END Includes */"},
    {
        "begin": "/* USER CODE BEGIN Variables */",
        "end": "/* USER CODE END Variables */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 0 */",
        "end": "/* USER CODE END Functions 0 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 1 */",
        "end": "/* USER CODE END Functions 1 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 2 */",
        "end": "/* USER CODE END Functions 2 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 3 */",
        "end": "/* USER CODE END Functions 3 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 4 */",
        "end": "/* USER CODE END Functions 4 */",
    },
    {"begin": "# USER CODE BEGIN Config", "end": "# USER CODE END Config"},
    {
        "begin": "/* USER CODE BEGIN Overlay */",
        "end": "/* USER CODE END Overlay */",
    },
]

SHIELDS_OVERLAY : dict[str, str] = {
    "ctr_lte": '&ctr_lte_if {\n\tstatus = "okay";\n};\n\n&uart0 {\n\tstatus = "okay";\n};',
    "ctr_lrw": '&ctr_lrw_if {\n\tstatus = "okay";\n};\n\n&uart1 {\n\tstatus = "okay";\n};',
    "ctr_z": '&ctr_z {\n\tstatus = "okay";\n};',
    "ctr_x0_a": '&ctr_x0_a {\n\tstatus = "okay";\n};\n\n&ctr_x0_pcal6416a_a {\n\tstatus = "okay";\n};',
    "ctr_s2": '&sht30_ext {\n\tstatus = "okay";\n};',
    "ctr_s1": '&ctr_s1 {\n\tstatus = "okay";\n};',
    "ctr_ds18b20": "&ds2484 {\n\t"
    + "ds18b20_0: ds18b20_0 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_1: ds18b20_1 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_2: ds18b20_2 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_3: ds18b20_3 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_4: ds18b20_4 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_5: ds18b20_5 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_6: ds18b20_6 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_7: ds18b20_7 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_8: ds18b20_8 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n\t"
    + "ds18b20_9: ds18b20_9 {\n\t\t"
    + 'compatible = "maxim,ds18b20";\n\t\t'
    + "resolution = <12>;\n\t\t"
    + "family-code = <0x28>;\n\t};\n"
    + "};",
    "ctr_rtd_a": '&ctr_x3_a {\n\tstatus = "okay";\n};\n\n'
    + '&ctr_x3_ads122c04_a1 {\n\tvref = <1>;\n\tidac = <6>;\n\ti1mux = <4>;\n\tstatus = "okay";\n};\n\n'
    + '&ctr_x3_ads122c04_a2 {\n\tvref = <1>;\n\tidac = <6>;\n\ti1mux = <4>;\n\tstatus = "okay";\n};',
}

CHESTER_VARIANTS: dict[str, dict[str, str]] = {
    "Clime": {"shield_1": "ctr_lte", "shield_2": "ctr_s2"},
    "Clime Z": {"shield_1": "ctr_lte", "shield_2": "ctr_s2", "shield_3": "ctr_z"},
    "Clime IAQ": {
        "shield_1": "ctr_lte",
        "shield_2": "ctr_s1",
    },
    "Clime 1W": {
        "shield_1": "ctr_lte",
        "shield_2": "ctr_ds18b20",
    },
    "Clime 1WH": {
        "shield_1": "ctr_lte",
        "shield_2": "ctr_ds18b20",
        "shield_3": "ctr_s2",
    },
    "Clime RTD": {
        "shield_1": "ctr_lte",
        "shield_2": "ctr_rtd_a",
    },
}

