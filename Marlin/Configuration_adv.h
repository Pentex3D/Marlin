/**
 * MARLIN 2.x - Configuration_adv.h
 * Two Trees Sapphire Pro (SP-3)
 * Scheda: MKS Robin Nano V2
 *
 * Setup:
 *  - TMC2208 standalone su X e Y
 *  - Motore estrusore: LDO-36STH20-1004AHG (NEMA14 pancake)
 *  - E3D V6 direct drive (Diamond Mount)
 *  - BLTouch
 */

#pragma once
#define CONFIGURATION_ADV_H_VERSION 02010300

//===========================================================================
//========================= Thermal Settings ================================
//===========================================================================

// Protezione termica hotend
#define THERMAL_PROTECTION_PERIOD        40    // secondi
#define THERMAL_PROTECTION_HYSTERESIS     4    // gradi C

// Protezione termica piatto
#define THERMAL_PROTECTION_BED_PERIOD   120
#define THERMAL_PROTECTION_BED_HYSTERESIS 2

//===========================================================================
//======================= Stepper Motor Drivers =============================
//===========================================================================

/**
 * Driver Stepper:
 *  X: TMC2208 standalone
 *  Y: TMC2208 standalone
 *  Z: A4988 (stock)
 *  E: A4988 (stock) - pilota il LDO NEMA14
 *
 * In modalità standalone i TMC2208 si comportano come A4988 migliorati:
 * nessuna configurazione UART necessaria, ma benefici di StealthChop
 * (moto silenzioso) attivo di default hardware.
 *
 * MICROSTEP: I TMC2208 standalone hanno microstep impostati tramite
 * jumper fisici sulla Robin Nano V2. Verifica che i jumper sotto
 * X e Y siano: MS1=ON, MS2=ON, MS3=ON -> 16 microsteps
 * (corrisponde a DEFAULT_AXIS_STEPS_PER_UNIT X/Y = 80)
 */

#define X_DRIVER_TYPE  TMC2208_STANDALONE
#define Y_DRIVER_TYPE  TMC2208_STANDALONE
#define Z_DRIVER_TYPE  A4988
#define E0_DRIVER_TYPE A4988

//===========================================================================
//========================= Motion Settings =================================
//===========================================================================

// Input Shaping (opzionale, migliora qualità a velocità alta)
// Abilita solo se hai dati dalle misurazioni con ADXL345
// #define INPUT_SHAPING_X
// #define INPUT_SHAPING_Y

// S-Curve acceleration (ammorbidisce i movimenti)
#define S_CURVE_ACCELERATION

// Junction Deviation (alternativa a Jerk, più moderno)
// #define JUNCTION_DEVIATION_MM 0.013   // decommenta per usarlo al posto di Classic Jerk

//===========================================================================
//============================= BLTouch =====================================
//===========================================================================

// Modalità probe BLTouch
#define BLTOUCH_DELAY  500    // ms - pausa dopo deploy/stow
#define BLTOUCH_FORCE_SW_MODE   // Compatibilità con cloni CR Touch

// Numero di misurazioni per mediare il Z
#define MULTIPLE_PROBING 2

// Margine sicurezza Z durante spostamenti con probe deployato
#define Z_CLEARANCE_DEPLOY_PROBE  10
#define Z_CLEARANCE_BETWEEN_PROBES 5
#define Z_CLEARANCE_MULTI_PROBE   5
#define Z_AFTER_PROBING           5

// Velocità probe
#define Z_PROBE_LOW_POINT -3   // quanti mm scende sotto zero prima di errore

//===========================================================================
//========================== Bed Leveling ===================================
//===========================================================================

// Fade leveling: la correzione si azzera gradualmente salendo in Z
// (così le prime layer sono corrette, quelle alte no)
#define ENABLE_LEVELING_FADE_HEIGHT

// G26 Mesh Validation (stampa pattern per verificare la mesh)
#define G26_MESH_VALIDATION

// Leveling automatico dopo G28
#define RESTORE_LEVELING_AFTER_G28

