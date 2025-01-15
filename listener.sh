#!/bin/zsh
mosquitto_sub -h broker.hivemq.com -p 1883 -t test/topic -d
