# DRDO Weapon Tracking Application

<img width="858" alt="drdo1" src="https://github.com/user-attachments/assets/fb4fd01f-8082-4943-abbd-da727bcb62a3">

<img width="847" alt="drdo4" src="https://github.com/user-attachments/assets/4d221945-5a59-4cbc-9879-52467a924e96">

<img width="821" alt="drdo5" src="https://github.com/user-attachments/assets/665c8b04-437b-4bd1-ad83-63acab6e0a61">


A GUI-based application designed with Qt for tracking, analyzing, and visualizing weapon information. This project integrates custom plotting capabilities using `qcustomplot` and includes database connectivity with SQL Server to retrieve and store weapon data.

## Features
- **GUI Interface**: Built using Qt, making it easy to interact with weapon data.
- **Database Integration**: SQL Server for data persistence, including adding, deleting, and updating weapon records.
- **Custom Plots**: Visualization of weapon positions and range using `qcustomplot` library.
- **Concurrency**: Utilizes `QtConcurrent` for efficient handling of multi-threaded tasks, such as plotting and data fetching.

## File Structure
### Header and Source Files
- **mainwindow.h / mainwindow.cpp**: Main application window, handling GUI components, weapon data retrieval, and plotting.
- **dialog.h / dialog.cpp**: Secondary dialog window for custom input, such as weapon position and adding new weapons.
- **main.cpp**: Entry point of the application.

## Installation
### Prerequisites
- Qt framework (5.x or later recommended)
- SQL Server with a database named `DRDO`
- QCustomPlot library

### Steps
1. Clone the repository.
    ```bash
    git clone <repository_url>
    cd DRDO-Weapon-Tracking
    ```
2. Open `DRDO.pro` in Qt Creator.
3. Set up the SQL database with the required tables. A sample schema:
    ```sql
    CREATE TABLE Weapons (
        Weapon_ID INT PRIMARY KEY,
        Range FLOAT,
        Azimuth FLOAT,
        Elevation FLOAT
    );
    ```
4. Run the project in Qt Creator.

## Usage
### GUI Overview
- **Weapon Selection**: Choose a weapon from the dropdown to display its details.
- **Data Input**: Enter X and Y coordinates for weapon positions in the main window.
- **Add Weapon**: Use the dialog window to input new weapon range and elevation.

### Main Functionalities
- **Data Plotting**: Visualize weapon range and trajectory using polar coordinates.
- **Database Operations**: Add, delete, or update weapons in the SQL database.

## Code Details
### MainWindow Class
- **`makePlot()`**: Generates plots for weapon data.
- **`on_pushButton_clicked()`**: Loads data from a specified file.
- **`circleFunction()`**: Generates a circular plot representing weapon range based on azimuth and elevation.
- **`on_Change_Position()`**: Updates weapon position on the plot.

### Dialog Class
- **`on_pushButton_clicked()`**: Sets X and Y positions for weapons.
- **`on_pushButton_2_clicked()`**: Adds a new weapon entry.

## Challenges
- **Learning Curve with Qt**: Understanding Qt’s syntax and functionality required time.
- **qcustomplot Integration**: Certain features of qcustomplot were challenging to interpret across different platforms.
- **Class Complexity**: Qt’s numerous classes with similar functions initially made it challenging to choose the correct functions for specific tasks.

## Requirements
- **Qt**: 5.x or higher
- **QCustomPlot**: Custom plotting library integrated into the project
- **SQL Server**: SQL database for persistent data storage

