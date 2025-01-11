idf_component_register(
    SRC_DIRS dot_matrix encoder mcu_init sd
    INCLUDE_DIRS dot_matrix encoder mcu_init sd
    PRIV_REQUIRES esp_driver_spi esp_driver_gpio
)