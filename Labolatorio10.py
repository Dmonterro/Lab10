import tkinter as tk
import serial

# Configuración del puerto serial
try:
    ser = serial.Serial('COM3', 9600, timeout=1)  # Cambiar 'COM3' por el puerto correcto de tu Arduino
except serial.SerialException as e:
    print("Error al abrir el puerto serial:", e)
    exit()

def move_right():
    ser.write(b'D')

def move_left():
    ser.write(b'I')

def set_speed():
    try:
        new_speed = int(speed_entry.get())
        if 0 <= new_speed <= 100:
            ser.write(b'V')
            ser.write(f"{new_speed}".encode())
        else:
            print("La velocidad debe estar en el rango de 0 a 100.")
    except ValueError:
        print("Ingrese un valor numérico para la velocidad.")

def set_angle():
    try:
        new_angle = int(angle_entry.get())
        if 0 <= new_angle <= 180:
            ser.write(b'G')
            ser.write(f"{new_angle}".encode())
        else:
            print("El ángulo debe estar en el rango de 0 a 180.")
    except ValueError:
        print("Ingrese un valor numérico para el ángulo.")

# Configuración de la ventana principal
root = tk.Tk()
root.title("Control de Servo")

# Botones para mover a la derecha e izquierda
right_button = tk.Button(root, text="Derecha", command=move_right)
right_button.pack()

left_button = tk.Button(root, text="Izquierda", command=move_left)
left_button.pack()

# Campo de entrada y botón para la velocidad
speed_label = tk.Label(root, text="Velocidad (0-100):")
speed_label.pack()
speed_entry = tk.Entry(root)
speed_entry.pack()
speed_button = tk.Button(root, text="Establecer Velocidad", command=set_speed)
speed_button.pack()

# Campo de entrada y botón para el ángulo
angle_label = tk.Label(root, text="Ángulo (0-180):")
angle_label.pack()
angle_entry = tk.Entry(root)
angle_entry.pack()
angle_button = tk.Button(root, text="Establecer Ángulo", command=set_angle)
angle_button.pack()

root.mainloop()

# Cerrar el puerto serial al salir
ser.close()
