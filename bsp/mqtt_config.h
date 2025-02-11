#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

// 基础配置
#define MQTT_ALIYUN     "ntp1.aliyun.com"  //阿里云NTP服务器地址
#define MQTT_ADDRESS    "k0404wymIZ4.iot-as-mqtt.cn-shanghai.aliyuncs.com"  //MQTT连接地址
#define MQTT_PORT       1883                //MQTT连接端口号

// MQTT连接参数 - 修改后的格式
#define MQTT_CLIENT     "Museum_Hardware|securemode=3,signmethod=hmacsha1|"  // 修改为设备名开头
#define MQTT_USERNAME   "Museum_Hardware"   // 只使用设备名
#define MQTT_PASSWORD   "F9D95D4FCCA0EECD6387311E2D5427D5F4E795A7" //MQTT密码

// 主题配置
// 主题配置
#define MQTT_PUBLIC_TOPIC      "/sys/k0404wymIZ4/Museum_Hardware/thing/event/property/post"
#define MQTT_SUBSCRIBE_TOPIC   "/sys/k0404wymIZ4/Museum_Hardware/thing/service/property/set"
#define MQTT_USER_TOPIC        "/k0404wymIZ4/Museum_Hardware/user/get"

#define MQTT_PARAM_TOPIC      "/sys/k0404wymIZ4/Museum_Hardware/thing/event/property/post"
#endif // MQTT_CONFIG_H