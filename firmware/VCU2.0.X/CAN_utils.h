/*
 * File:   CAN_utils.h
 * Author: pedro
 *
 * Created on 5 de Mar�o de 2024, 21:55
 */

#ifndef CAN_UTILS_H
#define CAN_UTILS_H

#define CAN_BUS1 0U
#define CAN_BUS2 1U
#define CAN_BUS3 2U
#define CAN_BUS4 3U

#include <stdbool.h>  // Defines true
#include <stddef.h>   // Defines NULL
#include <stdint.h>
#include <stdlib.h>  // Defines EXIT_FAILURE

#include "../../../../2_FIRMWARE/VCU_BANCADA/firmware/VCU_BANCADA.X/Can-Header-Map/CAN_asdb.h"
#include "../../../../2_FIRMWARE/VCU_BANCADA/firmware/VCU_BANCADA.X/Can-Header-Map/CAN_datadb.h"
#include "../../../../2_FIRMWARE/VCU_BANCADA/firmware/VCU_BANCADA.X/Can-Header-Map/CAN_pwtdb.h"
#include "definitions.h"

typedef struct {
    uint32_t id;
    uint8_t message[64];
    uint8_t length;
} can_data_t;

can_data_t can_bus_read(uint8_t bus);
void can_bus_send(uint8_t bus, can_data_t* data);

/* Send to DataBus*/
void can_bus_send_databus_1(uint16_t consumed_power, uint16_t target_power, uint8_t brake_pressure, uint8_t throttle_position);
void can_bus_send_databus_2(uint16_t motor_temperature, uint16_t inverter_temperature);
void can_bus_send_databus_3(uint8_t vcu_state, uint8_t lmt2, uint8_t lmt1, uint16_t inverter_error);
void can_bus_send_databus_4(uint16_t rpm, uint16_t inverter_voltage);

/* Send to PowerTrainBus*/
void can_bus_send_pwtbus_1(uint16_t ac_current, uint16_t brake_current);
void can_bus_send_pwtbus_2(uint32_t erpm, uint32_t position);
void can_bus_send_pwtbus_3(uint32_t rel_current, uint32_t rel_brake_current);
void can_bus_send_pwtbus_4(uint32_t max_ac_current, uint32_t max_ac_brake_current);

/*Send Directly to AutonomousBus*/
void CAN_Send_VCU_TOJAL(uint32_t rpm);
void CAN_Send_VCU_TOJAL_POWERTRAIN(uint8_t* rpm);

void CAN_Filter_IDS_BUS1(can_data_t* data);
void CAN_Filter_IDS_BUS2(can_data_t* data);

/*data stucture for interating with the HV500 inverter*/
typedef struct {
    // Received data
    uint32_t Actual_ERPM;
    uint32_t Actual_Duty;
    uint32_t Actual_InputVoltage;
    uint32_t Actual_ACCurrent;
    uint32_t Actual_DCCurrent;
    uint32_t Actual_TempController;
    uint32_t Actual_TempMotor;
    uint32_t Actual_FaultCode;
    uint32_t Actual_FOC_id;
    uint32_t Actual_FOC_iq;
    uint32_t Actual_Throttle;
    uint32_t Actual_Brake;
    uint32_t Digital_input_1;
    uint32_t Digital_input_2;
    uint32_t Digital_input_3;
    uint32_t Digital_input_4;
    uint32_t Digital_output_1;
    uint32_t Digital_output_2;
    uint32_t Digital_output_3;
    uint32_t Digital_output_4;
    uint32_t Drive_enable;
    uint32_t Capacitor_temp_limit;
    uint32_t DC_current_limit;
    uint32_t Drive_enable_limit;
    uint32_t IGBT_accel_limit;
    uint32_t IGBT_temp_limit;
    uint32_t Input_voltage_limit;
    uint32_t Motor_accel_limit;
    uint32_t Motor_temp_limit;
    uint32_t RPM_min_limit;
    uint32_t RPM_max_limit;
    uint32_t Power_limit;
    uint32_t CAN_map_version;

    uint16_t SetCurrent;
    uint16_t SetBrakeCurrent;
    uint32_t SetERPM;
    uint16_t SetPosition;
    uint16_t SetRelativeCurrent;
    uint16_t SetRelativeBrakeCurrent;
    uint32_t SetDigitalOutput;
    uint16_t SetMaxACCurrent;
    uint16_t SetMaxACBrakeCurrent;
    uint16_t SetMaxDCCurrent;
    uint16_t SetMaxDCBrakeCurrent;
    uint8_t DriveEnable;
} HV500;
extern HV500 myHV500;

typedef struct {
    bool VCU;
    bool PDM;
    bool IMU;
    bool DynamicsRear;
    bool DynamicsFront;
} CAN1;

typedef struct {
    bool VCU;
    bool Inverter;
    bool TCU;
    bool BMS;
} CAN2;

typedef struct {
    bool ACU;
    bool FSG_Datalogger;
    bool ALC;
    bool SteeringWheel;
} CAN3;

typedef struct {
    CAN1 can1;
    CAN2 can2;
    CAN3 can3;
} BoardStatus;
extern BoardStatus myboardStatus;

extern bool CANRX_ON[4];  // flag to check if CAN is receiving
extern bool CANTX_ON[4];  // flag to check if CAN is transmitting

extern uint16_t TOJAL_RX_RPM;
extern uint16_t TOJAL_TX_RPM;

extern bool AS_Emergency;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* CAN_UTILS_H */
