# Setting Up F´ GDS Communication with STM32 over USB

This guide explains how to control your STM32 Nucleo-H7A3ZI-Q board from the F´ Ground Data System (GDS) on Windows via USB.

## Overview

Your STM32 board connects to Windows via USB, which appears as a Virtual COM Port (VCP). The F´ GDS will communicate with the board using the F´ framing protocol over UART.

## Architecture

```
Windows PC (GDS)  <--USB/Serial-->  STM32 Board (F´ Flight Software)
     |                                    |
  fprime-gds                         UART Driver
     |                                    |
  Framing Protocol  <-- Packets -->  Deframing Protocol
     |                                    |
Commands/Telemetry                   Components (LedBlinker)
```

## Prerequisites

1. **Python Environment** on Windows with F´ installed
2. **USB Cable** connecting STM32 board to Windows PC
3. **COM Port Driver** - Usually auto-installed, check Device Manager for "STMicroelectronics Virtual COM Port"

## Part 1: Identify the COM Port (Windows)

### Method 1: Device Manager
1. Open **Device Manager** (Win + X → Device Manager)
2. Expand **Ports (COM & LPT)**
3. Look for "STMicroelectronics Virtual COM Port (COMx)"
4. Note the port number (e.g., `COM3`, `COM5`, etc.)

### Method 2: PowerShell
```powershell
Get-WmiObject Win32_SerialPort | Select-Object DeviceID, Description
```

## Part 2: On Linux (Development Machine)

### Build the Project with UART Support

Your current build is minimal. To add GDS communication, you need to:

1. **Create documentation** on connecting components (see below)
2. **Flash the firmware** to the board
3. **Connect from Windows**

## Part 3: Connecting from Windows

### Install F´ GDS on Windows

```powershell
# Create Python virtual environment
python -m venv fprime-venv
.\fprime-venv\Scripts\activate

# Install fprime-gds
pip install fprime-gds fprime-tools
```

### Run GDS with Serial Communication

```powershell
# Replace COM3 with your actual COM port
fprime-gds -n --comm-adapter uart --uart-device COM3 --uart-baud 115200

# Or using full path
fprime-gds -n ^
  --dictionary C:\path\to\LedBlinkerDeploymentTopologyDictionary.xml ^
  --comm-adapter uart ^
  --uart-device COM3 ^
  --uart-baud 115200
```

### GDS Command Line Options

- `--comm-adapter uart` - Use UART communication
- `--uart-device COM3` - Specify COM port
- `--uart-baud 115200` - Baud rate (match STM32 configuration)
- `--dictionary <path>` - Path to topology dictionary (auto-detected if in standard location)
- `-n` - No GUI HTML interface (use command line)
- Without `-n` - Opens web browser interface at http://localhost:5000

## Part 4: Testing Communication

### From GDS Command Line

Once connected:

```python
# Send LED blink command
ledBlinker.BLINKING_ON_OFF(Fw.On.ON)

# Send LED blink command to turn off
ledBlinker.BLINKING_ON_OFF(Fw.On.OFF)
```

### From GDS Web Interface

1. Open browser to `http://localhost:5000`
2. Go to **Commanding** tab
3. Select `ledBlinker.BLINKING_ON_OFF` command
4. Set parameter to `ON` or `OFF`
5. Click **Send**

6. Go to **Events** tab to see event logs
7. Go to **Channels** tab to see telemetry (BLINK_COUNT)

## Part 5: Current Implementation Status

### ⚠️ What's Missing

Your current deployment is **MINIMAL** and lacks GDS communication components:

**Missing Components:**
- ❌ Command Dispatcher (`Svc.CommandDispatcher`)
- ❌ Event Logger (`Svc.ActiveLogger`)
- ❌ Telemetry Channel (`Svc.TlmChan`)
- ❌ Framer/Deframer (`Svc.FprimeFramer`, `Svc.FprimeDeframer`)
- ❌ COM Queue (`Svc.ComQueue`)
- ❌ UART Driver configured for GDS
- ❌ Buffer Manager for communication

### ✅ What You Have

- ✅ LedBlinker component with commands
- ✅ Basic rate group
- ✅ LED GPIO control

## Part 6: Next Steps to Enable GDS

To enable full GDS communication, you need to:

### Option A: Use F´ Communication Subtopology (Recommended)

1. **Import ComFprime subtopology** in your topology:
```fpp
module LedBlinkerDeployment {
  import Svc.ComFprime
  
  # ... your existing instances ...
}
```

2. **Add UART driver instance and connections**

3. **Rebuild and reflash**

### Option B: Add Components Manually

This requires adding approximately 10-15 components and 50+ port connections. See the complete guide below.

## Simplified Quick Start (Testing Without Full GDS)

If you just want to test basic UART communication without full GDS:

### 1. Use a Serial Terminal on Windows

**Tools:**
- PuTTY
- TeraTerm  
- RealTerm
- Arduino Serial Monitor

**Settings:**
- Port: COMx (your port)
- Baud: 115200
- Data bits: 8
- Stop bits: 1
- Parity: None
- Flow control: None

### 2. Send Raw Commands

You can send simple text commands for testing. This requires modifying your code to accept text-based commands instead of framed F´ protocol.

## Troubleshooting

### No COM Port Visible
- Check USB cable (use data cable, not charge-only)
- Install STM32 VCP drivers from ST website
- Try different USB port

### GDS Cannot Connect
- Verify COM port number
- Check if another program is using the port
- Verify baud rate matches (115200)
- Ensure firewall allows Python/GDS

### Board Resets When Connecting
- Normal behavior on first connection
- Wait 2-3 seconds after connection

### No Data Received
- Check UART initialization in code
- Verify TX/RX pins configuration
- Verify framing protocol implementation

## Additional Resources

- [F´ Documentation](https://nasa.github.io/fprime/)
- [F´ GDS Guide](https://nasa.github.io/fprime/latest/user-guide/gds/gds-introduction.html)
- [STM32 VCP Driver](https://www.st.com/en/development-tools/stsw-stm32102.html)

## Summary

**Current State**: Your deployment runs standalone without GDS communication

**To Enable GDS**: 
1. Add communication subtopology (15+ components)
2. Configure UART driver
3. Connect topolog ports (50+ connections)
4. Rebuild and flash
5. Run GDS on Windows

**Estimated Effort**: 2-4 hours to properly integrate communication stack

Would you like me to generate the complete topology with all communication components integrated?
