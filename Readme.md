# Sistema de Control Industrial para Hornos - ESP32

## 📋 Descripción General

**Sistema de Control para Hornos** es una solución de automatización industrial desarrollada para ESP32, diseñada para el control de temperatura y procesos en **hornos industriales**. El sistema implementa múltiples estrategias de control (PID, ON/OFF, PWM) con interfaz HMI Nextion y capacidades de monitoreo en tiempo real.

## 🎯 Características Principales

### 🔥 Control de Procesos Térmicos
- **Control PID Avanzado**: Regulación precisa de temperatura con anti-windup
- **Control ON/OFF**: Regulación básica con histéresis configurable  
- **Control PWM**: Modulación por ancho de pulso para control suave
- **Rampas de Temperatura**: Perfiles programables de 8 segmentos
- **Sistema de Setpoints**: Temperaturas objetivo configurables

### 🌡️ Sensores y Monitoreo
- **Sensores MAX6675**: Lectura de termopares tipo K
- **Doble Sensor**: Temperatura principal y auxiliar
- **Filtro de Media Móvil**: Estabilización de lecturas analógicas
- **Supervisión Continua**: Verificación de estado de todos los componentes
- **Sistema de Alarmas**: Detección de fallas y condiciones críticas

### ⚙️ Actuadores y Equipos
- **Quemador Industrial**: Control de encendido/apagado y potencia variable
- **Quemador Resistivo**: Soporte para calentamiento eléctrico
- **Motor/Ventilador**: Control de velocidad y confirmación de funcionamiento
- **Válvula de Control**: Regulación de flujo de gas/aire
- **Baliza Luminosa**: Indicación visual de estados del sistema

### 🖥️ Interfaz de Usuario
- **Pantalla Nextion**: HMI táctil para operación y configuración
- **Navegación por Páginas**: Interfaz organizada y intuitiva
- **Sistema de Claves**: Acceso controlado a configuraciones
- **Visualización en Tiempo Real**: Temperaturas, setpoints y estados
- **Control Manual**: Activación/desactivación de equipos

### 🔧 Funciones de Control Avanzadas
- **Temporizadores de Precisión**: Milisegundos y microsegundos
- **Sistema de Confirmaciones**: Verificación de estado de actuadores
- **Gestión de Eventos**: Control de secuencias de proceso
- **Emulación de Planta**: Modo simulación para testing
- **Debug Integrado**: Comunicación serial para diagnóstico

## 🏗️ Arquitectura del Sistema

```
┌─────────────────┐     ┌──────────────────┐     ┌─────────────────┐
│   Pantalla      │───▶│     ESP32         │───▶│   Quemador      │
│   Nextion       │     │   (Control       │     │   Industrial    │
│   (HMI)         │◀───│   Principal)      │◀───│                 │
└─────────────────┘     └──────────────────┘     └─────────────────┘
                               │
                  ┌────────────┼────────────┐
                  ▼            ▼            ▼
        ┌─────────────┐ ┌─────────────┐ ┌─────────────┐
        │ Sensores    │ │   Motor/    │ │   Válvula   │
        │ Temperatura │ │ Ventilador  │ │   Control   │
        │ (MAX6675)   │ │             │ │             │
        └─────────────┘ └─────────────┘ └─────────────┘
```

## 📊 Tipos de Control Implementados

### 1. **Control PID**
```cpp
- Parámetros: Kp=1.0, Ki=0.005, Kd=0.05
- Anti-windup automático
- Filtro de derivativa
- Saturación configurable (-100% a +100%)
```

### 2. **Control ON/OFF**
```cpp
- Histéresis: ±5°C (configurable)
- Activación por umbral
- Protección contra oscilaciones
```

### 3. **Control PWM**
```cpp
- Resolución: 0-100%
- Modulación suave
- Reducción de stress térmico
```

## 📈 Funcionalidades de Proceso

### 🔥 **Gestión de Rampas**
- **8 Segmentos Configurables**: Temperaturas y tiempos programables
- **Ejecución Automática**: Transiciones suaves entre setpoints
- **Monitoreo en Tiempo Real**: Seguimiento de progreso
- **Parada de Emergencia**: Detención segura del proceso

### 🛡️ **Sistema de Seguridad**
- **Termostato de Seguridad**: Protección por sobretemperatura
- **Confirmación de Encendido**: Verificación de equipos activos
- **Detección de Alarmas**: Quemador, ventilador, válvulas
- **Supervisión Continua**: Monitoreo cada 200ms
- **Parada Automática**: En caso de fallas críticas

### 📊 **Logging y Diagnóstico**
- **Comunicación Serial**: Debug a 115200 baud
- **Trazas Configurables**: Diferentes niveles de detalle
- **Estado de Variables**: Temperaturas, setpoints, acciones PID
- **Confirmaciones**: Estado de todos los actuadores

## 🚀 Modos de Operación

### 1. **Modo Manual**
- Control directo desde HMI
- Activación individual de equipos
- Ajuste manual de potencias
- Setpoint fijo configurable

### 2. **Modo Automático (Rampa)**
- Ejecución de perfiles programados
- Control PID automático
- Transiciones temporales
- Supervisión continua

### 3. **Modo Simulación**
- Emulación de planta térmica
- Testing sin hardware real
- Validación de algoritmos
- Desarrollo y depuración

## 📦 Dependencias

- **ESP32 Arduino Core**: Framework base
- **MAX6675 Library**: Lectura de termopares
- **EEPROM**: Almacenamiento persistente
- **Serial Communication**: Debug y HMI

## 🔄 Estado del Proyecto

✅ **Implementado:**
- Control PID con anti-windup
- Interfaz Nextion completa
- Sistema de seguridad
- Rampas de temperatura
- Comunicación serial debug

🚧 **En Desarrollo:**
- Interfaz web adicional
- Logging en SD card
- Conectividad IoT
- Recetas almacenadas