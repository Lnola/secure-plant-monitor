#!/bin/zsh
mosquitto_sub -h broker.hivemq.com -p 1883 -t test/topic -d
mosquitto_sub -h broker.hivemq.com -p 1883 -t lnola/sensor/temperature -d
mosquitto_sub -h broker.hivemq.com -p 1883 -t lnola/sensor/humidity -d
mosquitto_sub -h broker.hivemq.com -p 1883 -t lnola/sensor/light-level -d
mosquitto_sub -h broker.hivemq.com -p 1883 -t lnola/sensor/flame -d
