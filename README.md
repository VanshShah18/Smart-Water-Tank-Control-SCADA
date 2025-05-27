# Smart Water Tank Control System

## Overview
SCADA-based control system for intelligent water tank management using OpenPLC Editor and IEC 61131-3 Structured Text programming.

## Functional Requirements
- **Tank Filling Control**: Start pump when level <30%, stop when level >80%
- **Time-Based Operation**: Pump operates only during off-peak hours (10 PM - 6 AM)
- **Overflow Safety**: Emergency stop when level >95% with critical alarm
- **Flow Rate Monitoring**: Alarm if flow rate <10 L/min for more than 5 minutes
- **Maintenance Mode**: Override switch to disable all pump operations

## System Architecture
- **Control Logic**: IEC 61131-3 Structured Text
- **Development Environment**: OpenPLC Editor
- **Timer Functions**: TON function block for 5-minute flow monitoring delay
- **Safety Priority**: Overflow protection > Maintenance mode > Time window > Normal operation

## Variables Declaration
| Variable | Type | Initial Value | Purpose |
|----------|------|---------------|---------|
| tankLevel | INT | 50 | Water level percentage (0-100%) |
| flowRate | INT | 15 | Flow rate in L/min |
| currentHour | INT | 12 | Current time (0-23) for off-peak control |
| maintenanceMode | BOOL | FALSE | Manual override switch |
| pumpCmd | BOOL | FALSE | Final pump control output |
| lowFlowAlarm | BOOL | FALSE | Flow rate alarm status |
| overflowAlarm | BOOL | FALSE | Critical level alarm |
| offPeakActive | BOOL | FALSE | Off-peak hours flag |
| pumpEnable | BOOL | FALSE | Internal pump enable signal |
| flowTimer | TON | - | Timer for flow monitoring |
| timerInput | BOOL | FALSE | Timer input condition |

## Implementation Logic

### Control Priority Hierarchy
1. **Emergency Overflow** (Highest Priority)
   - Tank level >95% → Force pump OFF + Trigger alarm
2. **Maintenance Override**
   - Manual mode enabled → Disable all pump operations
3. **Time Window Enforcement**
   - Only operate during off-peak hours (22:00-06:00)
4. **Normal Level Control**
   - Start: Tank <30% AND off-peak AND NOT maintenance
   - Stop: Tank >80% OR peak hours OR maintenance

### Flow Monitoring System
- **Timer Delay**: 5-minute delay using TON function block
- **Trigger Condition**: Flow rate <10 L/min while pump is enabled
- **Auto-Reset**: Alarm automatically clears when flow ≥10 L/min

### Time-Based Operation
Off-peak hours: 22:00 (10 PM) to 06:00 (6 AM)
Peak hours: 06:00 (6 AM) to 22:00 (10 PM) - Pump disabled


## Code Structure

(* Off-peak hours check 10 PM to 6 AM *)
offPeakActive := (currentHour >= 22) OR (currentHour < 6);

(* Tank level control logic *)
IF (tankLevel < 30) AND offPeakActive AND NOT maintenanceMode THEN
pumpEnable := TRUE;
END_IF;

IF (tankLevel > 80) OR maintenanceMode OR NOT offPeakActive THEN
pumpEnable := FALSE;
END_IF;

(* Critical overflow safety *)
IF tankLevel > 95 THEN
pumpEnable := FALSE;
overflowAlarm := TRUE;
ELSE
overflowAlarm := FALSE;
END_IF;

