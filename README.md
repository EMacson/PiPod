
# 🎵 PiPod — Raspberry Pi Pico W MP3 Player

A lightweight embedded MP3 player built on the **Raspberry Pi Pico W** that reads audio files from a microSD card and supports browsing by **songs, artists, genres, and playlists** — without duplicating files.

This project focuses on efficient data handling and low-memory design suitable for microcontrollers.

---

## 🚀 Features

- 🎧 MP3 playback from microSD card (SPI interface)
- 📂 Single-copy file storage (no duplication)
- 🔤 Browse **Songs (sorted by title)**
- 🎤 Browse **Artists (grouped view)**
- 🎼 Browse **Genres (filtered via metadata)**
- 📜 Playlist support using `.m3u` files
- ⚡ Fast startup using prebuilt metadata index
- 🧠 Memory-efficient (no database required)

---

## 🧠 System Architecture

Due to the limited resources of the RP2040 (264KB RAM), this project avoids heavy solutions like SQLite.

Instead, it uses:

- A **flat file system (FAT32)**
- A **metadata index file (`songs.csv`)**
- **Pointer-based indexing in memory**

### Conceptual Model

```
songs[]        -> master list of all songs
byTitle[]      -> sorted view (Songs menu)
byArtist[]     -> grouped view (Artists menu)
byGenre[]      -> filtered view (Genre menu)
playlist[]     -> dynamic list from .m3u files
```

All views reference the same MP3 file paths.

---

## 💾 microSD Card Setup

### Format

```
FAT32
```

### Directory Structure

```
/music/
    song1.mp3
    song2.mp3
    song3.mp3

/index/
    songs.csv

/playlists/
    chill.m3u
    workout.m3u
```

---

## 📄 Metadata Index (`songs.csv`)

To avoid parsing MP3 files on-device, metadata is precomputed.

### Example

```
title,artist,genre,path
Song A,Artist X,Rock,/music/songA.mp3
Song B,Artist Y,Jazz,/music/songB.mp3
```

### Why use this?

- Faster boot time
- Simpler firmware
- Lower CPU usage

---

## 📜 Playlists (M3U)

Playlists are stored as standard `.m3u` files.

### Example

```
/music/song1.mp3
/music/song3.mp3
/music/song7.mp3
```

The player reads file paths and maps them to the internal song list.

---

## 📱 Menu System

```
> Songs
  Artists
  Genre
  Playlists
```

### Behavior

| Menu       | Action                          |
|------------|---------------------------------|
| Songs      | Sort all songs by title         |
| Artists    | Group songs by artist           |
| Genre      | Filter songs by genre           |
| Playlists  | Load `.m3u` file and play list  |

---

## ⚙️ Firmware Overview

### Core Data Structure

```c
typedef struct {
    char title[64];
    char artist[48];
    char genre[32];
    char path[128];
} Song;
```

### Startup Flow

1. Initialize SPI + microSD
2. Mount FAT filesystem
3. Load `songs.csv`
4. Populate `songs[]`
5. Build indexes:
   - Sorted (title)
   - Grouped (artist)
   - Filtered (genre)

---

## 🔄 Sorting & Indexing

To minimize memory usage:

- Use **pointer arrays** instead of copying structs
- Sort using `qsort`
- Build lightweight lookup tables

Example:

```c
Song* byTitle[MAX_SONGS];
```

---

## 🛠️ Hardware Requirements

- Raspberry Pi Pico W
- microSD card module (SPI)
- microSD card (FAT32)
- Audio output:
  - DAC / PWM / I2S  
  - or MP3 decoder (e.g., VS1053)

---

## 🧑‍💻 Build & Flash

### Requirements

- Pico SDK
- CMake
- ARM GCC toolchain

### Build

```bash
mkdir build
cd build
cmake ..
make
```

### Flash

- Hold BOOTSEL on Pico W
- Copy `.uf2` file to device

---

## ⚡ Performance Notes

- Avoid scanning `/music` at runtime for large libraries
- Use `songs.csv` for fast initialization
- Keep metadata structures small to fit RAM constraints

---

## 🧰 Optional: Index Generator

You can generate `songs.csv` using a Python script:

- Scan `/music`
- Extract ID3 tags
- Output CSV

Suggested library:

```python
mutagen
```

---

## 🔮 Future Improvements

- Search functionality
- Album-based navigation
- Shuffle / repeat modes
- Display (OLED/LCD)
- Bluetooth audio
- WiFi sync using Pico W

---

## 📜 License

MIT License

---

## 👤 Author

**Ethan Macson**  
GitHub: https://github.com/EMacson

---

## 💡 Notes

This project demonstrates:

- Embedded systems design
- Efficient data structures under memory constraints
- File system handling on microcontrollers
- Real-time audio pipeline considerations
