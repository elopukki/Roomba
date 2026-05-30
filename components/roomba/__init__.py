import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import register_action
from esphome.components import uart
from esphome.const import (
    CONF_ID,
    CONF_UART_ID,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_ICON,
    CONF_ACCURACY_DECIMALS,
    CONF_NAME,
    DEVICE_CLASS_BATTERY,
    STATE_CLASS_MEASUREMENT,
)
from esphome.components import sensor
from esphome.components import text_sensor

CODEOWNERS = ["@elopukki"]

DEPENDENCIES = ["uart"]

roomba_ns = cg.esphome_ns.namespace("roomba")

Roomba = roomba_ns.class_("RoombaComponent", cg.Component)

# Датчики
RoombaVoltageSensor = roomba_ns.class_("RoombaVoltageSensor", sensor.Sensor, cg.Component)
RoombaCurrentSensor = roomba_ns.class_("RoombaCurrentSensor", sensor.Sensor, cg.Component)
RoombaChargeSensor = roomba_ns.class_("RoombaChargeSensor", sensor.Sensor, cg.Component)
RoombaCapacitySensor = roomba_ns.class_("RoombaCapacitySensor", sensor.Sensor, cg.Component)
RoombaPercentSensor = roomba_ns.class_("RoombaPercentSensor", sensor.Sensor, cg.Component)
RoombaTemperatureSensor = roomba_ns.class_("RoombaTemperatureSensor", sensor.Sensor, cg.Component)
RoombaSpeedSensor = roomba_ns.class_("RoombaSpeedSensor", sensor.Sensor, cg.Component)

# Текстовые датчики
RoombaChargingSensor = roomba_ns.class_("RoombaChargingSensor", text_sensor.TextSensor, cg.Component)
RoombaActivitySensor = roomba_ns.class_("RoombaActivitySensor", text_sensor.TextSensor, cg.Component)
RoombaModeSensor = roomba_ns.class_("RoombaModeSensor", text_sensor.TextSensor, cg.Component)

# Конфигурация
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Roomba),
        cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTBus),
        cv.Optional("polling_interval", default="8000ms"): cv.time_period,
    }
).extend(cv.COMPONENT_SCHEMA)

# Схемот датчиков
SENSOR_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(sensor.Sensor),
        cv.Optional(CONF_NAME): cv.string,
        cv.Optional(CONF_UNIT_OF_MEASUREMENT): cv.string,
        cv.Optional(CONF_ICON): cv.icon,
        cv.Optional(CONF_ACCURACY_DECIMALS, default=2): cv.int_,
    }
)

TEXT_SENSOR_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
        cv.Optional(CONF_NAME): cv.string,
        cv.Optional(CONF_ICON): cv.icon,
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add_build_flag("-DESPHOME_ROOMBA_COMPONENT")
    
    uart_var = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart(uart_var))
    
    await cg.register_component(var, config)