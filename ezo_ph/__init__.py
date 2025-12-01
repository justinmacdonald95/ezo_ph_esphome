import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import core, pins
from esphome.components import sensor, uart

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor"]

ezo_ph_ns = cg.esphome_ns.namespace("ezo_ph")
EzoPH = ezo_ph_ns.class_("EzoPH", sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = sensor.sensor_schema(unit_of_measurement="pH", accuracy_decimals=2).extend(
    cv.polling_component_schema("30s")
).extend({
    cv.GenerateID(): cv.declare_id(EzoPH),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
})

async def to_code(config):
    var = cg.new_Pvariable(config[core.CONF_ID])
    await sensor.register_sensor(var, config)
    await cg.register_component(var, config)

    uart_comp = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart(uart_comp))
