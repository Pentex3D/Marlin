/**
 * MARLIN 2.x - Configuration.h
 * Two Trees Sapphire Pro (SP-3)
 * Scheda: MKS Robin Nano V2 (STM32F407)
 *
 * Setup:
 *  - TMC2208 standalone su X e Y
 *  - Driver stock (A4988) su Z ed E
 *  - Motore estrusore: LDO-36STH20-1004AHG (NEMA14 pancake, 10T gear)
 *  - Hotend: E3D V6
 *  - Direct drive (Diamond Mount)
 *  - BLTouch per livellamento automatico
 *
 * ISTRUZIONI COMPILAZIONE:
 *  1. Apri il repo Marlin 2.x con VSCode + PlatformIO
 *  2. Sostituisci Marlin/Configuration.h con questo file
 *  3. Sostituisci Marlin/Configuration_adv.h con il file allegato
 *  4. In platformio.ini imposta: default_envs = mks_robin_nano_v2
 *  5. Build -> copia out/Robin_nano35.bin sulla SD -> accendi la stampante
 *
 * NOTA: dopo il flash esegui sempre:
 *   M502 (carica defaults)
 *   M500 (salva in EEPROM)
 *   poi calibra il Z-offset del BLTouch
 */

#pragma once
#define CONFIGURATION_H_VERSION 02010300

//===========================================================================
//============================= Getting Started =============================
//===========================================================================

#define STRING_CONFIG_H_AUTHOR "(Sapphire Pro - TMC2208 standalone + LDO E3D V6 DD + BLTouch)"
#define CUSTOM_MACHINE_NAME "Sapphire Pro"

//===========================================================================
//============================= Motherboard =================================
//===========================================================================

// MKS Robin Nano V2 (STM32F407)
#define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V2

//===========================================================================
//============================== Serial =====================================
//===========================================================================

#define SERIAL_PORT 1
#define SERIAL_PORT_2 3   // USB
#define BAUDRATE 250000

//===========================================================================
//========================= Extruder Settings ================================
//===========================================================================

#define EXTRUDERS 1
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75

//===========================================================================
//====================== Thermal Settings ===================================
//===========================================================================

// Sensore hotend E3D V6
#define TEMP_SENSOR_0 5        // ATC Semitec 104GT-2 (usato da E3D V6)
#define TEMP_SENSOR_BED 1      // EPCOS 100K NTC

#define HEATER_0_MINTEMP   5
#define HEATER_0_MAXTEMP 275
#define BED_MINTEMP        5
#define BED_MAXTEMP      120

// Protezione termica - IMPORTANTE: disabilita solo per PID tuning
#define THERMAL_PROTECTION_HOTENDS
#define THERMAL_PROTECTION_BED
#define THERMAL_PROTECTION_CHAMBER

//===========================================================================
//============================== PID Settings ================================
//===========================================================================

// PID Hotend - valori di partenza per E3D V6, fai PID tuning dopo il flash
// Comando: M303 E0 S200 C8 U1
#define PIDTEMP
#define PID_K1 0.95
#define DEFAULT_Kp  22.20
#define DEFAULT_Ki   1.08
#define DEFAULT_Kd 114.00

// PID Piatto
#define PIDTEMPBED
#define DEFAULT_bedKp 325.10
#define DEFAULT_bedKi  63.35
#define DEFAULT_bedKd 417.10

//===========================================================================
//============================== Kinematics =================================
//===========================================================================

#define COREXY

//===========================================================================
//============================== Endstops ===================================
//===========================================================================

#define USE_XMIN_PLUG
#define USE_YMAX_PLUG
#define USE_ZMIN_PLUG     // BLTouch usa Z_MIN

// Logica endstop (normalmente chiusi sulla Sapphire Pro)
#define X_MIN_ENDSTOP_INVERTING true
#define Y_MAX_ENDSTOP_INVERTING true
#define Z_MIN_ENDSTOP_INVERTING false   // BLTouch: false

#define ENDSTOPPULLUPS

//===========================================================================
//============================== Movement ===================================
//===========================================================================

/**
 * Steps per mm:
 *  X/Y: CoreXY con pulegge 20T GT2 = 80 steps/mm (TMC2208 a 16 microsteps)
 *  Z:   Vite M5 passo 2mm = 1600 steps/mm (A4988 a 16 microsteps) -> 2mm/giro
 *       rotation_distance Klipper=2, qui: (200*16)/2 = 1600
 *  E:   LDO NEMA14 10T gear, direct drive E3D V6
 *       Base di partenza: ~415 steps/mm - CALIBRARE dopo il flash!
 *       Formula: (200 * 16 * gear_ratio) / (circonferenza ruota dentata)
 */
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 1600, 415 }

#define DEFAULT_MAX_FEEDRATE          { 200, 200, 5, 50 }
#define DEFAULT_MAX_ACCELERATION      { 2000, 2000, 100, 5000 }

