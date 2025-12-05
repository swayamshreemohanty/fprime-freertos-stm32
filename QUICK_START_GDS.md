# Quick Start: Connect STM32 Board to F´ GDS on Windows

## Current Status

Your STM32 board currently runs **standalone** without Ground Data System (GDS) communication. 

- ✅ LED blinks on the board
- ❌ Cannot control from computer
- ❌ Cannot see telemetry/events

## What You Need to Add GDS Support

### Short Answer
To control your board from Windows GDS, you need to:
1. Add ~15 communication components to your topology
2. Implement UART communication driver
3. Connect all the components (~50 port connections)
4. Flash updated firmware
5. Run `fprime-gds` on Windows with COM port

**Time Required**: 3-4 hours for someone familiar with F´

## Option 1: Simple Serial Test (10 minutes)

Test basic USB communication without full GDS:

### On Windows:
1. **Find COM Port**:
   - Open Device Manager
   - Look under "Ports (COM & LPT)"
   - Find "STMicroelectronics Virtual COM Port (COMx)"
   - Note the number (e.g., COM3)

2. **Use Serial Terminal**:
   - Download [PuTTY](https://www.putty.org/)
   - Settings:
     - Connection type: Serial
     - Serial line: COM3 (your port)
     - Speed: 115200
   - Click "Open"

3. **What to expect**:
   - Currently: Nothing (UART not implemented)
   - After adding code: You'll see debug messages

## Option 2: Full GDS Integration (Required Steps)

### Step 1: Check Current Setup

Your `/HeaterBoard/LedBlinkerDeployment/Top/` currently has:
- ✅ `ledBlinker` - Your LED component
- ✅ `rateGroup1` - Timing
- ❌ **Missing**: Command dispatcher, event logger, telemetry, framer, deframer, UART driver

### Step 2: What Needs to be Added

**Communication Components Needed:**
```
1. Svc.CommandDispatcher  - Routes commands to components
2. Svc.ActiveLogger       - Logs events
3. Svc.TlmChan           - Sends telemetry
4. Svc.FprimeFramer      - Frames outgoing data
5. Svc.FprimeDeframer    - Deframes incoming data
6. Svc.ComQueue          - Queues outgoing data
7. Svc.BufferManager     - Manages buffers
8. Drv.ByteStreamDriverModel - Driver wrapper
9. STM32UartDriver       - Hardware UART (created for you)
... plus 5-6 more support components
```

### Step 3: UART Pins on Your Board

According to your `.ioc` file:
- **USART1**: PA9 (TX), PB15 (RX) - Connected to ST-LINK VCP (USB)
- **USART3**: PD8 (TX), PD9 (RX) - Available on connectors

**Use USART1** - It's already connected to USB!

## Simplified Approach: Copy Reference Topology

The easiest way is to copy from an F´ reference deployment:

```bash
# On your Linux development machine
cd /path/to/my-fprime-project

# Copy reference topology from fprime
cp -r lib/fprime/Ref/Top/RefTopologyDefs.fpp HeaterBoard/LedBlinkerDeployment/Top/
cp -r lib/fprime/Ref/Top/topology.fpp HeaterBoard/LedBlinkerDeployment/Top/

# Then modify to keep only needed components
```

## What I've Created for You

I've already created:
1. ✅ `STM32UartDriver` - UART hardware driver
2. ✅ `GDS_SETUP_GUIDE.md` - Complete documentation
3. ❌ Full topology (would require major changes)

## Recommendation

**For Learning & Quick Testing:**
1. Start with simple serial terminal test
2. Add printf debugging via UART
3. Gradually add GDS components

**For Production:**
1. Use F´ reference topology as template
2. Add your custom components (LedBlinker)
3. Full GDS integration

## Quick Command Reference

### On Windows (After Full Setup):

```powershell
# Activate Python environment
.\fprime-venv\Scripts\activate

# Run GDS
fprime-gds --comm-adapter uart --uart-device COM3 --uart-baud 115200

# Open browser
# Go to http://localhost:5000

# Send command to LED
# Commanding tab → ledBlinker.BLINKING_ON_OFF → ON/OFF
```

## Do You Want Me To...?

1. **Generate complete topology with all GDS components** (large change, 200+ lines)
2. **Create simple printf debug setup** (small change, easier to test)
3. **Provide step-by-step component addition guide** (medium effort)

Let me know which approach you prefer!
