EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Modular Half-Bridge"
Date "2021-04-22"
Rev "1.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 607ECAEC
P 4450 3650
F 0 "J1" H 4558 3931 50  0000 C CNN
F 1 "Conn_01x04_Male" H 4558 3840 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4450 3650 50  0001 C CNN
F 3 "~" H 4450 3650 50  0001 C CNN
	1    4450 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NIGBT_GCE Q1
U 1 1 607EDC6D
P 6700 3250
F 0 "Q1" H 6890 3296 50  0000 L CNN
F 1 "Q_NIGBT_GCE" H 6890 3205 50  0001 L CNN
F 2 "Package_TO_SOT_THT:TO-247-3_Horizontal_TabUp" H 6900 3350 50  0001 C CNN
F 3 "~" H 6700 3250 50  0001 C CNN
	1    6700 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NIGBT_GCE Q2
U 1 1 607EE765
P 6700 4050
F 0 "Q2" H 6890 4096 50  0000 L CNN
F 1 "Q_NIGBT_GCE" H 6890 4005 50  0001 L CNN
F 2 "Package_TO_SOT_THT:TO-247-3_Horizontal_TabUp" H 6900 4150 50  0001 C CNN
F 3 "~" H 6700 4050 50  0001 C CNN
	1    6700 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 607F0BF4
P 7400 2850
F 0 "J2" H 7428 2876 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7428 2785 50  0001 L CNN
F 2 "half-bridge-mod:Terminal_Block_Welder_no_hole" H 7400 2850 50  0001 C CNN
F 3 "~" H 7400 2850 50  0001 C CNN
	1    7400 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J3
U 1 1 607F148E
P 7400 3650
F 0 "J3" H 7428 3676 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7428 3585 50  0001 L CNN
F 2 "half-bridge-mod:Terminal_Block_Welder_no_hole" H 7400 3650 50  0001 C CNN
F 3 "~" H 7400 3650 50  0001 C CNN
	1    7400 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J4
U 1 1 607F178F
P 7400 4500
F 0 "J4" H 7428 4526 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7428 4435 50  0001 L CNN
F 2 "half-bridge-mod:Terminal_Block_Welder_no_hole" H 7400 4500 50  0001 C CNN
F 3 "~" H 7400 4500 50  0001 C CNN
	1    7400 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 607F3F15
P 6250 3250
F 0 "R3" V 6043 3250 50  0000 C CNN
F 1 "10" V 6134 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6180 3250 50  0001 C CNN
F 3 "~" H 6250 3250 50  0001 C CNN
	1    6250 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 607F44AC
P 6250 4050
F 0 "R4" V 6043 4050 50  0000 C CNN
F 1 "10" V 6134 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 6180 4050 50  0001 C CNN
F 3 "~" H 6250 4050 50  0001 C CNN
	1    6250 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 607F5579
P 5750 3250
F 0 "R1" V 5543 3250 50  0000 C CNN
F 1 "22" V 5634 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5680 3250 50  0001 C CNN
F 3 "~" H 5750 3250 50  0001 C CNN
	1    5750 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 607F594D
P 5750 4050
F 0 "R2" V 5543 4050 50  0000 C CNN
F 1 "22" V 5634 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5680 4050 50  0001 C CNN
F 3 "~" H 5750 4050 50  0001 C CNN
	1    5750 4050
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 607F5F03
P 5750 3400
F 0 "D1" H 5750 3617 50  0000 C CNN
F 1 "1N4005" H 5750 3526 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 5750 3400 50  0001 C CNN
F 3 "~" H 5750 3400 50  0001 C CNN
	1    5750 3400
	1    0    0    1   
$EndComp
$Comp
L Device:D D2
U 1 1 607F9057
P 5750 4200
F 0 "D2" H 5750 4417 50  0000 C CNN
F 1 "1N4005" H 5750 4326 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 5750 4200 50  0001 C CNN
F 3 "~" H 5750 4200 50  0001 C CNN
	1    5750 4200
	1    0    0    1   
$EndComp
Wire Wire Line
	6500 3250 6450 3250
Wire Wire Line
	4650 3550 4900 3550
Wire Wire Line
	5300 3550 5300 3250
Wire Wire Line
	5300 3250 5500 3250
Wire Wire Line
	5600 3400 5500 3400
Wire Wire Line
	5500 3400 5500 3250
Connection ~ 5500 3250
Wire Wire Line
	5500 3250 5600 3250
Wire Wire Line
	5900 3250 6000 3250
Wire Wire Line
	6000 3400 6000 3250
Wire Wire Line
	5900 3400 6000 3400
Connection ~ 6000 3250
Wire Wire Line
	6000 3250 6100 3250
Wire Wire Line
	6400 4050 6450 4050
Wire Wire Line
	6100 4050 6000 4050
Wire Wire Line
	5900 4200 6000 4200
