OLED_DRIVER_ENABLE= no

# only uncomment on the side you have your trackball on
POINTING_DEVICE_ENABLE = yes
SRC += pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master