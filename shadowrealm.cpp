#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Simple game structures
struct Player {
    string name;
    int health;
    int maxHealth;
    int attack;
    int gold;
    int potions;
    int level;
    int exp;
};

struct Monster {
    string name;
    int health;
    int attack;
    int goldDrop;
    int expDrop;
};

// Function prototypes
void showIntro();
void showStats(Player p);
Monster createMonster(int level);
void combat(Player& p, Monster m);
void heal(Player& p);
void levelUp(Player& p);
void village(Player& p);
void forest(Player& p);
void cave(Player& p);
void boss(Player& p);

// Main function
int main() {
    srand(time(0));
    
    showIntro();
    
    Player hero;
    cout << "Enter your hero's name: ";
    getline(cin, hero.name);
    
    hero.health = 100;
    hero.maxHealth = 100;
    hero.attack = 15;
    hero.gold = 50;
    hero.potions = 3;
    hero.level = 1;
    hero.exp = 0;
    
    cout << "\nWelcome, " << hero.name << "! Your adventure begins!\n";
    
    bool playing = true;
    
    while (playing && hero.health > 0) {
        cout << "\n========================================\n";
        cout << "Where do you want to go?\n";
        cout << "1. Village (safe)\n";
        cout << "2. Dark Forest (monsters)\n";
        cout << "3. Ancient Cave (tough monsters)\n";
        cout << "4. Dragon's Lair (boss fight)\n";
        cout << "5. View Stats\n";
        cout << "6. Quit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1:
                village(hero);
                break;
            case 2:
                forest(hero);
                break;
            case 3:
                cave(hero);
                break;
            case 4:
                boss(hero);
                if (hero.health > 0) {
                    cout << "\n*** YOU WIN! ***\n";
                    cout << "You saved the kingdom!\n";
                    playing = false;
                }
                break;
            case 5:
                showStats(hero);
                break;
            case 6:
                cout << "Thanks for playing!\n";
                playing = false;
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
    
    if (hero.health <= 0) {
        cout << "\n*** GAME OVER ***\n";
        cout << "You were defeated...\n";
    }
    
    return 0;
}

void showIntro() {
    cout << "========================================\n";
    cout << "     QUEST OF THE BRAVE\n";
    cout << "========================================\n";
    cout << "\nA dragon terrorizes the kingdom!\n";
    cout << "You must train and defeat it!\n\n";
}

void showStats(Player p) {
    cout << "\n=== " << p.name << " ===\n";
    cout << "Level: " << p.level << "\n";
    cout << "HP: " << p.health << "/" << p.maxHealth << "\n";
    cout << "Attack: " << p.attack << "\n";
    cout << "Gold: " << p.gold << "\n";
    cout << "Potions: " << p.potions << "\n";
    cout << "EXP: " << p.exp << "/" << (p.level * 50) << "\n";
}

Monster createMonster(int level) {
    Monster m;
    int type = rand() % 4;
    
    if (type == 0) {
        m.name = "Goblin";
        m.health = 30 + (level * 5);
        m.attack = 8 + level;
        m.goldDrop = 20;
        m.expDrop = 25;
    } else if (type == 1) {
        m.name = "Wolf";
        m.health = 25 + (level * 5);
        m.attack = 10 + level;
        m.goldDrop = 15;
        m.expDrop = 20;
    } else if (type == 2) {
        m.name = "Skeleton";
        m.health = 35 + (level * 5);
        m.attack = 7 + level;
        m.goldDrop = 25;
        m.expDrop = 30;
    } else {
        m.name = "Orc";
        m.health = 40 + (level * 5);
        m.attack = 12 + level;
        m.goldDrop = 30;
        m.expDrop = 35;
    }
    
    return m;
}

void combat(Player& p, Monster m) {
    cout << "\n*** " << m.name << " appears! ***\n";
    cout << m.name << " HP: " << m.health << "\n";
    
    while (p.health > 0 && m.health > 0) {
        cout << "\n1. Attack\n";
        cout << "2. Use Potion (heal 50 HP)\n";
        cout << "3. Run\n";
        cout << "Choice: ";
        
        int action;
        cin >> action;
        
        if (action == 1) {
            int damage = p.attack + (rand() % 5);
            m.health -= damage;
            cout << "You hit for " << damage << " damage!\n";
            
            if (m.health > 0) {
                cout << m.name << " HP: " << m.health << "\n";
            }
        } else if (action == 2) {
            if (p.potions > 0) {
                heal(p);
            } else {
                cout << "No potions left!\n";
                continue;
            }
        } else if (action == 3) {
            if (rand() % 2 == 0) {
                cout << "You escaped!\n";
                return;
            } else {
                cout << "Can't escape!\n";
            }
        }
        
        if (m.health > 0) {
            int damage = m.attack + (rand() % 3);
            p.health -= damage;
            cout << m.name << " hits you for " << damage << " damage!\n";
            cout << "Your HP: " << p.health << "/" << p.maxHealth << "\n";
        }
    }
    
    if (p.health > 0) {
        cout << "\n*** VICTORY! ***\n";
        p.gold += m.goldDrop;
        p.exp += m.expDrop;
        cout << "Got " << m.goldDrop << " gold!\n";
        cout << "Got " << m.expDrop << " EXP!\n";
        levelUp(p);
    }
}

void heal(Player& p) {
    p.potions--;
    p.health += 50;
    if (p.health > p.maxHealth) {
        p.health = p.maxHealth;
    }
    cout << "Healed! HP: " << p.health << "/" << p.maxHealth << "\n";
    cout << "Potions left: " << p.potions << "\n";
}

void levelUp(Player& p) {
    int expNeeded = p.level * 50;
    if (p.exp >= expNeeded) {
        p.level++;
        p.exp -= expNeeded;
        p.maxHealth += 20;
        p.health = p.maxHealth;
        p.attack += 3;
        cout << "\n*** LEVEL UP! ***\n";
        cout << "Now level " << p.level << "!\n";
        cout << "Max HP increased!\n";
        cout << "Attack increased!\n";
    }
}

void village(Player& p) {
    cout << "\n=== VILLAGE ===\n";
    cout << "A peaceful village with friendly people.\n";
    cout << "\n1. Rest (heal to full)\n";
    cout << "2. Shop\n";
    cout << "3. Leave\n";
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        p.health = p.maxHealth;
        cout << "You rest and recover. HP: " << p.health << "\n";
    } else if (choice == 2) {
        cout << "\n=== SHOP ===\n";
        cout << "1. Potion (30 gold) - heals 50 HP\n";
        cout << "2. Sword Upgrade (100 gold) - +5 attack\n";
        cout << "3. Leave\n";
        cout << "Your gold: " << p.gold << "\n";
        cout << "Choice: ";
        
        int shopChoice;
        cin >> shopChoice;
        
        if (shopChoice == 1 && p.gold >= 30) {
            p.gold -= 30;
            p.potions++;
            cout << "Bought potion!\n";
        } else if (shopChoice == 2 && p.gold >= 100) {
            p.gold -= 100;
            p.attack += 5;
            cout << "Bought sword! Attack increased!\n";
        } else if (shopChoice != 3) {
            cout << "Not enough gold!\n";
        }
    }
}

void forest(Player& p) {
    cout << "\n=== DARK FOREST ===\n";
    cout << "A spooky forest filled with monsters.\n";
    
    Monster m = createMonster(p.level);
    combat(p, m);
}

void cave(Player& p) {
    cout << "\n=== ANCIENT CAVE ===\n";
    cout << "A dangerous cave with powerful creatures.\n";
    
    Monster m = createMonster(p.level + 2);
    combat(p, m);
}

void boss(Player& p) {
    cout << "\n=== DRAGON'S LAIR ===\n";
    cout << "The massive dragon awaits you!\n";
    
    if (p.level < 3) {
        cout << "You feel too weak to fight the dragon.\n";
        cout << "Come back when you're stronger! (level 3+)\n";
        return;
    }
    
    Monster dragon;
    dragon.name = "ANCIENT DRAGON";
    dragon.health = 150;
    dragon.attack = 25;
    dragon.goldDrop = 1000;
    dragon.expDrop = 500;
    
    cout << "The dragon roars at you!\n";
    combat(p, dragon);
}