//===========================================================================
//======================= Extruder / Direct Drive ===========================
//===========================================================================

/**
 * LDO-36STH20-1004AHG con E3D V6 in direct drive:
 * - Retrazione consigliata: 0.5 - 1.0mm (direct drive!)
 *   NON usare i valori Bowden (4-6mm) o bruci il filamento nell'hotend
 * - Imposta nel tuo slicer: retrazione 0.6-0.8mm, velocità 40-60mm/s
 */

// Prevenzione stringing (park durante cambio colore/pausa)
#define ADVANCED_PAUSE_FEATURE
#define PAUSE_PARK_RETRACT_FEEDRATE    60   // mm/s
#define PAUSE_PARK_RETRACT_LENGTH       1   // mm - direct drive!
#define FILAMENT_CHANGE_UNLOAD_FEEDRATE 20
#define FILAMENT_CHANGE_UNLOAD_LENGTH   50  // mm - direct drive, basta poco
#define FILAMENT_CHANGE_LOAD_FEEDRATE   20
#define FILAMENT_CHANGE_LOAD_LENGTH     40
#define FILAMENT_CHANGE_FAST_LOAD_FEEDRATE 20
#define FILAMENT_CHANGE_FAST_LOAD_LENGTH   0

// Lin Advance (migliora la qualità angoli e curve)
// Abilita e calibra con la torre di pressione K
// #define LIN_ADVANCE
// #define LIN_ADVANCE_K 0.05    // Punto di partenza per E3D V6 DD, da calibrare

//===========================================================================
//=========================== Power Loss Recovery ===========================
//===========================================================================

// Ripresa dopo mancanza di corrente (richiede modulo dedicato)
// #define POWER_LOSS_RECOVERY

//===========================================================================
//============================ EEPROM =======================================
//===========================================================================

#define EEPROM_SETTINGS
#define EEPROM_AUTO_INIT
#define EEPROM_BOOT_SILENT

//===========================================================================
//========================== LCD / Interface ================================
//===========================================================================

// Timeout schermo (ms)
#define LCD_TIMEOUT_TO_STATUS 60000

// Mostra coordinate realtime sul display
#define LCD_INFO_MENU
#define STATUS_MESSAGE_SCROLLING

// Encoder (non usato su touch screen, ma lascialo definito)
#define ENCODER_PULSES_PER_STEP 4
#define ENCODER_STEPS_PER_MENU_ITEM 1

//===========================================================================
//========================== Host / OctoPrint ===============================
//===========================================================================

// Comunicazione con host (OctoPrint, Pronterface, ecc.)
#define HOST_KEEPALIVE_FEATURE
#define DEFAULT_KEEPALIVE_INTERVAL 2   // secondi
#define BUSY_WHILE_HEATING

// Abilita M150 per eventuale LED RGB (per dopo)
// #define NEOPIXEL_LED

//===========================================================================
//========================= Calibration Helpers =============================
//===========================================================================

/**
 * PASSI CALIBRAZIONE DOPO IL FLASH:
 *
 * 1. M502 + M500    -> Reset e salva defaults
 * 2. G28            -> Homing completo
 * 3. G29            -> Auto bed leveling (salva mesh)
 * 4. Calibra Z offset BLTouch:
 *    - G28, poi sposta Z manualmente fino a paper test
 *    - M851 Z-X.XX  (es: M851 Z-1.5)
 *    - M500
 * 5. Calibra E steps/mm:
 *    - Marca 100mm di filamento
 *    - M83 + G1 E100 F100
 *    - Misura quanto ha estruso realmente
 *    - Nuovo valore = (100 / estrus_reale) * 415
 *    - M92 E[nuovo_valore] + M500
 * 6. PID Hotend:
 *    - M303 E0 S200 C8 U1 + M500
 * 7. PID Piatto:
 *    - M303 E-1 S60 C8 U1 + M500
 * 8. Calibra retrazione:
 *    - Parti da 0.6mm a 45mm/s nel tuo slicer
 */

//===========================================================================
//============================ FINE FILE ====================================
//===========================================================================
