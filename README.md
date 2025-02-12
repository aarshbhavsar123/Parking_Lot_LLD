# Parking Lot Management System

## Overview
The **Parking Lot Management System** is a **Low-Level Design (LLD) project** implemented in **C++**. It simulates the operations of a real-world parking lot, including vehicle parking, retrieval, and slot availability tracking.

## Features
- **Object-Oriented Design (OOD)** with encapsulated classes (`ParkingLot`, `Vehicle`, `Slot`, `Floor`, `Ticket`).
- **Efficient Data Structures** (`vector`, `map`, `set`) to manage parking slots dynamically.
- **Vehicle Parking & Unparking** with unique ticket ID generation.
- **Slot Availability Tracking** for different vehicle types (`Car`, `Bike`, `Truck`).
- **Real-time Slot Occupancy Display**.
- **Command-line Interface** to interact with the system.

## Technologies Used
- **Language**: C++
- **STL Containers**: `vector`, `map`, `set`
- **OOP Concepts**: Encapsulation, Abstraction, Inheritance

## Installation & Usage
### Prerequisites
Ensure you have a C++ compiler installed (e.g., `gcc`).

### Steps to Run
1. Clone the repository:
   ```sh
   git clone https://github.com/aarshbhavsar123/Parking_Lot_LLD.git
   cd Parking_Lot_LLD
   ```
2. Compile the code:
   ```sh
   gcc Parking_Lot_LLD.cpp -o Parking_Lot_LLD
   ```
3. Run the program:
   ```sh
   ./Parking_Lot_LLD
   ```

## Example Commands & Output
```sh
Created a Parking lot with 2 floors and 6 slots per floor
No of free slots for the vehicle type Car at floor 0 is 3
No of free slots for the vehicle type Bike at floor 0 is 2
No of free slots for the vehicle type Truck at floor 0 is 1
Vehicle parked with ticket ID: PR1234_1_4
```

## Project Structure
```
Parking_Lot_LLD/
│── Parking_Lot_LLD.cpp  # Main source code
│── README.md        # Documentation
```

## Future Improvements
- Extend to **multi-level parking** with dynamic slot allocation.
- Implement **database storage** for persistent data.
- Develop a **Graphical User Interface (GUI)**.


---
**Author**: Aarsh Bhavsar

