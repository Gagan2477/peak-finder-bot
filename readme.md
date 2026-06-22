# Peak Finder Optimization Bot

A C++ terminal-based algorithmic assistant built to solve constraint-based height optimization problems using Binary Search. 

## The Problem
Given an array of integer terrain heights and a maximum constraint of "operations" (adding +1 to a height), what is the absolute highest minimum peak we can achieve? This bot rapidly calculates the optimal uniform height without exceeding the allocated constraint.

## Technical Highlights
* **Language:** C++
* **Core Algorithm:** Binary Search on Answer
* **Time Complexity:** $O(N \log M)$ where $N$ is the size of the terrain array and $M$ is the maximum possible height. 
* **Space Complexity:** $O(N)$ to store the terrain vectors dynamically.
* **Features:** Continuous interactive state loop, input sanitization, and custom terminal UI.

## How to Run

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/YourUsername/peak-finder-bot.git