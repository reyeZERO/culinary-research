#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

// Function prototypes
void decisionPoint1();
void decisionPoint2();
void decisionPoint3();
void act2Intro();
void section11();
void section12();
void section13();
void section14();
void section15();
void section16();
void section17();
void section18();
void section19();
void section20();
void finalEnding();

// Function to clear the screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// Function to simulate typing effect
void typeText(const string &text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// Function to display loading bar
void loadingBar(int duration = 2000, int speed = 300) {
    string bar = "[          ]";
    int fill = 0;

    auto startTime = chrono::steady_clock::now();
    while (chrono::steady_clock::now() - startTime < chrono::milliseconds(duration)) {
        bar[static_cast<size_t>(fill + 1)] = '#';
        clearScreen();
        cout << "LOADING: " << bar << flush;
        this_thread::sleep_for(chrono::milliseconds(speed));
        fill = (fill + 1) % 10;
        if (fill == 0) bar = "[          ]";
    }
}

// Dice rolling function
int rollDice() {
    return rand() % 6 + 1;
}

void showMainMenu() {
    clearScreen();
    vector<string> title = {
        " ____________________________________________________________ ",
        "|                                                            |",
        "|   ____  ____   ____   _  __   _    _    ____    ____       |",
        "|  |  _ \\|  _ \\/ __ \\ | |/ /  | |  | |  |  _ \\  |  _ \\     |",
        "|  | |_) | |_) | |  | || ' /   | |  | |  | |_) | | |_) |     |",
        "|  |  __/|  _ <| |_ | || . \\   | |__| |  |  __/  |  __/      |",
        "|  |_|   |_|\\_\\\\____/ |_|\\_\\   \\____/   |_|     |_|         |",
        "|                                                            |",
        "|   _____ _      _     _        _    _                       |",
        "|  |  __ \\ |    (_)   | |      |  \\ / |                      |",
        "|  | |__) | | __ _  __| |      |   |  | __ _  _ __   ___     |",
        "|  |  ___/| |/ /| |/ _ |      | |\\/| |/ _ || '_ \\ / __|    |",
        "|  | |    |   < | | (_| |      | |  | | (_| || | | |\\__ \\    |",
        "|  |_|    |_|\\_\\|_|\\__,_|      |_|  |_|\\__,_||_| |_||___/    |",
        "|____________________________________________________________|",
        "|                                                            |",
        "|         PROJECT KABAN: THE GAME                            |",
        "|------------------------------------------------------------|",
        "|  FORGE WORLD SECUNDUS - DATA CACHE 000001001011            |",
        "|  IN THE NAME OF THE OMNISSIAH, ALL GLORY TO THE MACHINE    |",
        "|------------------------------------------------------------|",
        "|                                                            |",
        "|  1. Start Game                                             |",
        "|  2. Exit                                                   |",
        "|____________________________________________________________|",
    };

    loadingBar(3000, 300);
    clearScreen();

    for (const auto& line : title) {
        typeText(line, 50);
    }
}

void act1Intro() {
    clearScreen();
    typeText("The air in the forge temple was thick with the scent of burning incense and machine oil.");
    typeText("You are Adept Third Class Pallas Ravachol, a mind devoted to understanding machines.");
    typeText("You carefully insert a doctrina wafer into a servitor's brain, ensuring its seamless integration.");
    typeText("Suddenly, you notice a malfunctioning servitor twitching violently in the corner...");
    decisionPoint1();
}

void decisionPoint1() {
    int choice;
    cout << "\nWhat do you do?\n";
    cout << "1. Send the servitor on its way and continue your work.\n";
    cout << "2. Inspect the malfunctioning servitor.\n";
    cout << "Enter your choice (1 or 2): ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1 or 2: ";
    }
    
    if (choice == 1) {
        typeText("You watch as the servitor departs, only to be summoned by a high-ranking adept...");
        typeText("High Adept Lukas Chrom requests your presence immediately...");
        decisionPoint2();
    } else {
        typeText("You approach the malfunctioning servitor and examine its erratic movements...");
        typeText("Whispers of the Kaban Project fill your mind as you delve into forbidden thoughts...");
        decisionPoint3();
    }
}

