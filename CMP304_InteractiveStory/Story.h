#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include "DecisionNode.h"

class Story {
public:
    std::vector<DecisionNode*> nodes;
    std::stack<DecisionNode*> history;  // History stack to store previous nodes
    DecisionNode* currentNode;

    // Function to initialize nodes
    void initNodes() {
        nodes.push_back(new DecisionNode("\nYou wake up in a strange forest. What will you do?"));
        nodes.push_back(new DecisionNode("\nYou walk through the dense forest and find an abandoned cabin."));
        nodes.push_back(new DecisionNode("\nYou hear a growl from behind a tree and decide to investigate."));
        nodes.push_back(new DecisionNode("\nYou find a peaceful stream and decide to follow it."));
        nodes.push_back(new DecisionNode("\nYou are attacked by a wild bear! Fortunately, you manage to escape."));
        nodes.push_back(new DecisionNode("\nInside the cabin, you find some supplies and a map leading to a treasure."));
        nodes.push_back(new DecisionNode("\nYou find a mysterious key in the cabin's drawer."));
        nodes.push_back(new DecisionNode("\nThe stream leads you to a hidden waterfall with a treasure chest!"));
        nodes.push_back(new DecisionNode("\nYou eventually find a village after following the stream for hours."));
        nodes.push_back(new DecisionNode("\nYou are lost and confused. Perhaps you should turn back."));

        // Define choices between nodes
        nodes[0]->addChoice(1, "Walk through the forest", nodes[1]);
        nodes[0]->addChoice(2, "Investigate the growl", nodes[2]);
        nodes[0]->addChoice(3, "Follow the stream", nodes[3]);

        nodes[1]->addChoice(1, "Enter the cabin", nodes[5]);
        nodes[1]->addChoice(2, "Look around the cabin", nodes[6]);

        nodes[2]->addChoice(1, "Fight the beast", nodes[4]);
        nodes[2]->addChoice(2, "Run away", nodes[9]);

        nodes[3]->addChoice(1, "Follow the stream to the waterfall", nodes[7]);
        nodes[3]->addChoice(2, "Keep walking until you find a village", nodes[8]);

        // Set starting node
        currentNode = nodes[0];
    }

    // Clean up nodes when the story ends
    ~Story() {
        for (auto node : nodes) {
            delete node;
        }
    }


    // Function to play the game from the start node
    void playGame() {

        DecisionNode* currentNode = nodes[0]; // Starting node
        while (currentNode) {
            currentNode->displayNode();

            // Add the current node to the history stack
            history.push(currentNode);

            // Display the "Go Back" option only if we're not at the start node
            if (currentNode != nodes[0]) {
                std::cout << "0. Go back" << std::endl;
            }

            std::cout << "Enter your choice (number): ";
            int choice;
            std::cin >> choice;

            // If the player wants to go back and it's not the starting node
            if (choice == 0 && !history.empty() && currentNode != nodes[0]) {
                if (history.size() > 1) {
                    history.pop();  // Remove current node
                    currentNode = history.top();  // Get previous node
                    std::cout << "You go back to the previous choice.\n";
                }
                else {
                    std::cout << "You can't go back any further.\n";
                }
                continue;  // Skip the normal choice logic if going back
            }

            // Proceed with the regular choice flow
            DecisionNode* nextNode = currentNode->getNextNode(choice);
            if (nextNode) {
                currentNode = nextNode;
            }
            else {
                std::cout << "Invalid choice, please try again.\n";
            }
        }
    }
};

//-------------------------------------------------------------------------------STORY ENDINGS

//enum class EndingType { BAD, GOOD, NEUTRAL };
//
//class Story {
//    EndingType ending;
//public:
//    void setEnding(EndingType e) {
//        ending = e;
//    }
//
//    void showEnding() {
//        switch (ending) {
//        case EndingType::BAD:
//            std::cout << "You have failed. The story ends in disaster." << std::endl;
//            break;
//        case EndingType::GOOD:
//            std::cout << "You have succeeded! Congratulations on completing the quest!" << std::endl;
//            break;
//        case EndingType::NEUTRAL:
//            std::cout << "The story ends with no real resolution, leaving you wondering what might have been." << std::endl;
//            break;
//        }
//    }
//};


//-------------------------------------------------------------------------------TIMED DECISIONS

//#include <chrono>
//
//bool promptWithTimeout(const std::string& prompt, int timeoutSeconds = 10) {
//    std::cout << prompt << std::endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    int choice;
//    while (true) {
//        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() > timeoutSeconds) {
//            std::cout << "Time's up! You failed to make a decision in time." << std::endl;
//            return false;
//        }
//
//        std::cout << "Your choice: ";
//        std::cin >> choice;
//
//        // If input is valid, return true.
//        if (choice > 0) {
//            return true;
//        }
//    }
//}


//-------------------------------------------------------------------------------PLAYER HEALTH (OPTIONAL)

//class Player {
//public:
//    int health;
//    int stamina;
//    std::vector<std::string> inventory;
//
//    Player() : health(100), stamina(100) {}
//
//    void addItem(const std::string& item) {
//        inventory.push_back(item);
//    }
//
//    bool useItem(const std::string& item) {
//        auto it = std::find(inventory.begin(), inventory.end(), item);
//        if (it != inventory.end()) {
//            inventory.erase(it);
//            return true;
//        }
//        return false;
//    }
//};
//


int main()
{
    Story game;
    game.initNodes();
    game.playGame();

    return 0;
}