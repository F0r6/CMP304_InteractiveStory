#include <iostream>
#include <string>
#include <vector>
#include <map>

// Class representing a Decision Node in the story
class DecisionNode {
public:
    std::string storyText; // The narrative text or the event in the story
    std::map<int, std::pair<std::string, DecisionNode*>> choices; // Available choices for the player

    // Constructor for initializing a node with story text
    DecisionNode(const std::string& text) : storyText(text) {}

    // Function to add a choice to the node, along with the next node for that choice
    void addChoice(int choiceNumber, const std::string& choiceText, DecisionNode* nextNode) 
    {
        choices[choiceNumber] = { choiceText, nextNode };
    }

    // Function to display the current story and choices to the player
    void displayNode() const 
    {
        std::cout << storyText << std::endl;
        for (const auto& choice : choices) 
        {
            std::cout << choice.first << ". " << choice.second.first << std::endl;
        }
    }

    // Function to get the next node based on player's choice
    DecisionNode* getNextNode(int choice) 
    {
        if (choices.find(choice) != choices.end()) 
        {
            return choices[choice].second;
        }
        return nullptr; // Invalid choice
    }
};


