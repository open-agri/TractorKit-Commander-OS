set(SOURCES main.c)
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS .
                    REQUIRES app_update lvgl_esp32_drivers lvgl_touch lvgl_tft lvgl tkos)

target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_CONF_INCLUDE_SIMPLE=1)
