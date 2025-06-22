# Voting System with Fraud Detection

A command-line voting system implemented in C++ that demonstrates fundamental Data Structures and Algorithms (DSA) concepts without relying on external libraries or frameworks.

## Overview

This project implements a secure voting system with basic fraud detection mechanisms using only core DSA concepts:
- Hash sets and maps for efficient lookups
- Arrays and vectors for data storage
- Sorting algorithms for result display
- Simple validation algorithms

## Features

### 1. Secure Vote Entry
- Single vote per unique user ID
- Input validation for voter IDs and candidate names
- O(1) time complexity for vote verification

### 2. Admin Statistics Panel
- Real-time vote counting and percentage calculation
- Leading candidate identification
- Sorted results display

### 3. Result Visualization
- ASCII-based bar chart visualization
- Percentage-based representation
- Clear tabular output formatting

### 4. Fraud Detection
- Duplicate vote attempt detection
- Invalid entry logging
- Comprehensive fraud reporting

## Files Included

- voting_system.cpp - Main implementation of the voting system
- dummy_outcome_generator.cpp - Automated test script that generates sample data
- README.md - This documentation file

## Requirements

- C++11 compatible compiler
- Standard C++ libraries only (no external dependencies)

## Compilation

bash
# Compile the main voting system
g++ -std=c++11 voting_system.cpp -o voting_system

# Compile the test generator (optional)
g++ -std=c++11 dummy_outcome_generator.cpp -o test_voting_system


## Usage

### Running the Main Voting System

bash
./voting_system


This will present you with a menu-driven interface:


===== VOTING SYSTEM MENU =====
1. Cast Vote
2. Add Candidate
3. View Statistics
4. View Fraud Logs
5. Reset System
6. Exit


### Running the Automated Test Script

bash
./test_voting_system


This will automatically generate test data, simulate voting, attempt fraud, and display results without requiring user input.

## Data Structures Used

1. **unordered_set<string>**: For tracking voter IDs that have already voted (O(1) lookup)
2. **unordered_map<string, int>**: For tracking vote counts for each candidate (O(1) lookup/update)
3. **vector<FraudLog>**: For storing fraud attempt logs
4. *Custom sorting comparator*: For displaying results in descending order of votes

## Design Choices

### Why Use Hash-Based Data Structures?
- O(1) average time complexity for lookups and updates
- Efficient detection of duplicate voter IDs
- Fast vote counting and retrieval

### Visualization Approach
- ASCII bar charts using '#' characters for simplicity and portability
- Each '#' represents 5% of total votes
- Sorted display for ease of interpretation

### Fraud Detection Logic
- Immediate detection of duplicate vote attempts during vote casting
- Comprehensive logging with timestamps
- Administrative interface for monitoring fraud attempts

## Example Output

### Vote Statistics

===== VOTING STATISTICS =====
Total votes cast: 20

Candidate Results:
CANDIDATE      VOTES     PERCENT   VISUALIZATION
------------------------------------------------------------
Alice Johnson  6         30.00     ######
Bob Smith      5         25.00     #####
Charlie Brown  4         20.00     ####
Diana Prince   3         15.00     ###
Candidate1     2         10.00     ##
Candidate2     0         0.00      
Candidate3     0         0.00      

Leading candidate: Alice Johnson with 6 votes (30.00%)


### Fraud Logs

===== FRAUD DETECTION LOGS =====
VOTER ID   TIMESTAMP                DETAILS
------------------------------------------------------------
voter1001  2023-05-15 14:23:45      Attempted duplicate vote for Bob Smith
voter1002  2023-05-15 14:23:46      Attempted duplicate vote for Alice Johnson
voter1003  2023-05-15 14:23:46      Attempted duplicate vote for Charlie Brown


## Time Complexity Analysis

- *Vote Casting*: O(1) average case
- *Fraud Detection*: O(1) average case
- *Statistics Calculation*: O(n) where n is the number of candidates
- *Result Sorting*: O(n log n) where n is the number of candidates

## Space Complexity Analysis

O(V + C + F) where:
- V = number of voters
- C = number of candidates
- F = number of fraud attempts

## Future Enhancements

While maintaining the constraint of using only basic DSA:

1. *Simple Encryption*: Add basic encryption for voter IDs
2. *Time-based Voting Windows*: Implement voting periods using queue structures
3. *Pattern Detection*: Add advanced fraud pattern detection using frequency analysis
4. *Export/Import*: Add functionality to export/import voting data

## Author

Madhav Mahajan

## License

This project is for educational purposes only.
