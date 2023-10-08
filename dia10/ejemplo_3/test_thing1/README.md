# Prueba usando el cliente mosquito pub y sub


![red_mqtt](mqtt_ejemplo3-mosquitto-client.png)



```bash
mosquitto_pub -h test.mosquitto.org -t IOT_UDEA-001/commands -m '{"alarm_on":1}'
mosquitto_pub -h test.mosquitto.org -t IOT_UDEA-001/commands -m '{"alarm_on":0}'
```


```bash
mosquitto_sub -h test.mosquitto.org -t IOT_UDEA-001/#
```

