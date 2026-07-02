# Collab Connect — DSA GUI Project

Collab Connect is a desktop application for managing influencer-brand collaborations. It is developed in **C++** using **Qt Widgets**, **CMake**, and core **Data Structures and Algorithms**.

The system allows brands to search influencers, create campaigns, add campaign tasks, and send collaboration requests. Influencers can sign in, view offers, accept or reject requests, track assigned tasks, and view activity updates.

---

## Features

### Brand Side
- Brand login
- Search influencers by niche and minimum follower count
- Create campaigns with budget and selected influencer
- Add campaign tasks
- View campaign history
- Manage influencer records
- Send collaboration requests

### Influencer Side
- Influencer login
- View incoming collaboration offers
- Accept or reject requests
- View assigned campaign tasks
- Mark tasks as complete
- View activity and notification updates

---

## Data Structures Used

| Data Structure | Module | Purpose |
|---|---|---|
| Binary Search Tree (BST) | `InfluencerTree` | Stores influencers ordered by follower count and supports searches |
| Singly Linked List | `CampaignTasks` | Stores tasks for each campaign |
| Queue (FIFO) | `RequestQueue` | Manages pending collaboration requests |
| Stack (LIFO) | `NotificationStack` | Manages recent notifications |
| Vector | `CampaignManager` | Stores and manages campaign records |

---

## Project Structure

```text
Collab-Connect-DSA/
│
├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
│
├── StartPage.cpp
├── StartPage.h
├── BrandLoginPage.cpp
├── BrandLoginPage.h
├── BrandDashboard.cpp
├── BrandDashboard.h
├── InfluencerLoginPage.cpp
├── InfluencerLoginPage.h
├── InfluencerDashboard.cpp
├── InfluencerDashboard.h
│
├── include/
│   ├── CampaignManager.h
│   ├── CampaignTasks.h
│   ├── InfluencerTree.h
│   ├── NotificationStack.h
│   ├── RequestQueue.h
│   └── SystemManager.h
│
├── src/
│   ├── CampaignManager.cpp
│   ├── CampaignTasks.cpp
│   ├── InfluencerTree.cpp
│   ├── NotificationStack.cpp
│   ├── RequestQueue.cpp
│   └── SystemManager.cpp
│
├── data/
│   ├── brands.txt
│   ├── campaigns.txt
│   ├── influencers.txt
│   ├── notifications.txt
│   ├── requests.txt
│   └── tasks.txt
│
└── assets/
    └── screenshots/
```

---

## Technologies Used

- C++17
- Qt Widgets
- CMake
- Object-Oriented Programming
- File Handling with `QFile` and `QTextStream`

---

## Requirements

Install the following before running the project:

- Qt 6 or Qt 5 with the **Widgets** module
- CMake 3.16 or later
- A C++17 compatible compiler
- Qt Creator, Visual Studio, or another C++ IDE

---

## Setup and Run

### Option 1: Using Qt Creator

1. Open **Qt Creator**.
2. Click **File → Open File or Project**.
3. Select the project's `CMakeLists.txt`.
4. Choose a suitable Desktop Qt kit.
5. Build the project.
6. Run the application.

### Option 2: Using CMake

From the project root folder, run:

```bash
cmake -S . -B build
cmake --build build
```

Then run the generated executable from the `build` folder.

---

## Important: Data File Paths

The project should use **relative paths** for all data files, for example:

```cpp
QFile file("data/influencers.txt");
```

Do not use a personal absolute path such as:

```cpp
QFile file("C:/project/DSA_GUI/data/influencers.txt");
```

Relative paths allow anyone who downloads this GitHub repository to run the project without changing your personal computer path.

---

## Demo Data and Login Details

The `data/` folder contains sample academic project data.

- Brand login credentials are stored in `data/brands.txt`.
- Influencer login credentials are stored in `data/influencers.txt`.
- These credentials are for demonstration only and must not be used for a real production system.

`requests.txt` may remain empty. It is filled automatically after a brand sends a collaboration request.

---

## Screenshots

Add project screenshots inside:

```text
assets/screenshots/
```

Suggested screenshots:

- Start page
- Brand login page
- Brand dashboard
- Campaign creation page
- Influencer login page
- Influencer dashboard

---

## Learning Outcomes

This project demonstrates:

- Practical use of BSTs, linked lists, queues, and stacks
- GUI development using Qt Widgets
- C++ object-oriented programming
- CMake project configuration
- Text-file based data persistence
- Integration of frontend GUI screens with backend DSA logic

---

## Authors

- Shahbaz Abrar


---

## License

Created for academic and educational purposes.