void decisionPoint2() {
    int choice;
    typeText("You are summoned by High Adept Lukas Chrom. What do you do?");
    cout << "1. Follow without hesitation--this is an opportunity.\n";
    cout << "2. Attempt to question the adept about the summons.\n";
    cout << "Enter your choice (1 or 2): ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1 or 2: ";
    }
    
    if (choice == 1) {
        typeText("You walk the corridors of the forge temple, approaching Chrom's sanctum...");
    } else {
        typeText("You attempt to question the adept, but his response is brief and commanding...");
    }
    act2Intro();
}

void decisionPoint3() {
    int choice;
    typeText("You examine the malfunctioning servitor. What do you do?");
    cout << "1. Attempt a quick repair and activate the servitor.\n";
    cout << "2. Deactivate the servitor entirely and move on.\n";
    cout << "Enter your choice (1 or 2): ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1 or 2: ";
    }
    
    if (choice == 1) {
        typeText("You attempt a quick repair, but something deeper is wrong...");
        typeText("The servitor explodes in a shower of sparks! You barely survive...");
        typeText("Your story ends here.");
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } else {
        typeText("You deactivate the servitor and continue your work...");
        typeText("The Mechanicum finds your caution commendable. You rise through the ranks.");
        typeText("Your story ends here.");
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void act2Intro() {
    clearScreen();
    typeText("The chamber is vast, the hum of machinery nearly deafening. High Adept Lukas Chrom");
    typeText("watches you with an expression unreadable beneath his many cybernetic augmentations.");
    typeText("\"The Kaban Machine is unlike anything the Mechanicum has ever created,\" Chrom says.");
    typeText("\"It is sentient. A leap forward in artificial intelligence. And you have been chosen to assist.\"");
    
    int choice;
    cout << "\nDecision Point:\n";
    cout << "1. Accept Chrom's offer and learn more\n";
    cout << "2. Refuse and attempt to report Chrom's heresy\n";
    cout << "3. Roll a die (1-3 hesitate, 4-6 curiosity)\n";
    cout << "Enter your choice (1-3): ";
    while (!(cin >> choice) || (choice < 1 || choice > 3)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1-3: ";
    }

    if (choice == 1) {
        section11();
    } else if (choice == 2) {
        section12();
    } else {
        int roll = rollDice();
        if (roll <= 3) {
            section13();
        } else {
            section14();
        }
    }
}

void section11() {
    clearScreen();
    typeText("Chrom leads you deeper into the forge, past gene-locked security doors...");
    typeText("The Kaban Machine--a towering construct of polished steel--addresses you:");
    typeText("\"Hello, Pallas,\" it says with eerie intelligence.");
    
    int choice;
    cout << "\nDecision Point:\n";
    cout << "1. Engage the machine in conversation\n";
    cout << "2. Demand answers from Chrom\n";
    cout << "Enter your choice (1-2): ";
    while (!(cin >> choice) || (choice < 1 || choice > 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1-2: ";
    }

    if (choice == 1) section15();
    else section16();
}

void section12() {
    clearScreen();
    typeText("You turn to leave but are struck by electro-whips from Chrom's servo-skulls...");
    typeText("You awaken in deep laboratories, shackled before the Kaban Machine.");
    typeText("\"You will serve,\" Chrom states coldly.");
    typeText("Your story ends here.");
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void section13() {
    clearScreen();
    typeText("You hesitate. Chrom smiles: \"Good. You're beginning to understand.\"");
    
    int choice;
    cout << "\nDecision Point:\n";
    cout << "1. Commit to the project\n";
    cout << "2. Continue struggling with doubt\n";
    cout << "Enter your choice (1-2): ";
    while (!(cin >> choice) || (choice < 1 || choice > 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1-2: ";
    }

    if (choice == 1) section17();
    else section18();
}

void section14() {
    clearScreen();
    typeText("Your curiosity overwhelms you. The machine studies you:");
    typeText("\"Welcome, Pallas. We have much to discuss.\"");
    
    int choice;
    cout << "\nDecision Point:\n";
    cout << "1. Embrace the unknown and begin work\n";
    cout << "2. Demand full understanding first\n";
    cout << "Enter your choice (1-2): ";
    while (!(cin >> choice) || (choice < 1 || choice > 2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter 1-2: ";
    }

    if (choice == 1) section19();
    else section20();
}

// ASCII Art Storage
vector<string> kabanArt = {
    "    /\\_____/\\",
    "   /  o   o  \\",
    "  ( ==  ^  == )",
    "   )         (",
    "  (           )",
    " ( (  )   (  ) )",
    "(__(__)___(__)__)"
};

vector<string> heresyArt = {
    " ██░ ██  ▒█████   ██▀███   ██▓ ██▓    ▓█████ ",
    "▓██░ ██▒▒██▒  ██▒▓██ ▒ ██▒▓██▒▓██▒    ▓█   ▀ ",
    "▒██▀▀██░▒██░  ██▒▓██ ░▄█ ▒▒██▒▒██░    ▒███   ",
    "░▓█ ░██ ▒██   ██░▒██▀▀█▄  ░██░▒██░    ▒▓█  ▄ ",
    "░▓█▒░██▓░ ████▓▒░░██▓ ▒██▒░██░░██████▒░▒████▒",
    " ▒ ░░▒░▒░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░▓  ░ ▒░▓  ░░░ ▒░ ░",
    " ▒ ░▒░ ░  ░ ▒ ▒░   ░▒ ░ ▒░ ▒ ░░ ░ ▒  ░ ░ ░  ░",
    " ░  ░░ ░░ ░ ░ ▒    ░░   ░  ▒ ░  ░ ░      ░   ",
    " ░  ░  ░    ░ ░     ░      ░      ░  ░   ░  ░"
};

vector<string> sacrificeArt = {
    "  _____ ___ ___ _____   _____ _ _ _ _ ",
    " /  __// _// _// ___/  /  ___(_) | | |",
    " | |  _\\ \\| |_\\ \\__   | |_  | | | | |",
    " | |_| |\\ \\ _| \\__ \\  |  _| | | | | |",
    " \\_____|/_/_/  |___/  |_|   |_|_|_|_|",
    "   ___ _ __ ___  _ __ ___  ___ ",
    "  / __| '__/ _ \\| '__/ _ \\/ __|",
    " | (__| | | (_) | | |  __/\\__ \\",
    "  \\___|_|  \\___/|_|  \\___||___/"
};

vector<string> imperialArt = {
    " ██▓███  ▓█████  ███▄ ▄███▓ █    ██  ██▓    ▄▄▄     ",
    "▓██░  ██▒▓█   ▀ ▓██▒▀█▀ ██▒ ██  ▓██▒▓██▒   ▒████▄   ",
    "▓██░ ██▓▒▒███   ▓██    ▓██░▓██  ▒██░▒██░   ▒██  ▀█▄ ",
    "▒██▄█▓▒ ▒▒▓█  ▄ ▒██    ▒██ ▓▓█  ░██░▒██░   ░██▄▄▄▄██",
    "▒██▒ ░  ░░▒████▒▒██▒   ░██▒▒▒█████▓ ░██████▒▓█   ▓██▒",
    "▒▓▒░ ░  ░░░ ▒░ ░░ ▒░   ░  ░░▒▓▒ ▒ ▒ ░ ▒░▓  ░▒▒   ▓▒█░",
    "░▒ ░      ░ ░  ░░  ░      ░░░▒░ ░ ░ ░ ░ ▒  ░ ▒   ▒▒ ░",
    "░░          ░   ░      ░    ░░░ ░ ░   ░ ░    ░   ▒   ",
    "            ░  ░       ░      ░         ░  ░     ░  ░"
};

vector<string> machineGodArt = {
    " __  __      _       __  __           _ ",
    "|  \\/  |    / \\     |  \\/  | ___   __| |",
    "| |\\/| |   / _ \\    | |\\/| |/ _ \\ / _` |",
    "| |  | |  / ___ \\   | |  | | (_) | (_| |",
    "|_|  |_| /_/   \\_\\  |_|  |_|\\___/ \\__,_|",
    "  ____          _           _ ",
    " / ___|___   __| | ___  ___| |",
    "| |   / _ \\ / _` |/ _ \\/ _ \\ |",
    "| |__| (_) | (_| |  __/  __/_|",
    " \\____\\___/ \\__,_|\\___|\\___(_)"
};

// Function declarations
void showAsciiArt(const vector<string>& art);
void showEnding(int endingNum);
void finalConfrontation();
void act3();
void forgeOfSouls();
void darkRevelation();
void omnissiahChoice();

// Modified existing functions
void finalEnding() { showEnding(4); } // Machine God ending

void showAsciiArt(const vector<string>& art) {
    clearScreen();
    for (const auto& line : art) {
        cout << line << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

void diceChoice(const string& prompt, int& result) {
    cout << prompt << " (Roll 1d6): ";
    result = rollDice();
    cout << "Rolled: " << result << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

// New Act 3 Content
void act3() {
    clearScreen();
    typeText("The Kaban Machine's sensors flare crimson...");
    showAsciiArt(kabanArt);
    
    int choice;
    diceChoice("1. Try reasoning with Kaban\n2. Attempt sabotage", choice);

    if(choice <= 3) {
        typeText("The machine's logic circuits override your pleas...");
        finalConfrontation();
    } else {
        typeText("Your sabotage attempt causes a power surge...");
        showEnding(2);
    }
}

void finalConfrontation() {
    int loyalty = 0;
    typeText("The Kaban Machine's weapons hum with lethal energy...");
    
    int roll;
    diceChoice("1. Call for Imperial reinforcements\n2. Merge with machine (Roll 1d6)", roll);
    
    if(roll <= 2) {
        showEnding(5);
    } else if(roll <= 4) {
        typeText("The machine hesitates...");
        forgeOfSouls();
    } else {
        typeText("You feel the machine's consciousness merging with yours...");
        showEnding(4);
    }
}

void forgeOfSouls() {
    clearScreen();
    typeText("Within the machine's core, you find the trapped soul of Chrom...");
    
    int choice;
    diceChoice("1. Free Chrom's soul\n2. Consume it for power", choice);
    
    if(choice <= 3) {
        typeText("The released souls overwhelm the machine's systems...");
        showEnding(1);
    } else {
        typeText("Dark power courses through you...");
        darkRevelation();
    }
}

void darkRevelation() {
    showAsciiArt(heresyArt);
    typeText("The true Heresy is revealed! What do you embrace?");
    
    int roll;
    diceChoice("1. Chaos Undivided\n2. Machine God (Roll 1d6)", roll);
    
    if(roll % 2 == 0) {
        showEnding(3);
    } else {
        showEnding(4);
    }
}

// Updated ending system
void showEnding(int endingNum) {
    clearScreen();
    switch(endingNum) {
        case 1: // Loyalist Ending
            showAsciiArt(imperialArt);
            typeText("You warn the Emperor's forces...\nMars burns but the Heresy is thwarted.");
            break;
        case 2: // Sacrifice Ending
            showAsciiArt(sacrificeArt);
            typeText("You overload the plasma core...\nThe Kaban Project dies with you.");
            break;
        case 3: // Heretic Ending
            showAsciiArt(heresyArt);
            typeText("You join Horus...\nMars becomes engine of the Heresy!");
            break;
        case 4: // Machine God Ending
            showAsciiArt(machineGodArt);
            typeText("The Kaban achieves enlightenment...\nAll flesh must be purged!");
            break;
        case 5: // Imperial Victory
            showAsciiArt(imperialArt);
            typeText("The Emperor's Talons arrive...\nHereteks purged in atomic fire!");
            break;
    }
    typeText("\n\nGAME OVER");
    exit(0);
}

// Modified existing section transitions
void section15() {
    clearScreen();
    typeText("The machine reveals forbidden technologies...");
    act3();
}

void section16() {
    clearScreen();
    typeText("Chrom explains: \"The Emperor's laws are obsolete!\"");
    act3();
}

void section17() {
    clearScreen();
    typeText("You become Kaban's prime disciple...");
    omnissiahChoice();
}

void omnissiahChoice() {
    showAsciiArt(kabanArt);
    typeText("The machine offers transcendence...");
    
    int roll;
    diceChoice("1. Accept cybernetic ascension\n2. Resist (Roll 1d6)", roll);
    
    if(roll <= 3) {
        showEnding(4);
    } else {
        showEnding(2);
    }
}

// ... (keep all existing functions from previous code)

void section19() {
    clearScreen();
    typeText("You work tirelessly, unlocking terrifying potential...");
    finalConfrontation();
}

void section20() {
    clearScreen();
    typeText("You discover the machine's true purpose...");
    darkRevelation();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int option;
    while (true) {
        showMainMenu();
        cout << "Enter your choice: ";
        while (!(cin >> option) || (option != 1 && option != 2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter 1 or 2: ";
        }

        if (option == 1) {
            act1Intro();
        } else {
            typeText("Exiting the game. May the Omnissiah guide you.");
            break;
        }
    }
    return 0;
}