(* Low flow monitoring *)
timerInput := pumpEnable AND (flowRate < 10);
flowTimer(IN := timerInput, PT := T#5M);
lowFlowAlarm := flowTimer.Q;

(* Final pump command *)
pumpCmd := pumpEnable AND NOT overflowAlarm AND NOT maintenanceMode;


## Testing Results
✅ **Compilation Status**: Code compiles successfully in OpenPLC Editor  
✅ **Syntax Validation**: All IEC 61131-3 standards compliance verified  
✅ **Logic Verification**: All functional requirements implemented correctly  
✅ **Safety Features**: Overflow protection and maintenance override operational  
✅ **Timer Functions**: 5-minute flow monitoring delay working properly  

## Test Scenarios
1. **Normal Operation**: Tank level 25% at 23:00 → Pump starts
2. **Tank Full**: Tank level reaches 85% → Pump stops
3. **Peak Hours**: Tank level 25% at 14:00 → Pump remains off
4. **Overflow Emergency**: Tank level 98% → Pump force stop + Alarm
5. **Maintenance Mode**: Any condition + maintenance ON → Pump disabled
6. **Low Flow**: Flow <10 L/min for 5+ minutes → Alarm triggered

## File Structure

SmartWaterTank.project/
├── build/ # OpenPLC generated files
├── docs/ # Documentation folder
│ └── screenshots/ # Project screenshots
│ ├── Code Area.png # Structured Text code view
│ ├── PLC Log.png # Compilation logs
│ ├── Simulation Success Console.png # Build success
│ └── Variable Description Table.png # Variable declarations
├── project_files/ # OpenPLC project files
├── src/ # Source code folder
├── .gitignore # Git ignore file
├── beremiz # Beremiz configuration
├── plc # PLC configuration
└── README.md # This documentation

text

## Installation & Usage
1. **Open OpenPLC Editor**
2. **Load project file** from project_files/ directory
3. **Configure variables** using the provided table
4. **Build and compile** the project
5. **Test scenarios** by modifying input values in debug mode

## Safety Features
- **Overflow Protection**: Immediate pump shutdown at 95% level
- **Maintenance Override**: Complete system disable capability
- **Time Enforcement**: Prevents operation during peak hours
- **Flow Monitoring**: Early warning system for pump/system issues
- **Priority Logic**: Critical safety takes precedence over normal operation

## Technical Specifications
- **Programming Language**: IEC 61131-3 Structured Text
- **Development Platform**: OpenPLC Editor
- **Timer Resolution**: 1-minute precision for flow monitoring
- **Level Range**: 0-100% integer values
- **Flow Range**: 0+ L/min integer values
- **Time Format**: 24-hour format (0-23)

## Future Enhancements
- **HMI Integration**: SCADA visualization interface
- **Remote Monitoring**: Modbus TCP communication
- **Data Logging**: Historical


## Installation & Usage
1. **Open OpenPLC Editor**
2. **Create new Structured Text program**
3. **Configure variables** using the provided table
4. **Copy the control logic** from src/WaterTankControl.st
5. **Build and compile** the project
6. **Test scenarios** by modifying input values

## Safety Features
- **Overflow Protection**: Immediate pump shutdown at 95% level
- **Maintenance Override**: Complete system disable capability
- **Time Enforcement**: Prevents operation during peak hours
- **Flow Monitoring**: Early warning system for pump/system issues
- **Priority Logic**: Critical safety takes precedence over normal operation

## Technical Specifications
- **Programming Language**: IEC 61131-3 Structured Text
- **Development Platform**: OpenPLC Editor
- **Timer Resolution**: 1-minute precision for flow monitoring
- **Level Range**: 0-100% integer values
- **Flow Range**: 0+ L/min integer values
- **Time Format**: 24-hour format (0-23)

## Future Enhancements
- **HMI Integration**: SCADA visualization interface
- **Remote Monitoring**: Modbus TCP communication
- **Data Logging**: Historical trend analysis
- **Mobile Control**: Remote operation capability
- **Predictive Maintenance**: AI-based failure prediction

## Bonus: AI Code Generation

### Natural Language Prompt
"Create IEC 61131-3 Structured Text code for a smart water tank controller with these requirements:
1. Start pump when tank level <30% during off-peak hours (10 PM to 6 AM)
2. Stop pump when level >80% or during peak hours or maintenance mode
3. Emergency stop if level >95% with overflow alarm
4. Monitor flow rate - trigger alarm if <10 L/min for 5+ minutes
5. Include maintenance mode override that disables all pump operations
6. Use TON timer for flow monitoring delay
7. Implement priority-based control: overflow safety > maintenance > time window > normal operation"

### Expected AI Output
(* AI-generated control logic structure *)
offPeakActive := (currentHour >= 22) OR (currentHour < 6);

IF NOT overflowAlarm THEN
pumpEnable := (tankLevel < 30) AND offPeakActive
AND NOT maintenanceMode AND NOT (tankLevel > 80);
END_IF;

IF tankLevel > 95 THEN
pumpEnable := FALSE;
overflowAlarm := TRUE;
END_IF;

flowTimer(IN := (flowRate < 10), PT := T#5M);
lowFlowAlarm := flowTimer.Q;


This demonstrates how natural language requirements can be effectively translated into functional PLC code through AI assistance, potentially reducing development time and improving code consistency.

## License
MIT License - Educational project for SCADA system development and automation learning.

## Author
Smart Water Tank Control Automation Project  
Developed using OpenPLC Editor and IEC 61131-3 Structured Text  
Implementation Date: May 2025
