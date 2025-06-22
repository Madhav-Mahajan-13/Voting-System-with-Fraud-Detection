
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <ctime>

// Ensure compatibility with C++11
#if __cplusplus < 201103L
#error This code requires C++11 support. Please compile with -std=c++11 or newer.
#endif

class VotingSystem {
private:
    // Data structure to store candidates and votes
    std::unordered_map<std::string, int> voteCounts;
    
    // Data structure to track who has already voted
    std::unordered_set<std::string> voterRegistry;
    
    // Data structure to log fraud attempts
    struct FraudLog {
        std::string voterID;
        std::string timestamp;
        std::string attemptDetails;
    };
    std::vector<FraudLog> fraudLogs;
    
    // Function to get current timestamp
    std::string getCurrentTimestamp() {
        // Use C-style time functions instead of chrono for better compatibility
        std::time_t currentTime = std::time(nullptr);
        
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
        return std::string(buffer);
    }
    
    // Function to validate voter ID (simple version)
    bool isValidVoterID(const std::string& voterID) {
        // Check if ID is not empty and has at least 5 characters
        return !voterID.empty() && voterID.length() >= 5;
    }
    
    // Function to validate candidate name
    bool isValidCandidate(const std::string& candidate) {
        // Check if the candidate exists in our voting system
        return voteCounts.find(candidate) != voteCounts.end();
    }

public:
    // Constructor
    VotingSystem() {
        // Initialize with some candidates
        addCandidate("Candidate1");
        addCandidate("Candidate2");
        addCandidate("Candidate3");
    }
    
    // Function to add a candidate
    void addCandidate(const std::string& name) {
        if (voteCounts.find(name) == voteCounts.end()) {
            voteCounts[name] = 0;
            std::cout << "Candidate " << name << " added successfully." << std::endl;
        } else {
            std::cout << "Candidate " << name << " already exists." << std::endl;
        }
    }
    
    // Function to cast a vote
    bool castVote(const std::string& voterID, const std::string& candidate) {
        // Validate voter ID
        if (!isValidVoterID(voterID)) {
            std::cout << "Invalid voter ID format." << std::endl;
            return false;
        }
        
        // Check if voter has already voted
        if (voterRegistry.find(voterID) != voterRegistry.end()) {
            // Log fraud attempt
            FraudLog log = {
                voterID,
                getCurrentTimestamp(),
                "Attempted duplicate vote for " + candidate
            };
            fraudLogs.push_back(log);
            
            std::cout << "Fraud detected: Voter " << voterID << " has already voted." << std::endl;
            return false;
        }
        
        // Validate candidate
        if (!isValidCandidate(candidate)) {
            std::cout << "Invalid candidate name." << std::endl;
            return false;
        }
        
        // Register the vote
        voterRegistry.insert(voterID);
        voteCounts[candidate]++;
        
        std::cout << "Vote for " << candidate << " registered successfully." << std::endl;
        return true;
    }
    
    // Function to display voting statistics
    void displayStats() {
        int totalVotes = 0;
        std::string leadingCandidate;
        int maxVotes = 0;
        
        // Calculate total votes and find leading candidate
        for (const auto& pair : voteCounts) {
            totalVotes += pair.second;
            if (pair.second > maxVotes) {
                maxVotes = pair.second;
                leadingCandidate = pair.first;
            }
        }
        
        // Display header
        std::cout << "\n===== VOTING STATISTICS =====" << std::endl;
        std::cout << "Total votes cast: " << totalVotes << std::endl;
        
        // Prevent division by zero
        if (totalVotes > 0) {
            std::cout << "\nCandidate Results:" << std::endl;
            std::cout << std::left << std::setw(15) << "CANDIDATE" << std::setw(10) << "VOTES" 
                      << std::setw(10) << "PERCENT" << "VISUALIZATION" << std::endl;
            std::cout << std::string(60, '-') << std::endl;
            
            // Copy vote data to a vector for sorting
            std::vector<std::pair<std::string, int>> sortedResults;
            for (const auto& pair : voteCounts) {
                sortedResults.push_back(pair);
            }
            
            // Sort candidates by vote count (descending)
            // Using a named comparison function instead of a lambda for better compatibility
            struct CompareVotes {
                bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
                    return a.second > b.second;
                }
            };
            std::sort(sortedResults.begin(), sortedResults.end(), CompareVotes());
            
            // Display results
            for (const auto& result : sortedResults) {
                double percentage = (static_cast<double>(result.second) / totalVotes) * 100;
                int barLength = static_cast<int>(percentage / 5);  // Each '#' represents 5%
                
                std::cout << std::left << std::setw(15) << result.first 
                          << std::setw(10) << result.second
                          << std::fixed << std::setprecision(2) << std::setw(10) << percentage
                          << std::string(barLength, '#') << std::endl;
            }
            
            std::cout << "\nLeading candidate: " << leadingCandidate << " with " 
                      << maxVotes << " votes (" 
                      << std::fixed << std::setprecision(2) 
                      << (static_cast<double>(maxVotes) / totalVotes) * 100 << "%)" << std::endl;
        } else {
            std::cout << "No votes have been cast yet." << std::endl;
        }
    }
    
    // Function to display fraud attempts
    void displayFraudLogs() {
        std::cout << "\n===== FRAUD DETECTION LOGS =====" << std::endl;
        
        if (fraudLogs.empty()) {
            std::cout << "No fraud attempts detected." << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(10) << "VOTER ID" 
                  << std::setw(25) << "TIMESTAMP" 
                  << "DETAILS" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (const auto& log : fraudLogs) {
            std::cout << std::left << std::setw(10) << log.voterID 
                      << std::setw(25) << log.timestamp 
                      << log.attemptDetails << std::endl;
        }
    }
    
    // Function to reset the entire voting system
    void resetSystem() {
        voteCounts.clear();
        voterRegistry.clear();
        fraudLogs.clear();
        
        // Reinitialize with default candidates
        addCandidate("Candidate1");
        addCandidate("Candidate2");
        addCandidate("Candidate3");
        
        std::cout << "Voting system reset successfully." << std::endl;
    }
};

// Main function to demonstrate the voting system
int main() {
    VotingSystem votingSystem;
    std::string voterID, candidate;
    int choice;
    
    while (true) {
        std::cout << "\n===== VOTING SYSTEM MENU =====" << std::endl;
        std::cout << "1. Cast Vote" << std::endl;
        std::cout << "2. Add Candidate" << std::endl;
        std::cout << "3. View Statistics" << std::endl;
        std::cout << "4. View Fraud Logs" << std::endl;
        std::cout << "5. Reset System" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                std::cout << "Enter your Voter ID: ";
                std::cin >> voterID;
                std::cout << "Enter candidate name: ";
                std::cin >> candidate;
                votingSystem.castVote(voterID, candidate);
                break;
                
            case 2:
                std::cout << "Enter new candidate name: ";
                std::cin >> candidate;
                votingSystem.addCandidate(candidate);
                break;
                
            case 3:
                votingSystem.displayStats();
                break;
                
            case 4:
                votingSystem.displayFraudLogs();
                break;
                
            case 5:
                votingSystem.resetSystem();
                break;
                
            case 6:
                std::cout << "Thank you for using the Voting System." << std::endl;
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}
