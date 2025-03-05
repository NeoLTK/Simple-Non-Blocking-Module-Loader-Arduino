#ifndef Configuration_h
#define Configuration_h


//board
#define NANO 1024
#define BOARD NANO
#define BAUDRATE 115200
#define DELAY 0


//pinout
#define DHT_pin 4
#define HEATER_pin 10
#define FRIDGE_pin 6
#define ULTRASONIC_pin 2
#define HYDROPONIC_pin 7
#define LIGHT_pin FRIDGE_pin

#define CAPACITIVE_SEND_pin 3
#define CAPACITIVE_RECV_pin 8
#define DIGITALTHERMO_pin 9

#define THERMISTOR_pin A1
#define TDS_pin A2
#define PH_pin A3
#define MOISTURE_pin A4
#define PHOTORESISTOR_pin A0

//modules
#define DHTSENSOR 1
#define HEATER 0
#define HYDRATION 0
#define HYDRO 0
#define MOISTURE 0
#define ULTRASONIC 0
#define FONT 1
#define SCREEN 1
#define LIGTHMETER 0
#define TDS 0
#define THERMISTOR 0
#define PH 0
#define FRIDGE 0
#define SERIALMONITOR 1
#define SERIALTRACING 0
#define CAPACITIVE 0
#define DIGITALTHERMO 0
#define PHOTORESISTOR 1
#define ROTARY 1
#define EPROMM 0
#define LIGHT 1


#define FIVE_VOLT_TOLERANCE_WORKAROUND 1

//params
#define RELAY_SECURETIME 18000000 //5h
#define RELAY_SECUREWAIT 450000

#define DHT_type DHT22 

#define FRIDGE_low_trigger 19
#define FRIDGE_hight_trigger 21

#define HEATER_low_trigger 21
#define HEATER_hight_trigger 26

#define HYDRATION_hydrating_time 3000
#define HYDRATION_hydrating_interval 20000

#define HYDRO_HYDRATION_hydrating_time 600000//10m 2400000 // 40m
#define HYDRO_HYDRATION_hydrating_interval 3600000 //h1 //2h//18000000 //5h //54000000 // 15h

#define MOISTURE_air_value  560 //560
#define MOISTURE_water_value  230;
#define MOISTURE_stabilized_trigger 2000
#define MOISTURE_disconnect_trigger 5000
#define MOISTURE_version 2.0 //<-
#define MOISTURE_resistor_disconnect_trigger 1 //<-

#define ULTRASONIC_low_trigger 45
#define ULTRASONIC_hight_trigger 70
#define ULTRASONIC_overtemp_trigger 3 
#define ULTRASONIC_reset_time 3600000
#define ULTRASONIC_hight_temp_trigger HEATER_hight_trigger + ULTRASONIC_overtemp_trigger

#define SCREEN_SSD1306 //Supported : SH1106, SSD1306

#define LIGHT_SLAVE 1

#define PMax 0


//moduleDef
#define THERMISTOR_ID 0x00
#define FRIDGE_ID 0x01
#define HEATER_ID 0x03
#define ULTRASONIC_ID 0x04
#define HYDROPONICS_ID 0x05
#define TDS_ID 0x06
#define PH_ID 0x07
#define SCREEN_ID 0x08
#define LIGHTMETER_ID 0x09
#define DHT_ID 0x0A
#define MOISTURE_ID 0x0B
#define CAPACITIVE_ID 0x0C
#define DIGITALTHERMO_ID 0x0D
#define PHOTORESISTOR_ID 0x0E
#define ROTARY_ID 0x0F
#define LIGHT_ID 0x10

#endif
