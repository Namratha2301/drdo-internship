# Real-Time Target Detection

## Abstract

Drones, or Unmanned Aerial Vehicles (UAVs), have become essential for defense applications like surveillance, mapping, and real-time target tracking. This project uses drones to identify, track, and geolocate both moving and stationary objects. Our software was developed using Qt in C++ to manage the drone's coordinates, available missiles, and target tracking within missile range, enhancing administrative control and response efficiency.

## 1. Introduction

The Defense Research and Development Organization (DRDO), under India’s Ministry of Defence, develops advanced defense technologies to meet the needs of India’s armed forces. This project aligns with DRDO’s mission by creating a real-time drone-based tracking system capable of identifying, tracking, and geolocating objects.

## 2. Software Development Life Cycle (SDLC)

We followed the Iterative Model for SDLC. Each version was completed in set timeframes and included:

1. Requirement Gathering & Analysis
2. Design
3. Implementation
4. Testing
5. Deployment
6. Review
7. Maintenance

## 3. Requirements Gathering

### Functional Requirements

- Input of a file path to read data and display its contents.
- Warnings if targets are outside a defined range, with display of target ID and coordinates.
- Graphical representation of target positions and selection of available weapons.
- Options to add new weapons or adjust their positions.

### Non-Functional Requirements

The application should be secure, reliable, and user-friendly.

## 4. System Analysis and Design

### Platform

Developed primarily on the Qt framework in C++ for its portability and cross-platform capabilities.

### Design Components

1. Input Text Box for file path.
2. Button to read and display file data.
3. Graphical display for range and warning messages.
4. UI dropdown to select weapons, integrated with a SQL database for weapon management.

## 5. Implementation and Coding

### Main Features

- **File Reading and Processing:** Reads input coordinates and displays the data on a plot with warning messages for targets outside the weapon's radar.
- **Graphical Plotting:** Using x and y coordinates, a scatter plot visually displays targets within or beyond weapon range.
- **Weapon Selection and Modification:** The dropdown allows selection of weapons with adjustable parameters like range and position, updating the plot in real time.

## 6. Testing and Deployment

Each feature was tested iteratively, ensuring functionality like file reading, target plotting, and weapon modification were accurate. SQL Server Management Studio (SSMS) was used for database management, with options to add, edit, and delete weapon data.

## 7. Conclusion

This project provided a practical understanding of end-to-end software development in Qt, specifically for real-time UAV target tracking. Through this experience, we gained insights into time management, self-motivation, and new technical skills.

## Acknowledgment

We extend our gratitude to Bidisha Ma’am and Urvashi Ma’am for their guidance and mentorship, providing us with this valuable opportunity to work on the Real-Time Target Detection project.
