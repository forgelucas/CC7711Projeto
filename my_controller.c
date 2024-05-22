#include <stdio.h>
#include <webots/supervisor.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <math.h>

#define TIME_STEP 256
#define QtddSensoresProx 8
#define QtddLeds 10

int main(int argc, char **argv) {
    int i = 0;
    char texto[256];
    double LeituraSensorProx[QtddSensoresProx];
    double AceleradorDireito = 1.0, AceleradorEsquerdo = 1.0;
    for (i = 0; i < 256; i++) texto[i] = '0';

    wb_robot_init();
    
    // Configuração dos motores
    WbDeviceTag MotorEsquerdo, MotorDireito;
    MotorEsquerdo = wb_robot_get_device("left wheel motor");
    MotorDireito = wb_robot_get_device("right wheel motor");
    wb_motor_set_position(MotorEsquerdo, INFINITY);
    wb_motor_set_position(MotorDireito, INFINITY);
    wb_motor_set_velocity(MotorEsquerdo, 0);
    wb_motor_set_velocity(MotorDireito, 0);

    // Configuração dos sensores de proximidade
    WbDeviceTag SensorProx[QtddSensoresProx];
    SensorProx[0] = wb_robot_get_device("ps0");
    SensorProx[1] = wb_robot_get_device("ps1");
    SensorProx[2] = wb_robot_get_device("ps2");
    SensorProx[3] = wb_robot_get_device("ps3");
    SensorProx[4] = wb_robot_get_device("ps4");
    SensorProx[5] = wb_robot_get_device("ps5");
    SensorProx[6] = wb_robot_get_device("ps6");
    SensorProx[7] = wb_robot_get_device("ps7");

    wb_distance_sensor_enable(SensorProx[0], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[1], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[2], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[3], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[4], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[5], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[6], TIME_STEP);
    wb_distance_sensor_enable(SensorProx[7], TIME_STEP);

    // Configuração dos LEDs
    WbDeviceTag Leds[QtddLeds];
    Leds[0] = wb_robot_get_device("led0");
    Leds[1] = wb_robot_get_device("led1");
    Leds[2] = wb_robot_get_device("led2");
    Leds[3] = wb_robot_get_device("led3");
    Leds[4] = wb_robot_get_device("led4");
    Leds[5] = wb_robot_get_device("led5");
    Leds[6] = wb_robot_get_device("led6");
    Leds[7] = wb_robot_get_device("led7");
    Leds[8] = wb_robot_get_device("led8");
    Leds[9] = wb_robot_get_device("led9");

    wb_led_set(Leds[0], 0);
    wb_led_set(Leds[1], 0);
    wb_led_set(Leds[2], 0);
    wb_led_set(Leds[3], 0);
    wb_led_set(Leds[4], 0);
    wb_led_set(Leds[5], 0);
    wb_led_set(Leds[6], 0);
    wb_led_set(Leds[7], 0);
    wb_led_set(Leds[8], 0);
    wb_led_set(Leds[9], 0);

    WbNodeRef constCaixa = wb_supervisor_node_get_from_def("wooden_box");
    double vector[3] = {-0.35, -0.35, 0.039995};
    
    while (wb_robot_step(TIME_STEP) != -1) {
        for (i = 0; i < 256; i++) texto[i] = 0;
        for (i = 0; i < QtddSensoresProx; i++) {
            LeituraSensorProx[i] = wb_distance_sensor_get_value(SensorProx[i]) - 60;
            sprintf(texto, "%s|%d: %5.2f  ", texto, i, LeituraSensorProx[i]);
        }
        printf("%s\n", texto);
        
        double movimentoCoordenadas = 0.02;
        
        const double *caixa_movel = wb_supervisor_node_get_position(constCaixa);
        if (fabs(vector[0] - caixa_movel[0]) > movimentoCoordenadas ||
            fabs(vector[1] - caixa_movel[1]) > movimentoCoordenadas ||
            fabs(vector[2] - caixa_movel[2]) > movimentoCoordenadas) {
            printf("A caixa se moveu.\n");
            AceleradorDireito = 0;
            AceleradorEsquerdo = 0;
            wb_motor_set_velocity(MotorEsquerdo, 0);
            wb_motor_set_velocity(MotorDireito, 0);

            for (i = 0; i < QtddLeds; i++) {
                wb_led_set(Leds[i], 1);
            }
            break;
        }

        if (LeituraSensorProx[0] > 10) {
            AceleradorDireito = -1;
            AceleradorEsquerdo = 1;
        } else {
            AceleradorDireito = 1.0;
            AceleradorEsquerdo = 1.0;
        }

        wb_motor_set_velocity(MotorEsquerdo, 6.28 * AceleradorEsquerdo);
        wb_motor_set_velocity(MotorDireito, 6.28 * AceleradorDireito);
    }

    wb_robot_cleanup();

    return 0;
}