#define DEFAULT_ACCELERATION          1000   // Stampa
#define DEFAULT_RETRACT_ACCELERATION  1000   // Retrazione
#define DEFAULT_TRAVEL_ACCELERATION   2000   // Viaggi vuoti

// Jerk (ridotto per CoreXY con direct drive)
#define CLASSIC_JERK
#define DEFAULT_XJERK  10.0
#define DEFAULT_YJERK  10.0
#define DEFAULT_ZJERK   0.3
#define DEFAULT_EJERK   5.0

//===========================================================================
//============================== Z Offset ===================================
//===========================================================================

// Attiva la regolazione Z offset via menu LCD
#define EEPROM_SETTINGS
#define EEPROM_AUTO_INIT

//===========================================================================
//============================== BLTouch ====================================
//===========================================================================

#define BLTOUCH

// Pin BLTouch sulla Robin Nano V2
// Servo pin: PA8 (servo connettore)
// Z_MIN_PIN: PG9 (z-stop)
#define SERVO0_PIN PA8

/**
 * OFFSET BLTouch dal nozzle - MISURA FISICAMENTE!
 * X positivo = BLTouch a destra del nozzle
 * Y positivo = BLTouch davanti al nozzle
 * Z: da calibrare con M851 dopo il flash
 *
 * Valori placeholder - MODIFICA con le tue misure reali!
 */
#define NOZZLE_TO_PROBE_OFFSET { -30, -10, -2.0 }

#define PROBING_MARGIN 20          // Margine dai bordi del piatto
#define XY_PROBE_FEEDRATE (133*60) // Velocità spostamento durante probe
#define Z_PROBE_FEEDRATE_FAST (4*60)
#define Z_PROBE_FEEDRATE_SLOW (Z_PROBE_FEEDRATE_FAST / 2)

// Abilita software endstop per Z
#define MIN_SOFTWARE_ENDSTOP_Z

//===========================================================================
//========================= Auto Bed Leveling ===============================
//===========================================================================

#define AUTO_BED_LEVELING_BILINEAR

#define GRID_MAX_POINTS_X 5    // Griglia 5x5 punti
#define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

#define EXTRAPOLATE_BEYOND_GRID

// Abilita mesh leveling durante la stampa
#define ENABLE_LEVELING_FADE_HEIGHT
#define DEFAULT_LEVELING_FADE_HEIGHT 10.0

// Salva la mesh in EEPROM
#define RESTORE_LEVELING_AFTER_G28

//===========================================================================
//============================== Homing =====================================
//===========================================================================

// Homing order: X poi Y poi Z con BLTouch
#define HOME_AFTER_DEACTIVATE
#define Z_SAFE_HOMING          // Homing Z al centro del piatto

#define Z_SAFE_HOMING_X_POINT  115   // Centro X (230/2)
#define Z_SAFE_HOMING_Y_POINT  115   // Centro Y (230/2)

// Direzioni homing
#define X_HOME_DIR -1   // X va a min
#define Y_HOME_DIR  1   // Y va a max
#define Z_HOME_DIR -1   // Z va verso il piatto

// Dimensioni piatto
#define X_BED_SIZE 220
#define Y_BED_SIZE 220

#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define X_MAX_POS X_BED_SIZE
#define Y_MAX_POS Y_BED_SIZE
#define Z_MAX_POS 220

//===========================================================================
//============================== Filament =================================
//===========================================================================

// Rilevamento fine filamento (se hai il sensore, altrimenti lascia commentato)
// #define FILAMENT_RUNOUT_SENSOR

//===========================================================================
//============================== LCD / Display ==============================
//===========================================================================

// Display TFT touch originale della Sapphire Pro (MKS TFT35)
#define TFT_LVGL_UI
#define MKS_ROBIN_TFT35

//===========================================================================
//============================== Fan ========================================
//===========================================================================

// Fan part cooling (controllato dal gcode)
#define FAN_SOFT_PWM

// Fan hotend sempre acceso sopra soglia temperatura
#define E0_AUTO_FAN_PIN PB0
#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED 255

//===========================================================================
//======================== Extra Features ===================================
//===========================================================================

#define BABYSTEPPING
#define BABYSTEP_MULTIPLICATOR_Z  1
#define BABYSTEP_MULTIPLICATOR_XY 1

// Preheat presets
#define PREHEAT_1_LABEL       "PLA"
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_FAN_SPEED   255

#define PREHEAT_2_LABEL       "PETG"
#define PREHEAT_2_TEMP_HOTEND 235
#define PREHEAT_2_TEMP_BED     80
#define PREHEAT_2_FAN_SPEED   255

#define PREHEAT_3_LABEL       "ABS"
#define PREHEAT_3_TEMP_HOTEND 240
#define PREHEAT_3_TEMP_BED    100
#define PREHEAT_3_FAN_SPEED     0

// Nozzle Park (utile per filament change e pause)
#define NOZZLE_PARK_FEATURE
#define NOZZLE_PARK_POINT { 5, 215, 10 }

// Print Counter
#define PRINTCOUNTER

//===========================================================================
//============================ FINE FILE ====================================
//===========================================================================