Wire Wire Line
	6000 4200 6000 4050
Connection ~ 6000 4050
Wire Wire Line
	6000 4050 5900 4050
Wire Wire Line
	5600 4200 5500 4200
Wire Wire Line
	5500 4200 5500 4050
Wire Wire Line
	5500 4050 5600 4050
Wire Wire Line
	5500 4050 5300 4050
Wire Wire Line
	5300 4050 5300 3750
Wire Wire Line
	5300 3750 5100 3750
Connection ~ 5500 4050
Wire Wire Line
	7200 4500 6800 4500
Wire Wire Line
	5200 4500 5200 3850
Wire Wire Line
	5200 3850 4650 3850
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 6081E3D8
P 4450 4300
F 0 "J5" H 4558 4581 50  0000 C CNN
F 1 "Conn_01x04_Male" H 4558 4490 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4450 4300 50  0001 C CNN
F 3 "~" H 4450 4300 50  0001 C CNN
	1    4450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 4500 5200 4500
Connection ~ 5200 4500
Wire Wire Line
	4650 4400 5100 4400
Wire Wire Line
	5100 4400 5100 3750
Connection ~ 5100 3750
Wire Wire Line
	5100 3750 4650 3750
Wire Wire Line
	4650 4300 5000 4300
Wire Wire Line
	5000 4300 5000 3650
Connection ~ 5000 3650
Wire Wire Line
	5000 3650 4650 3650
Wire Wire Line
	4650 4200 4900 4200
Wire Wire Line
	4900 4200 4900 3550
Connection ~ 4900 3550
Wire Wire Line
	4900 3550 5300 3550
$Comp
L Device:C C1
U 1 1 6082B4D3
P 6450 3450
F 0 "C1" H 6565 3496 50  0000 L CNN
F 1 "1n" H 6565 3405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6488 3300 50  0001 C CNN
F 3 "~" H 6450 3450 50  0001 C CNN
	1    6450 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6082B954
P 6450 4300
F 0 "C2" H 6565 4346 50  0000 L CNN
F 1 "1n" H 6565 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6488 4150 50  0001 C CNN
F 3 "~" H 6450 4300 50  0001 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4450 6450 4500
Connection ~ 6450 4500
Wire Wire Line
	6450 4500 5200 4500
Wire Wire Line
	6450 4150 6450 4050
Connection ~ 6450 4050
Wire Wire Line
	6450 4050 6500 4050
Wire Wire Line
	6450 3600 6450 3650
Wire Wire Line
	6450 3650 5000 3650
Wire Wire Line
	6450 3300 6450 3250
Connection ~ 6450 3250
Wire Wire Line
	6450 3250 6400 3250
Text Notes 4300 3600 0    50   ~ 0
G1
Text Notes 4300 3700 0    50   ~ 0
E1
Text Notes 4300 3800 0    50   ~ 0
G2
Text Notes 4300 3900 0    50   ~ 0
E2
Wire Wire Line
	6800 3050 6800 2850
Wire Wire Line
	6800 2850 7200 2850
Wire Wire Line
	6800 4250 6800 4500
Connection ~ 6800 4500
Wire Wire Line
	6800 4500 6450 4500
Connection ~ 6450 3650
Wire Wire Line
	7200 3650 6800 3650
Wire Wire Line
	6800 3850 6800 3650
Connection ~ 6800 3650
Wire Wire Line
	6800 3650 6450 3650
Wire Wire Line
	6800 3650 6800 3450
Text Label 6900 2850 0    50   ~ 0
C1
Text Label 6900 3650 0    50   ~ 0
E1C2
Text Label 6900 4500 0    50   ~ 0
E2
$Comp
L Mechanical:MountingHole H1
U 1 1 608177F3
P 1200 6450
F 0 "H1" H 1300 6496 50  0000 L CNN
F 1 "MountingHole" H 1300 6405 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1200 6450 50  0001 C CNN
F 3 "~" H 1200 6450 50  0001 C CNN
	1    1200 6450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60817FDB
P 1200 6650
F 0 "H2" H 1300 6696 50  0000 L CNN
F 1 "MountingHole" H 1300 6605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1200 6650 50  0001 C CNN
F 3 "~" H 1200 6650 50  0001 C CNN
	1    1200 6650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 60818381
P 1200 6850
F 0 "H3" H 1300 6896 50  0000 L CNN
F 1 "MountingHole" H 1300 6805 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1200 6850 50  0001 C CNN
F 3 "~" H 1200 6850 50  0001 C CNN
	1    1200 6850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 60822F0E
P 1200 7050
F 0 "H4" H 1300 7096 50  0000 L CNN
F 1 "MountingHole" H 1300 7005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1200 7050 50  0001 C CNN
F 3 "~" H 1200 7050 50  0001 C CNN
	1    1200 7050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
