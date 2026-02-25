import serial
from pynput import keyboard

# ================== CONFIG ==================
SERIAL_PORT = "COM5"     # Windows: COM5 | Linux/macOS: /dev/ttyUSB0 or /dev/tty.HC-05-DevB
BAUD_RATE = 9600
# ============================================

# Key → command mapping
KEY_MAP = {
    'w': 'F',
    's': 'B',
    'a': 'L',
    'd': 'R',
    'e': 'E',
    'q'; 'e'
}

STOP_COMMAND = 'S'

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
print(f"Connected to {SERIAL_PORT}")

pressed_keys = set()

def send(cmd):
    ser.write(cmd.encode())
    print(f"Sent: {cmd}")

def on_press(key):
    try:
        k = key.char.lower()
        if k in KEY_MAP and k not in pressed_keys:
            pressed_keys.add(k)
            send(KEY_MAP[k])
    except AttributeError:
        pass

def on_release(key):
    try:
        k = key.char.lower()
        if k in pressed_keys:
            pressed_keys.remove(k)
            send(STOP_COMMAND)
    except AttributeError:
        pass

    # ESC to quit safely
    if key == keyboard.Key.esc:
        send(STOP_COMMAND)
        ser.close()
        return False

print("WASD to drive | ESC to quit")

with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
